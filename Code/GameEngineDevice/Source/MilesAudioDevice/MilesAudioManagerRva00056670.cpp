// cl: /Ireference/shims/bfme2_ascii /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00056670@MilesAudioManager@@QAE_NW4ObjectID@@@Z @0x00056670 70B chain: calls 0x00054899 just landed
// Evidence: calls rowed findObjectByID 0x00049DC5 via TheGameLogic ?TheGameLogic@@3PAVGameLogic@@A plus getDrawable 0x005508E2 plus dword getter 0x0055A88B plus rva00054899 0x00054899; prev 0x00056634 next 0x000566B6 MilesAudioManager.


class Object;
class Drawable;

#include "../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

#include "../../../GameEngine/Source/Common/Thing/thing.h"

#include "../../../GameEngine/Source/GameLogic/Object/object.h"

#include "../../../GameEngine/Include/Common/Rva0055A88BDwordField.h"

extern GameLogic *TheGameLogic;

#include "../../Include/MilesAudioDevice/MilesAudioManager.h"

bool MilesAudioManager::rva00056670(ObjectID id)
{
	if (!id)
		return false;
	Object *obj = TheGameLogic->findObjectByID(id);
	int val = 0;
	if (obj)
	{
		Drawable *drawable = obj->getDrawable();
		if (drawable)
			val = ((Rva0055A88BDwordField *)drawable)->get();
	}
	return rva00054899(id, val);
}
