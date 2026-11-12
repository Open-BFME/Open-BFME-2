// cl: /DNDEBUG /MD
// ?Rva002C06B9Set@@YAXPAVRva003140C8DwordField@@H@Z @0x002C06B9 27B: conditional hilite-color set via dword-field window
// Evidence: siblings Rva002C0619 0x002C0619 and Rva002C0669 0x002C0669 same shape same flags; callers 0x002C3D36 0x002C4020; callees rowed get 0x003140C8 and winSetHiliteColor 0x003144B3; int row really a GameWindow* (DispDwordField family is width-only)
#include "../../../../Include/Common/Rva003140C8DwordField.h"
#include "../../../../Include/GameClient/Bfme2GameWindow.h"
void __cdecl Rva002C06B9Set(Rva003140C8DwordField *holder, int color)
{
	int v = holder->get();
	if (v)
		((GameWindow *)v)->winSetHiliteColor(0, color);
}
