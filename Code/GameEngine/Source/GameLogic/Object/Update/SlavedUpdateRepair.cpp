// cl: /DNDEBUG /MD /GX
//
// SlavedUpdate methods, Zero Hour SlavedUpdate.cpp transferred: endRepair
// (retail 0x004A1C10, 73 bytes) and setRepairModelConditionStates (retail
// 0x004A197D, 236 bytes). Identity: both sit in the retail SlavedUpdate.cpp
// block (matched pool key 0x004A1875, ctor 0x004A18C5, xfer 0x004A1B54), the
// former calls the latter with MODELCONDITION_PACKING, and both bodies follow
// the Zero Hour source statement for statement.
// BFME2 deltas: model conditions live on the Object (word array at +0x10C) with
// the BFME2 indexes read from these bodies (PACKING 94, UNPACKING 96, FIRING_B
// 47, FIRING_C 53, BETWEEN_FIRING_SHOTS_B 50 / C 56, RELOADING_B 51 / C 57) and
// are updated through masked-word accessors around the pinned notifier
// 0x0028AE6D (unsigned index for the variable one); SLAVED_UPDATE_RATE is the
// int global at VA 0x00E03BBC, assigned before the repair state is reset (the
// load precedes that store in retail); chooseLocomotorSet is AIUpdateInterface
// slot 142 and m_curLocomotor sits at +0x1F0; the two inline Locomotor flag
// clears fold into one and of ~0x48 (PRECISE_Z_POS bit 3, ULTRA_ACCURATE bit 6).
//
// The drone behaviours that follow in the same retail block are Zero Hour's
// doAttackLogic (0x004A1C77), doScoutLogic (0x004A1E3B), doGuardLogic
// (0x004A1FDC) and doRepairLogic (0x004A24D3): each pushes the SlavedUpdate.cpp
// path with its own source line to the logic random number generator, and
// update's call sites (0x004A2864, 0x004A28CC, 0x004A2B2F, 0x004A28DC) pass
// them the master's victim, its goal position, the pinned position and
// nothing. Module data offsets are the ones SlavedUpdateModuleDataCtor
// initialises, in Zero Hour field order. doAttackLogic (452 bytes, line 437)
// and doScoutLogic (417 bytes, line 500) are transferred here statement for
// statement; BFME2 reads the attack distance through the rowed Object
// distance helper 0x002C97E8, issues the move through AICommandInterface at
// AIUpdateInterface +0x20 (0x0026C26D, whose body is visible as in BFME 1's
// twin so the position temporaries share a stack slot) and sets the
// DRONE_SPOTTING weapon bonus (bit 6 of Object +0x380) inline.

typedef float Real;
typedef int Int;
typedef bool Bool;

// class-gate: allow Coord3D the Zero Hour inline members (zero/set/add/sub/scale)
// and the out-of-line ?normalize@Coord3D@@QAEXXZ (0x000035B6) these bodies call;
// the variant-data canonical header declares only the fields.
struct Coord3D
{
	Real x;
	Real y;
	Real z;
	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	void set(const Coord3D *p)
	{
		x = p->x;
		y = p->y;
		z = p->z;
	}
	void add(const Coord3D *a)
	{
		x += a->x;
		y += a->y;
		z += a->z;
	}
	void sub(const Coord3D *a)
	{
		x -= a->x;
		y -= a->y;
		z -= a->z;
	}
	void scale(Real s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
	void normalize();
};

template <class NUM> inline NUM sqr(NUM x)
{
	return x * x;
}

#define PI 3.14159265359f

enum ObjectID
{
	INVALID_ID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

// BFME2 indexes read from these bodies.
enum ObjectStatusTypes
{
	OBJECT_STATUS_SLAVE_RETURNING = 30
};

enum WeaponBonusConditionType
{
	WEAPONBONUSCONDITION_DRONE_SPOTTING = 6
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// BFME2 model-condition indexes read from this body (Object word array at
// +0x10C): the Zero Hour names it clears, in the Zero Hour order.
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1,
	MODELCONDITION_FIRING_B = 47,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_B = 50,
	MODELCONDITION_RELOADING_B = 51,
	MODELCONDITION_FIRING_C = 53,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_C = 56,
	MODELCONDITION_RELOADING_C = 57,
	MODELCONDITION_PACKING = 94,
	MODELCONDITION_UNPACKING = 96,
	MODELCONDITION_SLAVE_RETURNING = 342
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
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
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0);
};
extern TerrainLogic *TheTerrainLogic;

float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
#define GameLogicRandomValueReal(lo, hi, line) GetGameLogicRandomValueReal(lo, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp", line)
float Cos(float value);
float Sin(float value);

extern const int g_009BA4E4;
#define LOGICFRAMES_PER_SECOND g_009BA4E4

// Zero Hour's DamageInfo as Rva00466C04Heal.cpp views it: the 0x7C record
// built by the rowed constructor 0x00263895.
class Rva00263653
{
public:
	Rva00263653() throw();
	virtual void rva00263653_dummy();
	int m_04;
	int m_08;
	int m_0C; // m_damageType
	int m_10;
	int m_14;
	int m_18; // m_deathType
	float m_1C; // m_amount
	unsigned char m_20;
	unsigned char m_21;
	unsigned char m_pad22[2];
	float m_24;
	int m_28;
	int m_2C;
	float m_30;
	float m_34;
	float m_38;
	float m_3C;
	float m_40;
	float m_44;
	float m_48;
	unsigned char m_4C;
	unsigned char m_pad4D[3];
	float m_50;
	float m_54;
	float m_58;
	float m_5C;
	float m_60;
	float m_64;
};

class Rva00263895Member
{
public:
	Rva00263895Member() throw();
	virtual void rva00263895_dummy();
	Rva00263653 m_mem;
	const void *m_ptr;
	float m_f70;
	float m_f74;
	unsigned char m_b78;
};
typedef Rva00263895Member DamageInfo;

enum DamageType
{
	DAMAGE_HEALING = 7
};

enum DeathType
{
	DEATH_NORMAL = 1
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void attemptHealing(DamageInfo *info);
};

class Weapon
{
public:
	Int getMaxShotCount() const { return m_maxShotCount; }
private:
	unsigned char m_pad00[0x34];
	Int m_maxShotCount; // +0x34
};

// The 3D distance squared from an object's position, rowed at 0x001E435D
// under its BFME 1 donor's names.
class BfmeVec3EJ;
class Gen_000E5A50
{
public:
	Real bfmeDistanceSquared(const BfmeVec3EJ *point) const;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }
	BodyModuleInterface *getBodyModule() const { return m_body; }
	Real getBoundingSphereRadius() const { return m_boundingSphereRadius; }
	Real getDistanceSquared(const Coord3D *pos) const
	{
		return ((const Gen_000E5A50 *)this)->bfmeDistanceSquared((const BfmeVec3EJ *)pos);
	}
	Real rva002C97E8(const Coord3D *from, const Coord3D *to) const;
	Real rva00263763(const void *other) const;
	Bool testStatus(ObjectStatusTypes bit) const;
	void setStatus(ObjectStatusTypes bit, Bool set = true);
	const Weapon *getCurrentWeapon(WeaponSlotType *wslot = 0) const;
	void setWeaponBonusCondition(WeaponBonusConditionType wbc)
	{
		m_weaponBonusCondition |= (1 << wbc);
	}
	void rva0028AE6D();
	__forceinline void setModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) == 0)
		{
			m_modelConditionFlags.set(flag);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType flag)
	{
		if (m_modelConditionFlags.test(flag) != 0)
		{
			m_modelConditionFlags.clear(flag);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0xBC - 0x44];
	Real m_boundingSphereRadius; // +0xBC
	unsigned char m_pad0C0[0x10C - 0xC0];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x380 - 0x25C];
	int m_weaponBonusCondition; // +0x380
};
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
enum RepairStates
{
	REPAIRSTATE_NONE = 0,
	REPAIRSTATE_UNPACKING = 1,
	REPAIRSTATE_PACKING = 2,
	REPAIRSTATE_READY = 3,
	REPAIRSTATE_EXTENDING = 4,
	REPAIRSTATE_RETRACTING = 5,
	REPAIRSTATE_WELDING = 6
};
enum LocomotorSetType
{
	LOCOMOTORSET_NORMAL = 0
};
class Locomotor
{
public:
	enum LocoFlag
	{
		PRECISE_Z_POS = 3,
		ULTRA_ACCURATE = 6
	};
	inline void setUsePreciseZPos(bool u) { setFlag(PRECISE_Z_POS, u); }
	inline void setUltraAccurate(bool u) { setFlag(ULTRA_ACCURATE, u); }
private:
	inline void setFlag(LocoFlag f, bool b) { if (b) m_flags |= (1 << f); else m_flags &= ~(1 << f); }
	unsigned char m_pad[0x44];
	unsigned int m_flags; // +0x44
};
extern "C" void free(void *block);
enum AICommandType
{
	AICMD_MOVE_TO_POSITION = 0
};
// The 0xC0 command block of AICommandInterfaceAttackCommands.cpp: opaque
// constructor 0x00351BD0, inline coordinate-buffer free on teardown.
struct AICommandParms
{
	AICommandParms(AICommandType cmd, CommandSourceType cmdSource);
	~AICommandParms() { if (m_coordsStart) free(m_coordsStart); }

	AICommandType m_cmd; // +0x00
	CommandSourceType m_cmdSource; // +0x04
	Coord3D m_pos; // +0x08
	char m_pad14[0x20 - 0x14];
	void *m_coordsStart; // +0x20
	char m_pad24[0xC0 - 0x24];
};
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void aiIdle(CommandSourceType cmdSource);
	// Retail 0x0026C26D; visible here (as in BFME1's twin) so VC7.1 sees it
	// does not retain the position.
	__declspec(noinline) void aiMoveToPosition(const Coord3D *pos, Int cmdSource)
	{
		AICommandParms parms(AICMD_MOVE_TO_POSITION, (CommandSourceType)cmdSource);
		parms.m_pos = *pos;
		aiDoCommand(&parms);
	}
};
// The three-argument position command at 0x00295A0F (target, shot count,
// source), rowed under a placeholder name.
class Rva00295A0FCommands
{
public:
	void Rva00295A0FCommand(void *pos, int maxShotsToFire, int cmdSource);
};
template <int N> class AIUpdateSlots : public AIUpdateSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class AIUpdateSlots<0>
{
};
// AIUpdateInterface: chooseLocomotorSet is primary slot 142 in BFME2; the
// command interface is the subobject at +0x20.
class AIUpdateInterface : public AIUpdateSlots<142>
{
public:
	virtual bool chooseLocomotorSet(LocomotorSetType wst) = 0;
	Locomotor *getCurLocomotor() { return m_curLocomotor; }
	void aiIdle(CommandSourceType cmdSource) { m_commands.aiIdle(cmdSource); }
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource) { m_commands.aiMoveToPosition(pos, cmdSource); }
	void aiAttackPosition(Coord3D *pos, Int maxShotsToFire, CommandSourceType cmdSource)
	{
		((Rva00295A0FCommands *)&m_commands)->Rva00295A0FCommand(pos, maxShotsToFire, cmdSource);
	}
private:
	unsigned char m_pad004[0x20 - 4];
	AICommandInterface m_commands; // +0x20
	unsigned char m_pad024[0x1F0 - 0x24];
	Locomotor *m_curLocomotor; // +0x1F0
};
class SlavedUpdateModuleData
{
public:
	virtual ~SlavedUpdateModuleData();
	Int m_unused04;
	Int m_leashRange; // +0x08
	Int m_guardMaxRange; // +0x0C
	Int m_guardWanderRange; // +0x10
	Int m_attackRange; // +0x14
	Int m_attackWanderRange; // +0x18
	Int m_scoutRange; // +0x1C
	Int m_scoutWanderRange; // +0x20
	Int m_distToTargetToGrantRangeBonus; // +0x24
	Int m_repairRange; // +0x28
	Real m_repairMinAltitude; // +0x2C
	Real m_repairMaxAltitude; // +0x30
	Real m_repairRatePerSecond; // +0x34
};
extern int g_Va00E03BBC; // SLAVED_UPDATE_RATE
// g_Va00E03BBC: matched references place it at VA 0xe03bbc (zero-filled .bss).
int g_Va00E03BBC;
class SlavedUpdate : public BehaviorModule
{
public:
	void endRepair();
	void setRepairModelConditionStates(ModelConditionFlagType flag);
	void doAttackLogic(const Object *target);
	void doScoutLogic(const Coord3D *mastersDestination);
	void doGuardLogic(Coord3D *pinnedPosition, Bool idle);
	void doRepairLogic();
	void setRepairState(RepairStates repairState);
	const SlavedUpdateModuleData *getSlavedUpdateModuleData() const { return (const SlavedUpdateModuleData *)m_moduleData; }
private:
	unsigned char m_pad0C[0x24 - 0x0C];
	ObjectID m_slaver; // +0x24
	Coord3D m_guardPointOffset; // +0x28
	int m_framesToWait; // +0x34
	RepairStates m_repairState; // +0x38
	bool m_repairing; // +0x3C
};
void SlavedUpdate::setRepairModelConditionStates(ModelConditionFlagType flag)
{
	Object *obj = getObject();
	obj->clearModelConditionState(MODELCONDITION_PACKING);
	obj->clearModelConditionState(MODELCONDITION_UNPACKING);
	obj->clearModelConditionState(MODELCONDITION_FIRING_B);
	obj->clearModelConditionState(MODELCONDITION_FIRING_C);
	obj->clearModelConditionState(MODELCONDITION_BETWEEN_FIRING_SHOTS_B);
	obj->clearModelConditionState(MODELCONDITION_BETWEEN_FIRING_SHOTS_C);
	obj->clearModelConditionState(MODELCONDITION_RELOADING_B);
	obj->clearModelConditionState(MODELCONDITION_RELOADING_C);
	obj->setModelConditionState(flag);
}
void SlavedUpdate::endRepair()
{
	if (m_repairState != REPAIRSTATE_NONE)
	{
		m_framesToWait = g_Va00E03BBC;
		m_repairState = REPAIRSTATE_NONE;
		m_repairing = false;
		setRepairModelConditionStates(MODELCONDITION_PACKING);
	}
	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
	{
		ai->chooseLocomotorSet(LOCOMOTORSET_NORMAL);
		Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
		{
			locomotor->setUltraAccurate(false);
			locomotor->setUsePreciseZPos(false);
		}
	}
}

// We are ordered to attempt to get as close as possible to my master's target.
void SlavedUpdate::doAttackLogic(const Object *target)
{
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	Object *me = getObject();
	Object *master = TheGameLogic->findObjectByID(m_slaver);
	Coord3D attackPosition;

	// First, determine the attack position. If the target is too far away,
	// then we'll calculate the closest allowable position.
	const Coord3D *targetPos = target->getPosition();
	Real dist = me->rva002C97E8(me->getPosition(), targetPos);
	if (dist > sqr(data->m_attackRange))
	{
		Coord3D vector;
		vector.set(targetPos);
		vector.sub(master->getPosition());
		vector.normalize();
		vector.scale(data->m_attackRange);

		attackPosition.set(master->getPosition());
		attackPosition.add(&vector);
	}
	else
	{
		attackPosition.set(targetPos);
	}

	// Finally, if we have a wander distance, then randomly select a point
	// within the wander range radius of the pinned position.
	if (data->m_attackWanderRange)
	{
		Real randomDirection = GameLogicRandomValueReal(0, 2 * PI, 437);
		m_guardPointOffset.zero();
		m_guardPointOffset.x += data->m_attackWanderRange * Cos(randomDirection);
		m_guardPointOffset.y += data->m_attackWanderRange * Sin(randomDirection);

		attackPosition.x += m_guardPointOffset.x;
		attackPosition.y += m_guardPointOffset.y;
		m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(attackPosition.x, attackPosition.y);
	}

	AIUpdateInterface *ai = me->getAIUpdateInterface();
	if (ai)
	{
		ai->aiMoveToPosition(&attackPosition, CMD_FROM_AI);
	}

	if (dist < sqr(data->m_distToTargetToGrantRangeBonus))
	{
		// Seeing we are close enough to the target, grant our master
		// extended weapon range!
		master->setWeaponBonusCondition(WEAPONBONUSCONDITION_DRONE_SPOTTING);
	}
}

// We are ordered to attempt to get as close as possible to my master's
// movement destination point.
void SlavedUpdate::doScoutLogic(const Coord3D *mastersDestination)
{
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	Object *me = getObject();
	Object *master = TheGameLogic->findObjectByID(m_slaver);
	Coord3D scoutPosition;

	Real dist = me->rva002C97E8(me->getPosition(), mastersDestination);
	if (dist > sqr(data->m_scoutRange))
	{
		Coord3D vector;
		vector.set(mastersDestination);
		vector.sub(master->getPosition());
		vector.normalize();
		vector.scale(data->m_scoutRange);

		scoutPosition.set(master->getPosition());
		scoutPosition.add(&vector);
	}
	else
	{
		scoutPosition.set(mastersDestination);
	}

	if (data->m_scoutWanderRange)
	{
		Real randomDirection = GameLogicRandomValueReal(0, 2 * PI, 500);
		m_guardPointOffset.zero();
		m_guardPointOffset.x += data->m_scoutWanderRange * Cos(randomDirection);
		m_guardPointOffset.y += data->m_scoutWanderRange * Sin(randomDirection);

		scoutPosition.x += m_guardPointOffset.x;
		scoutPosition.y += m_guardPointOffset.y;
		m_guardPointOffset.z = TheTerrainLogic->getGroundHeight(scoutPosition.x, scoutPosition.y);
	}

	AIUpdateInterface *ai = me->getAIUpdateInterface();
	if (ai)
	{
		ai->aiMoveToPosition(&scoutPosition, CMD_FROM_AI);
	}
}
