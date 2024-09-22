#include "driver.hpp"
#include "race_context.hpp"

#include <car.h>
#include <robottools/robottools.h>
#include <tgf/tgf.h>
#include <track.h>

#include <cmath>


namespace torcs {
namespace brabham {

driver::driver(const race_context& context):
    context_(context)
{}

action driver::drive(const tCarElt& car, const tSituation& situation) const
{
    // robottools is not const correct
    tTrkLocPos* track_pos = const_cast<tTrkLocPos*>(&(car.pub.trkPos));

    // relative angle of current track segment tangent to the middle line of starting segment
    float track_seg_relative_angle = RtTrackSideTgAngleL(track_pos);

    // relative angle of car yaw to the the middle line of starting segment
    float car_yaw_relative_angle = track_seg_relative_angle - car.pub.DynGC.pos.az;

    // adjust the relative car yaw to middle line to ensure it is within 2 PI
    car_yaw_relative_angle = remainder(car_yaw_relative_angle, 2 * PI);

    // ratio of distance from car to middle relative to the segment width
    float middle_offset_to_width_ratio = car.pub.trkPos.toMiddle / car.pub.trkPos.seg->width;

    float steering_adjustment = (car_yaw_relative_angle - middle_offset_to_width_ratio) / car.info.steerLock;

    // acceleration should be inversely proportional to the steering adjustment allowing between 30 to 35%
    float acceleration = 0.35 - (0.05 * fabs(steering_adjustment));

    // braking should be proportional to the steering adjustment allowing between 0 to 10%
    // when the steering adjustment needed is more than 10% of full steering lock
    float braking = 0.0;
    if (fabs(steering_adjustment) > 0.1)
    {
        braking = 0.15 - (0.15 * fabs(steering_adjustment));
    }

    action result;
    result.steering = steering_adjustment;
    result.acceleration = acceleration;
    result.braking = braking;
    result.gear_selection = 1;         // drive in 1st gear
    result.clutch = 0.0;  // clutch pedal disengaged
    result.race_command = race_command::NONE;

    return result;
}

} // namespace brabham
} // namespace torcs
