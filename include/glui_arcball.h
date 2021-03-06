/**********************************************************************

  arcball.h

  GLUI User Interface Toolkit
  Copyright (c) 1998 Paul Rademacher
     Feb 1998, Paul Rademacher (rademach@cs.unc.edu)
     Oct 2003, Nigel Stewart - GLUI Code Cleaning


  WWW:    http://sourceforge.net/projects/glui/
  Forums: http://sourceforge.net/forum/?group_id=92496

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
  claim that you wrote the original software. If you use this software
  in a product, an acknowledgment in the product documentation would be
  appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
  misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

 ---------------------------------------------------------------------

  A C++ class that implements the Arcball, as described by Ken
  Shoemake in Graphics Gems IV.
  This class takes as input mouse events (mouse down, mouse drag,
  mouse up), and creates the appropriate quaternions and 4x4 matrices
  to represent the rotation given by the mouse.

  This class is used as follows:
  - initialize [either in the constructor or with set_params()], the
    center position (x,y) of the arcball on the screen, and the radius
  - on mouse down, call mouse_down(x,y) with the mouse position
  - as the mouse is dragged, repeatedly call mouse_motion() with the
    current x and y positions.  One can optionally pass in the current
    state of the SHIFT, ALT, and CONTROL keys (passing zero if keys
    are not pressed, non-zero otherwise), which constrains
    the rotation to certain axes (X for CONTROL, Y for ALT).
  - when the mouse button is released, call mouse_up()

  Axis constraints can also be explicitly set with the
  set_constraints() function.

  The current rotation is stored in the 4x4 double matrix 'rot'.
  It is also stored in the quaternion 'q_now'.

**********************************************************************/

#ifndef GLUI_ARCBALL_H
#define GLUI_ARCBALL_H

#include "glui_algebra3.h"
#include "glui_quaternion.h"

namespace GLUI_Library
{//-.
//<-'

class Arcball
{
public:

	Arcball();
	Arcball(mat4 *mtx);
	Arcball(const vec2 &center, double radius);

	void set_damping(double d);
	void idle();
	void mouse_down(int x, int y);
	void mouse_up();
	//cx+xy is currently cz.
	void mouse_motion(int x, int y, double shift, bool cx, bool cy);
	void mouse_motion(int x, int y);
	//void set_constraints(bool constrain_x, bool constrain_y);
	void set_params(const vec2 &center, double radius);
	void reset_mouse();
	void init();

	vec3 constrain_vector(const vec3 &vector, const vec3 &axis);
	vec3 mouse_to_sphere(const vec2 &p, bool cx, bool cy);

	quat q_now, q_drag, q_increment; //quat q_down; //unused
	vec2 prev_pt; //down_pt
	mat4 rot; //mat4 rot_increment; //eliminating
	mat4 *rot_ptr;

	bool is_mouse_down;
	bool is_spinning;
	//bool zero_increment; //unused //???

	vec2 center; //leaving at 0,0

	double radius, damp_factor;	
};
		  
//---.
}//<-'

#endif
