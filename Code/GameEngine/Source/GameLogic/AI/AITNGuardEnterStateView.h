// Shared consumed AIEnterState view for the AITNGuard units, not an original
// BFME 2 header-path claim. Native constructor 0x00342EAC calls the
// AIInternalMoveToState base and clears dwords +0x4C/+0x50. Its table's name
// getter 0x00342ED1 identifies AIEnterState. The existing onEnter owner
// (0x0034FB77) uses the entry timeout at +0x50; onExit (0x003510A5) uses
// the entry ObjectID at +0x4C and calls AIInternalMoveToState::onExit.
// The base header proves its 0x4C extent. No constructor, destructor or
// snapshot-provider identity is transferred by sharing this view.
#ifndef AITNGUARD_ENTER_STATE_VIEW_H
#define AITNGUARD_ENTER_STATE_VIEW_H
#include "../../../Include/GameLogic/AIInternalMoveToState.h"
class AIEnterState : public AIInternalMoveToState
{
public:
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);
    virtual StateReturnType update();
protected:
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *xfer);
    ObjectID m_entryToClear;
    unsigned int m_entryTimeoutFrame;
};
typedef char AITNGuardEnterStateSizeCheck[sizeof(AIEnterState) == 0x54 ? 1 : -1];
#endif
