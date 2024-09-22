#pragma once

#include <raceman.h>
#include <track.h> 


namespace torcs {
namespace brabham {

enum race_state
{
    RUNNING = RM_RACE_RUNNING,
    FINISHING = RM_RACE_FINISHING,
    ENDED = RM_RACE_ENDED,
    STARTING = RM_RACE_STARTING,
    PRESTART = RM_RACE_PRESTART,
    PAUSED = RM_RACE_PAUSED,
};

struct race_context
{
    tTrack* track;
    race_state state;

    race_context();
};

race_context& current_race();

} // namespace brabham
} // namespace torcs
