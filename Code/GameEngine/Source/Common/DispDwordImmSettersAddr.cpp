// Retail stores the entry point at VA 0x006D7B50 in the +0x9C slot.
// Its matched provider is rva002D7B50 in VslotSmallBodiesAG.cpp; naming it
// gives the store a relocation when the linked image moves. The owner's
// identity and the slot's purpose remain unknown.
void rva002D7B50(int a, int b);

#include "../../Include/GameLogic/FireLogicSystem.h"

void FireLogicSystem::init()
{
	field9C = (unsigned int)&rva002D7B50;
}
