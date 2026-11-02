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

// Coord3D: shared header/view; no private copy.
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"

#include "../../../Common/GameLogicObjectLookupView.h"

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

extern GameLogic *TheGameLogic;

#include "../../../../Include/GameLogic/TerrainLogic.h"
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
	__declspec(dllimport) __forceinline void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	__declspec(dllimport) __forceinline void setUltraAccurate(bool u) { setFlag(ULTRA_ACCURATE, u); }
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

#include "../object.h"

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

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

class SlavedUpdate : public BehaviorModule
{
public:
	void moveToNewRepairSpot();
	SlavedUpdateModuleData *getSlavedUpdateModuleData() const { return (SlavedUpdateModuleData *)m_moduleData; }
private:
	unsigned char m_pad0C[0x24 - 0x10];
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
