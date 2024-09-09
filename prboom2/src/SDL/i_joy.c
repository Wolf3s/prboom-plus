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

#ifdef HAVE_SDL_JOYSTICKGETAXIS
static SDL_Joystick *joystick;
#endif

static void I_EndJoystick(void)
{
  lprintf(LO_DEBUG, "I_EndJoystick : closing joystick\n");
}

void I_PollJoystick(void)
{
#ifdef HAVE_SDL_JOYSTICKGETAXIS
  event_t ev;
#ifdef _EE
  Sint16 xaxisl, yaxisl, xaxisr;
  Uint8 hat;
#else
  Sint16 axis_value;
#endif
#ifdef _EE
  ev.data1 = 0;
  // rm -- treat buttons like key inputs (easier than recoding main)
  //ev.data1 =
  //	(SDL_JoystickGetButton(joystick, 0)<<0) |
  //	(SDL_JoystickGetButton(joystick, 1)<<1) |
  //	(SDL_JoystickGetButton(joystick, 2)<<2) |
  //	(SDL_JoystickGetButton(joystick, 3)<<3);
  
  hat = SDL_JoystickGetHat(joystick, 0);
  
  if(hat == SDL_HAT_CENTERED)
  {
	xaxisl = SDL_JoystickGetAxis(joystick, 0) / 3000;
	  
	if(abs(xaxisl) < 3)
	    ev.data1 = 0;
	else if(xaxisl > 0)
		ev.data1 = 1;
	else
		ev.data1 = -1;

	yaxisl = SDL_JoystickGetAxis(joystick, 1) / 3000;
	
	if(abs(yaxisl) < 2)
		ev.data3 = 0;
	else if(yaxisl > 0)
		ev.data3 = 1;
	else
		ev.data3 = -1;

	xaxisr = SDL_JoystickGetAxis(joystick, 2) / 3000;
	
	if(abs(xaxisr) < 2)
		ev.data2 = 0;
	else if(xaxisr > 0)
		ev.data2 = 1;
	else
		ev.data2 = -1;
	}
	else
	{
		if(hat & SDL_HAT_UP)
			ev.data3 = -1;

		if(hat & SDL_HAT_RIGHT)
			ev.data2 = 1;

		if(hat & SDL_HAT_DOWN)
			ev.data3 = 1;

		if(hat & SDL_HAT_LEFT)
			ev.data2 = -1;
	
    }
#else
  if (!usejoystick || (!joystick)) return;
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
#endif
  D_PostEvent(&ev);
#endif
}

void I_InitJoystick(void)
{
#ifdef HAVE_SDL_JOYSTICKGETAXIS
  const char* fname = "I_InitJoystick : ";
  int num_joysticks;

  if (!usejoystick) return;
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  num_joysticks=SDL_NumJoysticks();
  if (M_CheckParm("-nojoy") || (usejoystick>num_joysticks) || (usejoystick<0)) {
    if ((usejoystick > num_joysticks) || (usejoystick < 0))
      lprintf(LO_WARN, "%sinvalid joystick %d\n", fname, usejoystick);
    else
      lprintf(LO_INFO, "%suser disabled\n", fname);
    return;
  }
  joystick=SDL_JoystickOpen(usejoystick-1);
  if (!joystick)
    lprintf(LO_ERROR, "%serror opening joystick %d\n", fname, usejoystick);
  else {
    I_AtExit(I_EndJoystick, true);
    lprintf(LO_INFO, "%sopened %s\n", fname, SDL_JoystickName(joystick));
#ifndef _EE
    joyup = 32767;
    joydown = -32768;
    joyright = 32767;
    joyleft = -32768;
#endif
  }
#endif
}
