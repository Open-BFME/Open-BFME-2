// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?requestSafePath@AIUpdateInterface@@QAEXW4ObjectID@@@Z
// retail 0x00263EA2, 261 bytes.
//
// BFME1 donor game/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// AIUpdateInterface::requestSafePath. Retail differences read off the body:
// repulsor current +0x18c prev +0x190, victim +0x144 cleared final +0x3B3
// attack +0x3B2 approach +0x3B4 safe +0x3B5, repath guard frame-2 via
// TheGameLogic+0x40, quick path uses setQueueForPathTime 2x g_Va00DBA4E4
// plus destroyPath, else waitingForPath +0x3B1 plus CritterDesync logs via
// g_00E03745 plus theLogicRandomLogFile with _fprintf row 0x002CEC42,
// destination +0x148 from object pos +0x38 plus g_Va009FF0F8 pathfinder
// queueForPath. Evidence: donor plus CritterDesync requestSafePath strings
// plus rowed callees 0x0026282A 0x00262A8A 0x002CEC42 0x002EBD31.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;
};

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

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
	const Coord3D &getPosition() const { return m_position; }
private:
	char m_pad00[0x38];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
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
	bool queueForPath(ObjectID id);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
};
extern class AI *TheAI;

class Path;

class AIUpdateInterface
{
public:
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
	virtual void setLocomotorGoalNone();

	void requestSafePath(ObjectID repulsor);
	void setQueueForPathTime(Int frames);
	void destroyPath();

private:
	Object *getObject() const { return m_object; }

	char m_pad04[0x08 - 0x04];
	Object *m_object;
	char m_pad0C[0x140 - 0x0C];
	Path *m_path;
	ObjectID m_requestedVictimID;
	Coord3D m_requestedDestination;
	char m_pad154[0x160 - 0x154];
	UnsignedInt m_pathTimestamp;
	char m_pad164[0x16C - 0x164];
	Int m_blockedAndStuck;
	char m_pad170[0x18C - 0x170];
	ObjectID m_repulsorID;
	ObjectID m_prevRepulsorID;
	char m_pad194[0x3B1 - 0x194];
	Bool m_waitingForPath;
	Bool m_isAttackPath;
	Bool m_isFinalGoal;
	Bool m_isApproachPath;
	Bool m_isSafePath;
};

void AIUpdateInterface::requestSafePath(ObjectID repulsor)
{
	if (repulsor != m_repulsorID)
		m_prevRepulsorID = m_repulsorID;
	m_repulsorID = repulsor;
	m_isFinalGoal = false;
	m_isAttackPath = false;
	m_requestedVictimID = INVALID_ID;
	m_isApproachPath = false;
	m_isSafePath = true;

	if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
	{
		setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
		destroyPath();
		return;
	}

	m_waitingForPath = true;
	if (g_00E03745)
	{
		void *log = theLogicRandomLogFile;
		if (log != 0)
		{
			fprintf(log, "CritterDesync: requestSafePath 'I don't believe this line accomplishes anything' ");
			void *log2 = theLogicRandomLogFile;
			if (log2 != 0)
				fprintf(log2, "-- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
					m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
					getObject()->getPosition().x, getObject()->getPosition().y, getObject()->getPosition().z);
		}
	}

	m_requestedDestination = getObject()->getPosition();
	TheAI->pathfinder()->queueForPath(getObject()->getID());
}
