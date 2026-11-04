// cl: /DNDEBUG /MD
//
// ?init@Win32Mouse@@UAEXXZ, retail 0x000419F5, 17 bytes (pinned; next to
// the rowed Win32Mouse::addWin32Event 0x00041A10). The Zero Hour body
// extends Mouse::init(); BFME2 then sets the byte at +0x4F9C. The base
// call goes to 0x001EE4DC, whose only caller is this one, so it is pinned
// as Mouse::init from this call. The byte lies in Mouse's opaque storage.
#include "../../../../GameEngine/Include/GameClient/Mouse.h"

class Win32Mouse : public Mouse
{
public:
	virtual void init(void);
};

void Win32Mouse::init(void)
{
	// extend
	Mouse::init();
	field4F14[0x4F9C - 0x4F14] = true;
}
