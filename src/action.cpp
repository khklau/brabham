#include "action.hpp"

namespace torcs {
namespace brabham {

action::action():
    steering(0.0),
    acceleration(0.0),
    braking(0.0),
    clutch(0.0),
    gear_selection(0),
    race_command(race_command::NONE)
{}

} // namespace brabham
} // namespace torcs
