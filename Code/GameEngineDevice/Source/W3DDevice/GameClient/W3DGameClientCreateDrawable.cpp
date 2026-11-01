// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?friend_createDrawable@W3DGameClient@@UAEPAVDrawable@@PBVThingTemplate@@W4DrawableStatus@@H@Z,
// retail 0x0004C75F..0x0004C7A8 (73B), thiscall ret 0xC.
//
// Zero Hour's W3DGameClient::friend_createDrawable (W3DGameClient.cpp) in its
// BFME 2 form: the same null template check, then a plain heap Drawable built
// by the rowed three-argument constructor 0x002797BD (BFME 2 adds the int).
//
// Evidence (target): the W3DGameClient vftable entry sits right before
// GameClient::destroyDrawable 0x00239F40, between the GameClient iterator
// slots and W3DGameClient::setTimeOfDay. W3DGameClient.cpp keeps the Zero
// Hour two-argument text built on the shared headers, so this BFME 2 body
// has its own unit with only the types it touches.

class ThingTemplate;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

// The 0x470-byte Drawable; only the rowed constructor is modelled.
#include "../../../../GameEngine/Include/GameClient/Drawable.h"

class W3DGameClient
{
public:
	virtual Drawable *friend_createDrawable(const ThingTemplate *tmplate, DrawableStatus statusBits, int extra);
};

Drawable *W3DGameClient::friend_createDrawable(const ThingTemplate *thingTemplate, DrawableStatus statusBits, int extra)
{
	// sanity
	if (thingTemplate == 0)
		return 0;

	return new Drawable(thingTemplate, statusBits, extra);
}
