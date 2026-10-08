// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /GX
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
//
// setRepairState (0x004A2258, 635 bytes) follows BFME 1's matched twin and the
// Zero Hour state machine: it is the setter doRepairLogic and update call with
// REPAIRSTATE_READY/WELDING, the ready and weld frame counts come from module
// data +0x3C..+0x48 at SlavedUpdate.cpp lines 750 and 767, and the welding
// effect uses the template named at +0x4C placed at the bone named at +0x50
// (Thing::getDrawable 0x005508E2, Drawable::getPristineBonePositions
// 0x0027274D). BFME2's lifetime is m_framesToWait * LOGICFRAMES_PER_SECOND;
// the position and lifetime setters are the rowed 0x001F3899 and 0x001F3D03,
// and the sparks event is the canonical 0x88-byte audio event built from
// TheAudio's misc-audio entry at +0x68. The handle's destructor only unlinks a
// live system (its out-of-line copy is 0x002115C5, the unwind action), so the
// unlink 0x0004CBC0 is declared not to throw, as retail sets no state before it.
// Retail adds the bone offset with the object's coordinate loaded first.
//
// doRepairLogic (0x004A24D3, 395 bytes, line 636) is Zero Hour's: the 12-unit
// closeness test reads the rowed Object distance helper 0x00263763, the heal
// is the rowed DamageInfo 0x00263895 sent to body slot 1, and the precise-Z
// toggle calls Locomotor::setFlag out of line. That is the 31-byte COMDAT at
// 0x001E3459 (formerly a placeholder): mask 1 << flag at Locomotor +0x44, set
// or cleared by the bool, which this unit emits byte for byte.
//
// stopSlavedEffects (0x004A1B17, 61 bytes) is Zero Hour's: BFME2 keeps the
// slave when module data +0x55 (DieOnMastersDeath, after the +0x54
// StayOnSameLayerAsMaster bool in the INI parse table) is set, else forgets
// the slaver, zeroes the guard offset and clears UNSELECTABLE (status 3,
// through setStatus 0x0023DB0E) and DISABLED_HELD (3, clearDisabled
// 0x00291CAC). RepairWhenBelowHealth% (+0x38) is an Int in that table.
//
// startSlavedEffects (0x004A1A69, 174 bytes, line 862) is Zero Hour's; BFME2
// sets UNSELECTABLE only under MarkUnselectable (+0x6C in the INI parse
// table) and passes the slave interface to Drawable 0x002710AE. The slave
// interface overrides follow its vftable at 0x00851E30: onEnslave
// (0x004A1BFD), onSlaverDie (0x004A1C05) and onSlaverDamage (0x004A1C59,
// aiGoProne). They run on the +0x20 subobject, behind UpdateModule's 0x20
// bytes (interface vptrs at +0x0C and +0x10).

#include "Common/BfmeAudioEventPrefix136.h"

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
	OBJECT_STATUS_UNSELECTABLE = 3,
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

enum DisabledType
{
	DISABLED_HELD = 3
};

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

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
#define GameLogicRandomValue(lo, hi, line) GetGameLogicRandomValue(lo, hi, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\SlavedUpdate.cpp", line)
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

class Matrix3D;
class Drawable
{
public:
	Int getPristineBonePositions(const char *boneNamePrefix, Int startIndex,
		Coord3D *positions, Matrix3D *transforms, Int maxBones, Int extra) const;
};

// Object's Thing base: the drawable getter rowed at 0x005508E2.
class Thing
{
public:
	Drawable *getDrawable() const;
};

// Drawable 0x002710AE takes the slaver and this module's slave interface:
// when the interface's slot 5 (UseSlaverAsControlForEvaObjectSightedEvents,
// module data +0x6D) is set it copies the slaver drawable's bytes +0x445 and
// +0x446. Rowed under a placeholder name and parameter classes.
class BuildListInfo;
class Arg2;
class Rva002710AE
{
public:
	void rva002710AE(BuildListInfo *slaver, Arg2 *slavedInterface);
};

// The welding system's position and lifetime setters, rowed under placeholder
// names at 0x001F3899 (position copy) and 0x001F3D03 (lifetime range).
struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
class Rva001F3D03Slot
{
public:
	void set(float a, float b);
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	__forceinline void setLifetimeRange(Real lo, Real hi)
	{
		((Rva001F3D03Slot *)this)->set(lo, hi);
	}
};
ParticleSystem *Make001FCBD7();

// The 12-byte handle: the out-of-line unlink is 0x0004CBC0, which the handle's
// destructor calls only for a live system (out of line, retail 0x002115C5).
class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

// TheAudio's misc-audio table (slot 78) holds the repair sparks event at +0x68;
// addAudioEvent is slot 25 and 0x002D9508 sets an event's position.
struct MiscAudio
{
	char m_pad[0x68];
	OpaqueRefElement4 m_repairSparks; // +0x68
};
class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24)
	virtual int addAudioEvent(const BfmeAudioEventPrefix136 *event);
	AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
	AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
	AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
	AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
	AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
	AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
	AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
	AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57)
	AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61)
	AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
	AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
	AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72) AUDIO_SLOT(73)
	AUDIO_SLOT(74) AUDIO_SLOT(75) AUDIO_SLOT(76) AUDIO_SLOT(77)
#undef AUDIO_SLOT
	virtual MiscAudio *getMiscAudio();
};
extern AudioManager *TheAudio;
class Rva002D9508
{
public:
	void rva002D9508(const void *src);
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
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
	void clearStatus(ObjectStatusTypes bit) { setStatus(bit, false); }
	Bool clearDisabled(DisabledType type);
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
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_id; // +0x74
	unsigned char m_pad078[0xBC - 0x78];
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
class ObjectModule
{
public:
	virtual ~ObjectModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceSlot00();
};
// BehaviorModule's interface vptr is at +0x0C, UpdateModule's at +0x10.
class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
private:
	unsigned char m_pad14[0x20 - 0x14];
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
	// Zero Hour's aiGoProne (0x0036F400: AICMD 0x1D copying the DamageInfo
	// into the command block at +0x3C), rowed under a placeholder whose
	// parameter class Rva003427DD is that DamageInfo.
	void rva0036F400(const class Rva003427DD *info, CommandSourceType cmdSource);
	// Retail 0x0026C26D; visible here (as in BFME1's twin) so VC7.1 sees it
	// does not retain the position.
	__declspec(noinline) void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource)
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
	void aiGoProne(const DamageInfo *info, CommandSourceType cmdSource)
	{
		m_commands.rva0036F400((const Rva003427DD *)info, cmdSource);
	}
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
	Int m_repairWhenHealthBelowPercentage; // +0x38
	Int m_minReadyFrames; // +0x3C
	Int m_maxReadyFrames; // +0x40
	Int m_minWeldFrames; // +0x44
	Int m_maxWeldFrames; // +0x48
	AsciiString m_weldingSysName; // +0x4C
	AsciiString m_weldingFXBone; // +0x50
	Bool m_stayOnSameLayerAsMaster; // +0x54
	Bool m_dieOnMastersDeath; // +0x55
	unsigned char m_pad56[0x6C - 0x56];
	Bool m_markUnselectable; // +0x6C
};
extern int g_Va00E03BBC; // SLAVED_UPDATE_RATE
// g_Va00E03BBC: matched references place it at VA 0xe03bbc (zero-filled .bss).
int g_Va00E03BBC;
// SlavedUpdateInterface (vptr at +0x20), Zero Hour's slot order: retail
// vftable 0x00851E30 holds getSlaverID, onEnslave 0x004A1BFD, onSlaverDie
// 0x004A1C05, onSlaverDamage 0x004A1C59, isSelfTasking, then BFME2's
// additions.
class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const = 0;
	virtual void onEnslave(const Object *slaver) = 0;
	virtual void onSlaverDie(const DamageInfo *info) = 0;
	virtual void onSlaverDamage(const DamageInfo *info) = 0;
	virtual Bool isSelfTasking() const = 0;
};
class SlavedUpdate : public UpdateModule, public SlavedUpdateInterface
{
public:
	virtual void onEnslave(const Object *slaver);
	virtual void onSlaverDie(const DamageInfo *info);
	virtual void onSlaverDamage(const DamageInfo *info);
	void startSlavedEffects(const Object *slaver);
	void endRepair();
	void setRepairModelConditionStates(ModelConditionFlagType flag);
	void doAttackLogic(const Object *target);
	void doScoutLogic(const Coord3D *mastersDestination);
	void doGuardLogic(Coord3D *pinnedPosition, Bool idle);
	void doRepairLogic();
	void setRepairState(RepairStates repairState);
	void moveToNewRepairSpot();
	void stopSlavedEffects();
	const SlavedUpdateModuleData *getSlavedUpdateModuleData() const { return (const SlavedUpdateModuleData *)m_moduleData; }
private:
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

// We are ordered to repair our master
void SlavedUpdate::doRepairLogic()
{
	Object *me = getObject();
	Object *master = TheGameLogic->findObjectByID(m_slaver);
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	AIUpdateInterface *ai = me->getAIUpdateInterface();
	if (!ai)
	{
		return;
	}

	// There are two major things... either move closer or repair.
	Real distSqr = getObject()->rva00263763(master);
	Bool closeEnough = distSqr < 12.0f * 12.0f;

	if (closeEnough)
	{
		switch (m_repairState)
		{
			case REPAIRSTATE_NONE:
				setRepairState(REPAIRSTATE_READY);
				break;
			case REPAIRSTATE_READY:
			case REPAIRSTATE_EXTENDING:
				if (m_framesToWait == 0)
				{
					setRepairState(REPAIRSTATE_WELDING);
				}
				break;
			case REPAIRSTATE_UNPACKING:
			case REPAIRSTATE_WELDING:
			case REPAIRSTATE_RETRACTING:
				if (m_framesToWait == 0)
				{
					setRepairState(REPAIRSTATE_READY);
				}
				break;
		}
	}
	else
	{
		m_repairing = false;

		Bool closeEnoughForZPrecision = distSqr < sqr(master->getBoundingSphereRadius() * 2);

		// We're too far away to repair, so get closer.
		Locomotor *locomotor = ai->getCurLocomotor();
		if (locomotor)
		{
			locomotor->setUsePreciseZPos(closeEnoughForZPrecision);
		}
		Coord3D pos;
		pos.set(master->getPosition());
		Real altitude = GameLogicRandomValueReal(data->m_repairMinAltitude, data->m_repairMaxAltitude, 636);
		pos.z += altitude;
		ai->aiMoveToPosition(&pos, CMD_FROM_AI);

		// Also speed things up by retracting the repair arm.
		if (m_framesToWait == 0)
		{
			setRepairState(REPAIRSTATE_READY);
		}
	}

	if (closeEnough && m_repairing)
	{
		// We're close enough to repair.
		BodyModuleInterface *body = master->getBodyModule();
		if (body)
		{
			Real repairAmount = data->m_repairRatePerSecond / LOGICFRAMES_PER_SECOND;

			DamageInfo healingInfo;
			healingInfo.m_mem.m_1C = repairAmount;
			healingInfo.m_mem.m_0C = DAMAGE_HEALING;
			healingInfo.m_mem.m_18 = DEATH_NORMAL;
			body->attemptHealing(&healingInfo);
		}
	}
}

void SlavedUpdate::setRepairState(RepairStates repairState)
{
	Object *obj = getObject();
	Drawable *draw = obj->getDrawable();
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();

	if (repairState == m_repairState)
		return;

	switch (repairState)
	{
		case REPAIRSTATE_UNPACKING:
			setRepairModelConditionStates(MODELCONDITION_UNPACKING);
			m_framesToWait = 15;
			break;
		case REPAIRSTATE_PACKING:
			setRepairModelConditionStates(MODELCONDITION_PACKING);
			m_framesToWait = 15;
			break;
		case REPAIRSTATE_READY:
		{
			switch (m_repairState)
			{
				case REPAIRSTATE_NONE:
					setRepairModelConditionStates(MODELCONDITION_UNPACKING);
					m_repairState = REPAIRSTATE_UNPACKING;
					m_framesToWait = 15;
					break;
				case REPAIRSTATE_WELDING:
					m_repairState = REPAIRSTATE_RETRACTING;
					m_framesToWait = 5;
					setRepairModelConditionStates(MODELCONDITION_FIRING_C);
					moveToNewRepairSpot();
					break;
				default:
					m_repairState = REPAIRSTATE_READY;
					m_framesToWait = GameLogicRandomValue(data->m_minReadyFrames, data->m_maxReadyFrames, 750);
					break;
			}
			break;
		}
		case REPAIRSTATE_WELDING:
		{
			if (m_repairState == REPAIRSTATE_READY)
			{
				m_repairState = REPAIRSTATE_EXTENDING;
				m_framesToWait = 5;
				setRepairModelConditionStates(MODELCONDITION_FIRING_B);
				break;
			}
			m_repairState = REPAIRSTATE_WELDING;
			m_framesToWait = GameLogicRandomValue(data->m_minWeldFrames, data->m_maxWeldFrames, 767);

			if (!data->m_weldingSysName.isEmpty())
			{
				const ParticleSystemTemplate *tmp = TheParticleSystemManager->findTemplate(data->m_weldingSysName);
				if (tmp)
				{
					BfmeParticleSystemHandle weldingSys = TheParticleSystemManager->createParticleSystem(tmp, true);
					if (weldingSys)
					{
						Coord3D pos;
						if (draw->getPristineBonePositions(data->m_weldingFXBone.str(), 0, &pos, 0, 1, 0))
						{
							pos.x = obj->getPosition()->x + pos.x;
							pos.y = obj->getPosition()->y + pos.y;
							pos.z = obj->getPosition()->z + pos.z;
						}
						else
							pos.set(obj->getPosition());

						weldingSys->setPosition(&pos);
						Real time = (Real)(m_framesToWait * LOGICFRAMES_PER_SECOND);
						weldingSys->setLifetimeRange(time, time);

						BfmeAudioEventPrefix136 soundToPlay(TheAudio->getMiscAudio()->m_repairSparks, 0);
						((Rva002D9508 *)&soundToPlay)->rva002D9508(&pos);
						TheAudio->addAudioEvent(&soundToPlay);
					}
				}
			}

			if (!m_repairing)
			{
				m_repairing = true;
			}
			break;
		}
	}
}

void SlavedUpdate::stopSlavedEffects()
{
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();
	if (data && data->m_dieOnMastersDeath)
		return;

	m_slaver = INVALID_ID;
	m_guardPointOffset.zero();

	getObject()->clearStatus(OBJECT_STATUS_UNSELECTABLE);
	getObject()->clearDisabled(DISABLED_HELD);
}

void SlavedUpdate::onEnslave(const Object *slaver)
{
	startSlavedEffects(slaver);
}

void SlavedUpdate::onSlaverDie(const DamageInfo *info)
{
	stopSlavedEffects();
}

void SlavedUpdate::onSlaverDamage(const DamageInfo *info)
{
	// Only slaves with a ProneUpdate will even care.
	AIUpdateInterface *ai = getObject()->getAIUpdateInterface();
	if (ai)
		ai->aiGoProne(info, CMD_FROM_AI);
}

void SlavedUpdate::startSlavedEffects(const Object *slaver)
{
	if (!slaver)
		return;

	m_slaver = slaver->getID();
	const SlavedUpdateModuleData *data = getSlavedUpdateModuleData();

	// Decide where our pinned stray point is
	Real randomDirection = GameLogicRandomValueReal(0, 2 * PI, 862);
	m_guardPointOffset.zero();
	m_guardPointOffset.x += data->m_guardMaxRange * Cos(randomDirection);
	m_guardPointOffset.y += data->m_guardMaxRange * Sin(randomDirection);

	if (data->m_markUnselectable)
		getObject()->setStatus(OBJECT_STATUS_UNSELECTABLE);

	Drawable *draw = getObject()->getDrawable();
	if (draw)
		((Rva002710AE *)draw)->rva002710AE((BuildListInfo *)slaver, (Arg2 *)(SlavedUpdateInterface *)this);
}
