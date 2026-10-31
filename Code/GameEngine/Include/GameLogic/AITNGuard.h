#pragma once
// Native545D50/545B95/C6A140, bounded consumed AITNGuardInnerState view.
#include "../Common/StateMachine.h"
struct TunnelNetworkExitConditions {
 const void *m_vptr; //Existing raw view of tableC6A13C; no lifetime/provider claim.
 unsigned int m_attackGiveUpFrame;
};
class AITNGuardInnerState : public State {
public:
 AITNGuardInnerState(StateMachine *);
 virtual StateReturnType onEnter(); //4
 virtual void onExit(StateExitType); //5
 virtual StateReturnType update(); //6, existing owned provider
protected:
 virtual void loadPostProcess(); //1, native forwarder; declaration only
 virtual const char *GetSnapshotName() const; //2, native getter; declaration only
 virtual void xfer(Xfer *); //3
private:
 TunnelNetworkExitConditions m_exitConditions; //20
 bool m_scanForEnemy; //28
 void *m_attackState; //2C, native allocation30
};
