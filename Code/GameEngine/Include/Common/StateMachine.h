#pragma once
// BFME2 consumed State surface. Native4D73FC gives20hex-byte data and C605D8 gives17slots.
// StateMachine is intentionally forward-declared; this does not reconstruct that class.
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_STATE_RESTORE_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#ifdef BFME_STATE_RESTORE_NAME_SLOT
#undef BFME_SNAPSHOT_NAME_SLOT
#undef BFME_STATE_RESTORE_NAME_SLOT
#endif
class StateMachine;
typedef unsigned int StateID;
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
enum StateExitType { EXIT_NORMAL=0, EXIT_RESET=1 };
class State : public Snapshot {
public:
 State(StateMachine *,unsigned int);
 virtual ~State();
 virtual StateReturnType onEnter(); //4
 virtual void onExit(StateExitType); //5
 virtual StateReturnType update()=0; //6
protected:
 virtual void loadPostProcess(); //1
 virtual const char *GetSnapshotName() const=0; //2
 virtual void xfer(Xfer *)=0; //3
private:
 // Target-bounded positions only; no callable signatures/providers admitted.
 virtual void _bfme_state_slot7();
 virtual void _bfme_state_slot8();
 virtual void _bfme_state_slot9();
 virtual void _bfme_state_slot10();
 virtual void _bfme_state_slot11();
 virtual void _bfme_state_slot12();
 virtual void _bfme_state_slot13();
 virtual void _bfme_state_slot14();
 virtual void _bfme_state_slot15();
 virtual void _bfme_state_slot16();
public:
 int m_id; //4
 int m_successStateID; //8
 int m_failureStateID; //C
 void *m_transitionsFirst; //10
 void *m_transitionsLast; //14
 StateMachine *m_machine; //18
 bool m_tail1C; //1C, native ctor stores zero; rounded extent20
};
