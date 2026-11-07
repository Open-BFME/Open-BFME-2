#pragma once
// BFME2 consumed State surface. Native4D73FC gives20hex-byte data and C605D8 gives17slots.
// StateMachine is intentionally forward-declared; this does not reconstruct that class.
// Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class StateMachine;
class Object;
struct StateConditionInfo;
typedef unsigned int StateID;
enum StateReturnType { STATE_CONTINUE=0, STATE_SUCCESS=-1, STATE_FAILURE=-2 };
enum StateExitType { EXIT_NORMAL=0, EXIT_RESET=1 };
// Base slot bodies (target facts, table C605D8 installed by 4D73FC): slot 1
// and slots 7 and 16 are the shared bare RET 0B3FD0, slot 4 the shared
// `xor eax,eax; ret` 0D43D0 (STATE_CONTINUE), slot 5 the pinned RET 4
// 47A69C, slots 2, 3 and 6 __purecall, and slots 8-15 the shared
// `xor al,al; ret` 47A699 (false). The 103 State-shaped retail tables
// never override slot 1. The bodies below compile to those bytes, so a
// unit that emits a State-derived table defines the base slots it does not
// override as COMDATs instead of referencing names no unit provides.
// Slot 8 is isAttack: the rowed overrides AIAttackAreaState/AIGuardState/
// AIAttackState::isAttack (0x003422EF, 0x00341D81, 0x0034141F) sit in slot 8
// of their tables, and StateMachine::isInAttackState 0x002621B8 calls
// [eax+20h]. The other slots keep placeholder names: their callers and
// overrides are rowed only under address names or under conflicting views.
class State : public Snapshot {
public:
 State(StateMachine *,unsigned int);
 virtual ~State();
 virtual StateReturnType onEnter() { return STATE_CONTINUE; } //4
 virtual void onExit(StateExitType); //5
 virtual StateReturnType update()=0; //6
protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
 virtual void LoadPostProcess() {} //1
#else
 virtual void loadPostProcess() {} //1
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
 virtual const char *GetSnapshotName()=0; //2
#else
 virtual const char *GetSnapshotName() const=0; //2
#endif
#else
 virtual void crc(Xfer *)=0; //2
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer &)=0; //3
#else
 virtual void DoXfer(Xfer *)=0; //3
#endif
#else
 virtual void xfer(Xfer *)=0; //3
#endif
private:
 virtual void _bfme_state_slot7() {}
public:
 virtual bool isAttack() const { return false; } //8
private:
 virtual bool _bfme_state_slot9() const { return false; }
 virtual bool _bfme_state_slot10() const { return false; }
 virtual bool _bfme_state_slot11() const { return false; }
 virtual bool _bfme_state_slot12() const { return false; }
 virtual bool _bfme_state_slot13() const { return false; }
 virtual bool _bfme_state_slot14() const { return false; }
 virtual bool _bfme_state_slot15() const { return false; }
 virtual void _bfme_state_slot16() {}
public:
 // Zero Hour State accessors; retail inlines them (AIDockProcessDockState::
 // findMyDrone 0x00544B5B reads +0x18 then the machine's owner +0x14). The
 // two that need StateMachine are defined after it in StateMachineClass.h.
 StateMachine *getMachine() const { return m_machine; }
 Object *getMachineOwner() const;
 Object *getMachineGoalObject() const;
 // Existing native transition helpers, rowed in Common/StateMachine.cpp.
 void rva004D7127(const StateConditionInfo *conditions);
 StateReturnType friend_checkForTransitions(StateReturnType status);
 StateReturnType friend_checkForSleepTransitions(StateReturnType status);
 int m_id; //4
 int m_successStateID; //8
 int m_failureStateID; //C
 const StateConditionInfo *m_transitionsFirst; //10
 int m_transitionsLast; //14: native transition count, legacy spelling
 StateMachine *m_machine; //18
 bool m_tail1C; //1C, native ctor stores zero; rounded extent20
};
