#pragma once

namespace torcs {
namespace brabham {

// forward declarations
struct race_context;
class driver;

race_context& current_race();
driver& current_driver();

} // namespace brabham
} // namespace torcs
