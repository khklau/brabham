#include "state.hpp"

#include "driver.hpp"
#include "race_context.hpp"


namespace torcs {
namespace brabham {

race_context& current_race()
{
    static race_context current;
    return current;
}

driver& current_driver()
{
    const race_context& context = current_race();
    static driver current(context);
    return current;
}

} // namespace brabham
} // namespace torcs
