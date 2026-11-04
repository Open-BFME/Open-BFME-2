// cl: /O1 /DNDEBUG /MD
//
// ?getRebuildHoleBehaviorInterface@RebuildHoleBehavior@@UAEPAVRebuildHoleBehaviorInterface@@XZ
// retail 0x00483322, 12 bytes: slot 13 of the RebuildHoleBehavior behavior-
// module vtable (0x00849AA8 entry). Zero Hour's RebuildHoleBehavior.h
// defines it inline as { return this; }: the conversion to the
// RebuildHoleBehaviorInterface base, which sits at +0x24 here as in the
// rowed getRebuildHoleBehaviorInterfaceFromObject 0x004831CB (module+0x24),
// null-checked by the compiler. Only the bases' sizes are modelled.

#include "../../../../Include/GameLogic/Module/RebuildHoleBehaviorClass.h"



RebuildHoleBehaviorInterface *RebuildHoleBehavior::getRebuildHoleBehaviorInterface()
{
	return this;
}
