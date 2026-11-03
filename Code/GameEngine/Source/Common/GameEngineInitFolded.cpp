// cl: /O1 /DNDEBUG /MD /EHsc
// Retail ICF bodies called by GameEngine::init. These are ordinary C++
// definitions compiled separately so init retains the retail calls.
// ZH supplies the addSubsystem/init/setSeed roles; BFME2's direct call sites
// prove the empty registration operation, reset vslot +0x28 and seed +0x50.
class SubsystemInterface;
#include "../../Include/Common/SubsystemInterfaceList.h"
void SubsystemInterfaceList::addSubsystem(SubsystemInterface *) {}

#include "../../Include/GameNetwork/GameInfo.h"
void GameInfo::init() { reset(); }
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline void GameInfo::setSeed(int seed) { m_seed = seed; }

// ?bfmeAnchorGameInfoSetSeed absent-from-retail
void bfmeAnchorGameInfoSetSeed(GameInfo *gameInfo, int seed)
{
	gameInfo->setSeed(seed);
}


// The early argc/argv hook is a bare RET in this build; its original name
// and disabled-purpose identity are unknown.
void Rva000B3FD0(int, char *[]) {}
