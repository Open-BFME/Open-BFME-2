// cl: /DNDEBUG /MD
//
// Retail RE: ?ownerRva004A6D15@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
// @0x004A6D15 (35B).
//
// BFME2 SupplyTruck state-machine condition, sibling of landed
// ?ownerDocking@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z @0x004A6CF2 (35B),
// ?ownerIdle@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z @0x004A6D38 (37B),
// ?ownerAvailableForSupplying@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
// @0x004A6D5D (68B) and
// ?ownerNotDockingOrIdle@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
// @0x004A6DA1 (67B).
// Pattern reuses the PROVEN landing TU (SupplyTruckOwnerDocking.cpp) VERBATIM:
// TU-scoped minimal classes at retail offsets + direct member chain + direct
// getCurrentStateID call + cmp/sete tail. Retail differs from docking in exactly
// two bytes: the REL32 (call-site shift) and the cmp immediate (0x2F vs 0x0E).
//
// Target facts from retail bytes (game.dat PE section parse, struct-verified,
// independent of donor):
// - Boundary 0x004A6D15..0x004A6D38 35B: prev landed docking 0x004A6CF2+35 ends
//   exactly 0x004A6D15; next rowed idle starts exactly 0x004A6D38
//   (0x004A6D15+35). File offsets 0x4a62f2/0x4a6315/0x4a6338 (+0x23 steps).
// - Bytes: 8B442404 8B4018 8B4014 8B8858020000 85C9 7503 32C0 C3
//   E892C2DBFF(=call 0x00262FC3) 83F82F 0F94C0 C3.
//   Chain State+0x18 / Machine+0x14 / Object+0x258 (same three offsets the
//   landed siblings proved exact); null-guard returns false; tail is a DIRECT
//   call + cmp eax,0x2F + sete al.
// - Callee 0x00262FC3 is rowed ?getCurrentStateID@AIUpdateInterface@@QBEHXZ
//   (40B, matched). Struct decode: E8 site 0x004A6D2C, REL32 -2375022 ->
//   0x00262FC3, same target as docking's E8 (REL diff 0x23 = call-site shift).
//   Spelling here calls getCurrentStateID directly so the E8 resolves through
//   the matched row with no symbols.csv pin (pins are candidates, not proof).
// - ABI: static Bool(State*,void*) matches retail stack-arg prologue 8B442404
//   + bool sete tail; native StateConditionInfo callback shape, same as the
//   four table-referenced siblings. No specific table slot is claimed for this
//   body (see naming note).
//
// Naming (address-derived, no invented semantics): state 47 (0x2F) has no proven
// BFME2 AI-state name (BFME2 AI enum is renumbered/extended vs ZH, whose
// NUM_AI_STATES ends near 44; 47 is outside it). The cmp constant is kept as a
// raw 0x2F literal; the function name embeds the RVA only. Lead-only context,
// NOT identity evidence: BFME1 donor
// reference/open-bfme-1/game/.../WorkerStateMachineSupplyPredicate.cpp notes a
// "second supply state" 47 accepted alongside AI_DOCK in a Worker predicate -
// different class (WorkerStateMachine), different body shape (3-way OR), so it
// names nothing here. Home-TU SupplyTruckAIUpdate.cpp (ZH-verbatim, 7
// conditions) lists no 47-predicate; retail tables were not located as stored
// pointers in game.dat (zero hits for all seven family RVAs either absolute or
// image-relative), so no table slot is cited as proof. The SupplyTruckStateMachine
// class claim rests on cluster contiguity + identical chain/offsets/ABI/callee
// with the four table-proven siblings, not on bytes alone.
// Donor-carried only: family name/shape/role pattern from ZH GeneralsMD
// SupplyTruckAIUpdate + BFME1 game tree + landed BFME2 siblings @6583b3c1;
// offsets/call target/constant read off retail. No shared-header edits;
// TU-scoped views only. Code/gen_asm never touched.

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

class SupplyTruckStateMachine
{
public:
	static bool ownerRva004A6D15(State *thisState, void *userData);
};

// ?ownerRva004A6D15@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
// Address-derived placeholder: returns true iff the owner's AI state ID is
// retail-observed 0x2F (47). No BFME2 state name is claimed for 47.
bool SupplyTruckStateMachine::ownerRva004A6D15(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return false;
	if (ai->getCurrentStateID() == 0x2F)
		return true;
	return false;
}
