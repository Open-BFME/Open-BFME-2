// cl: /DNDEBUG /MD
// ?Rva00525162Check@@YGEPAVObject@@@Z, retail 0x00525162 44B unlock via controlling player plus status.
// Local-player gate then ObjectStatus 0x5c inverted via rowed testStatus.
// Evidence: callees rowed getControllingPlayer 0x0028AFA9 plus isLocalPlayer 0x002A9D89 plus testStatus 0x0004E536; callers 0x00526553 0x00526966; prev 0x0052510C same flags.
#include "../../Include/Common/Player.h"

enum ObjectStatusTypes;

#include "../GameLogic/Object/object.h"

unsigned char __stdcall Rva00525162Check(Object *obj)
{
	Player *player = obj->getControllingPlayer();
	if (player->isLocalPlayer())
		return (unsigned char)!obj->testStatus((ObjectStatusTypes)0x5c);
	else
		return 0;
}
