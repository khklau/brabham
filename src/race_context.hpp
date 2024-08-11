#pragma once

#include <track.h> 


namespace bot {

struct race_context
{
    tTrack* track;

    race_context();
};

race_context& current_race();

} // namespace bot
