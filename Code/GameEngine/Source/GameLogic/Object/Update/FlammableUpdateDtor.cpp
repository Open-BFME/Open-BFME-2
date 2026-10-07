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

class Rva0048C8F9Module258
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
	virtual void rva142(Bool set); // vslot 142 (+0x238)
	char m_unknown004[0x3C9 - 4];
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
	Rva0048C8F9Module258 *m_module258; // +0x258
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
};

extern TerrainLogic *TheTerrainLogic;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
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

class BfmeObjectEventDispatch
{
public:
	void rva003360D2(int index, void *object, BfmeDelayedLuaEventList *eventList);
};

extern BfmeObjectEventDispatch *g_00E01DBC;

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
	char m_unknown3A[0x48 - 0x3A];
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
	virtual void update();
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
	Int m_unknown40;
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
	g_00E01DBC->rva003360D2(OBJECT_STATUS_BURNED, me, &list);

	stopBurningSound();
	me->setStatus(OBJECT_STATUS_AFLAME, false);
	me->clearModelConditionState(MODELCONDITION_AFLAME);
	if (data->m_flag48 && m_flag4C)
	{
		Rva0048C8F9Module258 *module = me->m_module258;
		if (module)
		{
			module->m_flag3C9 = false;
			me->m_module258->rva142(false);
			m_flag4C = false;
		}
	}
	me->m_body->updateAflame();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
