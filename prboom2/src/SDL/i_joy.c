/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *   Joystick handling for Linux
 *
 *-----------------------------------------------------------------------------
 */

#ifndef lint
#endif /* lint */

#include <stdlib.h>

#include "SDL.h"
#include "doomdef.h"
#include "doomtype.h"
#include "m_argv.h"
#include "d_event.h"
#include "d_main.h"
#include "i_joy.h"
#include "lprintf.h"
#include "i_system.h"

int joyleft;
int joyright;
int joyup;
int joydown;

int usejoystick;

#ifdef __PS2__
static int prev_axis[SDL_CONTROLLER_AXIS_MAX];

#define TRIGGER_DEADZONE 16384

// 0-16
static int joy_permastrafe = 1;

#endif

#ifdef HAVE_SDL_JOYSTICKGETAXIS
#ifdef __PS2__
static SDL_GameController * joystick;
#else
static SDL_Joystick *joystick;
#endif
#endif

static void I_EndJoystick(void)
{
  lprintf(LO_DEBUG, "I_EndJoystick : closing joystick\n");
#ifdef __PS2__
  if (joystick)
  {
    SDL_GameControllerClose(joystick);
    joystick = NULL;
  }
#endif
}

#ifdef __PS2__
static inline int JoystickMove(const int axis)
{
  int axis_value;
  if (axis >= 0 && axis < SDL_CONTROLLER_AXIS_MAX)
  {
    prev_axis[axis] = SDL_GameControllerGetAxis(joystick, axis);
    axis_value = prev_axis[axis] / 3000;
    if (abs(axis_value) < 7) axis_value = 0;
    return axis_value;
  }
  return 0;
}
static inline int JoystickLook(const int axis)
{
  int axis_value, delta;
  if (axis >= 0 && axis < SDL_CONTROLLER_AXIS_MAX)
  {
    axis_value = SDL_GameControllerGetAxis(joystick, axis);
    delta = axis_value - prev_axis[axis];
    if (delta)
    {
      prev_axis[axis] = axis_value;
      return delta << 4;
    }
  }
  return 0;
}
#endif

void I_PollJoystick(void)
{
#ifdef HAVE_SDL_JOYSTICKGETAXIS
  event_t ev;
  Sint16 axis_value;
#ifdef __PS2__
  Sint16 xaxisl = SDL_CONTROLLER_AXIS_LEFTX, yaxisl, xaxisr;
  int i;
  int hat;
#endif
  if (!usejoystick || (!joystick)) return;
#ifdef __PS2__  
  // movement uses the old joystick system
  ev.type = ev_joystick;
  ev.data1 = 0;
#if 0  
  ev.data2 = JoystickMove(joyaxis_moveh);
  ev.data3 = JoystickMove(joyaxis_movev);
  D_PostEvent(&ev);
  // look translates to mouse motion
  ev.type = ev_mouse;
  ev.data1 = 0;
  ev.data2 = JoystickLook(joyaxis_lookh);
  ev.data3 = JoystickLook(joyaxis_lookv);
  
#endif

  xaxisl = SDL_GameControllerGetAxis(joystick, 0) / 3000;
	
  if(D_abs(xaxisl) < 3)
	    ev.data1 = 0;
	else if(xaxisl > 0)
		ev.data1 = 1;
	else
		ev.data1 = -1;

	yaxisl  = SDL_GameControllerGetAxis(joystick, 1) / 3000;
	if(D_abs(yaxisl) < 2)
		ev.data3 = 0;
	else if(yaxisl > 0)
		ev.data3 = 1;
	else
		ev.data3 = -1;

	xaxisr = SDL_GameControllerGetAxis(joystick, 2) / 3000;
	
  if(D_abs(xaxisr) < 2)
		ev.data2 = 0;
	else if(xaxisr > 0)
		ev.data2 = 1;
	else
		ev.data2 = -1;

  D_PostEvent(&ev);
#else
  ev.type = ev_joystick;
  ev.data1 =
    (SDL_JoystickGetButton(joystick, 0)<<0) |
    (SDL_JoystickGetButton(joystick, 1)<<1) |
    (SDL_JoystickGetButton(joystick, 2)<<2) |
    (SDL_JoystickGetButton(joystick, 3)<<3) |
    (SDL_JoystickGetButton(joystick, 4)<<4) |
    (SDL_JoystickGetButton(joystick, 5)<<5) |
    (SDL_JoystickGetButton(joystick, 6)<<6) |
    (SDL_JoystickGetButton(joystick, 7)<<7);
  axis_value = SDL_JoystickGetAxis(joystick, 0) / 3000;
  if (abs(axis_value)<7) axis_value=0;
  ev.data2 = axis_value;
  axis_value = SDL_JoystickGetAxis(joystick, 1) / 3000;
  if (abs(axis_value)<7) axis_value=0;
  ev.data3 = axis_value;

  D_PostEvent(&ev);
#endif  
#endif
}

void I_InitJoystick(void)
{
#ifdef HAVE_SDL_JOYSTICKGETAXIS
  const char* fname = "I_InitJoystick : ";
  int num_joysticks;
  
#ifdef __PS2__
  if (!usejoystick || M_CheckParm("-nojoy")) return;
  SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
#else
  if (!usejoystick) return;
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
#endif
  num_joysticks=SDL_NumJoysticks();
#ifdef __PS2
  if ((usejoystick>num_joysticks) || (usejoystick <= 0) || !SDL_IsGameController(usejoystick-1)) {
#else
  if (M_CheckParm("-nojoy") || (usejoystick>num_joysticks) || (usejoystick<0)) {
#endif
    if ((usejoystick > num_joysticks) || (usejoystick < 0))
      lprintf(LO_WARN, "%sinvalid joystick %d\n", fname, usejoystick);
    else
      lprintf(LO_INFO, "%suser disabled\n", fname);
    return;
  }
#ifdef __PS2__
  joystick=SDL_GameControllerOpen(usejoystick-1);
#else
  joystick=SDL_JoystickOpen(usejoystick-1);
#endif
  if (!joystick)
    lprintf(LO_ERROR, "%serror opening joystick %d\n", fname, usejoystick);
  else {
    I_AtExit(I_EndJoystick, true);
#ifdef __PS2__
    SDL_GameControllerEventState(SDL_ENABLE);
    lprintf(LO_INFO, "%sopened %s\n", fname, SDL_GameControllerName(joystick));
#else
    lprintf(LO_INFO, "%sopened %s\n", fname, SDL_JoystickName(joystick));
#endif
#ifndef __PS2__
    joyup = 32767;
    joydown = -32768;
    joyright = 32767;
    joyleft = -32768;
#endif
  }
#endif
}
