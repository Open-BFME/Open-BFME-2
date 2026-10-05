// cl: /O1 /MD /DNDEBUG
//
// ?requestPath@AIUpdateInterface@@QAEXPAUCoord3D@@_N@Z
// retail 0x0026893F, 248 bytes (Ghidra FUN_0066893f).
//
// Donor: GeneralsMD AIUpdate.cpp AIUpdateInterface::requestPath. BFME 2
// differences, all read off the body: an immobile unit (no valid locomotor
// surfaces, +0x1DC) returns at once instead of asserting; the old and new
// destinations go to the "CritterDesync: requestPath1" log (the debug flag
// and FILE globals the AIWanderStateMethods.cpp logs use); the victim ID is
// reset before the flags; the repath guard compares against frame - 2 and
// only reschedules (no blocked-and-stuck reset); m_waitingForPath is set on
// the queueForPath path only. Layout: destination +0x148, victim +0x144,
// timestamp +0x160, flags +0x3B1..+0x3B5.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;
};

struct FprintfTarget
{
	char m_pad[4];
};
extern "C" void fprintf(FprintfTarget *target, const char *format, ...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;

extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
private:
	char m_pad00[0x74];
	ObjectID m_id;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

class Pathfinder
{
public:
	void queueForPath(ObjectID id);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern AI *TheAI;

class AIUpdateInterface
{
public:
	void requestPath(Coord3D *destination, Bool isFinalGoal);
	Bool canComputeQuickPath();
	void computeQuickPath(const Coord3D *destination);
	void setQueueForPathTime(Int frames);

private:
	Object *getObject() const { return m_object; }

	void *m_vtable;
	char m_pad04[0x08 - 0x04];
	Object *m_object;
	char m_pad0C[0x144 - 0x0C];
	ObjectID m_requestedVictimID;
	Coord3D m_requestedDestination;
	char m_pad154[0x160 - 0x154];
	UnsignedInt m_pathTimestamp;
	char m_pad164[0x1DC - 0x164];
	Int m_validLocomotorSurfaces;
	char m_pad1E0[0x3B1 - 0x1E0];
	Bool m_waitingForPath;
	Bool m_isAttackPath;
	Bool m_isFinalGoal;
	Bool m_isApproachPath;
	Bool m_isSafePath;
};

void AIUpdateInterface::requestPath( Coord3D *destination, Bool isFinalGoal )
{
	if (m_validLocomotorSurfaces == 0)
		return;

	if (g_00E03745)
	{
		FprintfTarget *log = (FprintfTarget *)g_00DFEFF0;
		if (log)
			fprintf(log, "CritterDesync: requestPath1-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
				m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
				destination->x, destination->y, destination->z);
	}

	m_requestedDestination = *destination;
	m_requestedVictimID = INVALID_ID;
	m_isFinalGoal = isFinalGoal;
	m_isAttackPath = false;
	m_isApproachPath = false;
	m_isSafePath = false;
	if (canComputeQuickPath()) {
		computeQuickPath(destination);
		return;
	}
	if (m_pathTimestamp > TheGameLogic->getFrame() - 2) {
		/* Requesting path very quickly.  Can cause a spin. */
		setQueueForPathTime(LogicFramesPerSecond);
		return;
	}
	m_waitingForPath = true;
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}
