// cl: /MD /GX- /Ireference/shims/bfme2_ascii
// stlport
// ?rva002AC673@Player@@QAEXXZ @0x002AC673 (62B): Player science reset.
// Iterates the ScienceType vector at +0x2F0..+0x2F4, notifying ScriptEngine
// via rowed ?rva00357A03@ScriptEngine@@QAEXHW4ScienceType@@@Z at 0x00357A03
// with player index at +0x54, then clears the range through rowed
// vector<ScienceType>::erase at 0x00532803. Caller at 0x002AE258. Prev
// PlayerRva002AC629 next PlayerRva002ACD09.

enum ScienceType
{
	SCIENCE_INVALID = -1
};

#include <vector>

#include "../../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;


#include "../../../Include/Common/Player.h"

void Player::rva002AC673()
{
	ScienceType *end = m_sciences.end();
	_STL::vector<ScienceType> *vec = &m_sciences;
	for (ScienceType *it = vec->begin(); it != end; ++it) {
		TheScriptEngine->rva00357A03(m_playerIndex, *it);
	}
	vec->erase(vec->begin(), vec->end());
}
