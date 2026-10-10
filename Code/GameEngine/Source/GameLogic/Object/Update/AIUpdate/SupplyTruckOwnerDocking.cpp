// cl: /DNDEBUG /MD
//
// Retail RE: ?ownerDocking@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z @0x004A6CF2 (35B).
//
// BFME2 SupplyTruck state-machine condition, sibling of landed
// ?ownerIdle@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z @0x004A6D38 (37B).
// Pattern reuses the PROVEN landing TU (SupplyTruckOwnerIdle.cpp): TU-scoped
// minimal classes at retail offsets + direct member chain. That TU's 16B
// prologue (8B442404/8B4018/8B4014/8B8858020000/85C9) is byte-identical to
// this body's 16B prologue, so the same spelling should give the same EAX
// chain (single-expression/named-local/flag levers all refuted on the old TU,
// r13/r16/r18; this is a new TU, not a repeat).
//
// Target facts from retail bytes (PE section parse of game.dat, independent
// of donor; boundary prev-ret-0x004A6CF1 / next-prologue-0x004A6D15):
// - Boundary 0x004A6CF2..0x004A6D15 35B.
// - Bytes: 8B442404 8B4018 8B4014 8B8858020000 85C9 7503 32C0 C3
//   E8B5C2DBFF(=call 0x00262FC3) 83F80E 0F94C0 C3.
//   Chain State+0x18 / Machine+0x14 / Object+0x258 (r18 proved exact;
//   Object+0x258 AI slot corroborated by rowed Rva004884B7Check,
//   BattlePlanUpdate_isTurretInNaturalPosition, TeamDidPartialEnter);
//   null-guard returns false; tail is a DIRECT call + cmp eax,0xE + sete al.
// - Callee 0x00262FC3 is rowed ?getCurrentStateID@AIUpdateInterface@@QBEHXZ
//   (40B, AIUpdateInterface_getCurrentStateID.cpp, matched). Spelling here
//   calls getCurrentStateID directly so the E8 resolves through the matched
//   row with no symbols.csv pin (pins are candidates, not proof).
// - getCurrentStateID-vs-getAIStateType equivalence (why the respell keeps
//   donor semantics): ZH AIUpdate.h:375 declares getAIStateType out-of-line
//   and :635 defines getCurrentStateID inline via getStateMachine()->
//   getCurrentStateID; BFME1 game AIUpdate.cpp:5918-5924 defines
//   getAIStateType() as `(AIStateType)machine->getCurrentStateID()`; BFME2
//   AIUpdate.cpp:4200 keeps the same wrapper shape
//   `return (AIStateType)getStateMachine()->getCurrentStateID();`
//   (present-unmatched). AI_DOCK=14 (AIStateMachine.h AI_IDLE=0..AI_DEAD=13,
//   AI_DOCK=14) matches retail cmp eax,0xE. Same receiver ABI either way
//   (const thiscall ECX=this, EAX=int), so the respell is semantics-preserving
//   (coverage-first escalation step 2) and directly targets retail's call.
// Donor-carried only: reference/open-bfme-1 rev 6583b3c1 ZH GeneralsMD
// SupplyTruckAIUpdate.cpp:730 ownerDocking (same name/shape/role: machine
// owner + AI null-guard + AI_DOCK compare); BFME2 offsets read off retail.
// No shared-header edits; TU-scoped views only.

class Object;
class StateMachine;
class AIUpdateInterface;

struct State
{
public:
	char m_pad[0x18];
	StateMachine *m_machine; // +0x18
};

class StateMachine
{
public:
	char m_pad[0x14];
	Object *m_owner; // +0x14
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class AIUpdateInterface
{
public:
	int getCurrentStateID() const;
};

enum { AI_DOCK = 14 };

class SupplyTruckStateMachine
{
public:
	static bool ownerDocking(State *thisState, void *userData);
};

// ?ownerDocking@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
bool SupplyTruckStateMachine::ownerDocking(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return false;
	if (ai->getCurrentStateID() == AI_DOCK)
		return true;
	return false;
}
