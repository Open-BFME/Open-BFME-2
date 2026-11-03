// cl: /MD
#include "../../Common/GameLogicObjectLookupView.h"
#include "TeamInQueue.h"
// ZH TeamInQueue::isBuildTimeExpired supplies the semantic lead.
// Native call4F1676 in checkQueuedTeams4F1653 targets4F0681 on the queue
// entry. Native reads Team1C->prototype30->idleFrames1F8, tests >=1,
// then compares game frame unsigned above start24+idleFrames.
// The two existing accessed-prefix views are retained; no complete Team
// or TeamPrototype layout is inferred here.
struct Rva004F0681Inner {
    char m_pad00[0x1F8];
    int m_1F8;
};
struct Rva004F0681Mid {
    char m_pad00[0x30];
    Rva004F0681Inner *m_30;
};
extern GameLogic *TheGameLogic;
bool TeamInQueue::isBuildTimeExpired()
{
    int idleFrames=((Rva004F0681Mid *)m_team)->m_30->m_1F8;
    if(idleFrames<1)
        return false;
    unsigned int deadline=(unsigned int)m_frameStarted+(unsigned int)idleFrames;
    unsigned char result=TheGameLogic->getFrame()>deadline;
    return result;
}
