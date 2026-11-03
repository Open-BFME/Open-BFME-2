// cl: /DNDEBUG /MD
//
// ?rva0028AFBB@Object@@QBE_NXZ @0x0028AFBB 23B
// Wraps the rowed Object::getControllingPlayer (retail 0x0028AFA9): null
// check then test of the Player word at +0x5C for zero. Forty-plus raw
// callers game-wide. The +0x5C Player offset is witnessed only here.
// Identity beyond the wrapper is unproven so the name stays
// address-derived. Flags from the next rowed Object sibling
// (ObjectSetProducer.cpp /O1 /DNDEBUG /MD); /O1 selects the retail
// xor-first cmp plus sete shape.

#include "../../../Include/Common/Player.h"

#include "object.h"

bool Object::rva0028AFBB() const
{
	Player *player = getControllingPlayer();
	if (player != 0)
		return player->m_playerType == 0;
	return false;
}
