// cl: /O1 /I. /arch:SSE /G7 /DNDEBUG /MD /EHsc
// platformsdk
//
// AttackPositionStateMachine::AttackPositionStateMachine, retail 0x3438c7: a
// BFME 2 state machine constructor. The name is a target fact: the vftable
// 0x00811C90 it installs (dtor 0x0033FBA6, deleting dtor 0x00343A6A in slot
// 0) has the name getter 0x0033FBB1 in slot 2, returning
// "AttackPositionStateMachine". The base
// is the rowed StateMachine constructor 0x004D79E1 with the caller's name key
// (its unsigned spelling is pinned); each state comes from plain operator
// new and its rowed constructor, registered with the IDs and transitions
// read from the retail call sequence (Zero Hour's defineState pattern).
#include <windows.h>
#include "Code/Libraries/Include/Lib/Coord3D.h"
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef UnsignedInt StateID;
typedef UnsignedInt ObjectID;
class Object;
#include "../../../Include/Common/StateConditionInfo.h"
class State
{
public:
	virtual ~State();
};
class StateMachine
{
public:
	StateMachine(Object *owner, UnsignedInt nameKey, Bool flag);
 virtual ~StateMachine();
	void defineState(StateID id, State *state, StateID successID, StateID failureID, const StateConditionInfo *conditions = NULL);
protected:
	unsigned char m_pad04[0x3C - 0x04];
};
class Rva0033F3EF : public State
{
public:
	Rva0033F3EF(StateMachine *machine);
private:
	unsigned char m_pad04[0x24 - 0x04];
};
class Rva0033F4B1 : public State
{
public:
	Rva0033F4B1(StateMachine *machine, int a0);
private:
	unsigned char m_pad04[0x28 - 0x04];
};
class Rva0033F43D : public State
{
public:
	Rva0033F43D(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva004D7491 : public State
{
public:
	Rva004D7491(StateMachine *machine);
private:
	unsigned char m_pad04[0x20 - 0x04];
};
// The host passed in: its +0x20 base is what the 0x0033F4B1 state gets.
class Rva003438C7HostHead
{
public:
	virtual void v00();
	unsigned char m_pad04[0x20 - 0x04];
};
class Rva003438C7HostInterface
{
public:
	virtual void v00();
};
class Rva003438C7Host : public Rva003438C7HostHead, public Rva003438C7HostInterface
{
};
class Rva004D74AC : public State { public: Rva004D74AC(StateMachine*); private: char pad[0x20-4]; };
class AIAttackApproachTargetState00C12678 : public State { public: AIAttackApproachTargetState00C12678(StateMachine*); private: char pad[0x64-4]; };
struct AttackKindPrefixView { char before108[0x108]; unsigned char kind108; char gap[6]; unsigned char kind10F; };
struct AttackOwnerPrefixView { char first[4]; AttackKindPrefixView *thing; };
class AttackPositionStateMachine : public StateMachine
{
public:
	AttackPositionStateMachine(Object *owner, Rva003438C7Host *host, UnsignedInt nameKey);
	virtual ~AttackPositionStateMachine();

};
// condition 0x0033FD98 (retail .rdata table entry)
class Rva00343F8A;
Bool rva0033FD98(Rva00343F8A *thisState, void *userData);
Bool rva0033FDD6(Rva00343F8A *thisState, void *userData);

AttackPositionStateMachine::AttackPositionStateMachine(Object *owner, Rva003438C7Host *host, UnsignedInt nameKey) : StateMachine(owner, nameKey, false)
{
	static const StateConditionInfo positionConditions[] =
	{
		{ (bool (*)(State *, void *))rva0033FD98, 600, NULL },
		{ NULL, 0, NULL }	// keep last
	};

	// order matters: first state is the default state.
	defineState( 601, new Rva0033F3EF( this ), 602, 9999, positionConditions );
	defineState( 602, new Rva0033F4B1( this, (int)static_cast<Rva003438C7HostInterface *>(host) ), 603, 600, positionConditions );
	defineState( 603, new Rva0033F43D( this ), 601, 9999 );
    static const StateConditionInfo portableConditions[] = { {(bool (*)(State *, void *))rva0033FDD6,601,0}, {0,0,0} };
    AttackKindPrefixView *thing=reinterpret_cast<AttackOwnerPrefixView*>(owner)->thing;
    if(((this?reinterpret_cast<AttackOwnerPrefixView*>(owner)->thing:reinterpret_cast<AttackOwnerPrefixView*>(owner)->thing)->kind108 & 4)==0) {
        if((thing->kind10F & 2) && ((this?reinterpret_cast<AttackOwnerPrefixView*>(owner)->thing:reinterpret_cast<AttackOwnerPrefixView*>(owner)->thing)->kind108 & 8))
            defineState(600,new Rva004D74AC(this),9999,9999,portableConditions);
        else
            defineState(600,new AIAttackApproachTargetState00C12678(this),601,9999);
    } else defineState(600,new Rva004D7491(this),9999,9999);
}

// The destructor restores vtable 0x00811C90 and tail-calls the base; slot 0
// of that vtable is the deleting destructor 0x00343A6A.
AttackPositionStateMachine::~AttackPositionStateMachine()
{
}
