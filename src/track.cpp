#include "track.hpp"
#include "physics.hpp"

#include <cmath>
#include <limits>


namespace torcs {
namespace brabham {

float suggested_speed(const tTrackSeg& segment)
{
    float speed = 0.0;
    if (segment.type == segment_geometry::STRAIGHT)
    {
        speed = std::numeric_limits<float>::max();
    }
    else
    {
        const float friction = segment.surface->kFriction;
        speed = sqrt(friction * GRAVITY * segment.radius);
    }
    return speed;
}

float distance_to_segment_end(const tCarElt& car)
{
    float distance = 0.0;
    if (car.pub.trkPos.seg->type == segment_geometry::STRAIGHT)
    {
        distance = car.pub.trkPos.seg->length - car.pub.trkPos.toStart;
    }
    else
    {
        const float arc = car.pub.trkPos.seg->arc - car.pub.trkPos.toStart;
        distance = arc * car.pub.trkPos.seg->radius;
    }
    return distance;
}

}  // namespace brabham
}  // namespace torcs
