// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /I.
// stlport
// Retail 0x0047DC88, 87B: TunnelContain::removeFromContain, entered through
// the contain interface at TunnelContain+0x20 (object this-0x18, primary
// vtable this-0x20).
// Body: Zero Hour's TunnelContain::removeFromContain (GeneralsMD GameEngine/
// Source/GameLogic/Object/Contain/TunnelContain.cpp) reshaped for BFME 2:
// the onRemoving/onRemovedFrom notifications are the inherited body
// 0x00479DCD (called on the same interface), then, with a controlling
// player, the object is removed from the player's tunnel tracker (+0x2E8)
// when primary slot 0x80 reports it or the tracker says it is contained
// (0x004F550A); TunnelTracker::removeFromContain is 0x004F54BF. The tracker
// methods are rowed with ObjectID parameters while retail passes the Object
// pointer, hence the casts.

#include "TunnelContainView.h"

// The contain interface at +0x20; its inherited removeFromContain body is
// the rowed 0x00479DCD (address-named class and method as rowed).
void TunnelContain::removeFromContain( Object *obj, int exposeStealthUnits )
{
	rva00479DCD( obj, exposeStealthUnits );

	Player *owningPlayer = m_object->getControllingPlayer();
	if( owningPlayer == 0 )
		return;

	if( p32( obj ) == 0 && !owningPlayer->getTunnelSystem()->isInContainer( (ObjectID)(int)obj ) )
		return;

	owningPlayer->getTunnelSystem()->removeFromContain( (ObjectID)(int)obj, exposeStealthUnits );
}
