// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1FlammableUpdate@@UAE@XZ @0x0048C724 77B
// Dtor restores four vptrs (+0 +0xC +0x10 +0x20) then calls rowed stopBurningSound at 0x0048C55E and pinned base ??1UpdateModule at 0x0024A797; DamageModuleInterface trivial so no call; vtable values DIR32 auto-patches. Model follows PoisonedBehaviorDtor.
#include <list>
#include <vector>
#include <algorithm>
#include "ascii_string.h"
namespace _STL
{
template<> _List_base<int, allocator<int> >::~_List_base();
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Thing;
class ModuleData;
class Module;
class Object;
class Drawable;
class FXList;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

enum ObjectStatusTypes
{
	OBJECT_STATUS_STATUS_3 = 3,
	OBJECT_STATUS_STATUS_5 = 5,
	OBJECT_STATUS_AFLAME = 10,
	OBJECT_STATUS_BURNED = 11,
	OBJECT_STATUS_STATUS_82 = 82
};

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1,
	MODELCONDITION_AFLAME = 2 * 32 + 14,
	MODELCONDITION_SMOLDERING = 2 * 32 + 16,
	MODELCONDITION_FLAG_190 = 5 * 32 + 30,
	MODELCONDITION_FLAG_191 = 5 * 32 + 31
};

enum DisabledType
{
	DISABLED_TYPE_4 = 4
};

enum DamageType
{
	DAMAGE_FLAME = 6
};

enum DeathType
{
	DEATH_BURNED = 3
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// The BFME 2 DamageInfo as these bodies reach it: the 0x7C-byte record the
// rowed initializer 0x00263895 builds.
class DamageInfo
{
public:
	DamageInfo();
	Int m_unknown00[2];
	UnsignedInt m_sourceID; // +0x08
	Int m_unknown0C;
	Int m_damageType; // +0x10
	Int m_unknown14[2];
	Int m_deathType; // +0x1C
	Real m_amount; // +0x20
	char m_unknown24[0x70 - 0x24];
	Real m_actualDamageDealt; // +0x70
	Real m_actualDamageClipped; // +0x74
	char m_unknown78[0x7C - 0x78];
};

class Drawable
{
public:
	void rva00274176(Bool set);
	Bool rva00272835(Int boneName, Int transform);
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
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};

class ThingTemplate
{
public:
	char m_unknown00[0x11C];
	UnsignedInt m_kindOf11C;
};

class BodyModuleInterface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void updateAflame(); // vslot 10
};

// The two-pointer range the contain's slot 70 returns by value; the rowed
// 0x0036AE51 turns it into a list.
class Rva0036AE51ListView
{
public:
	void *m_first;
	void *m_last;
	_STL::list<int> rva0036AE51();
};

class ContainModuleInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual void rva34(Int how); // vslot 34
	virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44();
	virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
	virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
	virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual Rva0036AE51ListView rva70(); // vslot 70
};

// The AIUpdateInterface at Object+0x258 (isMoving row 0x00264688): slot 142
// of its primary table takes a mode (0 when a burn ends, 4 when the flee
// starts), its AICommandInterface base sits at +0x20 (aiMoveToPosition row
// 0x0026C26D) and both bodies write the flag at +0x3C9.
class AIUpdatePrimaryView
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void rva142(Int mode); // vslot 142 (+0x238)
	char m_unknown004[0x20 - 4];
};

// Zero Hour's AICommandInterface takes a CommandSourceType (row 0x0026C26D).
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_SCRIPT, CMD_FROM_AI, CMD_FROM_DOZER, CMD_DEFAULT_SWITCH_WEAPON };
class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

class AIUpdateInterface : public AIUpdatePrimaryView, public AICommandInterface
{
public:
	Bool isMoving() const;
	char m_unknown024[0x3C9 - 0x24];
	Bool m_flag3C9;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes status) const;
	void setStatus(ObjectStatusTypes status, Bool set);
	void rva0028AE6D();
	void rva0028EBDA(Bool set);
	Drawable *getDrawable() const;
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);
	void setDisabledUntil(DisabledType type, UnsignedInt frame);
	void attemptDamage(DamageInfo *damageInfo);
	Module *findModule(NameKeyType key) const;

	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}

	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_unknown08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	char m_unknown44[0x74 - 0x44];
	UnsignedInt m_id; // +0x74
	char m_unknown78[0x10C - 0x78];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	char m_unknown158[0x250 - 0x158];
	ContainModuleInterface *m_contain; // +0x250
	BodyModuleInterface *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = 0, Real *terrainZ = 0, Int unused = 0);
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	// Water depth at (x, y): waterZ - terrainZ when isUnderwater, else 0
	// (W3DTerrainLogic slot 25, row 0x0027D815).
	virtual Real Rva0027D815(Real x, Real y);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int zero);
};

class AI
{
public:
	char m_unknown00[0x10];
	Pathfinder *m_pathfinder; // +0x10

	Pathfinder *pathfinder() { return m_pathfinder; }
};

extern AI *TheAI;

// BFME 2 keeps the logic frame rate in a global (0x009BA4E4).
extern int g_Va00DBA4E4;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	void deselectObject(Object *obj, UnsignedInt playerMask, Bool affectClient);
private:
	char m_unknown00[0x40];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Matrix3D
{
public:
	Matrix3D(bool init)
	{
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	}
	Real m[3][4];
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0,
		Real primarySpeed = 0.0f, const Coord3D *secondary = 0);
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary = 0);
};

struct BfmeDelayedLuaEvent
{
	unsigned char m_data[0x18];
};

struct BfmeDelayedLuaEventList
{
	BfmeDelayedLuaEventList();
	~BfmeDelayedLuaEventList();
	void *m_vtable;
	BfmeDelayedLuaEvent m_events[3];
};

// The object-event dispatch at 0x003360D2 is rowed as a method of an
// address-level view of TheLuaScriptEngine's object.
class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class Rva002918E0Object
{
public:
	void rva004B239A(unsigned char a, unsigned char b);
	void set(unsigned char value);
};

// FireSpreadUpdate, looked up by its module key below. Its startFireSpreading
// (Zero Hour tryToIgnite makes the same call) is rowed at 0x0048B938 under
// the address-named view Rva0048B7D9, whose calcNextSpreadDelay sibling
// carries the FireSpreadUpdate.cpp file literal.
class Rva0048B7D9
{
public:
	void rva0048B938();
};

// One FireFX entry: the effect and the bone it plays at (BFME 1's parser
// builds the same pair, also address-named). Retail copies it through the
// folded {dword, AsciiString} copy constructor at 0x000CF475; the type's own
// name is unknown.
struct Rva000CF475FireFX
{
	const FXList *fx;
	AsciiString boneName;
	Rva000CF475FireFX(const Rva000CF475FireFX &that);
};

class FlammableUpdateModuleData
{
public:
	char m_unknown00[8];
	UnsignedInt m_burnedDelay; // +0x08
	UnsignedInt m_aflameDuration; // +0x0C
	UnsignedInt m_aflameDamageDelay; // +0x10
	Int m_aflameDamageAmount; // +0x14
	AsciiString m_burningSoundName; // +0x18
	Real m_flameDamageLimitData; // +0x1C
	Int m_flameDamageExpirationDelay; // +0x20
	Int m_damageType; // +0x24
	_STL::vector<Rva000CF475FireFX> m_fireFXList; // +0x28
	Bool m_flag34;
	Bool m_flag35;
	Bool m_flag36;
	Bool m_flag37;
	Bool m_flag38;
	Bool m_damageContained; // +0x39
	Bool m_fleeToWater; // +0x3A
	Real m_minWaterDepth; // +0x3C
	Real m_fleeSearchRadius; // +0x40
	Real m_fleeSearchStep; // +0x44
	Bool m_flag48;
	ModelConditionFlagType m_specialCondition; // +0x4C
	UnsignedInt m_specialConditionFrames; // +0x50
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
};

enum FlammabilityStatusType
{
	FS_NORMAL = 0,
	FS_AFLAME,
	FS_BURNED
};

class FlammableUpdate : public UpdateModule, public DamageModuleInterface
{
public:
	virtual ~FlammableUpdate();
	virtual void onDamage(DamageInfo *damageInfo);
	void tryToIgnite();
	void rva0048C8F9();
	void rva0048C7BF();
	void rva0048C771();
	virtual UpdateSleepTime update();

protected:
	UpdateSleepTime calcSleepTime();
	void stopBurningSound();
	const FlammableUpdateModuleData *getFlammableUpdateModuleData() const
	{
		return (const FlammableUpdateModuleData *)m_moduleData;
	}

private:
	int m_status;
	unsigned int m_aflameEndFrame;
	unsigned int m_burnedEndFrame;
	unsigned int m_damageEndFrame;
	void *m_audioHandle;
	Real m_flameDamageLimit; // +0x38
	Int m_lastFlameDamageDealt; // +0x3C
	Bool m_fleeing; // +0x40
	UnsignedInt m_specialConditionEndFrame; // +0x44
	UnsignedInt m_lastIgniterID; // +0x48
	Bool m_flag4C;
};

FlammableUpdate::~FlammableUpdate()
{
	stopBurningSound();
}

// ?rva0048C8F9@FlammableUpdate@@QAEXXZ @0x0048C8F9 467B (Ghidra boundary;
// calls at 0x003BC2D3, 0x0048CB08 and 0x0048D473; BFME 1's counterpart is
// FlameCleanup00293E50::apply).
// Target facts: this is FlammableUpdate (module data at +4 read for the
// +0x34/+0x36/+0x38/+0x48 flags, m_status at +0x24, stopBurningSound row
// 0x0048C55E, setWakeFrame row 0x0044DF71). It ends a burn: status becomes
// BURNED or NORMAL from the object's BURNED bit, clears statuses 3/5 and
// AFLAME and the AFLAME model condition, optionally marks SMOLDERING, resets
// the EntEnragedUpdate module (rows 0x004B239A/0x004B23B3), dispatches the
// BURNED Lua event through 0x003360D2, clears flag 0x3C9 of the +0x258
// module through its slot 142 and refreshes the body's aflame state (slot
// 10). The method name is unknown, so it stays address-based; flag names are
// offsets.
void FlammableUpdate::rva0048C8F9()
{
	Object *me = getObject();
	m_status = me->testStatus(OBJECT_STATUS_BURNED) ? FS_BURNED : FS_NORMAL;
	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
	m_aflameEndFrame = 1;
	setWakeFrame(me, UPDATE_SLEEP_NONE);
	me->setStatus(OBJECT_STATUS_STATUS_3, false);
	me->setStatus(OBJECT_STATUS_STATUS_5, false);
	if (data->m_flag34)
	{
		me->setStatus(OBJECT_STATUS_BURNED, true);
		me->setModelConditionState(MODELCONDITION_SMOLDERING);
	}
	me->rva0028EBDA(false);

	static const NameKeyType key_EntEnragedUpdate = TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
	Module *enraged = me->findModule(key_EntEnragedUpdate);
	if (enraged)
	{
		((Rva002918E0Object *)enraged)->rva004B239A(0, 0);
		((Rva002918E0Object *)enraged)->set(0);
	}

	if (data->m_flag36)
		me->clearModelConditionState(MODELCONDITION_FLAG_190);
	if (data->m_flag38)
		me->clearModelConditionState(MODELCONDITION_FLAG_191);
	if (data->m_flag36 || data->m_flag38)
		me->getDrawable()->rva00274176(true);

	BfmeDelayedLuaEventList list;
	((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(OBJECT_STATUS_BURNED, me, &list);

	stopBurningSound();
	me->setStatus(OBJECT_STATUS_AFLAME, false);
	me->clearModelConditionState(MODELCONDITION_AFLAME);
	if (data->m_flag48 && m_flag4C)
	{
		AIUpdateInterface *ai = me->m_ai;
		if (ai)
		{
			ai->m_flag3C9 = false;
			me->m_ai->rva142(0);
			m_flag4C = false;
		}
	}
	me->m_body->updateAflame();
}

// ?tryToIgnite@FlammableUpdate@@QAEXXZ @0x0048CB18 781B (Ghidra boundary;
// pinned name; calls at 0x003BC2CC, 0x0048B919 in FireSpreadUpdate's update
// and 0x0048CF23 in onDamage below).
// Donor: Zero Hour FlammableUpdate::tryToIgnite -- set AFLAME, the AFLAME
// model condition, start the burning sound (row 0x0048C7BF), start fire
// spreading, set the aflame/burned/damage end frames and sleep by
// calcSleepTime. Target-only additions read from retail: the AFLAME Lua
// event (0x003360D2), model-condition flags 190/191 with a drawable refresh
// (0x00274176), the FireFX list at module data +0x28 played at a bone
// transform (0x00272835, doFXPos 0x00094C29) or on the object (doFXObj
// 0x000B2235), and the special model condition with a type-4 disable timer
// and status 82.
void FlammableUpdate::tryToIgnite()
{
	if (m_status == FS_NORMAL)
	{
		Object *me = getObject();
		me->setStatus(OBJECT_STATUS_AFLAME, true);
		me->m_body->updateAflame();
		me->setModelConditionState(MODELCONDITION_AFLAME);
		rva0048C7BF();

		static const NameKeyType key_FireSpreadUpdate = TheNameKeyGenerator->nameToKey("FireSpreadUpdate");
		Rva0048B7D9 *fu = (Rva0048B7D9 *)getObject()->findModule(key_FireSpreadUpdate);
		if (fu != 0)
			fu->rva0048B938();

		m_status = FS_AFLAME;

		BfmeDelayedLuaEventList list;
		((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(OBJECT_STATUS_AFLAME, me, &list);

		const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
		UnsignedInt now = TheGameLogic->getFrame();
		if (data->m_aflameDuration > 0)
			m_aflameEndFrame = now + data->m_aflameDuration;
		else
			m_aflameEndFrame = 0x3fffffff;
		m_burnedEndFrame = data->m_burnedDelay ? now + data->m_burnedDelay : 0;
		m_damageEndFrame = data->m_aflameDamageDelay ? now + data->m_aflameDamageDelay : 0;

		setWakeFrame(m_object, calcSleepTime());

		if (data->m_flag35)
			me->setModelConditionState(MODELCONDITION_FLAG_190);
		if (data->m_flag37)
			me->setModelConditionState(MODELCONDITION_FLAG_191);
		if (data->m_flag35 || data->m_flag37)
			me->getDrawable()->rva00274176(true);

		for (_STL::vector<Rva000CF475FireFX>::const_iterator it = data->m_fireFXList.begin(); it != data->m_fireFXList.end(); )
		{
			Rva000CF475FireFX info = *it;
			if (!info.boneName.isEmpty() && getObject()->getDrawable())
			{
				Matrix3D mtx(true);
				getObject()->getDrawable()->rva00272835((Int)info.boneName.str(), (Int)&mtx);
				Coord3D pos;
				pos.x = mtx.m[0][3];
				pos.y = mtx.m[1][3];
				pos.z = mtx.m[2][3];
				FXList::doFXPos(info.fx, &pos, &mtx);
			}
			else
			{
				FXList::doFXObj(info.fx, getObject());
			}
			++it;
		}

		if (data->m_specialConditionFrames > 0)
		{
			me->setSpecialModelConditionState(data->m_specialCondition, data->m_specialConditionFrames);
			me->setDisabledUntil(DISABLED_TYPE_4, TheGameLogic->getFrame() + data->m_specialConditionFrames - 1);
			m_specialConditionEndFrame = TheGameLogic->getFrame() + data->m_specialConditionFrames;
			me->setStatus(OBJECT_STATUS_STATUS_82, true);
		}
		else
		{
			m_specialConditionEndFrame = TheGameLogic->getFrame();
		}
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}
}

// ?onDamage@FlammableUpdate@@UAEXPAVDamageInfo@@@Z @0x0048CE3E 453B (Ghidra
// boundary; vftable entry 0x0084C3BC, this = the DamageModuleInterface base
// at +0x20). Donor: Zero Hour FlammableUpdate::onDamage -- remember the
// igniter, refresh the flame damage limit after the expiration delay, and
// ignite once the limit is used up. Target-only parts read from retail: an
// underwater test (TheTerrainLogic slot 19 unless kind bit 0x11C:31 is set)
// and a module-data damage-type filter in place of ZH's DAMAGE_FLAME test;
// on ignition, with module-data +0x39 set, the contained objects (contain
// slot 70, list helper 0x0036AE51) each take a FLAME/BURNED DamageInfo of
// max(damage amount / 2, 1) via attemptDamage 0x0029848E, else contain slot
// 34 runs with 2.
void FlammableUpdate::onDamage(DamageInfo *damageInfo)
{
	if (damageInfo->m_actualDamageClipped > 0.0f)
		m_lastIgniterID = damageInfo->m_sourceID;

	Object *me = getObject();
	Bool underwater = !(me->m_template->m_kindOf11C & 0x80000000)
		&& TheTerrainLogic->isUnderwater(me->m_pos.x, me->m_pos.y);

	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
	if ((data->m_damageType == 0 || data->m_damageType == damageInfo->m_damageType) && !underwater)
	{
		Int now = TheGameLogic->getFrame();
		Int since = now - data->m_flameDamageExpirationDelay;
		if (since > m_lastFlameDamageDealt)
			m_flameDamageLimit = data->m_flameDamageLimitData;
		m_lastFlameDamageDealt = now;

		if (!me->testStatus(OBJECT_STATUS_AFLAME) && !me->testStatus(OBJECT_STATUS_BURNED))
		{
			m_flameDamageLimit -= damageInfo->m_actualDamageDealt;
			if (m_flameDamageLimit <= 0.0f)
			{
				m_flameDamageLimit = 0.0f;
				tryToIgnite();
				if (data->m_damageContained && me->m_contain)
				{
					DamageInfo info;
					info.m_amount = (Real)_STL::max(data->m_aflameDamageAmount / 2, 1);
					info.m_sourceID = me->m_id;
					info.m_damageType = DAMAGE_FLAME;
					info.m_deathType = DEATH_BURNED;
					_STL::list<int> contained = me->m_contain->rva70().rva0036AE51();
					for (_STL::list<int>::iterator it = contained.begin(); it != contained.end(); )
					{
						Object *obj = (Object *)*it;
						++it;
						if (obj)
							obj->attemptDamage(&info);
					}
				}
				else
				{
					ContainModuleInterface *contain = me->m_contain;
					if (contain)
						contain->rva34(2);
				}
			}
		}
	}
}

// ?update@FlammableUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048D0BE 977B
// (Ghidra boundary; slot 0 of the UpdateModuleInterface vftable, this = the
// +0x10 base). Donor: Zero Hour FlammableUpdate::update -- expire the damage,
// burned and aflame timers, then sleep via calcSleepTime. Target-only parts
// read from retail: when the special-condition timer expires and module data
// +0x3A asks to flee to water, scan a grid of +0x40 radius in +0x44 steps
// around the object for the closest cell deeper than +0x3C (TheTerrainLogic
// slot 25) that TheAI's pathfinder can reach, then order the move, deselect,
// set status bits 3 and 5 and notify an EntEnragedUpdate module; while
// underwater and not moving, the aflame end is clamped to three seconds.
UpdateSleepTime FlammableUpdate::update()
{
	Object *me = getObject();
	UnsignedInt now = TheGameLogic->getFrame();
	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();

	if (m_specialConditionEndFrame > 0)
	{
		if (now >= m_specialConditionEndFrame)
		{
			m_specialConditionEndFrame = 0;
			if (data->m_fleeToWater)
			{
				const Coord3D *pos = &me->m_pos;
				Coord3D best;
				best.x = 10000000.0f;
				best.y = 10000000.0f;
				best.z = 10000000.0f;
				AIUpdateInterface *ai = me->m_ai;
				if (ai)
				{
					Real radius = data->m_fleeSearchRadius;
					Real step = data->m_fleeSearchStep;
					for (Real x = (Real)(Int)(pos->x - radius); pos->x + radius >= x; x = (Real)(Int)(x + step))
					{
						// A second pointer for the row bounds: retail loads row->y before
						// adding the radius, which the shared pos pointer does not give.
						const Coord3D *row = pos;
						for (Real y = (Real)(Int)(row->y - radius); row->y + radius >= y; y = (Real)(Int)(y + step))
						{
							if (TheTerrainLogic->Rva0027D815(x, y) > getFlammableUpdateModuleData()->m_minWaterDepth)
							{
								Coord3D cand;
								cand.z = pos->z;
								cand.x = x;
								cand.y = y;
								Real candDX = pos->x - cand.x;
								Real candDY = pos->y - cand.y;
								Real bestDX = pos->x - best.x;
								Real bestDY = pos->y - best.y;
								if (candDX * candDX + candDY * candDY < bestDX * bestDX + bestDY * bestDY
									&& TheAI->pathfinder()->QuickDoesPathExist(me, pos, &cand, 0))
									best = cand;
							}
						}
					}

					static const NameKeyType key_EntEnragedUpdate = TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
					Module *enraged = me->findModule(key_EntEnragedUpdate);
					if (TheTerrainLogic->isUnderwater(best.x, best.y))
					{
						if (data->m_flag48)
						{
							AIUpdateInterface *ai2 = me->m_ai;
							if (ai2)
							{
								ai2->rva142(4);
								me->m_ai->m_flag3C9 = true;
								m_flag4C = true;
							}
						}
						ai->aiMoveToPosition(&best, (CommandSourceType)1);
						m_fleeing = true;
						TheGameLogic->deselectObject(me, 0xFFFFF, true);
						me->setStatus(OBJECT_STATUS_STATUS_3, true);
						me->setStatus(OBJECT_STATUS_STATUS_5, true);
						if (enraged)
							((Rva002918E0Object *)enraged)->set(1);
					}
					else if (enraged)
					{
						((Rva002918E0Object *)enraged)->rva004B239A(1, 0);
					}
				}
			}
		}
		return UPDATE_SLEEP_NONE;
	}

	if (!(me->m_template->m_kindOf11C & 0x80000000)
		&& TheTerrainLogic->isUnderwater(me->m_pos.x, me->m_pos.y))
	{
		AIUpdateInterface *ai = me->m_ai;
		if (ai && !ai->isMoving())
		{
			m_aflameEndFrame = _STL::min((UnsignedInt)(g_Va00DBA4E4 * 3 + TheGameLogic->getFrame()), m_aflameEndFrame);
			m_fleeing = false;
		}
	}

	if (m_damageEndFrame != 0 && now >= m_damageEndFrame)
	{
		m_damageEndFrame = now + data->m_aflameDamageDelay;
		rva0048C771();
	}
	if (m_burnedEndFrame != 0 && now >= m_burnedEndFrame && data->m_flag34)
	{
		me->setStatus(OBJECT_STATUS_BURNED, true);
		me->setModelConditionState(MODELCONDITION_SMOLDERING);
	}
	if (m_aflameEndFrame != 0 && now >= m_aflameEndFrame)
		rva0048C8F9();
	return calcSleepTime();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
