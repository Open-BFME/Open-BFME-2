// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?update@SiegeDeployHordeSpecialPower@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x004C64EE (154 bytes): slot 9 of the +0x10 update table 0x0085DD64 just
// before SiegeDeployHordeSpecialPower's primary vtable 0x0085DD94, so `this`
// is the module +0x10 (Object at -8). The horde marches its siege engine to
// the deploy target (ObjectID +0x38, rowed xfer): nothing more once the AI
// is gone or its last command came from the player (AI slot +0x23C); a dead
// or missing target idles the AI. A target without status 0x3B is handed to
// the AI command 0x00352ECA each frame; with it, once a logic second has
// passed (+0x48 counter, BfmeLogicFramesPerSecond frames) the AI idles and moves to the
// stored deploy position (+0x3C, set by slot 14 0x004C63DE). Storage view: no
// constructor or destructor, no vtable emitted.
#include "../../../Common/GameLogicObjectLookupView.h"

typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 2
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_3B = 0x3B
};

struct Coord3D;
extern int BfmeLogicFramesPerSecond;	// logic frames per second
extern GameLogic *TheGameLogic;

class Object;

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToObject(Object *target, CommandSourceType cmdSource);
	void rva0045003E(int value, CommandSourceType cmdSource);
};

class SiegeDeployHordeAIView
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual void s016();
	virtual void s017();
	virtual void s018();
	virtual void s019();
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual CommandSourceType getLastCommandSource();	// +0x23C
	unsigned char m_pad04[0x20 - 0x04];
	AICommandInterface m_command;			// +0x20
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	SiegeDeployHordeAIView *getAI() { return m_ai; }
	unsigned char m_pad000[0x258];
	SiegeDeployHordeAIView *m_ai;		// +0x258
	unsigned char m_pad25C[0x438 - 0x25C];
	unsigned char m_privateStatus;		// +0x438
};

class SiegeDeployHordePrimary
{
public:
	virtual ~SiegeDeployHordePrimary();
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class SiegeDeployHordeIface0C
{
public:
	virtual void f0C();
};
class SiegeDeployHordeUpdateIface
{
public:
	virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3();
	virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7();
	virtual void u8();
	virtual UpdateSleepTime update() = 0;	// slot 9
};

class SiegeDeployHordeSpecialPower : public SiegeDeployHordePrimary, public SiegeDeployHordeIface0C, public SiegeDeployHordeUpdateIface
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned char m_pad14[0x38 - 0x14];
	ObjectID m_targetID;		// +0x38
	unsigned char m_pos[12];	// +0x3C, the deploy position
	int m_counter;			// +0x48
};

UpdateSleepTime SiegeDeployHordeSpecialPower::update()
{
	Object *target = TheGameLogic->findObjectByID(m_targetID);
	SiegeDeployHordeAIView *ai = m_object->getAI();
	if (ai && ai->getLastCommandSource() != CMD_FROM_PLAYER)
	{
		if (target && !(target->m_privateStatus & 1))
		{
			if (target->testStatus(OBJECT_STATUS_3B))
			{
				if (++m_counter < BfmeLogicFramesPerSecond)
					return UPDATE_SLEEP_NONE;
				m_counter = 0;
				ai->m_command.aiIdle(CMD_FROM_AI);
				ai->m_command.aiMoveToPosition((const Coord3D *)m_pos, CMD_FROM_AI);
			}
			else
			{
				((AICommandInterface *)&ai->m_command)->aiMoveToObject((Object *)target, CMD_FROM_AI);
				return UPDATE_SLEEP_NONE;
			}
		}
		else
		{
			ai->m_command.aiIdle(CMD_FROM_AI);
		}
	}
	return UPDATE_SLEEP_FOREVER;
}
