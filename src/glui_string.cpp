/****************************************************************************

  GLUI User Interface Toolkit
  ---------------------------

     glui.cpp


          --------------------------------------------------

  Copyright (c) 1998 Paul Rademacher (this file, Bill Baxter 2005)

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

*****************************************************************************/

#include "../include/glui_internal.h" //"glui_internal_control.h" //PCH

namespace GLUI_Library
{//-.
//<-'
		
String &glui_format_str(String &str, const char *fmt,...)
{
	enum{ ISIZE=128 };
	char stackbuf[ISIZE];
	size_t bufsz = ISIZE;
	char *buf = stackbuf;

	int len; va_list arg; for(;;)
	{
		va_start(arg,fmt);
		#ifdef _WIN32 //stdio.h
		len = _vsprintf_p(buf,bufsz,fmt,arg);
		#else
		len = vsnprintf(buf,bufsz,fmt,arg);
		#endif
		va_end(arg);
		if(len>=0) break;

		// else make a bigger buf, try again
		bufsz*=2; if(buf==stackbuf) 
		{
			buf = (char*)malloc(sizeof(char)*bufsz);
		}
		else buf = (char*)realloc(buf,sizeof(char)*bufsz);
	}

	str.assign(buf,len); if(buf!=stackbuf) free(buf); return str;
}

//---.
}//<-'
