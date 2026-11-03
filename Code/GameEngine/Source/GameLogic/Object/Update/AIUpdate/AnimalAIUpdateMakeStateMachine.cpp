// cl: /DNDEBUG /MD /EHsc
//
// ?makeStateMachine@AnimalAIUpdate@@MAEPAVAIStateMachine@@XZ, retail
// 0x0047EC69, 63 bytes: slot 150 of AnimalAIUpdate's primary vtable
// 0x00C47B98, the slot where the matched AIUpdateInterface::makeStateMachine
// 0x00262513 sits in the AIUpdate family. Same body with AnimalAIUpdate's own
// machine key 0xD7F450E0 (the base passes 0x4A9A0E38): a 0x68-byte
// AIStateMachine for the owner (pinned ctor 0x00351C48).
typedef unsigned int UnsignedInt;

class Object;

#include "../../../../../Include/GameLogic/AIStateMachineClass.h"

#include "../../../../../Include/GameLogic/Module/AIUpdate.h"

#include "../../../../../Include/GameLogic/Module/AnimalAIUpdate.h"

AIStateMachine *AnimalAIUpdate::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0xD7F450E0);
}
