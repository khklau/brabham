/***************************************************************************

    file                 : lib.cpp
    created              : Thu 08 Aug 2024 19:42:58 AEST
    copyright            : (C) 2002 khklau@users.noreply.github.com

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "race_context.hpp"

#include <tgf/tgf.h>
#include <track.h>
#include <car.h>
#include <raceman.h>
#include <robottools/robottools.h>
#include <robot.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


static void change_track(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s);
static void start_race(int index, tCarElt* car, tSituation *s);
static void drive(int index, tCarElt* car, tSituation *s);
static void end_race(int index, tCarElt *car, tSituation *s);
static void shut_down(int index);
static int  init_callback_table(int index, void *pt);


/**
 * Module entry point
 **/
extern "C"
int brabham(tModInfo* mod_info)
{
    memset(mod_info, 0, 10 * sizeof(tModInfo));

    mod_info->name    = strdup("brabham");    // name of the module (short)
    mod_info->desc    = strdup("");           // description of the module (can be long)
    mod_info->fctInit = init_callback_table;  // init function
    mod_info->gfId    = ROB_IDENT;            // supported framework version
    mod_info->index   = 1;

    return 0;
}

/**
 * Module interface initialization.
 **/
static int init_callback_table(int index, void* robot_itf)
{
    tRobotItf* iface  = static_cast<tRobotItf*>(robot_itf);

    iface->rbNewTrack = change_track;   // Give the robot the track view called
                                        // for every track change or new race
    iface->rbNewRace  = start_race;     // Start a new race
    iface->rbDrive    = drive;          // Drive during race
    iface->rbPitCmd   = NULL;
    iface->rbEndRace  = end_race;       // End of the current race
    iface->rbShutdown = shut_down;      // Called before the module is unloaded
    iface->index      = index;          // Index used if multiple interfaces
    return 0;
}

/**
 * Called for every track change or new race.
 **/
static void change_track(
    int index,
    tTrack* track,
    void* car_handle,
    void** car_param_handle,
    tSituation* situation)
{
    bot::current_race().track = track;
    *car_param_handle = nullptr;
}

/**
 * Start a new race.
 **/
static void start_race(
    int index,
    tCarElt* car,
    tSituation* s)
{
}

/**
 * Drive during race.
 **/
static void drive(
    int index,
    tCarElt* car,
    tSituation* s)
{
    memset(&car->ctrl, 0, sizeof(tCarCtrl));
    car->ctrl.brakeCmd = 1.0; /* all brakes on ... */
    /*
     * add the driving code here to modify the
     * car->_steerCmd
     * car->_accelCmd
     * car->_brakeCmd
     * car->_gearCmd
     * car->_clutchCmd
     */
}

/**
 * End of the current race
 **/
static void end_race(
    int index,
    tCarElt* car,
    tSituation* s)
{
}

/**
 * Called before the module is unloaded
 **/
static void shut_down(int index)
{
}
