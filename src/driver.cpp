#include "driver.hpp"
#include "physics.hpp"
#include "race_context.hpp"
#include "track.hpp"

#include <car.h>
#include <robottools/robottools.h>
#include <tgf/tgf.h>
#include <track.h>

#include <cassert>
#include <cmath>


namespace torcs {
namespace brabham {

driver::driver(const race_context& context):
    context_(context)
{}

action driver::drive(const tCarElt& car, const tSituation& situation) const
{
    action result;
    result.steering = this->calc_steering(car, situation);
    result.braking = this->calc_braking(car, situation);
    if (result.braking == 0.0)
    {
        result.acceleration = this->calc_acceleration(car, situation);
    }
    else
    {
        result.acceleration = 0.0;
    }
    result.gear_selection = this->select_gear(car, situation);
    result.clutch = 0.0;  // clutch pedal disengaged
    result.race_command = race_command::NONE;

    return result;
}

/**
 * Steers along the middle of the road
**/
float driver::calc_steering(const tCarElt& car, const tSituation& situation) const
{
    // robottools is not const correct
    tTrkLocPos* track_pos = const_cast<tTrkLocPos*>(&(car.pub.trkPos));

    // relative angle of current track segment tangent to the middle line of starting segment
    const float track_seg_relative_angle = RtTrackSideTgAngleL(track_pos);

    // relative angle of car yaw to the the middle line of starting segment
    const float car_yaw_relative_angle = track_seg_relative_angle - car.pub.DynGC.pos.az;

    // adjust the relative car yaw to middle line to ensure it is within 2 PI
    const float adjusted_yaw_relative_angle = remainder(car_yaw_relative_angle, 2 * PI);

    // ratio of distance from car to middle relative to the segment width
    const float middle_offset_to_width_ratio = car.pub.trkPos.toMiddle / car.pub.trkPos.seg->width;

    const float steering_adjustment = (adjusted_yaw_relative_angle - middle_offset_to_width_ratio) / car.info.steerLock;

    return steering_adjustment;
}

float driver::calc_braking(const tCarElt& car, const tSituation& situation) const
{
    assert(car.pub.trkPos.seg != nullptr);
    const float current_speed = car.pub.DynGC.vel.x;
    const float desired_speed = suggested_speed(*car.pub.trkPos.seg);

    if (desired_speed < current_speed)
    {
        return 1.0;
    }

    const float friction = car.pub.trkPos.seg->surface->kFriction;
    const float energy_burn_rate = 2.0 * GRAVITY * friction;
    const float max_distance = (current_speed * current_speed) / energy_burn_rate;
    float look_ahead_distance = distance_to_segment_end(car);
    tTrackSeg* segment = car.pub.trkPos.seg->next;
    float brake_pedal = 0.0;
    while (look_ahead_distance < max_distance && segment != nullptr)
    {
        const float segment_speed = suggested_speed(*segment);
        if (segment_speed < current_speed)
        {
            const float speed_diff_squared = (current_speed * current_speed) - (segment_speed * segment_speed);
            const float braking_distance = speed_diff_squared / energy_burn_rate;
            if (look_ahead_distance < braking_distance)
            {
                brake_pedal = 1.0;
                break;
            }
        }
        look_ahead_distance += segment->length;
        segment = segment->next;
    }
    return brake_pedal;
}

float driver::calc_acceleration(const tCarElt& car, const tSituation& situation) const
{
    assert(car.pub.trkPos.seg != nullptr);
    const float desired_speed = suggested_speed(*car.pub.trkPos.seg);
    const float gear_ratio = car.priv.gearRatio[car.priv.gear + car.priv.gearOffset];
    const float current_speed = car.pub.DynGC.vel.x + SPEED_MARGIN_FOR_FULL_ACCELERATION;
    float accelerator_pedal = 0.0;
    if (desired_speed > current_speed)
    {
        accelerator_pedal = 1.0;
    }
    else
    {
        const float wheel_radius = car.info.wheel[REAR_RGT].wheelRadius;
        const float angular_speed = desired_speed * wheel_radius;
        const float desired_rpm = angular_speed * gear_ratio;
        accelerator_pedal = desired_rpm / car.priv.enginerpmRedLine;
    }
    return accelerator_pedal;
}

std::int8_t driver::select_gear(const tCarElt& car, const tSituation& situation) const
{
    const std::int8_t current_gear = car.priv.gear;
    const float wheel_radius = car.info.wheel[REAR_RGT].wheelRadius;
    const float current_gear_ratio = car.priv.gearRatio[car.priv.gear + car.priv.gearOffset];
    const float current_engine_speed = car.priv.enginerpmRedLine / current_gear_ratio;
    const float current_max_speed = current_engine_speed * wheel_radius * SHIFT_AT_PERCENTAGE_OF_REDLINE;
    std::int8_t selected_gear = current_gear;
    if (current_gear <= 0)
    {
        selected_gear = 1;
    }
    else if (current_max_speed < car.pub.DynGC.vel.x)
    {
        selected_gear = current_gear + 1;
    }
    else if (current_gear > 1)
    {
        const float lower_gear_ratio = car.priv.gearRatio[car.priv.gear + car.priv.gearOffset - 1];
        const float lower_engine_speed = car.priv.enginerpmRedLine / lower_gear_ratio;
        const float lower_max_speed = lower_engine_speed * wheel_radius * SHIFT_AT_PERCENTAGE_OF_REDLINE;
        const float car_speed = car.pub.DynGC.vel.x + SHIFT_DOWN_MARGIN;
        if (car_speed < lower_max_speed)
        {
            selected_gear = current_gear - 1;
        }
    }
    return selected_gear;
}

} // namespace brabham
} // namespace torcs
