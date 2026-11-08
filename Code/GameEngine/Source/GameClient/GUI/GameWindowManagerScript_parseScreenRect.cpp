// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?parseScreenRect@@YA_NPAD0PAH111@Z, retail 0x0031583E, 342 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseScreenRect): peek the parent window, strtok the UPPERLEFT/BOTTOMRIGHT
// and CREATIONRESOLUTION ints out of the buffer, scale the region by the
// current-vs-creation resolution ratio, then store x/y (parent-relative when a
// parent exists) and the adjusted width/height.
// BFME2 facts (all retail-measured):
// - The function is file-static and the private convention drops the two
//   unused char* parameters: the caller parseWindow at 0x00316FF1 pushes only
//   the four Int* outputs, so x/y/width/height land at [ebp+8]/[ebp+0xC]/
//   [ebp+0x10]/[ebp+0x14] and the frame is sub esp,0x28. The scaffold caller
//   below keeps the static emitted with that convention.
// - strtok rides the msvcr71 import at 0xBBA5EC (<string.h> declares it
//   dllimport under /MD: mov esi, ds:0xBBA5EC then call esi); seps
//   " ,:=\n\r\t" lives at 0xC0C25C.
// - TheDisplay is at 0xDFE9D8; getWidth is vtable slot 0x40 and getHeight slot
//   0x44, both returning UnsignedInt (retail emits the test/jge/fadd 2^32
//   unsigned-to-Real fixup).
// - scanInt is the file-static at 0x00314E96; peekWindow at 0x00314EEE;
//   GameWindow::winGetScreenPosition at 0x00313B3C.
// - Identity: the retail caller at 0x00316FF1 passes exactly four Int* outputs
//   in source order, and the name is carried from the reference source.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#include <string.h>
#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Include/Lib/IRegion2D.h"

class GameWindow;

extern GameWindow *peekWindow(void);
extern Int scanInt(const char *source, Int &val);

#include "../../../Include/GameClient/Display.h"

extern Display *TheDisplay;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

// ?parseScreenRect@@YA_NPAD0PAH111@Z
static Bool parseScreenRect(char *token, char *buffer, Int *x, Int *y, Int *width, Int *height)
{
	GameWindow *parent = peekWindow();
	IRegion2D screenRegion;
	ICoord2D createRes;  // creation resolution
	char *seps = " ,:=\n\r\t";
	char *c;

	c = strtok(NULL, seps);  // UPPERLEFT token
	c = strtok(NULL, seps);  // x position
	scanInt(c, screenRegion.lo.x);
	c = strtok(NULL, seps);  // y posotion
	scanInt(c, screenRegion.lo.y);

	c = strtok(NULL, seps);  // BOTTOMRIGHT token
	c = strtok(NULL, seps);  // x position
	scanInt(c, screenRegion.hi.x);
	c = strtok(NULL, seps);  // y posotion
	scanInt(c, screenRegion.hi.y);

	c = strtok(NULL, seps);  // CREATIONRESOLUTION token
	c = strtok(NULL, seps);  // x creation resolution
	scanInt(c, createRes.x);
	c = strtok(NULL, seps);  // y creation resolution
	scanInt(c, createRes.y);

	//
	// shrink or expand the screen region by the ratio of the current
	// resolution divided by the creation resolution
	//
	Real xScale = (Real)TheDisplay->getWidth() / (Real)createRes.x;
	Real yScale = (Real)TheDisplay->getHeight() / (Real)createRes.y;
	screenRegion.lo.x = (Int)((Real)screenRegion.lo.x * xScale);
	screenRegion.lo.y = (Int)((Real)screenRegion.lo.y * yScale);
	screenRegion.hi.x = (Int)((Real)screenRegion.hi.x * xScale);
	screenRegion.hi.y = (Int)((Real)screenRegion.hi.y * yScale);

	//
	// given the screen region upper left compute the upper left that we
	// will give this window, if we have a parent note that the position
	// is relative to the parent client area, if no parent is present
	// we're talking about the screen
	//
	if (parent)
	{
		ICoord2D parentScreenPos;

		// get parent position on screen
		parent->winGetScreenPosition(&parentScreenPos.x, &parentScreenPos.y);

		// save x and y with parent position as relative (0,0) location
		*x = screenRegion.lo.x - parentScreenPos.x;
		*y = screenRegion.lo.y - parentScreenPos.y;
	}
	else
	{
		*x = screenRegion.lo.x;
		*y = screenRegion.lo.y;
	}

	// save our width and height from the adjusted screen region locations
	*width = screenRegion.hi.x - screenRegion.lo.x;
	*height = screenRegion.hi.y - screenRegion.lo.y;

	return true;
}

// Codegen scaffold: MSVC only drops the two unused char* parameters for a
// file-static with a visible caller, and parseScreenRect's only caller is
// parseWindow at 0x00316E8F. External linkage keeps the scaffold emitted.
// ?parseScreenRectCaller absent-from-retail
Bool parseScreenRectCaller(Int *x, Int *y, Int *w, Int *h)
{
	return parseScreenRect(0, 0, x, y, w, h);
}
