#pragma once

#include "action.hpp"

#include <raceman.h>

#include <cstdint>


namespace torcs {
namespace brabham {

// forward declarations
struct race_context;

class driver
{
public:
    driver(const race_context& context);
    action drive(const tCarElt& car, const tSituation& situation) const;
private:
    static constexpr float SPEED_MARGIN_FOR_FULL_ACCELERATION = 1.0;  // 1 m/s
    static constexpr float SHIFT_AT_PERCENTAGE_OF_REDLINE = 0.95;  // 95% of redline
    static constexpr float SHIFT_DOWN_MARGIN = 4.0;  // 4 m/s

    float calc_steering(const tCarElt& car, const tSituation& situation) const;
    float calc_braking(const tCarElt& car, const tSituation& situation) const;
    float calc_acceleration(const tCarElt& car, const tSituation& situation) const;
    std::int8_t select_gear(const tCarElt& car, const tSituation& situation) const;

    const race_context& context_;
};

} // namespace brabham
} // namespace torcs
