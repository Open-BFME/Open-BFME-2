// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// ScoredKillTracker::friend_addTrackedKill / friend_update (WorldBuilder names, ScoredKillTracker.cpp lines 190..195 and 210: push the kill onto the +0x18 list and count; age out the front).
// stlport
// was ?rva0055AA06@Rva0055AA06@@QAEXPBUCoord3D@@@Z @ 0x0055AA06, 49 bytes.
// Push TheGameLogic+0x40 onto list at +0x18 inc count at +0x1C copy 12B to +0x20.
// Evidence: retail lea-push-call push_back 0x5548F inc [esi+0x1C] lea edi [esi+0x20] movsd x3; caller 0x39CF0A.
extern class GameLogic *TheGameLogic;

#include <list>

struct GameLogic0055AA06
{
	char m_pad[0x40];
	unsigned int m_val;
};
#define TheGameLogic (*(GameLogic0055AA06 **)&TheGameLogic)

#include "ScoredKillTrackerView.h"

void ScoredKillTracker::friend_addTrackedKill(const Coord3D *src)
{
	int tmp = TheGameLogic->m_val;
	m_trackedKills.push_back(tmp);
	++m_trackedKillsCount;
	m_position.value = *src;
}

// was ?rva0055AA37@Rva0055AA06@@QAEXXZ @ 0x0055AA37, 49 bytes.
// Drain list at +0x18 while front+0x04 ult TheGameLogic+0x40 dec count at +0x1C.
// Evidence: retail lea edi plus18 jmp cond mov eax triple-deref plus8 add plus04 cmp TheGameLogic plus0x40 jae exit pop_front 0x37BCF9; caller 0x39D3FC.
void ScoredKillTracker::friend_update()
{
	while (!m_trackedKills.empty() && m_trackedKills.front() + m_lifetime < TheGameLogic->m_val) {
		m_trackedKills.pop_front();
		--m_trackedKillsCount;
	}
}
