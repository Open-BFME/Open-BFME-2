// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
// stlport
//
// ?setPosition@Win32Mouse@@UAEXHH@Z, retail 0x00041AD4 (60B).
// Target facts: 0x00041AD4 fills slot 17 (setPosition, between
// createStreamMessages and setCursor) of two vftables: ??_7Win32Mouse@@6B@
// 0x007C2478, whose other slots include Win32Mouse::update 0x00041A0B,
// initCursorResources 0x00041BA6 and setCursor 0x00041A83, and ??_7W3DMouse@@6B@
// 0x007C86D8, which inherits it beside W3DMouse::draw 0x000992B0 and setCursor
// 0x00099DCC. No other absolute pointer in the image references it, and
// the body sits in Win32Mouse.cpp's run between setCursor 0x00041A83 and
// getMouseEvent 0x00041B10. It calls Mouse::setPosition 0x001EDE4C, then
// ClientToScreen(ApplicationHWnd) and SetCursorPos.
// Donor facts: Zero Hour's Win32Mouse has no setPosition; its
// DirectInputMouse::setPosition (Win32DIMouse.cpp) is this body, and this file
// was first ported from Open-BFME-1's Win32DIMouse.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1), placed by
// masked whole-.text search under the DirectInputMouse name.
// Inference: BFME 2 gave Win32Mouse that override; the retail body is
// Win32Mouse::setPosition. Runtime/optimization flags stay as in the port;
// includes now use BFME 2's canonical Mouse and runner Windows declarations.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <windows.h>
#include "../../../../GameEngine/Include/GameClient/Mouse.h"

extern HWND ApplicationHWnd;

class Win32Mouse : public Mouse
{
public:
	virtual void setPosition(int x, int y);
};

void Win32Mouse::setPosition( int x, int y )
{
	POINT p;

	// extending functionality
	Mouse::setPosition( x, y );

	// set the windows cursor
	p.x = x;
	p.y = y;
	ClientToScreen( ApplicationHWnd, &p );

	// set the window mouse
	SetCursorPos( p.x, p.y );

}
