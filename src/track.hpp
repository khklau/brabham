#pragma once

#include <car.h>
#include <track.h>


namespace torcs {
namespace brabham {

enum segment_geometry
{
    RIGHT_TURN = TR_RGT,
    LEFT_TURN = TR_LFT,
    STRAIGHT = TR_STR,
};

float suggested_speed(const tTrackSeg& segment);

float distance_to_segment_end(const tCarElt& car);

}  // namespace brabham
}  // namespace torcs
