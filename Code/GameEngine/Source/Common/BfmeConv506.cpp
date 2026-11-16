// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
#include "../../Include/GameLogic/ObjectCreationListClass.h"
class BfmeSubBPB;

void bfmeGoBPB(BfmeSubBPB *sub, void *one, void *two, void *three)
{
	if (sub != 0)
		reinterpret_cast<ObjectCreationList *>(sub)->create(one, two, three);
}
