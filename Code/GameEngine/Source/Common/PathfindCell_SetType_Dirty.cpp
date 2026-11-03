// cl: /DNDEBUG /MD
// ?SetType_Dirty@PathfindCell@@QAE_NH@Z, retail 0x0052DA1C, 71 bytes.
// Low-nibble type setter with owner guard at +0x0/+0x28.
// Evidence: unlock lane unblocking 6 callers; same /O1 shape as Common neighbour.
#include "../../Include/Common/MixFileInfoBuffer.h"
#include "../../Include/GameLogic/PathfindCell.h"

bool PathfindCell::SetType_Dirty(int arg)
{
    if (m_info && ((MixFileInfoBuffer *)m_info)->field28 != 0) {
        if ((m_0C & 0xF) == 4)
            return false;
        m_0C = (m_0C & ~0xB) | 4;
        return true;
    }
    if ((m_0C & 0xF) == arg)
        return false;
    m_0C ^= ((m_0C ^ arg) & 0xF);
    return true;
}
