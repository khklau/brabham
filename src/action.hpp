#pragma once

#include <car.h>

#include <cstdint>


namespace torcs {
namespace brabham {

enum race_command
{
    NONE = RM_CMD_NONE,
    PIT = RM_CMD_PIT_ASKED,
};


struct action
{
    float steering;  // [-1.0, 1.0]
    float acceleration; // [0.0, 1.0]
    float braking;  // [0.0, 1.0]
    float clutch;  // [0.0, 1.0]
    std::int32_t gear_selection; // [-1, 6]
    std::int32_t race_command;

    action();
};

} // namespace brabham
} // namespace torcs
