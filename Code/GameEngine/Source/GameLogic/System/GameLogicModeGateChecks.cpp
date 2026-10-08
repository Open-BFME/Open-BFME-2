// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// GameLogic game-mode gate leaf called by BFMEDesyncCheck::writeReportIfMismatched:
// it rejects modes 9/4/7. Retail keeps the cold return in a tail block after
// its own ret (28B true extent, proven by raw-byte decode, not the first-ret
// guess). Member identity is the game-mode word at +0x110 (BFME1 carries it at
// +0x10C; retail is shifted +4, the same family as the +0x40 GameLogic frame
// lesson). The sibling gate at 0x42235 is the real ZH-verbatim
// GameLogic::isInMultiplayerGame in its own TU, not here.

#include "../../Common/GameLogicObjectLookupView.h"

// ?rva0042219@GameLogic@@QAE_NXZ
bool GameLogic::rva0042219(void)
{
    return m_110 != 9 && m_110 != 4 && m_110 != 7;
}

// ?rva001DCD1C@GameLogic@@QAE_NXZ at retail 0x001DCD1C (32B).
bool GameLogic::rva001DCD1C(void)
{
    return m_110 == 8 || (m_110 == 9 && m_114 != 3);
}
