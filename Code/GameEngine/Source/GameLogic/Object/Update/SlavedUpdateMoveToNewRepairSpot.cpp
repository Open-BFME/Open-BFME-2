// cl: /DNDEBUG /MD
//
// ?moveToNewRepairSpot@SlavedUpdate@@QAEXXZ @0x004A2144 276B
// Identity: SlavedUpdate::moveToNewRepairSpot from ZH SlavedUpdate.cpp,
// BFME2 deltas read from retail bytes (repairRange wander with Real random
// 0..2*PI at line 828, altitude from repairMin/Max at line 833, PANIC
// locomotor set with ultra-accurate + precise-Z, move via rowed
// AICommandInterface aiMoveToPosition). Neighbours 0x004A1C10 endRepair and
// 0x004A2258 caller in same SlavedUpdate block; module-data offsets from
// SlavedUpdateModuleDataCtor (repairRange +0x28, min +0x2C, max +0x30);
// Object position +0x38 and AI +0x258; AI curLocomotor +0x1F0 and
// chooseLocomotorSet slot 142; TerrainLogic getGroundHeight slot 6.
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

enum ObjectID
{
	INVALID_ID = 0
};

enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED = 1,
	LOCOMOTORSET_FREEFALL = 2,
	LOCOMOTORSET_WANDER = 3,
	LOCOMOTORSET_PANIC = 4
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object;
class AIUpdateInterface;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Int unused);
};
extern TerrainLogic *TheTerrainLogic;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
float Cos(float value);
float Sin(float value);

class Locomotor
{
public:
	enum LocoFlag
	{
		PRECISE_Z_POS = 3,
		ULTRA_ACCURATE = 6
	};
	void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	void setUltraAccurate(bool u) { setFlag(ULTRA_ACCURATE, u); }
private:
	void setFlag(LocoFlag f, bool b)
	{
		if (b)
			m_flags |= (1U << f);
		else
			m_flags &= ~(1U << f);
	}
	unsigned char m_pad00[0x44];
	unsigned int m_flags;
};

class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType v);
};

template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class AIUpdateSlots<0>
{
};

class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual bool chooseLocomotorSet(LocomotorSetType wst);
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
private:
	unsigned char m_pad004[0x20 - 4];
public:
	AICommandInterface m_commands;
private:
	unsigned char m_pad024[0x1F0 - 0x24];
	Locomotor *m_curLocomotor;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x258 - 0x44];
	AIUpdateInterface *m_ai;
};

class SlavedUpdateModuleData
{
public:
	virtual ~SlavedUpdateModuleData();
	int m_unused04;
	int m_leashRange;
	int m_guardMaxRange;
	int m_guardWanderRange;
	int m_attackRange;
	int m_attackWanderRange;
	int m_scoutRange;
	int m_scoutWanderRange;
	int m_distToTargetToGrantRangeBonus;
	int m_repairRange;
	float m_repairMinAltitude;
	float m_repairMaxAltitude;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const SlavedUpdateModuleData *m_moduleData;
	Object *m_object;
};

class SlavedUpdate : public BehaviorModule
{
public:
	void moveToNewRepairSpot();
	SlavedUpdateModuleData *getSlavedUpdateModuleData() const { return (SlavedUpdateModuleData *)m_moduleData; }
private:
	unsigned char m_pad0C[0x24 - 0x0C];
	Int m_slaver;
	Coord3D m_guardPointOffset;
};

void SlavedUpdate::moveToNewRepairSpot()
{
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	Object *me = getObject();
	Object *master = TheGameLogic->findObjectByID((ObjectID)m_slaver);
	if (data->m_repairRange)
	{
		Real randomDirection = GetGameLogicRandomValueReal(0.0f, 6.2831855f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp", 828);
		m_guardPointOffset.set(master->getPosition());
		m_guardPointOffset.x += Cos(randomDirection) * data->m_repairRange;
		m_guardPointOffset.y += Sin(randomDirection) * data->m_repairRange;
		m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(m_guardPointOffset.x, m_guardPointOffset.y, 0);
		Real altitude = GetGameLogicRandomValueReal(data->m_repairMinAltitude, data->m_repairMaxAltitude, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp", 833);
		m_guardPointOffset.z += altitude;
		AIUpdateInterface *ai = me->getAIUpdateInterface();
		if (ai)
		{
			ai->chooseLocomotorSet(LOCOMOTORSET_PANIC);
			ai->getCurLocomotor()->setUltraAccurate(true);
			ai->m_commands.aiMoveToPosition(&m_guardPointOffset, CMD_FROM_AI);
			Locomotor *locomotor = ai->getCurLocomotor();
			if (locomotor)
				locomotor->setUsePreciseZPos(true);
		}
	}
}
