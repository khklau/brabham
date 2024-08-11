#include "race_context.hpp"


namespace bot {

race_context::race_context():
    track(nullptr)
{}

race_context& current_race()
{
    static race_context current;
    return current;
}

} // namespace bot
