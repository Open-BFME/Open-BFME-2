// cl: /DNDEBUG /MD
//
// ?rva00262D2D@AIUpdateInterface@@QAEXXZ, retail 0x00262D2D, 19 bytes.
// AIUpdateInterface leaf: destroyPath then virtual slot 24 (offset 0x60,
// privateIdle) with CMD_FROM_AI. Callee destroyPath 0x00262A8A is rowed.
// No other callees.

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::rva00262D2D()
{
	destroyPath();
	privateIdle(CMD_FROM_AI);
}
