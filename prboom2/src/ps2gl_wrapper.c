
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
 *  PS2GL Wrapper for unimplemented functions 
 *-----------------------------------------------------------------------------
 */

#include <GL/gl.h>

void glMultiTexCoord2fvARB(GLenum target, const GLfloat* v)
{

}

void glActiveTextureARB(GLenum texture)
{

}

void glClientActiveTextureARB(GLenum texture)
{

}

void glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t)
{

}

void glTexGenfv(GLenum coord, GLenum pname, const GLfloat* params)
{

}

void glTexGenf(GLenum coord, GLenum pname, GLfloat param)
{

}

void glDepthRange(GLclampd near_val, GLclampd far_val)
{

}

void glStencilFunc(GLenum func, GLint ref, GLuint mask)
{

}

void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{

}

void glColor4ubv(const GLubyte* v)
{

}

void glGetTexLevelParameteriv(GLenum target, GLint level,
    GLenum pname, GLint* params)
{

}

void glGetTexImage(GLenum target, GLint level,
    GLenum format, GLenum type,
    GLvoid* pixels)
{
    
}