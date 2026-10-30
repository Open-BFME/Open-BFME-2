// cl: /O1 /MD /arch:SSE /Oy- /Op
// platformsdk
// Retail 0x0036A88A, 239 bytes. The target guard-state owner is not named;
// Rva0036A88AOwner remains an address-derived view. Target fields +0x3C/+0x40
// and calls are supported by retail accesses and REL32 sites; no donor name is
// asserted. Coordinate ordering uses the byte-matched sibling barrier pattern.

//
// ?update@Rva0036A88AOwner@@QAEHXZ @0x0036A88A 239B
// Guard-state tick on the +0x18 machine: when TheGameLogic's frame passes
// +0x24, refresh it from the AI interval (TheAI+0x18 then +0x44) plus the
// frame and return -2 when the machine's lookForInnerTarget scan succeeds.
// Otherwise resolve the machine's target/team ids into a target Coord3D
// (object +0x38 copy, or the team centre when the object is null and an
// early rva0036914D return when the team is null too), compare the
// +0x28-to-target distance against 10.0f (BfmeGlobalBC2428): above it copy
// the target into +0x28, set the machine goal there, call rva00369217(0)
// and return rva00369064(); at or below it return rva0036914D().
// Same +0x3C/+0x40 id pair and own-machine scan (0x00369FDF) as the landed
// 0x0036A979 idle-state update; owner identity unproven so the owner and
// its three same-this callees now bind the independently rowed normal-flight
// methods at the retail REL32 destinations. The machine view flattens the proven
// AIGuardMachine +0x3C/+0x40 id pair.

typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt TeamID;

#include <windows.h>
#include "../../Common/GameLogicObjectLookupView.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};


extern GameLogic *TheGameLogic;

#include "../../../Include/Common/TeamBFME2.h"

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;

struct TAiData
{
	unsigned char m_pad00[0x44];
	int m_guardEnemyReturnScanRate; // +0x44 update interval in frames
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};

extern AI *TheAI;
// BfmeGlobalBC2428 was the retail address alias (RVA 0x007C2428) of the constant 10.0f; the literal is the source.

class Rva00369FDFGuardMachine
{
public:
	bool lookForInnerTarget();

	char m_pad00[0x3C];
	ObjectID m_targetToGuard; // +0x3C
	TeamID m_teamToGuard; // +0x40
};

class StateMachine
{
public:
	void setGoalPosition(const Coord3D *pos);
};

enum StateExitType
{
	EXIT_NORMAL = 0
};
enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

// Declaration-only call view of the rowed providers. Explicit qualification
// preserves retail's direct calls; no virtual slot or owner layout is inferred.
class GiantBirdNormalFlightState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType status);
	virtual StateReturnType update();
};

class Rva0036A88AOwner
{
public:
	int update();

private:
	char m_pad00[0x18];
	Rva00369FDFGuardMachine *m_machine; // +0x18
	char m_pad1C[0x8]; // +0x1C..0x24
	UnsignedInt m_nextFrame; // +0x24
	Coord3D m_pos; // +0x28
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// Native direct destinations: onExit 0x00369217, onEnter 0x00369064,
// update 0x0036914D; all use this unchanged.
int Rva0036A88AOwner::update()
{
	UnsignedInt frame = TheGameLogic->getFrame();
	if (frame >= m_nextFrame) {
		m_nextFrame = TheAI->m_aiData->m_guardEnemyReturnScanRate + frame;
		if (m_machine->lookForInnerTarget())
			return -2;
	}
	const Rva00369FDFGuardMachine *machine = m_machine;
	Object *obj = TheGameLogic->findObjectByID(machine->m_targetToGuard);
	Coord3D target;
	if (obj != NULL) {
		target = *obj->getPosition();
	} else {
		Team *team = TheTeamFactory->findTeamByID(machine->m_teamToGuard);
		if (team == NULL)
			return ((GiantBirdNormalFlightState *)this)->GiantBirdNormalFlightState::update();
		team->rva0039E5B9(&target);
	}
	const Coord3D *position = &m_pos;
	Real dx = position->x;
	Real dy = position->y;
	Real dz = position->z;
	_ReadWriteBarrier();
	dx -= target.x;
	dy -= target.y;
	dz -= target.z;
	_ReadWriteBarrier();
	Coord3D delta;
	delta.x = dx;
	delta.y = dy;
	delta.z = dz;
	if (delta.GetLengthEstimate() > 10.0f) {
		m_pos = target;
		((StateMachine *)m_machine)->setGoalPosition(&m_pos);
		((GiantBirdNormalFlightState *)this)->GiantBirdNormalFlightState::onExit(EXIT_NORMAL);
		return ((GiantBirdNormalFlightState *)this)->GiantBirdNormalFlightState::onEnter();
	}
	return ((GiantBirdNormalFlightState *)this)->GiantBirdNormalFlightState::update();
}
