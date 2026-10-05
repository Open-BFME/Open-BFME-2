// ?rva0036A88A@Rva0036A88AOwner@@QAEHXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /MD /arch:SSE
//
// ?rva0036A88A@Rva0036A88AOwner@@QAEHXZ @0x0036A88A 239B
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
// its three opaque same-this callees carry address-derived names with pins
// read from the retail REL32 sites. The machine view flattens the proven
// AIGuardMachine +0x3C/+0x40 id pair.

typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt TeamID;
#define NULL 0

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(Real _x, Real _y, Real _z) { x = _x; y = _y; z = _z; }
	Real GetLengthEstimate() const;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};

extern GameLogic *TheGameLogic;

class Team
{
public:
	void rva0039E5B9(Coord3D *pos);
};

class TeamFactory
{
public:
	Team *findTeamByID(TeamID id);
};

extern TeamFactory *TheTeamFactory;

struct TAiData
{
	unsigned char m_pad00[0x44];
	int m_44; // +0x44 update interval in frames
};

class AI
{
public:
	char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};

extern AI *TheAI;
extern Real BfmeGlobalBC2428;

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

class Rva0036A88AOwner
{
public:
	int rva0036A88A();
	void rva00369217(int status);
	int rva00369064();
	int rva0036914D();

private:
	char m_pad00[0x18];
	Rva00369FDFGuardMachine *m_machine; // +0x18
	char m_pad1C[0x8]; // +0x1C..0x24
	UnsignedInt m_nextFrame; // +0x24
	Coord3D m_pos; // +0x28
};

// ?rva00369217@Rva0036A88AOwner@@QAEXH@Z pins 0x00369217 (rowed as
// GiantBirdNormalFlightState::onExit; same address, direct call here).
// ?rva00369064@Rva0036A88AOwner@@QAEHXZ pins 0x00369064.
// ?rva0036914D@Rva0036A88AOwner@@QAEHXZ pins 0x0036914D.
int Rva0036A88AOwner::rva0036A88A()
{
	UnsignedInt frame = TheGameLogic->m_frame;
	if (frame >= m_nextFrame) {
		m_nextFrame = TheAI->m_aiData->m_44 + frame;
		if (m_machine->lookForInnerTarget())
			return -2;
	}
	Rva00369FDFGuardMachine *machine = m_machine;
	Object *obj = TheGameLogic->findObjectByID(machine->m_targetToGuard);
	Coord3D target;
	if (obj != NULL) {
		target = *obj->getPosition();
	} else {
		Team *team = TheTeamFactory->findTeamByID(machine->m_teamToGuard);
		if (team == NULL)
			return rva0036914D();
		team->rva0039E5B9(&target);
	}
	Real dx = m_pos.x - target.x;
	Real dy = m_pos.y - target.y;
	Real dz = m_pos.z - target.z;
	Coord3D delta(dx, dy, dz);
	if (delta.GetLengthEstimate() > BfmeGlobalBC2428) {
		m_pos = target;
		((StateMachine *)m_machine)->setGoalPosition(&m_pos);
		rva00369217(0);
		return rva00369064();
	}
	return rva0036914D();
}
