// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_flammableupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum /Ireference/shims/moduledata /ICode/GameEngine/Include
// stlport
// ??1FlammableUpdate@@UAE@XZ @0x0048C724 77B
// Dtor restores four vptrs (+0 +0xC +0x10 +0x20) then calls rowed stopBurningSound at 0x0048C55E and pinned base ??1UpdateModule at 0x0024A797; DamageModuleInterface trivial so no call; vtable values DIR32 auto-patches. Model follows PoisonedBehaviorDtor.
// codegen otherwise instantiates the min<unsigned> COMDAT (one byte shape
// per TU flags); a file-static overload takes those calls instead so this
// TU emits no external copy.
#define BFME_SNAPSHOT_NAME_SLOT
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/FlammableUpdate.h"
#include "GameLogic/Module/FireSpreadUpdate.h"
namespace _STL {
static inline const unsigned int &min(const unsigned int &a, const unsigned int &b)
{
    return b < a ? b : a;
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base
// wrapper (_List_iterator_base::operator!=, retail's copy is 0x006CFE40).
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
#include "../../../../Include/GameLogic/ContainmentListView.h"
#include <algorithm>
namespace _STL
{
template<> _List_base<Rva0036ADF9Element, allocator<Rva0036ADF9Element> >::~_List_base();
// Branch-form int overloads: this TU's flags compile the generic max/min ?:
// to cmov, but retail's out-of-line copies use a branch (row 57 family-LK3).
inline const int &(max)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pa < *__pb) return __b; return __a; }
inline const int &(min)(const int &__a, const int &__b)
{ const int *__pa = &__a, *__pb = &__b; if (*__pb < *__pa) return __b; return __a; }
}


// BFME 2's bit numbers of the statuses, conditions and disabled type these bodies pass; Zero Hour's
// enumerators of the same names have other values.
static const ObjectStatusTypes OBJECT_STATUS_STATUS_3 = (ObjectStatusTypes)3;
static const ObjectStatusTypes OBJECT_STATUS_STATUS_5 = (ObjectStatusTypes)5;
static const ObjectStatusTypes BFME_OBJECT_STATUS_AFLAME = (ObjectStatusTypes)10;
static const ObjectStatusTypes BFME_OBJECT_STATUS_BURNED = (ObjectStatusTypes)11;
static const ObjectStatusTypes OBJECT_STATUS_STATUS_82 = (ObjectStatusTypes)82;
enum
{
	BFME_MODELCONDITION_AFLAME = 2 * 32 + 14,
	BFME_MODELCONDITION_SMOLDERING = 2 * 32 + 16,
	BFME_MODELCONDITION_FLAG_190 = 5 * 32 + 30,
	BFME_MODELCONDITION_FLAG_191 = 5 * 32 + 31
};
static const DisabledType DISABLED_TYPE_4 = (DisabledType)4;

class Drawable
{
public:
	void rva00274176(Bool set);
	Bool rva00272835(Int boneName, Int transform);
};

class BfmeModelConditionBits
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

// The two-pointer range the contain's slot 70 returns by value; the rowed
// 0x0036AE51 turns it into a list.

class ContainModuleSlots
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

// The body's slot 10 (retail call [edx+0x28] from the burn start and end).
class BodyModuleSlots
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

// The Object fields at their retail offsets; the header's Thing base and Object keep Zero Hour's
// layout there.
struct FlammableObjectView
{
	void *m_vtable;
	const ThingTemplate *m_template; // +0x04
	char m_unknown08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	char m_unknown44[0x10C - 0x44];
	BfmeModelConditionBits m_modelConditionFlags; // +0x10C
	char m_unknown158[0x250 - 0x158];
	ContainModuleSlots *m_contain; // +0x250
	BodyModuleSlots *m_body; // +0x254
	AIUpdateInterface *m_ai; // +0x258
};

static __forceinline void setModelConditionBit(Object *me, unsigned int mc)
{
	FlammableObjectView *view = (FlammableObjectView *)me;
	if (view->m_modelConditionFlags.test(mc) == 0)
	{
		view->m_modelConditionFlags.set(mc);
		me->rva0028AE6D();
	}
}

static __forceinline void clearModelConditionBit(Object *me, unsigned int mc)
{
	FlammableObjectView *view = (FlammableObjectView *)me;
	if (view->m_modelConditionFlags.test(mc) != 0)
	{
		view->m_modelConditionFlags.clear(mc);
		me->rva0028AE6D();
	}
}

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
extern int BfmeLogicFramesPerSecond;

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

// DelayedLuaEventList: ctor 0x000B6D8B and virtual dtor 0x000B6DD2 (slot 0 of its
// vftable 0x007C9CF0 is the scalar deleting dtor 0x000B6E0C); the vptr is the +0 word.
// BfmeDelayedLuaEventList is only the parameter tag of the 0x003360D2 row.
struct BfmeDelayedLuaEventList;
struct DelayedLuaEventList
{
	DelayedLuaEventList();
	virtual ~DelayedLuaEventList();
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
// an address-derived method name, and its calcNextSpreadDelay sibling
// carries the FireSpreadUpdate.cpp file literal.

// One FireFX entry: the effect and the bone it plays at (BFME 1's parser
// builds the same pair, also address-named). Retail copies it through the
// folded {dword, AsciiString} copy constructor at 0x000CF475; the type's own
// name is unknown.
// Spelled as the rowed twin TreeKey00242F5E (stlport_rb_tree_hint_00242f5e.cpp)
// so the copy binds to that row.
struct TreeKey00242F5E
{
	const FXList *fx;
	AsciiString boneName;
	TreeKey00242F5E(const TreeKey00242F5E &that);
};
typedef TreeKey00242F5E Rva000CF475FireFX;

// BFME2 reads the GameLogic frame at +0x40, four past the reference header's
// +0x3C (DeletionUpdate_calcSleepDelay precedent). TU-local view so the shared
// header stays untouched; every getFrame site below wants the retail offset.
class FlammableGameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad[ 0x40 ];
	UnsignedInt m_frame;
};

// BFME 2 keeps the logic frame rate in a global (0x009BA4E4).
extern int BfmeLogicFramesPerSecond;

// The module data's +0x28 vector holds these entries.
static __forceinline const _STL::vector<Rva000CF475FireFX> &fireFXList(const FlammableUpdateModuleData *data)
{
	return reinterpret_cast<const _STL::vector<Rva000CF475FireFX> &>(data->m_fireMarkers);
}

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
	m_status = me->testStatus(BFME_OBJECT_STATUS_BURNED) ? FS_BURNED : FS_NORMAL;
	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
	m_aflameEndFrame = 1;
	setWakeFrame(me, UPDATE_SLEEP_NONE);
	me->setStatus(OBJECT_STATUS_STATUS_3, false);
	me->setStatus(OBJECT_STATUS_STATUS_5, false);
	if (data->m_setBurnedStatus)
	{
		me->setStatus(BFME_OBJECT_STATUS_BURNED, true);
		setModelConditionBit(me, BFME_MODELCONDITION_SMOLDERING);
	}
	me->rva0028EBDA(false);

	static const NameKeyType key_EntEnragedUpdate = TheNameKeyGenerator->nameToKey("EntEnragedUpdate");
	Module *enraged = me->findModule(key_EntEnragedUpdate);
	if (enraged)
	{
		((Rva002918E0Object *)enraged)->rva004B239A(0, 0);
		((Rva002918E0Object *)enraged)->set(0);
	}

	if (data->m_swapModelWhenQuenched)
		clearModelConditionBit(me, BFME_MODELCONDITION_FLAG_190);
	if (data->m_swapTextureWhenQuenched)
		clearModelConditionBit(me, BFME_MODELCONDITION_FLAG_191);
	if (data->m_swapModelWhenQuenched || data->m_swapTextureWhenQuenched)
		me->getDrawable()->rva00274176(true);

	DelayedLuaEventList list;
	((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(BFME_OBJECT_STATUS_BURNED, me, (BfmeDelayedLuaEventList *)&list);

	stopBurningSound();
	me->setStatus(BFME_OBJECT_STATUS_AFLAME, false);
	clearModelConditionBit(me, BFME_MODELCONDITION_AFLAME);
	if (data->m_panicLocomotorWhileAflame && m_flag4C)
	{
		AIUpdateInterface *ai = ((FlammableObjectView *)me)->m_ai;
		if (ai)
		{
			ai->m_flag3C9 = false;
			((FlammableObjectView *)me)->m_ai->rva142(0);
			m_flag4C = false;
		}
	}
	((FlammableObjectView *)me)->m_body->updateAflame();
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
		me->setStatus(BFME_OBJECT_STATUS_AFLAME, true);
		((FlammableObjectView *)me)->m_body->updateAflame();
		setModelConditionBit(me, BFME_MODELCONDITION_AFLAME);
		rva0048C7BF();

		static const NameKeyType key_FireSpreadUpdate = TheNameKeyGenerator->nameToKey("FireSpreadUpdate");
		FireSpreadUpdate *fu = (FireSpreadUpdate *)getObject()->findModule(key_FireSpreadUpdate);
		if (fu != 0)
			fu->startFireSpreading();

		m_status = FS_AFLAME;

		DelayedLuaEventList list;
		((BfmeObjectEventDispatch *)TheLuaScriptEngine)->rva003360D2(BFME_OBJECT_STATUS_AFLAME, me, (BfmeDelayedLuaEventList *)&list);

		const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
		UnsignedInt now = ((FlammableGameLogic *)TheGameLogic)->getFrame();
		if (data->m_aflameDuration > 0)
			m_aflameEndFrame = now + data->m_aflameDuration;
		else
			m_aflameEndFrame = 0x3fffffff;
		m_burnedEndFrame = data->m_burnedDelay ? now + data->m_burnedDelay : 0;
		m_damageEndFrame = data->m_aflameDamageDelay ? now + data->m_aflameDamageDelay : 0;

		setWakeFrame(m_object, calcSleepTime());

		if (data->m_swapModelWhenAflame)
			setModelConditionBit(me, BFME_MODELCONDITION_FLAG_190);
		if (data->m_swapTextureWhenAflame)
			setModelConditionBit(me, BFME_MODELCONDITION_FLAG_191);
		if (data->m_swapModelWhenAflame || data->m_swapTextureWhenAflame)
			me->getDrawable()->rva00274176(true);

		for (_STL::vector<Rva000CF475FireFX>::const_iterator it = fireFXList(data).begin(); it != fireFXList(data).end(); )
		{
			Rva000CF475FireFX info = *it;
			if (!info.boneName.isEmpty() && getObject()->getDrawable())
			{
				Matrix3D mtx(true);
				getObject()->getDrawable()->rva00272835((Int)info.boneName.str(), (Int)&mtx);
				Coord3D pos;
				pos.x = mtx[0][3];
				pos.y = mtx[1][3];
				pos.z = mtx[2][3];
				FXList::doFXPos(info.fx, &pos, &mtx);
			}
			else
			{
				FXList::doFXObj(info.fx, getObject());
			}
			++it;
		}

		if (data->m_customAnimAndDuration.m_frames > 0)
		{
			me->setSpecialModelConditionState((ModelConditionFlagType)data->m_customAnimAndDuration.m_animType, data->m_customAnimAndDuration.m_frames);
			me->setDisabledUntil(DISABLED_TYPE_4, ((FlammableGameLogic *)TheGameLogic)->getFrame() + data->m_customAnimAndDuration.m_frames - 1);
			m_specialConditionEndFrame = ((FlammableGameLogic *)TheGameLogic)->getFrame() + data->m_customAnimAndDuration.m_frames;
			me->setStatus(OBJECT_STATUS_STATUS_82, true);
		}
		else
		{
			m_specialConditionEndFrame = ((FlammableGameLogic *)TheGameLogic)->getFrame();
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
	if (damageInfo->out.m_actualDamageClipped > 0.0f)
		m_lastIgniterID = damageInfo->in.m_sourceID;

	Object *me = getObject();
	Bool underwater = !(((const FlammableObjectView *)me)->m_template->m_kindOf11C & 0x80000000)
		&& TheTerrainLogic->isUnderwater(((const FlammableObjectView *)me)->m_pos.x, ((const FlammableObjectView *)me)->m_pos.y);

	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
	if ((data->m_damageType == 0 || data->m_damageType == damageInfo->in.m_damageType) && !underwater)
	{
		Int now = ((FlammableGameLogic *)TheGameLogic)->getFrame();
		Int since = now - (Int)data->m_flameDamageExpirationDelay;
		if (since > (Int)m_lastFlameDamageDealt)
			m_flameDamageLimit = data->m_flameDamageLimitData;
		m_lastFlameDamageDealt = now;

		if (!me->testStatus(BFME_OBJECT_STATUS_AFLAME) && !me->testStatus(BFME_OBJECT_STATUS_BURNED))
		{
			m_flameDamageLimit -= damageInfo->out.m_actualDamageDealt;
			if (m_flameDamageLimit <= 0.0f)
			{
				m_flameDamageLimit = 0.0f;
				tryToIgnite();
				if (data->m_burnContained && ((FlammableObjectView *)me)->m_contain)
				{
					Rva00263895Member damageRecord;
					DamageInfo &info = *(DamageInfo *)&damageRecord;
					info.in.m_amount = (Real)_STL::max(data->m_aflameDamageAmount / 2, 1);
					info.in.m_sourceID = me->getID();
					info.in.m_damageType = DAMAGE_FLAME;
					info.in.m_deathType = DEATH_BURNED;
					ContainmentList contained = ((FlammableObjectView *)me)->m_contain->rva70().rva0036AE51();
					for (ContainmentList::iterator it = contained.begin(); it != contained.end(); )
					{
						Object *obj = (Object *)containmentFirstWord(*it);
						++it;
						if (obj)
							obj->attemptDamage(&info);
					}
				}
				else
				{
					ContainModuleSlots *contain = ((FlammableObjectView *)me)->m_contain;
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
	UnsignedInt now = ((FlammableGameLogic *)TheGameLogic)->getFrame();
	const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();

	if (m_specialConditionEndFrame > 0)
	{
		if (now >= m_specialConditionEndFrame)
		{
			m_specialConditionEndFrame = 0;
			if (data->m_runToWater)
			{
				const Coord3D *pos = &((const FlammableObjectView *)me)->m_pos;
				Coord3D best;
				best.x = 10000000.0f;
				best.y = 10000000.0f;
				best.z = 10000000.0f;
				AIUpdateInterface *ai = ((FlammableObjectView *)me)->m_ai;
				if (ai)
				{
					Real radius = data->m_runToWaterSearchRadius;
					Real step = data->m_runToWaterSearchIncrement;
					for (Real x = (Real)(Int)(pos->x - radius); pos->x + radius >= x; x = (Real)(Int)(x + step))
					{
						// A second pointer for the row bounds: retail loads row->y before
						// adding the radius, which the shared pos pointer does not give.
						const Coord3D *row = pos;
						for (Real y = (Real)(Int)(row->y - radius); row->y + radius >= y; y = (Real)(Int)(y + step))
						{
							if (TheTerrainLogic->Rva0027D815(x, y) > getFlammableUpdateModuleData()->m_runToWaterDepth)
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
						if (data->m_panicLocomotorWhileAflame)
						{
							AIUpdateInterface *aIUpdate = ((FlammableObjectView *)me)->m_ai;
							if (aIUpdate)
							{
								aIUpdate->rva142(4);
								((FlammableObjectView *)me)->m_ai->m_flag3C9 = true;
								m_flag4C = true;
							}
						}
						ai->aiMoveToPosition(&best, (CommandSourceType)1);
						m_fleeing = true;
						TheGameLogic->deselectObject(me, (UnsignedInt)0xFFFFF, true);
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

	if (!(((const FlammableObjectView *)me)->m_template->m_kindOf11C & 0x80000000)
		&& TheTerrainLogic->isUnderwater(((const FlammableObjectView *)me)->m_pos.x, ((const FlammableObjectView *)me)->m_pos.y))
	{
		AIUpdateInterface *ai = ((FlammableObjectView *)me)->m_ai;
		if (ai && !ai->isMoving())
		{
			m_aflameEndFrame = _STL::min((UnsignedInt)(BfmeLogicFramesPerSecond * 3 + ((FlammableGameLogic *)TheGameLogic)->getFrame()), m_aflameEndFrame);
			m_fleeing = false;
		}
	}

	if (m_damageEndFrame != 0 && now >= m_damageEndFrame)
	{
		m_damageEndFrame = now + data->m_aflameDamageDelay;
		doAflameDamage();
	}
	if (m_burnedEndFrame != 0 && now >= m_burnedEndFrame && data->m_setBurnedStatus)
	{
		me->setStatus(BFME_OBJECT_STATUS_BURNED, true);
		setModelConditionBit(me, BFME_MODELCONDITION_SMOLDERING);
	}
	if (m_aflameEndFrame != 0 && now >= m_aflameEndFrame)
		rva0048C8F9();
	return calcSleepTime();
}
