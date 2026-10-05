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

enum LocomotorSurfaceType
{
	LOCOMOTORSURFACE_AIR = 8
};

class AIUpdateInterface
{
public:
	// Vtable slots before isDoingGroundMovement (byte offset 0x224); their
	// identities do not matter to the bodies here.
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual void vslot050();
	virtual void vslot051();
	virtual void vslot052();
	virtual void vslot053();
	virtual void vslot054();
	virtual void vslot055();
	virtual void vslot056();
	virtual void vslot057();
	virtual void vslot058();
	virtual void vslot059();
	virtual void vslot060();
	virtual void vslot061();
	virtual void vslot062();
	virtual void vslot063();
	virtual void vslot064();
	virtual void vslot065();
	virtual void vslot066();
	virtual void vslot067();
	virtual void vslot068();
	virtual void vslot069();
	virtual void vslot070();
	virtual void vslot071();
	virtual void vslot072();
	virtual void vslot073();
	virtual void vslot074();
	virtual void vslot075();
	virtual void vslot076();
	virtual void vslot077();
	virtual void vslot078();
	virtual void vslot079();
	virtual void vslot080();
	virtual void vslot081();
	virtual void vslot082();
	virtual void vslot083();
	virtual void vslot084();
	virtual void vslot085();
	virtual void vslot086();
	virtual void vslot087();
	virtual void vslot088();
	virtual void vslot089();
	virtual void vslot090();
	virtual void vslot091();
	virtual void vslot092();
	virtual void vslot093();
	virtual void vslot094();
	virtual void vslot095();
	virtual void vslot096();
	virtual void vslot097();
	virtual void vslot098();
	virtual void vslot099();
	virtual void vslot100();
	virtual void vslot101();
	virtual void vslot102();
	virtual void vslot103();
	virtual void vslot104();
	virtual void vslot105();
	virtual void vslot106();
	virtual void vslot107();
	virtual void vslot108();
	virtual void vslot109();
	virtual void vslot110();
	virtual void vslot111();
	virtual void vslot112();
	virtual void vslot113();
	virtual void vslot114();
	virtual void vslot115();
	virtual void vslot116();
	virtual void vslot117();
	virtual void vslot118();
	virtual void vslot119();
	virtual void vslot120();
	virtual void vslot121();
	virtual void vslot122();
	virtual void vslot123();
	virtual void vslot124();
	virtual void vslot125();
	virtual void vslot126();
	virtual void vslot127();
	virtual void vslot128();
	virtual void vslot129();
	virtual void vslot130();
	virtual void vslot131();
	virtual void vslot132();
	virtual void vslot133();
	virtual void vslot134();
	virtual void vslot135();
	virtual void vslot136();
	virtual Bool isDoingGroundMovement() const;

	void requestPath(Coord3D *destination, Bool isFinalGoal);
	Bool canComputeQuickPath();
	void computeQuickPath(const Coord3D *destination);
	void setQueueForPathTime(Int frames);

private:
	Object *getObject() const { return m_object; }

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

// ?canComputeQuickPath@AIUpdateInterface@@QAE_NXZ @0x00262A64 38B (Ghidra
// FUN_00662a64), pinned from requestPath's call: Zero Hour's body unchanged,
// isDoingGroundMovement at vtable byte offset 0x224.
Bool AIUpdateInterface::canComputeQuickPath( void )
{
	/* Basically, if a unit is moving through the air, we can quick path.  jba. */
	Bool landBound = false;
	if (!(m_validLocomotorSurfaces & LOCOMOTORSURFACE_AIR))
	{
		landBound = true;
	}

	Bool unitIsFlyingThroughTheAir = false;
	if (landBound) {
		unitIsFlyingThroughTheAir = false; // Land bound units never fly.
	}	else {
		if (!isDoingGroundMovement()) {
			// If it can fly, and it isn't moving on the ground, we're flying.
			unitIsFlyingThroughTheAir = true;
		}
	}
	return unitIsFlyingThroughTheAir;
}
