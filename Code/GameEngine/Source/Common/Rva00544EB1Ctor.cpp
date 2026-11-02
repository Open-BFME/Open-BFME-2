// cl: /MD
// ??0Rva00544EB1@@QAE@PAVStateMachine@@@Z, retail 0x00544EB1, 29 bytes.
// Derived AIInternalMoveToState ctor via pinned base ctor 0x0033F279 with hash
// 0x29E75AEF then vtable 0x00C69E08. Evidence: vtable store at [this]; base
// AIInternalMoveToState ctor pin; caller 0x00544F16; prev 0x00544E3B same dir.
class StateMachine;

#include "../../Include/GameLogic/AIInternalMoveToState.h"

// The retail table at RVA 0x00869E08: 18 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?Rva00544ECEGet@@YAHXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?onEnter@Rva00544EB1@@UAE?AW4StateReturnType@@XZ")();
void __identifier("?onExit@AIMoveToState@@UAEXW4StateExitType@@@Z")();
void __identifier("?rva00349D8D@Rva00349D8D@@QAEXXZ")();
void __identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?computePath@AIInternalMoveToState@@MAE_NXZ")();
}
extern const void *const g_00C69E08[18] = {
	(const void *)&__identifier("??_GAIFollowWaypointPathExactState@@UAEPAXI@Z"), // slot 0 0x00346CFB
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?Rva00544ECEGet@@YAHXZ"), // slot 2 0x00544ECE
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 3 0x0047A69C
	(const void *)&__identifier("?onEnter@Rva00544EB1@@UAE?AW4StateReturnType@@XZ"), // slot 4 0x00544C62
	(const void *)&__identifier("?onExit@AIMoveToState@@UAEXW4StateExitType@@@Z"), // slot 5 0x0034BA5F
	(const void *)&__identifier("?rva00349D8D@Rva00349D8D@@QAEXXZ"), // slot 6 0x00349D8D
	(const void *)&__identifier("?disable@Rva0033F2D7ByteSetter@@QAEXXZ"), // slot 7 0x0033F2D7
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 8 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 9 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 10 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 11 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 12 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 13 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 14 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 15 0x0047A699
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 16 0x000B3FD0
	(const void *)&__identifier("?computePath@AIInternalMoveToState@@MAE_NXZ"), // slot 17 0x003441F7
};

class Rva00544EB1 : public AIInternalMoveToState
{
public:
	Rva00544EB1(StateMachine *machine);
};

Rva00544EB1::Rva00544EB1(StateMachine *machine) : AIInternalMoveToState(machine, 0x29E75AEFu)
{
	*(const void **)this = g_00C69E08;
}
