// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7 /Ireference/shims/bfmelist /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// Overrides of the interface HordeContain carries at +0x11C (vtable
// 0x00C44C58 installed by the pinned HordeContain ctor 0x0046F543; inherited by
// the matched HorseHordeContain, vtable 0x00C45838). Compiled with the +0x11C
// subobject this (cl 7.1 folds the adjustment into [ecx-0x114] for the Object at
// +8 and [ecx-0x118] for the ModuleData at +4). Names by address.
// Retail 0x0046BB38 (55 bytes), slot 6: true when the other Object +0x274 points
// at our Object, else whether its ID (+0x74, read through a by-value getter, the
// temporary retail stores in the argument slot) is a key of the map<int,int> at
// +0x170 (matched _Rb_tree::_M_find 0x00388F63); written as if/return, the form
// that gives the direct setne.
// Retail 0x0046D1AC (75 bytes), slot 9: the only name of the AsciiString list at
// module data +0xA4, else AsciiString::TheEmptyString, returned by value.
// Keep math.h's float cos overload local: every use here is inlined, and this
// unit's out-of-line copy (only its own FPO record refers to it) is not retail's
// (0x0002FBC0). Exported, it would be the first in retail-truth-5 link order.
static float __cdecl cos(float);
#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>

// Retail compares typed list nodes inline, as in NetPacket.cpp.
namespace _STL {
template <class T, class L, class R>
static __forceinline bool operator!=(const _List_iterator<T, L> &a, const _List_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}

#include <map>
#include <hash_map>
#include <set>
#include <vector>
// Import-inline: this unit's bfmealloc _Vector_base<Object*> dtor copy is not retail's
// EH-framed body (0x001F1609); its uses here are all inlined, so none is emitted.
class Object;
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
#include <math.h>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../../Common/PartitionRangeQueryCallView.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}


// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
// The +0x258 map's comparator: a per-RVA stand-in for less<unsigned short>,
// so its instance names (operator[] 0x00470041 and the folded callees it
// reaches) stay placeholders.
struct Rva00470041Less : public _STL::less<unsigned short> {};
// Coord3D: shared header/view; no private copy.
// Preserve inline multiplies without emitting a nonretail scale copy.
#define BFME_COORD3D_INLINE_SCALE_LINK
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"
#undef BFME_COORD3D_INLINE_SCALE_LINK
#include "../../../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// The float triple whose length is the address-owned copy 0x00003571.
class Rva0055A627Difference
{
public:
	float x, y, z;
	float length() const;
};
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum WeaponSetType
{
	WEAPONSET_18 = 0x18,
	WEAPONSET_19 = 0x19,
	WEAPONSET_1A = 0x1A
};
#include "../../../Common/GameLogicObjectLookupView.h"
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
extern int BfmeLogicFramesPerSecond;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class Object;
class UpgradeTemplate;
class Rva004708BCBehavior;
class AttributeModifierPoolUpdate
{
public:
	bool addModifierToPool(const AsciiString &name, int a2);
	void rva00403744(const AsciiString &name);
};
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
// A store category: +0x0C is its index.
struct Rva0046DB6DCategory
{
	unsigned char m_pad00[0x0C];
	int m_index; // +0x0C
};
class AttributeModifierStore
{
public:
	int rva00214713(int key);
	void *GetCategoryContainer(int index);
};
extern AttributeModifierStore *TheAttributeModifierStore;
enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int a1, CommandSourceType cmdSource);
	void rva0026C2D9(Object *obj, int a2, CommandSourceType cmdSource);
	void rva0026C347(Object *obj, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
// Retail's random calls carry this source path literal.
#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
// The record is the player's SkirmishAI; 0x002C6AA8 is its rowed onHordeCreated.
class SkirmishAI
{
public:
	void onHordeCreated(Object *horde, Object *member);
};
struct Rva002A8AB1Record : SkirmishAI
{
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *TheSkirmishAIManager;
class LocomotorSet;
class Pathfinder
{
public:
	bool IsPointOnWall(int pos, bool flag);
	void AdjustLayer(Object *obj);
	bool AdjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
	bool IsPointOnRamp(const Coord3D *pos);
	void RemoveObjectFromPathfindMap(Object *object);
	void RemoveObjectGoalFromPathfindMap(Object *object);
	bool IsValidMovementPositionForObject(const Coord3D *pos, int layer, int surfaces, const Object *obj);
};
struct Rva00372571Params
{
	const Coord3D *m_pos;
	bool m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	bool m_1C;
};
class AIGroup
{
public:
	void add(Object *obj);
	void groupMoveToPosition(Rva00372571Params *params, int source);
};
class AttackPriorityInfo;
class PartitionFilter;
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers, const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int a6);
	static bool rva002FE193(Object *obj, Object *victim);	// rowed 0x002FE193
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
	Pathfinder *pathfinder() { return m_pathfinder; }
};
extern AI *TheAI;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class Team;
struct Vector4
{
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}
	float X;
	float Y;
	float Z;
	float W;
};
class Matrix3D
{
public:
	__forceinline Matrix3D(const Matrix3D &matrix3D)
	{
		Row[0] = matrix3D.Row[0];
		Row[1] = matrix3D.Row[1];
		Row[2] = matrix3D.Row[2];
	}
	Vector4 Row[3];
};
// The Drawable's position, under its placeholder pin.
class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};
class Drawable : public Rva00276470Drawable
{
public:
	void rva00272BE7();
	void rva00272BAB(int a1, int a2);
	void rva00274176(bool a1);
	void rva00272945(int a);
	void colorFlash(const RGBColor *color, unsigned int a2, unsigned int a3, unsigned int a4);
};
class Thing
{
public:
	void setPositionZ(float z);
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
	const Coord3D *getUnitDirectionVector2D() const;
	Drawable *getDrawable() const;
};
class GlobalData
{
public:
	unsigned char m_pad000[0x9A6];
	bool m_useSimpleHordeDecals; // +0x9A6
	unsigned char m_pad9A7[0x1230 - 0x9A7];
	int m_maxNumMembersToForceToImmediatelyEnter; // +0x1230
	int m_waitToForceMemberToEnterDelay; // +0x1234
};
extern GlobalData *TheWritableGlobalData;
class Player;
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;
struct Rva003642DFNode;
struct Rva003642DFResult;
struct Rva00468C37Holder;
// The AI's +0x140 path.
class Rva003638BA
{
public:
	bool rva003638BA();
	bool rva00363AD7();
};
// 0x00364521, the rowed Path member: the path point for the +0x1F0 member's
// distance (returns the 16-byte node+position value of 0x003642DF).
class Rva0008BB38FloatField;
class Path
{
public:
	Rva003642DFResult rva00364521(const Rva0008BB38FloatField *field);
};
// What 0x003642DF/0x00364521 return by value (16 bytes): a node and a
// position; 0x001E3511 reads its node's level value (0x7FFFFFFF without one).
struct Rva003642DFResult
{
	Rva003642DFNode *m_node; // +0x00
	Coord3D m_pos; // +0x04
};
struct Rva003642DFNode
{
	unsigned char m_pad00[0x08];
	int m_08; // +0x08
};
class Rva001E3511
{
public:
	int rva001E3511();
};
struct Rva00468C37Template
{
	unsigned char m_pad000[0x150];
	unsigned char m_150; // +0x150
};
struct Rva00468C37Holder
{
	unsigned char m_pad0[0x4];
	const Rva00468C37Template *m_4; // +0x04
};
template <int N> class Rva00468D11Slots : public Rva00468D11Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00468D11Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};
// TheTerrainLogic: only slot 35 (a level/portal query, unnamed) is called.
class TerrainLogic : public Rva00468D11Slots<35>
{
public:
	virtual int slot35(int level) = 0;
};
extern TerrainLogic *TheTerrainLogic;
class AIUpdateInterfaceSlots : public Rva00468D11Slots<110>
{
public:
	virtual bool rva0047306ESlot110() = 0;
	virtual bool rva0046A46FSlot111() = 0;
	virtual void gap112() = 0;
	virtual bool rva0047306ESlot113() = 0;
	virtual bool rva00468D11Slot114() = 0;
	virtual bool rva00468D2CSlot115() = 0;
	virtual void gap116() = 0; virtual void gap117() = 0; virtual void gap118() = 0; virtual void gap119() = 0;
	virtual void gap120() = 0; virtual void gap121() = 0; virtual void gap122() = 0; virtual void gap123() = 0;
	virtual void gap124() = 0; virtual void gap125() = 0; virtual void gap126() = 0; virtual void gap127() = 0;
	virtual void gap128() = 0; virtual void gap129() = 0; virtual void gap130() = 0; virtual void gap131() = 0;
	virtual void gap132() = 0; virtual void gap133() = 0;
	virtual void rva0046DDC5Slot134(int a1, int a2) = 0;
	virtual void gap135() = 0; virtual void gap136() = 0; virtual void gap137() = 0; virtual void gap138() = 0;
	virtual void gap139() = 0; virtual void gap140() = 0; virtual void gap141() = 0;
	virtual void slot142(int value) = 0;
};
class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
	bool isMoving() const;
	void rva00262D2D();
	Object *getCurrentVictim() const;
	int rva00260DED() const;
	unsigned char m_pad004[0x20 - 0x04];
	AICommandInterface m_command; // +0x20
	void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }
	unsigned char m_pad024[0x140 - 0x24];
	Rva003638BA *m_140; // +0x140
	unsigned char m_pad144[0x1CC - 0x144];
	unsigned char m_1CC[0x1F0 - 0x1CC]; // +0x1CC (the LocomotorSet slot 4 hands the pathfinder)
	Rva00468C37Holder *m_1F0; // +0x1F0
	// Keep the inline address calculation without emitting a competing private-view copy.
	__declspec(dllimport) __forceinline const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_1CC; }
	// The rowed 0x0026594F under its row spelling, for the slot-111 caller.
	void moveThroughPortalWithMicropath(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer, const Coord3D *a5, const Coord3D *a6);
	unsigned char m_pad1F4[0x1FC - 0x1F4];
	int m_1FC; // +0x1FC
};
class ModuleData;
// ModuleInfo: a vector of 0x14-byte entries.
class ModuleInfo
{
public:
	struct Entry
	{
		unsigned char m_pad[0x14];
	};
	__declspec(dllimport) int getCount() const { return m_end - m_begin; }
	const ModuleData *getNthData(int i) const;
	Entry *m_begin; // vector<Entry>
	Entry *m_end;
	Entry *m_cap;
};
// Retail 0x001E4426, the kind-of bit test of the header-inline ThingTemplate::isKindOf; both
// bodies are visible, so cl knows a kind-of test stores nothing (slot 69 relies on it).
__declspec(noinline) inline bool Rva001E4426Test(const unsigned int *bits, int bit)
{
	return (bits[(unsigned int)bit >> 5] & (1U << (bit & 31))) != 0;
}
enum KindOfType { KINDOF_INVALID = -1 };
class ThingTemplate
{
public:
	// Retail 0x000456AC: the kind-of bit words start at +0x108.
	__declspec(noinline) bool isKindOf(KindOfType t) const { return Rva001E4426Test(&m_108, t); }
	bool isEquivalentTo(const ThingTemplate *other) const;
	// This local +0x114 mask view must not emit the generic +0x108 kind helper.
	__forceinline unsigned int hordeKindMask(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x64];
	AsciiString m_64; // +0x64 (template name)
	unsigned char m_pad068[0x108 - 0x68];
	union { unsigned int m_108; struct { unsigned char m_108b; unsigned char m_109; }; };
	// WorldBuilder 0x010C7070 tests bit 0xB of the +0x108 flag word through an
	// out-of-line BitFlags test; retail inlines it as the +0x109 & 8 byte test.
	bool testFlag108(int bit) const { return (m_108 & (1U << bit)) != 0; }
	unsigned char m_pad10C[0x114 - 0x10C];
	unsigned int m_kindOf[4]; // +0x114
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo; // +0x2E4
	unsigned char m_pad2F0[0x528 - 0x2F0];
	float m_geometryFrontAngle; // +0x528 (an angle slot 130 adds to a wall's orientation)
	unsigned char m_pad52C[0x5D8 - 0x52C];
	short m_5D8; // +0x5D8
};
class Rva0028C197Slot149 : public Rva00468D11Slots<149>
{
public:
	virtual bool slot149() = 0;
};
float Sin(float x);
float Cos(float x);
// The tracker's 0x0039B3D1 entry, under the owner name its pin (read from
// ScriptActions::rva003BC93C) already carries.
class Rva003BD306Target
{
public:
	void rva0039B3D1(float value, bool flag);	// 0x0039B3D1
};
// Object +0x264: the experience tracker; +0x10 is the value slots 30 and 49
// record per template.
class ExperienceTracker : public Rva003BD306Target
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2);	// 0x0039B4EC
	unsigned char m_pad00[0x10];
	float m_10; // +0x10
	unsigned char m_pad14[0x24 - 0x14];
	int getVeterancyLevel() const { return m_24; }
	int m_24; // +0x24 (slot 48 compares it across 0x0039B3D1)
};
// The Object +0x254 module: slot 5 gives a float.
class Rva0046B850Module : public Rva00468D11Slots<5>
{
public:
	virtual float slot5() = 0;
	virtual void m254gap6() = 0; virtual void m254gap7() = 0; virtual void m254gap8() = 0; virtual void m254gap9() = 0;
	virtual void m254gap10() = 0; virtual void m254gap11() = 0; virtual void m254gap12() = 0; virtual void m254gap13() = 0;
	virtual void m254gap14() = 0; virtual void m254gap15() = 0; virtual void m254gap16() = 0; virtual void m254gap17() = 0;
	virtual ObjectID slot18() = 0;
};
// The Object +0x250 module: slot 58 answers for another Object.
class Rva0046A2ECContain : public Rva00468D11Slots<58>
{
public:
	virtual bool slot58(Object *other) = 0;
};
// The same module's slot 39, handed a member Object.
class Rva0046A2ECSlot39 : public Rva00468D11Slots<39>
{
public:
	virtual void slot39(Object *obj) = 0;
};
// The weapon's float range query is the rowed 0x002C9B80 (its row names the
// owner Rva002C9B80Owner).
class Object;
// The Weapon +4 byte field (rowed getter 0x002C9400).
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *victim, float rangeBonus = 0.0f, int useAimPos = 1) const;	// pinned 0x002CB933
	float getAttackRange(const Object *source) const;	// rowed 0x002C9BF8
	unsigned char m_pad00[0x04];
	const Rva002C9400ByteField *m_04; // +0x04
};
class Rva002C9B80Owner
{
public:
	float rva002C9B80(void *obj, float bonus);
};
enum WeaponSlotType;
class Module;
// Retail's shared 76-byte copy constructor at 0x00045455. Object's
// verified 0x0028CFB2 uses this same storage view for model conditions.
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
	unsigned int m_words[19];
};
struct Rva00469F3AFlags
{
	unsigned int m_words[19];
	__forceinline void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 31);
	}
	__forceinline void intersect(const unsigned int *words)
	{
		for (unsigned int i = 0; i < 19; ++i)
			m_words[i] &= words[i];
	}
	__forceinline void flip()
	{
		for (unsigned int i = 0; i < 19; ++i)
			m_words[i] = ~m_words[i];
	}
};
template <int N> class BitFlags;
template <> class BitFlags<11> {
    unsigned int m_bits[1];
public:
    bool any() const;
};

class Object
{
public:
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
	bool isKindOf(KindOfType kind) const;
	const ThingTemplate *getTemplate() const { return m_template; }
	ExperienceTracker *getExperienceTracker() const { return m_264; }
	bool isDisabled() const { return m_disabledMask.any(); }
	void rva00293077(const void *upgrade); // rowed 0x00293077

	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);	// pinned 0x0028AEBD
	int getID() const { return m_74; }
	void setProducer(Object *);
	__forceinline unsigned int testCondition(int bit) const
	{
		return m_conditionWords[bit >> 5] & (1U << (bit & 0x1f));
	}
	__forceinline void clearCondition(int bit)
	{
		m_conditionWords[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
	bool test110(int bit) const { return ((m_110 >> bit) & 1) != 0; }
	const Coord3D *getPosition() const { return &m_position; }
	bool isEquivalentTemplate(const ThingTemplate *thingTemplate) const { return m_template->isEquivalentTo(thingTemplate); }
	// This local +0x114 mask view must not emit the generic +0x108 kind helper.
	__forceinline unsigned int hordeKindMask(int kind) const
	{
		return m_template->m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_position; // +0x38
	float m_orientation; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	int m_74; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	float m_B8; // +0xB8
	unsigned char m_padBC[0x10C - 0xBC];
	union
	{
		unsigned int m_conditionWords[2]; // +0x10C (model-condition bits)
		struct
		{
			unsigned int m_10C;
			unsigned int m_110; // +0x110
		};
	};
	unsigned char m_pad114[0x1C8 - 0x114];
	BitFlags<11> m_disabledMask;
	unsigned char m_pad1CC[0x244 - 0x1CC];
	Rva004708BCBehavior **m_244; // +0x244
	unsigned char m_pad248[0x250 - 0x248];
	Rva0046A2ECContain *m_250; // +0x250
	Rva0046B850Module *m_254; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_264; // +0x264
	unsigned char m_pad268[0x274 - 0x268];
	Object *m_274; // +0x274
	unsigned char m_pad278[0x284 - 0x278];
	int m_284; // +0x284
	unsigned char m_pad288[0x304 - 0x288];
	int m_304; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_438; // +0x438
	unsigned char m_pad439[0x44C - 0x439];
	int m_44C; // +0x44C
	unsigned char m_pad450[0x45C - 0x450];
	int m_45C; // +0x45C
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	void rva0028AD32();
	Object *rva002931F5(bool flag);
	bool hasUpgradeMask(int a1) const;
	void setTeam(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void clearModelConditionStateForHorde(ModelConditionFlagType flag);
	void setModelConditionStateForHorde(ModelConditionFlagType flag);
	void rva001E42F2(const int *value);
	void rva0028B95F();
	unsigned char rva00290FBB() const;
	int rva0028B511() const;
	void setLayer(PathfindLayerEnum layer);
	void rva0028AE6D();
	void rva0029A12B();
	void defect(Object *source, bool flag);
	void bfmeTransferReplacementState(Object *replacement);
	void setWeaponSetFlag(WeaponSetType flag);
	void rva0028CFB2(const int *a, const int *b);
	void rva0028D412(const Matrix3D *mtx);	// rowed transform setter 0x0028D412
	void teleportTo(const Coord3D *pos, bool flag);	// rowed 0x0029660C
	float GetRelativeAngle(const Coord3D *pos) const;
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
	float getVisionRange() const;
	bool GetGoalPosition(Coord3D *pos) const;
	float GetGoalAngle() const;
	int GetGoalLayer() const;
	void rva0028ACEE(int a1, int a2);
	void rva00295F05(bool flag);	// rowed 0x00295F05
	void *rva0028C197() const;	// rowed 0x0028C197 (+0x250 interface slot 31)
protected:
	friend class HordeContain;
	Module *findModule(NameKeyType key) const;
public:
	bool addAttributeModifierToPool(const AsciiString &name, int a2);
	void rva0029041B(Player *player);
	bool isLocallyControlled() const;
	void removeAttributeModifierFromPool(const AsciiString &name);
private:
	friend class HordeContain;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};
typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;
// findObjectByID is the header inline over the object hash map at +0xB4;
// cl calls its out-of-line copy 0x00049DC5.
// The Generals header's inline findObjectByID over the object hash; the
// canonical view models the map at +0xB4 as ObjectIdMap, so this body views
// it as the STLport hash_map. MSVC still calls the out-of-line copy
// 0x00049DC5, but only this inline body gives retail's register homes.
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectPtrHash &objHash = reinterpret_cast<ObjectPtrHash &>(m_map);
	ObjectPtrHash::iterator it = objHash.find(id);
	if (it == objHash.end())
		return 0;
	return (*it).second;
}
extern GameLogic *TheGameLogic;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern class ThingFactory *TheThingFactory;
struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};
struct Rva00462D35Mapped
{
	Rva00462D35Mapped() : m_bits(0) {}
	unsigned int m_bits;
};
// Retail erases from the +0x170 ID set through 0x0046EDEF, the STLport
// erase(const key &) body ICF shares with the int map: it calls map<int, int>'s
// equal_range (0x002F1C89) and the erase-range body 0x0046A967 (rowed as
// Rva002EE9B7::rva0046A967 in RvaTreeEraseRangeFamily.cpp). Spelled that way,
// this unit's copy carries retail's callees.
class Rva002EE9B7
{
public:
	void rva0046A967(_STL::_Rb_tree<int, _STL::pair<const int, void *>, _STL::_Select1st<_STL::pair<const int, void *> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > >::iterator first,
		_STL::_Rb_tree<int, _STL::pair<const int, void *>, _STL::_Select1st<_STL::pair<const int, void *> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > >::iterator last);
};
namespace _STL {
template <> inline _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::size_type
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::erase(const int &x)
{
	typedef _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > > IntIntTree;
	typedef _Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >, less<int>, allocator<pair<const int, void *> > > IntPtrTree;
	pair<IntIntTree::iterator, IntIntTree::iterator> q = reinterpret_cast<IntIntTree *>(this)->equal_range(x);
	size_type n = distance(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	reinterpret_cast<Rva002EE9B7 *>(this)->rva0046A967(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	return n;
}
}
// The module data's +0x188-record lookup (its result carries a template name
// at +4).
class Rva00469294
{
public:
	void *rva00469294(int key);
	char *findEntry(int key) { return (char *)rva00469294(key); }
};
// A +0x188 record: the key the module data's +0x1B8 map is searched for.
struct Rva00472329Record
{
	int m_key; // +0x00
	float m_04; // +0x04
	float m_08; // +0x08
	unsigned char m_pad0C[0x1C - 0x0C];
};
// HordeContain's out-of-line Object tests, defined below ahead of their caller
// performReform: 0x004693AD matches the Object's ID against +0x264/+0x26C or
// its template flag, 0x0046ACF6 finds an ID's +0x188 record index in +0x17C.
struct Rva004693ADFlag109
{
	unsigned char m_pad[0x109];
	unsigned char m_flags;
};
struct Rva004693ADArg
{
	char m_pad00[4];
	Rva004693ADFlag109 *m_04;
	char m_pad08[0x6C];
	int m_74;
};
class Rva004693AD
{
public:
	bool rva004693AD(Rva004693ADArg *arg);
private:
	char m_pad[0x264];
	int m_264;
	int m_pad268;
	int m_26C;
};
class Rva0046ACF6
{
public:
	int rva0046ACF6(int key);
private:
	char m_pad[0x17C];
	_STL::map<int, int> m_map;
};
// The 8-byte record slot 137 hands back by value.
class Rva002390CB
{
	void *m_00;
	void *m_04;
public:
	Rva002390CB();
	__declspec(nothrow) Rva002390CB(const Rva002390CB &other);
	~Rva002390CB();
};
// A module data +0x198 entry: found by its leading name, carries the record
// slot 137 copies out at +8.
struct Rva0046D158Record
{
	AsciiString m_name; // +0x00
	unsigned char m_pad04[0x08 - 0x04];
	Rva002390CB m_08; // +0x08
};
// Returns its argument (eax after the stores), which slot 62 consumes.
class Rva0046247D
{
public:
	// Rowed at 0x0046247D (Rva0046247DCondPair.cpp); visible and kept out of
	// line so callers know the pair it fills keeps no pointer to it.
	__declspec(noinline) void *rva0046247D(Rva0046247DPair &p)
	{
		void *base = this;
		char *field = (char *)base + 0x20;
		p.m00 = base ? field : 0;
		p.m04 = (const _STL::list<Object *> *)((char *)base + 0x54);
		return &p;
	}
};
// Counts the nodes of the pair's +4 list.
class Rva00291793
{
public:
	int rva00291793();
};
// The +0x2C8 helper: slot 4 resets it, slot 14 answers for an Object.
class Rva00468FDCHelper : public Rva00468D11Slots<3>
{
public:
	virtual void slot3(Object *target) = 0;
	virtual void rva00468FDCSlot4() = 0;
	virtual void gap5() = 0; virtual void gap6() = 0; virtual void gap7() = 0; virtual void gap8() = 0;
	virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0; virtual void gap12() = 0;
	virtual void gap13() = 0;
	virtual bool rva00468DCDSlot14(Object *obj) = 0;
};
struct Rva00468CA3Arg
{
	unsigned char m_pad00[0x38];
	void *m_38; // +0x38
};
class HordeContainModuleData
{
public:
	unsigned char m_pad[0xA4];
	_STL::list<AsciiString> m_A4; // +0xA4
};
// Pointer vector (begin, end, capacity) as STLport lays it out.
struct Rva004698BCVector
{
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	void **m_begin;
	void **m_end;
	void **m_cap;
};
struct Rva00469851Names
{
	const AsciiString *begin() const { return m_begin; }
	const AsciiString *end() const { return m_end; }
	const AsciiString *m_begin;
	const AsciiString *m_end;
	const AsciiString *m_cap;
};
// The module data fields the +0x11C slots below read, by offset.
struct HordeContainModuleDataFields
{
	unsigned char m_pad000[0x98];
	int m_98; // +0x98
	unsigned char m_pad09C[0x18C - 0x9C];
	unsigned char m_18C[0x0C]; // +0x18C (address handed out by slot 129)
	_STL::vector<Rva0046D158Record *> m_198; // +0x198
	Rva004698BCVector m_1A4; // +0x1A4
	AsciiString m_1B0; // +0x1B0
	unsigned char m_pad1B4[0x1B8 - 0x1B4];
	_STL::map<int, int> m_1B8; // +0x1B8
	unsigned char m_pad1C4[0x1D8 - 0x1C4];
	bool m_1D8; // +0x1D8
	unsigned char m_pad1D9[0x1DC - 0x1D9];
	int m_1DC; // +0x1DC (back-away frames, low)
	int m_1E0; // +0x1E0 (back-away frames, high)
	float m_1E4; // +0x1E4 (back-away distance, low)
	float m_1E8; // +0x1E8 (back-away distance, high)
	float m_1EC; // +0x1EC (back-away chance)
	float m_1F0; // +0x1F0 (nonzero: every member backs away)
	Rva00469851Names m_1F4;
	unsigned char m_pad200[0x218 - 0x200];
	Rva00469851Names m_218;
	union
	{
		struct
		{
			const AsciiString *m_224Begin; // +0x224 (vector)
			const AsciiString *m_224End;
			const AsciiString *m_224Cap;
		};
		Rva00469851Names m_224;
	};
	bool m_230; // +0x230
	unsigned char m_pad231[0x234 - 0x231];
	int m_234; // +0x234 (slot 30 hands it to each AI's slot 142 unless -1)
	bool m_238;
	unsigned char m_pad239[0x23C - 0x239];
	AsciiString m_23C;
	unsigned char m_pad240[0x254 - 0x240];
	bool m_254; // +0x254
	unsigned char m_pad255[0x25C - 0x255];
	float m_25C; // +0x25C (a flank arc, degrees)
	unsigned char m_pad260[0x264 - 0x260];
	unsigned int m_264; // +0x264 (a frame count)
	unsigned int m_268; // +0x268
	float m_26C; // +0x26C
	float m_270; // +0x270
};
// Rowed helpers for slot 99 (0x004708BC), under the owner names their rows carry.
class Rva00469B73
{
public:
	void rva00469B73(void *obj);	// 0x00469B73
};
class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;	// 0x0028D891
};
class Rva0040334B
{
public:
	void rva0040334B(Object *obj);	// 0x0040334B
};
class LifetimeUpdate
{
public:
	void setLifetimeRange(unsigned int minFrames, unsigned int maxFrames);	// 0x003A4AB3
	unsigned char m_pad00[0x20];
	unsigned int m_20; // +0x20 (the frame it dies on)
};
// A behavior module: its interface at +0x0C hands back, from slot 5, an
// optional interface whose slot 1 takes an Object ID.
class Rva004708BCSlot5Iface : public Rva00468D11Slots<1>
{
public:
	virtual void slot1(int id) = 0;
};
class Rva004708BCModuleHead
{
public:
	virtual void moduleHeadAnchor();
	void *m_04;
	void *m_08;
};
class Rva004708BCBehaviorIface : public Rva00468D11Slots<5>
{
public:
	virtual Rva004708BCSlot5Iface *slot5() = 0;
};
class Rva004708BCBehavior : public Rva004708BCModuleHead, public Rva004708BCBehaviorIface
{
};
// The +0x250 module's slot 31 and what it hands back (slots 4 and 121).
class Rva004708BCTail : public Rva00468D11Slots<4>
{
public:
	virtual void slot4(int a1) = 0;
};
class Rva004708BCTail121 : public Rva00468D11Slots<121>
{
public:
	virtual void slot121() = 0;
};
class Rva004708BCContain : public Rva00468D11Slots<31>
{
public:
	virtual Rva004708BCTail *slot31() = 0;
};
// Slot 99's builder interface at HordeContain +0xFC (vtable 0x00C47834):
// slot 0 (0x00466FE0) builds the replacement Object from a template.
class Rva00466FE0Iface
{
public:
	virtual Object *rva00466FE0(const ThingTemplate *tmpl, Rva0046A2ECContain *contain, Object *obj, const char *name, int a5) = 0;
};
// The +0x20 contain interface out to slot 93 (unknown identity): slot 93
// takes a member-field pointer and a flag.
struct ContainIface93 : public Rva00468D11Slots<93>
{
public:
	virtual void slot93(int *a1, int a2) = 0;
};
struct HordeContainModuleDataFields;
// ModuleData slot 21 answers the HordeContain module data view (or null).
class ModuleData : public Rva00468D11Slots<21>
{
public:
	virtual const HordeContainModuleDataFields *slot21() const = 0;
};
template <int N> class Rva0046BB38Slots : public Rva0046BB38Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0046BB38Slots<0>
{
};
// The 0x4C-byte record instigateQuarrel takes twice by value and keeps at +0x1B4
// and +0x200; slot 107 hands both to the rowed Object 0x001E42F2.
struct QuarrelPacket
{
	int words[0x13];
};
// HordeContain's +0x11C interface (vtable 0x00C44C58), 152 slots; named ones are
// the overrides below plus slot 144 (banked) and the slots they call.
class Rva0046BB38Iface6 : public Rva0046BB38Slots<0>
{
public:
	virtual void rva00472329(const Coord3D *pos, int unused) = 0;
	virtual void attackTargetNow(Object *target, int select) = 0; virtual void rva00472235() = 0; virtual void rva0046E253() = 0; virtual void returnToFormation(bool reposition) = 0; virtual void rva004726DD(Object *target) = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void assignSpotToUnit(Object *obj) = 0; virtual void rva00469F2F(Object *obj) = 0; virtual void notifyOfMemberDeath(Object *obj) = 0;
	virtual void removeMemberFromHorde(Object *obj) = 0; virtual void gap15() = 0; virtual void performReform() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual Object *rva0046CC09() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup) = 0; virtual bool rva0046EA94(Object *obj) = 0; virtual void gap29() = 0;
	virtual void rva00473799(const _STL::list<Object *> &items) = 0; virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3) = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void rva0046BEAC(Object *obj) = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void rva0046E7E3(const UpgradeTemplate *upgrade, bool all) = 0; virtual void gap47() = 0; virtual void rva004707DB(Object *obj, float amount) = 0; virtual void rva004739B4() = 0;
	virtual void rva0046BC30() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void rva0046C3FE(Player *player) = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual bool rva0046AAB8() = 0; virtual void rva004738B6(Object *target) = 0; virtual void gap64() = 0; virtual unsigned int rva0046F7F8() const = 0;
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p) = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual Object *rva0046D2C3(int kind) = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void startMeleeAttack(Object *target) = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool canEngageInMelee(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual Object *rva004708BC(const Matrix3D *mtx) = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
	virtual void gap102() = 0; virtual void backAwaySomeMembersFrom(Object *attacker) = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void instigateQuarrel(int low, int high, QuarrelPacket packetA, QuarrelPacket packetB) = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
	virtual void rva0046A712(int unused) = 0; virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer) = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual bool rva0046992C() = 0;
	virtual void gap126() = 0; virtual bool rva004698BC() = 0; virtual const void *rva004698D6() = 0; virtual const void *rva004698E2() = 0;
	virtual void rva00469967() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
	virtual void gap134() = 0; virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after) = 0; virtual bool rva0046F8CD() = 0; virtual Rva002390CB rva0046EC7C(Object *obj) = 0;
	virtual ObjectID rva0046DEA1(ObjectID want) = 0; virtual bool rva0046DF9A(Coord3D *center) = 0; virtual bool rva0046E113(Coord3D *center) = 0; virtual void rva004690D0(int value) = 0;
	virtual bool rva00468C37() = 0; virtual void rva00468BDC(int on) = 0;
	virtual float rva00468B5B(float value) = 0;
	virtual void rva00468C60(const Coord3D *pos) = 0;
	virtual bool rva00468C7B(Coord3D *pos) = 0;
	virtual bool isFlankedBy(Object *attacker) = 0;
	virtual void rva0046E2BC() = 0;
	virtual void gap149() = 0;
	virtual float rva0046F8DA() = 0;
	virtual float rva0046F8E7() = 0;
	virtual void gap152() = 0;
	virtual float rva0046B850() = 0;
	virtual void endMove() = 0;
};
// Primary vtable 0x00C45050: gap slots, slot 37 (HordeContain's 0x00470B21,
// the bool performReform repeats until false) and slot 38, the matched
// HordeContainRva004725D5.cpp override (indices only matter for the calls).
class UpdateModule : public Rva00468D11Slots<32>
{
public:
	virtual void slot32(Object *obj) = 0;
	virtual void slot33(int a1) = 0;
	virtual void rva0046AF85() = 0;
	virtual void rva00470DC1() = 0;
	virtual void rva00474842(Object *obj, const Coord3D *pos, float angle, bool stopped) = 0;
	virtual bool rva00470B21() = 0;
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual void updateModuleInterfaceAnchor();
	unsigned char m_pad14[0x20 - 0x14];
};
// The +0x20 contain interface (vtable 0x00C44EC8): slot 70 fills the
// contained-items pair.
typedef void (*ContainIterateFunc)(Object *obj, void *userData);
// The base iteration body 0x004635EC is rowed as SlaughterHordeContain::rva004635EC;
// baseIterateContained calls that spelling with the interface's own this.
class SlaughterHordeContain { public: virtual void rva004635EC(ContainIterateFunc func, void *userData, int flags); };
class ContainModuleInterface : public Rva00468D11Slots<38>
{
public:
	virtual bool slot38(Object *obj, int a2, int a3) = 0;
	virtual void cgap39() = 0; virtual void cgap40() = 0; virtual void slot41(const Object *obj, int a2) = 0; virtual void cgap42() = 0; virtual void cgap43() = 0; virtual void cgap44() = 0; virtual void cgap45() = 0; virtual void cgap46() = 0; virtual void cgap47() = 0; virtual void cgap48() = 0; virtual void cgap49() = 0; virtual void cgap50() = 0; virtual void cgap51() = 0; virtual void cgap52() = 0; virtual void cgap53() = 0; virtual void cgap54() = 0; virtual void cgap55() = 0; virtual void cgap56() = 0; virtual void cgap57() = 0; virtual void cgap58() = 0; virtual void cgap59() = 0; virtual void cgap60() = 0; virtual void cgap61() = 0; virtual void cgap62() = 0; virtual void cgap63() = 0; virtual void cgap64() = 0; virtual void cgap65() = 0; virtual void cgap66() = 0; virtual void cgap67() = 0;
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3) = 0;	// slot 68; the base body is 0x004635EC
	__forceinline void baseIterateContained(ContainIterateFunc func, void *userData, int a3) { ((SlaughterHordeContain *)this)->SlaughterHordeContain::rva004635EC(func, userData, a3); }
	virtual int slot69(int a1) = 0;
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
	virtual void cgap71() = 0; virtual void cgap72() = 0; virtual void cgap73() = 0; virtual void cgap74() = 0; virtual void cgap75() = 0; virtual void cgap76() = 0; virtual void cgap77() = 0;
	virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim) = 0;
};
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
public:
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual void gatherUnitBack(Object *obj) = 0;
private:
	unsigned char m_pad024[0x11C - 0x24];
};
// The banner carrier's update module (rowed 0x00468E26 lookup); its data at
// +0x04 carries the carrier's value at +0x10.
struct HordeBannerCarrierUpdateData
{
	unsigned char m_pad00[0x10];
	int m_value;						// +0x10
};

struct HordeBannerCarrierUpdate
{
	void *m_vtbl;
	const HordeBannerCarrierUpdateData *m_data;		// +0x04
};

// The partition filter base and the KindOf mask filter (vftable 0x00BC2908,
// allow 0x002610DE: every kind of the first mask and none of the second).
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
struct Rva00045411BitSet
{
	Rva00045411BitSet(int unused, int bit) throw();	// 0x00045411
	unsigned int m_bits[7];
};
template <int N> class BitFlags
{
	unsigned int m_bits[7];
};
extern BitFlags<116> KINDOFMASK_NONE;
extern PartitionManager *ThePartitionManager;
// SiegeDockingBehavior's dock-point count (0x0045A199), under the owner name
// its row carries.
class BfmeThingBQA
{
public:
	int bfmeGoBQA() throw();
};
// The triple 0x004598F2 and 0x0045992F return (a Coord3D view under the
// name their unit gives it) and their owner.
struct Rva004598F2Point : public Coord3D
{
};
class SiegeDockingBehavior
{
public:
	Rva004598F2Point rva004598F2(int index);
	Rva004598F2Point rva0045992F(int index);
};

class Rva00468CB6A;
// The rowed 0x0046D946 on the HordeContain base: the contained Object
// closest to the argument.
#include "../../../Common/RTS/XYDistanceCallView.h"
class Rva001E431E { public: void rva001E431E(const int *slot); };
class Rva0046A024 { public: void rva0046A024(); };
float ACos(float x);
class Rva0046D946
{
public:
	Object *rva0046D946(Object *obj);
};
// The interface 0x0028C197 returns for a containing Object: slot 18 picks a
// victim near a position within a range, slot 68 is the fallback.
class Rva00471FFAVictimChooser : public Rva00468D11Slots<18>
{
public:
	virtual Object *slot18(int a1, const Coord3D *pos, float range, Object *source, bool flag) = 0;
	virtual void gap19() = 0; virtual void gap20() = 0; virtual void gap21() = 0; virtual void gap22() = 0;
	virtual void gap23() = 0; virtual void gap24() = 0; virtual void gap25() = 0; virtual void gap26() = 0;
	virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0; virtual void gap30() = 0;
	virtual void gap31() = 0; virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0;
	virtual void gap35() = 0; virtual void gap36() = 0; virtual void gap37() = 0; virtual void gap38() = 0;
	virtual void gap39() = 0; virtual void gap40() = 0; virtual void gap41() = 0; virtual void gap42() = 0;
	virtual void gap43() = 0; virtual void gap44() = 0; virtual void gap45() = 0; virtual void gap46() = 0;
	virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0; virtual void gap50() = 0;
	virtual void gap51() = 0; virtual void gap52() = 0; virtual void gap53() = 0; virtual void gap54() = 0;
	virtual void gap55() = 0; virtual void gap56() = 0; virtual void gap57() = 0; virtual void gap58() = 0;
	virtual void gap59() = 0; virtual void gap60() = 0; virtual void gap61() = 0; virtual void gap62() = 0;
	virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0; virtual void gap66() = 0;
	virtual void gap67() = 0;
	virtual Object *slot68() = 0;
};
struct Rva0046E6EAObject; struct Rva0046E6EACoord;
class Rva0046E6EA { public: bool rva0046E6EA(Rva0046E6EAObject *obj, const Rva0046E6EACoord *pos, Rva0046E6EACoord *out, bool flag); };

// The rowed Coord3D::length (0x00003571) and normalize (0x000035B6), visible and out of line like
// coord3d.cpp's select-any copies: cl then knows normalize keeps no pointer to the vector it scales.
__declspec(noinline) inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}
__declspec(noinline) inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}
// A back-away goal of the +0x1A0 map: ctor 0x00469155, operator= 0x0046916D (a copy goes through it).
class Rva00469155
{
public:
	Rva00469155();
	Rva00469155(const Rva00469155 &o) { *this = o; }
	Rva00469155 &operator=(const Rva00469155 &o);
	~Rva00469155() {}
	Coord3D m_pos; // +0x00
	unsigned int m_value; // +0x0C (a frame count)
};
// The map's key/record pair. Its rowed ctor 0x00469BEA (Rva00469BEACtor.cpp) is visible here, select-any,
// so cl sees that it keeps no pointer to the key.
class Rva00469BEA
{
public:
	Rva00469BEA(const int &a, const Rva00469155 &b);
	int m_00;
	Rva00469155 m_04;
};
__declspec(noinline) inline Rva00469BEA::Rva00469BEA(const int &a, const Rva00469155 &b) : m_00(a), m_04(b)
{
}
// The map is viewed through the rowed int-key instantiations, as in HordeContainIdMapGetOrInsert.cpp.
struct Rva00470205Record { char bytes[1]; };
typedef _STL::map<int, Rva00470205Record, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00470205Record> > > Rva00470205Map;
namespace _STL {
template <> Rva00470205Map::iterator Rva00470205Map::insert(iterator, const value_type &);
}
class Rva00473F81 : public Rva00470205Map
{
public:
	Rva00469155 &rva00473F81(const int &key);
};
// Select-any copy of the rowed get-or-insert 0x00473F81 (HordeContainIdMapGetOrInsert.cpp): visible, its
// key temporary's slot is free again after the call.
__declspec(noinline) inline Rva00469155 &Rva00473F81::rva00473F81(const int &key)
{
	_STL::map<int, int>::iterator found = ((_STL::map<int, int> *)this)->lower_bound(key);
	iterator i = *(iterator *)&found;
	if (i == end() || key < (*i).first)
	{
		const value_type &entry = *(const value_type *)&Rva00469BEA(key, Rva00469155());
		i = insert(i, entry);
	}
	return *(Rva00469155 *)&(*i).second;
}
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	void rva0046E740(int a1);	// 0x0046E740 (slots 30 and 49 pass 0)
	virtual void attackTargetNow(Object *target, int select);
	virtual void rva004726DD(Object *target);
	virtual void rva0046E7E3(const UpgradeTemplate *upgrade, bool all);
	virtual void removeMemberFromHorde(Object *obj);
	bool rva00468CB6(Rva00468CB6A *,Object *);
	void rva00468B24(float value);
	unsigned char usingMeleeAttack();	// 0x004695DA
	void rva0046A893(Object *obj);
	void checkSpecialUnitDeath(Object *obj);
	void *rva0046AF12();
	int getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate);
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);
	virtual bool attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim);
	virtual bool rva0046BB38(Object *other);
	virtual void rva0046FE99(_STL::list<Object *> &out);
	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
	virtual bool isFlankedBy(Object *attacker);
	virtual void backAwaySomeMembersFrom(Object *attacker);
	virtual void rva004738B6(Object *target);
	bool rva00468F0F(Object *obj, Object *target);
	virtual AsciiString rva0046D1AC();
	virtual void rva0046F7C9(Object *obj);
	virtual void rva00469F2F(Object *obj);
	virtual void notifyOfMemberDeath(Object *obj);
	void rva00469886(Object *obj);
	void rva00469F3A(Object *obj);
	virtual int rva0046979B();
	virtual void *rva004696CD();
	virtual void rva004696E5();
	virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource);
	virtual bool rva00468D11();
	virtual bool rva00468D2C();
	virtual bool rva0046F8A5();
	virtual bool rva0046F8F4();
	virtual Object *rva0046D372();
	virtual void rva0046F8B2();
	virtual int rva004697CD();
	virtual int rva00468F68();
	virtual int rva00468F7E();
	virtual Object *rva004708BC(const Matrix3D *mtx);
	virtual bool rva004698BC();
	virtual const void *rva004698D6();
	virtual const void *rva004698E2();
	virtual void rva00469967();
	virtual void rva004690A9(const Coord3D *pos);
	virtual bool rva0046F8CD();
	virtual bool rva00468C37();
	virtual void rva004690D0(int value);
	virtual float rva00468B5B(float value);
	virtual void rva00468C60(const Coord3D *pos);
	virtual bool rva00468C7B(Coord3D *pos);
	virtual float rva0046F8DA();
	virtual float rva0046F8E7();
	virtual bool rva0046C65C();
	virtual bool rva0046C71E();
	virtual bool rva0046C6E7();
	virtual void rva00468FDC();
	virtual bool rva0046A46F();
	virtual bool rva0046A416();
	virtual bool canEngageInMelee(Object *obj, int a2);
	virtual bool rva00468DCD(Object *obj);
	virtual bool rva0046A4C8();
	virtual void rva00468D7D(Object *obj);
	virtual void rva0046981C();
	virtual void rva00469851();
	virtual void rva00468BDC(int on);
	virtual void rva0046AF85();
	virtual void rva00473ADF();
	virtual bool rva0046A6C1();
	virtual bool rva0046A677();
	virtual Object *rva0046D27A();
	virtual Object *rva0046D2C3(int kind);
	virtual void rva0046D7AF(int a1);
	virtual void rva0046DDC5(int a1, int a2);
	virtual void rva0046D384(Team *team);
	virtual void rva004730B0(Object *target);
	virtual void rva0046DE2D(const FXList *fx);
	virtual void rva0046A712(int unused);
	virtual void rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer);
	virtual bool rva0046C5D7(int value);
	virtual bool rva0046A2EC(Object *target);
	virtual bool rva0046A381(Object *target);
	virtual void rva0046BEAC(Object *obj);
	virtual void rva0046BC30();
	virtual void rva0046BD70();
	virtual void rva0046BE0E();
	virtual void rva0046BA56(Object *source, int unused);
	void rva0046BACD();
	virtual void rva0046C3FE(Player *player);
	virtual void rva004707DB(Object *obj, float amount);
	virtual void rva004739B4();
	virtual void rva00473799(const _STL::list<Object *> &items);
	virtual void instigateQuarrel(int low, int high, QuarrelPacket packetA, QuarrelPacket packetB);
	virtual void rva0046D8AE();
	virtual Object *rva0046CB2C();
	virtual bool rva0046D80B();
	virtual bool rva0046BB6F(int *out, unsigned int frame);
	virtual int rva0046D3FC(Rva2225E0Filter *filter);
	virtual bool rva0046A2A7();
	virtual void rva0046E2BC();
	virtual void endMove();
	virtual bool rva0046992C();
	virtual Object *rva0046CC09();
	virtual Object *rva0046CBCA();
	virtual void rva0046C327();
	virtual void rva0046C20B();
	virtual ObjectID rva0046DEA1(ObjectID want);
	virtual bool rva0046DF9A(Coord3D *center);
	virtual bool rva0046E113(Coord3D *center);
	virtual void rva0046A78F(const Matrix3D *mtx);
	virtual void rva00472329(const Coord3D *pos, int unused);
	virtual void rva00472235();
	virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3);
	virtual void slot42(const Object *obj);
	virtual void assignSpotToUnit(Object *obj);
	virtual void startMeleeAttack(Object *target);
	virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup);
	virtual bool rva0046EA94(Object *obj);
	virtual void rva0046C4C0();
	virtual float rva0046B850();
	virtual void rva0046D1F7(_STL::list<const Object *> &out);
	virtual void rva0046E253();
	virtual void returnToFormation(bool reposition);
	void rva0046AA85();
	virtual bool rva0046CDC9();
	virtual bool rva0046CCEF(const ThingTemplate *tmpl);
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual bool rva0046B9DC(int a1);
	virtual bool rva0046B95E(int a1);
	virtual void rva00468CA3(const Rva00468CA3Arg *arg);
	virtual bool rva0046AAB8();
	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3);
	virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter);
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p);
	virtual Rva002390CB rva0046EC7C(Object *obj);
	Rva0046D158Record *rva0046D158(AsciiString name);
	virtual void performReform();
	virtual bool rva00470B21();
	virtual void rva00470DC1();
	Coord2D *rva0046A5B1(Coord2D *offset, int index);
	bool rva004723F2(Object *, const AsciiString &);
private:
	__forceinline const _STL::list<Object *> *containedItems()
	{
		Rva0046247DPair p;
		((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
		return p.m04;
	}
	const HordeContainModuleDataFields *fields() const { return (const HordeContainModuleDataFields *)m_moduleData; }
	bool m_120; // +0x120
	bool m_121; // +0x121
	unsigned char m_pad122[0x170 - 0x122];
	_STL::set<int> m_170; // +0x170 (Object IDs)
	_STL::map<int, int> m_17C; // +0x17C
	// The +0x188 vector's begin() and operator[] (base evaluated first).
	Rva00472329Record *begin188() { return m_188Begin; }
	Rva00472329Record &rec188(unsigned int n) { return *(begin188() + n); }
	Rva00472329Record *m_188Begin; // +0x188 (vector of 0x1C-byte records)
	Rva00472329Record *m_188End;
	Rva00472329Record *m_188Cap;
	_STL::list<int> m_194; // +0x194 (free +0x188 record indices)
	bool m_198; // +0x198
	unsigned char m_pad199[0x19C - 0x199];
	int m_19C; // +0x19C
	Rva00473F81 m_1A0; // +0x1A0 (back-away goals by member ID)
	ObjectID m_1AC; // +0x1AC
	ObjectID m_1B0; // +0x1B0
	QuarrelPacket m_1B4; // +0x1B4
	QuarrelPacket m_200; // +0x200
	_STL::map<ObjectID, int> m_24C; // +0x24C (member ID -> quarrel value)
	_STL::map<unsigned short, float, Rva00470041Less> m_258; // +0x258 (template +0x5D8 -> experience)
	void *m_264; // +0x264
	unsigned char m_pad268[0x26C - 0x268];
	ObjectID m_26C; // +0x26C
	struct BannerIndexEntry
	{
		const ThingTemplate *m_template;
		int m_index;
	};
	_STL::vector<BannerIndexEntry *> m_bannerIndices; // +0x270
	int m_27C; // +0x27C (the banner carrier's value)
	unsigned char m_pad280[0x288 - 0x280];
	int m_288; // +0x288 (an Object ID)
	unsigned int m_28C; // +0x28C (a logic frame)
	unsigned char m_pad290[0x294 - 0x290];
	bool m_294; // +0x294
	unsigned char m_pad295[0x298 - 0x295];
	unsigned int m_298; // +0x298 (a frame count, -1 for none)
	int m_29C; // +0x29C
	int m_2A0; // +0x2A0
	bool m_2A4; // +0x2A4
	unsigned char m_pad2A5[0x2B0 - 0x2A5];
	int m_2B0; // +0x2B0 (the ID of the last attacker backed away from)
	unsigned char m_pad2B4[0x2B8 - 0x2B4];
	Coord3D m_2B8; // +0x2B8
	bool m_2C4; // +0x2C4
	unsigned char m_pad2C5[0x2C8 - 0x2C5];
	Rva00468FDCHelper *m_2C8; // +0x2C8
	float *m_2CCBegin; // +0x2CC (vector<float> of flank angles)
	float *m_2CCEnd;
	float *m_2CCCap;
	unsigned char m_pad2D8[0x2DC - 0x2D8];
	_STL::map<int, Rva00462D35Mapped> m_2DC; // +0x2DC
	bool m_2E8; // +0x2E8
	unsigned char m_pad2E9[0x2EC - 0x2E9];
	float m_2EC; // +0x2EC
	int m_2F0; // +0x2F0
	unsigned char m_pad2F4[0x2F8 - 0x2F4];
	Coord3D m_2F8; // +0x2F8
	bool m_304; // +0x304
};
bool HordeContain::rva0046BB38(Object *other)
{
	if (other->m_274 == m_object)
		return true;
	if (m_170.find(other->getID()) != m_170.end())
		return true;
	return false;
}
AsciiString HordeContain::rva0046D1AC()
{
	const HordeContainModuleData *data = (const HordeContainModuleData *)m_moduleData;
	return data->m_A4.size() == 1 ? data->m_A4.front() : AsciiString::TheEmptyString;
}

// ?rva0046F7C9@HordeContain@@UAEXPAVObject@@@Z @0x0046F7C9: slot 8, forwards to
// the primary vtable's slot 38.
void HordeContain::rva0046F7C9(Object *obj)
{
	gatherUnitBack(obj);
}

// ?rva00469886@HordeContain@@QAEXPAVObject@@@Z @0x00469886: adds every name of
// the module data's +0x224 vector to the Object's attribute modifier pools
// (with -1); slot 12 below is its only caller.
void HordeContain::rva00469886(Object *obj)
{
	if (!obj)
		return;
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	const AsciiString *it = data->m_224Begin;
	const AsciiString *const *end = &data->m_224End;
	for (; it != *end; ++it)
		obj->addAttributeModifierToPool(*it, -1);
}

// ?rva00469F2F@HordeContain@@UAEXPAVObject@@@Z @0x00469F2F: slot 12, forwards to
// 0x00469886 on the HordeContain base.
void HordeContain::rva00469F2F(Object *obj)
{
	rva00469886(obj);
}

// Retail 0x00469F3A..0x0046A024, ret 4 (234 bytes). The primary
// HordeContain this supplies Object at +8; its condition mask is +0x10C.
// WB's BitFlags.h lead supplies the set/intersect/flip structure, while
// the bit indices, four 76-byte temporaries and callees follow retail.
// No enum names or the enclosing method's original name are claimed.
void HordeContain::rva00469F3A(Object *obj)
{
	if (!obj)
		return;
	Rva00469F3AFlags mask;
	memset(&mask, 0, sizeof(mask));
	((unsigned char *)mask.m_words)[31] |= 2;
	((unsigned char *)mask.m_words)[29] |= 0x80;
	mask.set(203);
	mask.set(204);
	mask.set(63);
	mask.set(64);
	mask.set(201);
	mask.set(205);
	mask.set(170);
	mask.set(65);
	mask.set(200);
	mask.set(314);
	mask.set(37);
	mask.set(118);
	mask.set(336);
	mask.set(240);
	mask.set(326);
	Rva00469F3AFlags set;
	memcpy(&set, &mask, sizeof(set));
	WeaponTemplateSetHead current(*(const WeaponTemplateSetHead *)m_object->m_conditionWords);
	set.intersect(current.m_words);
	Rva00469F3AFlags clear;
	memcpy(&clear, &current, sizeof(clear));
	clear.flip();
	clear.intersect(mask.m_words);
	obj->rva0028CFB2((const int *)clear.m_words, (const int *)set.m_words);
}

// ?rva0046979B@HordeContain@@UAEHXZ @0x0046979B: slot 10, module data +0x98.
int HordeContain::rva0046979B()
{
	return fields()->m_98;
}

// ?rva004696CD@HordeContain@@UAEPAXXZ @0x004696CD: slot 22, TheThingFactory's
// lookup of the module data's +0x1B0 name.
void *HordeContain::rva004696CD()
{
	return (void *)TheThingFactory->findTemplate(fields()->m_1B0);
}

// ?rva004696E5@HordeContain@@UAEXXZ @0x004696E5: slot 24, the same lookup handed
// to slot 26 when found.
void HordeContain::rva004696E5()
{
	void *thingTemplate = (void *)TheThingFactory->findTemplate(fields()->m_1B0);
	if (thingTemplate)
		rva00472D43(thingTemplate);
}

// ?rva00472C8E@HordeContain@@UAEXPAVObject@@W4CommandSourceType@@@Z @0x00472C8E:
// slot 33, forwards both arguments to the rowed AICommandInterface 0x0037379B
// of the owner's AI.
void HordeContain::rva00472C8E(Object *obj, CommandSourceType cmdSource)
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (ai)
		ai->m_command.rva0037379B(obj, cmdSource);
}

// ?rva00468D11@HordeContain@@UAE_NXZ @0x00468D11: slot 34, the owner's AI slot
// 114, false without an AI.
bool HordeContain::rva00468D11()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai)
		return false;
	return ai->rva00468D11Slot114();
}

// ?rva00468D2C@HordeContain@@UAE_NXZ @0x00468D2C: slot 35, the same for AI slot
// 115.
bool HordeContain::rva00468D2C()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai)
		return false;
	return ai->rva00468D2CSlot115();
}

// ?rva00468CA3@HordeContain@@UAEXPBURva00468CA3Arg@@@Z @0x00468CA3 (19 B): slot 45,
// forwards the argument's +0x38 word to slot 44 (rva0046B95E). Codegen: a compiler
// barrier between the argument read and the call keeps retail's load order.
void HordeContain::rva00468CA3(const Rva00468CA3Arg *arg)
{
	void *value = arg->m_38;
	_ReadWriteBarrier();
	rva0046B95E((int)value);
}

// ?rva0046F8A5@HordeContain@@UAE_NXZ @0x0046F8A5: slot 59, module data +0x1D8.
bool HordeContain::rva0046F8A5()
{
	return fields()->m_1D8;
}

// ?rva0046F8F4@HordeContain@@UAE_NXZ @0x0046F8F4: slot 60, module data +0x230.
bool HordeContain::rva0046F8F4()
{
	return fields()->m_230;
}

// ?rva0046D372@HordeContain@@UAEPAVObject@@XZ @0x0046D372: slot 70, the Object
// whose ID is at +0x26C.
Object *HordeContain::rva0046D372()
{
	return TheGameLogic->findObjectByID(m_26C);
}

// ?rva0046F8B2@HordeContain@@UAEXXZ @0x0046F8B2: slot 74, clears +0x2A4 and wakes
// the module next frame.
void HordeContain::rva0046F8B2()
{
	m_2A4 = false;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// ?rva004697CD@HordeContain@@UAEHXZ @0x004697CD: slot 95, module data +0x98, 0
// without module data.
int HordeContain::rva004697CD()
{
	const HordeContainModuleDataFields *data = fields();
	if (data)
		return data->m_98;
	return 0;
}

// ?rva00468F68@HordeContain@@UAEHXZ @0x00468F68: slot 97, how many of +0x264 and
// +0x26C are set.
int HordeContain::rva00468F68()
{
	int count = 0;
	if (m_264)
		++count;
	if (m_26C)
		++count;
	return count;
}

// ?rva00468F7E@HordeContain@@UAEHXZ @0x00468F7E: slot 98, slot 96 for 0 less
// slot 97.
int HordeContain::rva00468F7E()
{
	return rva0046D3FC(0) - rva00468F68();
}

// ?rva004698BC@HordeContain@@UAE_NXZ @0x004698BC: slot 127, whether the module
// data's +0x1A4 vector is non-empty.
bool HordeContain::rva004698BC()
{
	return fields()->m_1A4.size() > 0 ? true : false;
}

// ?rva004698D6@HordeContain@@UAEPBXXZ @0x004698D6: slot 128, &module data +0x1A4.
const void *HordeContain::rva004698D6()
{
	return &fields()->m_1A4;
}

// ?rva004698E2@HordeContain@@UAEPBXXZ @0x004698E2: slot 129, &module data +0x18C.
const void *HordeContain::rva004698E2()
{
	return fields()->m_18C;
}

// ?rva00469967@HordeContain@@UAEXXZ @0x00469967: slot 130. On a wall or ramp
// cell, faces the Object away from the nearest dock point of the closest
// kind-0x3C Object within 150 that has a SiegeDockingBehavior, else (off a
// ramp) along that Object's orientation plus its template's +0x528; then raises
// +0x120 and wakes the module. BFME 1's slot 118 (0x00239E00) is the donor.
void HordeContain::rva00469967()
{
	Object *obj = m_object;
	bool onRamp = false;
	if (!TheAI->m_pathfinder->IsPointOnWall((int)(void *)obj->getPosition(), false))
	{
		if (!TheAI->m_pathfinder->IsPointOnRamp(obj->getPosition()))
			return;
		onRamp = true;
	}
	const Coord3D *pos = obj->getPosition();

	Object *wall;
	{
		wall = ThePartitionManager->getClosestObject(pos, 150.0f, 1,
			&Rva0004584D(*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x3C),
				*(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE));
	}
	if (wall)
	{
		static NameKeyType key = TheNameKeyGenerator->nameToKey("SiegeDockingBehavior");
		Module *dock = wall->findModule(key);
		if (dock && ((BfmeThingBQA *)dock)->bfmeGoBQA())
		{
			int best = 0;
			{
				float bestDist = 1000000.0f;
				for (int i = 0; i < ((BfmeThingBQA *)dock)->bfmeGoBQA(); ++i)
				{
					Rva004598F2Point delta = ((SiegeDockingBehavior *)dock)->rva004598F2(i);
					delta.x -= pos->x;
					delta.y -= pos->y;
					delta.z -= pos->z;
					float dist = delta.GetLengthEstimate2D();
					if (dist < bestDist)
					{
						best = i;
						bestDist = dist;
					}
				}
			}
			{
				Coord2D dir;
				dir.x = -((SiegeDockingBehavior *)dock)->rva0045992F(best).x;
				dir.y = -((SiegeDockingBehavior *)dock)->rva0045992F(best).y;
				((Thing *)obj)->setOrientation(dir.toAngle());
			}
		}
		else if (!onRamp)
		{
			((Thing *)obj)->setOrientation(wall->m_orientation + wall->m_template->m_geometryFrontAngle);
		}
		m_120 = true;
	}
	setWakeFrame(obj, UPDATE_SLEEP_NONE);
}

// ?rva004690A9@HordeContain@@UAEXPBUCoord3D@@@Z @0x004690A9: slot 132, stores the
// position at +0x2B8 and raises +0x2C4 and +0x120.
void HordeContain::rva004690A9(const Coord3D *pos)
{
	m_2B8 = *pos;
	m_2C4 = true;
	m_120 = true;
}

// ?rva0046F8CD@HordeContain@@UAE_NXZ @0x0046F8CD: slot 136, module data +0x254.
bool HordeContain::rva0046F8CD()
{
	return fields()->m_254;
}

// ?rva00468C37@HordeContain@@UAE_NXZ @0x00468C37: slot 142, the byte at +0x150
// of what the owner's AI +0x1F0 holds at +4, and +0x2F0 set.
bool HordeContain::rva00468C37()
{
	return m_object->m_ai->m_1F0->m_4->m_150 && m_2F0;
}

// ?rva004690D0@HordeContain@@UAEXH@Z @0x004690D0: slot 141, hands the value and
// the contained Object to the SkirmishAI record the global manager returns for
// the controlling player. The equal-arm carrier on the manager global keeps the
// Object's address out of a CSE'd esi hold so retail's two [esi-0x114] loads
// stay put.
void HordeContain::rva004690D0(int value)
{
	Rva002A8AB1Record *rec = TheSkirmishAIManager->rva002A8AB1((TheSkirmishAIManager ? m_object : m_object)->getControllingPlayer());
	if (rec)
		rec->onHordeCreated((Object *)value, m_object);
}

// ?rva00468B5B@HordeContain@@UAEMM@Z @0x00468B5B: slot 144 (iface +0x1D0),
// scales the passed value by the module's remaining growth (1 - m_2EC*0.01)
// and decays m_2EC by 0.9. Two ordered early-outs (0 > d, then an equal-arm
// carrier for 0 >= d) reproduce retail's comiss/ja + comiss/jae pair; without
// the carrier the second compare folds into a jbe.
float HordeContain::rva00468B5B(float value)
{
	float b8 = m_object->m_B8;
	if (0.0f > m_2EC - b8)
		return value;
	if ((m_object ? (0.0f >= m_2EC - b8) : (0.0f >= m_2EC - b8)))
		return value;
	value = (1.0f - m_2EC * 0.01f) * value;
	m_2EC = m_2EC * 0.9f;
	if (value > 6.0f)
		value = 6.0f;
	return value;
}

// ?rva00468C60@HordeContain@@UAEXPBUCoord3D@@@Z @0x00468C60: slot 145, stores the
// position at +0x2F8 and raises +0x304.
void HordeContain::rva00468C60(const Coord3D *pos)
{
	m_2F8 = *pos;
	m_304 = true;
}

// ?rva00468C7B@HordeContain@@UAE_NPAUCoord3D@@@Z @0x00468C7B: slot 146, hands out
// and drops the position slot 145 stored.
bool HordeContain::rva00468C7B(Coord3D *pos)
{
	if (m_304)
	{
		m_304 = false;
		*pos = m_2F8;
		return true;
	}
	return false;
}

// ?rva0046F8DA@HordeContain@@UAEMXZ @0x0046F8DA: slot 150, module data +0x26C.
float HordeContain::rva0046F8DA()
{
	return fields()->m_26C;
}

// ?rva0046F8E7@HordeContain@@UAEMXZ @0x0046F8E7: slot 151, module data +0x270.
float HordeContain::rva0046F8E7()
{
	return fields()->m_270;
}

// ?rva0046C65C@HordeContain@@UAE_NXZ @0x0046C65C: slot 39, true when some key of
// the +0x170 tree names a live Object and none of those has an AI whose
// rva00260DED is nonzero and either not 1 or with Object +0x110 bit 29 up. The
// WorldBuilder twin (0x010C4800) sets the iterator before both flags and nests
// the == 1 test; the bit read is the inline bool bit test (retail mov/shr/test).
bool HordeContain::rva0046C65C()
{
	_STL::set<int>::iterator k = m_170.begin();
	bool busy = false;
	bool found = false;
	for (k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			found = true;
			if (ai->rva00260DED() != 0)
			{
				if (ai->rva00260DED() == 1)
				{
					if (obj->test110(29))
						busy = true;
				}
				else
				{
					busy = true;
				}
			}
		}
	}
	if (!found)
		return false;
	return !busy;
}

// ?rva0046C6E7@HordeContain@@UAE_NXZ @0x0046C6E7: slot 41, whether any key of the
// +0x170 tree names a live Object.
bool HordeContain::rva0046C6E7()
{
	for (_STL::set<int>::iterator it = m_170.begin(); it != m_170.end(); ++it)
	{
		if (TheGameLogic->findObjectByID((ObjectID)*it))
			return true;
	}
	return false;
}

// ?rva0046C71E@HordeContain@@UAE_NXZ @0x0046C71E: slot 40, true when a contained
// Object carries status 0x5A or when none exists at all. Native 0046C71E..0046C7A4
// and WB 0x010C4A90: the contained list first, then the +0x170 key tree walked from
// begin() up to begin() again (a loop the original source kept and cl keeps because
// the bound is a separate begin() evaluation, so its body never runs); the result is
// !any with the early `return true` paths sharing one epilogue (ternary form).
bool HordeContain::rva0046C71E()
{
	bool any = false;
	const _STL::list<Object *> *items = containedItems();
	_STL::list<Object *>::const_iterator end = items->end();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != end; ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			any = true;
			if (obj->testStatus((ObjectStatusTypes)0x5A))
				return true;
		}
	}
	_STL::set<int>::iterator bound = m_170.begin();
	for (_STL::set<int>::iterator k = m_170.begin(); k != bound; ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			any = true;
			if (obj->testStatus((ObjectStatusTypes)0x5A))
				return true;
		}
	}
	return any ? false : true;
}

// ?rva00468FDC@HordeContain@@UAEXXZ @0x00468FDC: slot 78, clears +0x2A0, +0x288
// and +0x28C, raises +0x294, resets the +0x2C8 helper (its slot 4) and, when
// +0x120 is up, raises +0x121.
void HordeContain::rva00468FDC()
{
	m_2A0 = 0;
	m_288 = 0;
	m_28C = 0;
	m_294 = true;
	m_2C8->rva00468FDCSlot4();
	if (m_120)
		m_121 = true;
}

// ?rva0046A46F@HordeContain@@UAE_NXZ @0x0046A46F: slot 81, whether a live
// contained Object's AI answers slot 111.
bool HordeContain::rva0046A46F()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0046A46FSlot111())
				return true;
		}
	}
	return false;
}

// ?rva0046A416@HordeContain@@UAE_NXZ @0x0046A416: slot 83, whether every live
// contained Object with an AI answers slot 111.
bool HordeContain::rva0046A416()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && !ai->rva0046A46FSlot111())
				return false;
		}
	}
	return true;
}

// ?rva0046A4C8@HordeContain@@UAE_NXZ @0x0046A4C8: slot 87, whether a contained
// Object's AI answers slot 111 while the Object has status 0x1C.
bool HordeContain::rva0046A4C8()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai && ai->rva0046A46FSlot111() && obj->testStatus((ObjectStatusTypes)0x1C))
			return true;
	}
	return false;
}

// ?canEngageInMelee@HordeContain@@UAE_NPAVObject@@H@Z @0x0047306E: slot 84, for the
// argument's AI: idles it (CMD_FROM_AI) and answers true when its slot 113
// does, else answers its slot 110; false without an AI. The second argument
// is not read.
bool HordeContain::canEngageInMelee(Object *obj, int)
{
	AIUpdateInterface *ai = obj->m_ai;
	if (!ai)
		return false;
	if (ai->rva0047306ESlot113())
	{
		ai->aiIdle(CMD_FROM_AI);
		return true;
	}
	return ai->rva0047306ESlot110() ? true : false;
}

// ?rva00468DCD@HordeContain@@UAE_NPAVObject@@@Z @0x00468DCD: slot 85, true while
// the argument (or the Object its rowed rva002931F5(false) hands back) is the
// one recorded at +0x288 and the frame is before +0x28C; otherwise the +0x2C8
// helper's slot 14.
bool HordeContain::rva00468DCD(Object *obj)
{
	if (!obj)
		return false;
	int id = obj->m_74;
	Object *other = obj->rva002931F5(false);
	if (other)
		id = other->m_74;
	if ((obj->m_74 == m_288 || id == m_288) && TheGameLogic->m_frame < m_28C)
		return true;
	return m_2C8->rva00468DCDSlot14(obj);
}

// ?rva00468D7D@HordeContain@@UAEXPAVObject@@@Z @0x00468D7D: slot 89, for the
// argument (or the Object its rowed rva002931F5(false) hands back) recorded
// at +0x288, sets +0x28C to the logic frame BfmeLogicFramesPerSecond * 3 frames from now.
// Retail computes the delay (imul esi,esi,3) before the call; /G7, which this
// unit is compiled with, is what selects that form over lea.
void HordeContain::rva00468D7D(Object *obj)
{
	if (!obj)
		return;
	int id = obj->m_74;
	unsigned int delay = BfmeLogicFramesPerSecond * 3;
	Object *other = obj->rva002931F5(false);
	if (other)
		id = other->m_74;
	if (obj->m_74 == m_288 || id == m_288)
		m_28C = TheGameLogic->m_frame + delay;
}

// ?rva0046981C@HordeContain@@UAEXXZ @0x0046981C: slot 121, slot 118 for each name
// of the module data's +0x224 vector, with 0 and -1.
void HordeContain::rva0046981C()
{
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	for (const AsciiString *it = data->m_224Begin; it != data->m_224End; ++it)
		rva0046DB6D(*it, 0, -1);
}

// ?rva00469851@HordeContain@@UAEXXZ @0x00469851: slot 122, slot 119 for each name
// of the same vector, with 0.
void HordeContain::rva00469851()
{
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	const AsciiString *it = data->m_224Begin;
	const AsciiString *const *end = &data->m_224End;
	for (; it != *end; ++it)
		rva0046DC92(*it, 0);
}

// ?rva00468BDC@HordeContain@@UAEXH@Z @0x00468BDC: slot 143, for an owner with an
// AI: setting sets model condition 0x1BA unless +0x2F0 was already set,
// clearing clears 0x1BA and 0x1BB (rowed Object setModelConditionStateForHorde/clearModelConditionStateForHorde);
// then stores the argument at +0x2F0.
void HordeContain::rva00468BDC(int on)
{
	Object *obj = m_object;
	if (!obj || !obj->m_ai)
		return;
	if (on)
	{
		if (!m_2F0)
			obj->setModelConditionStateForHorde((ModelConditionFlagType)0x1BA);
	}
	else
	{
		obj->clearModelConditionStateForHorde((ModelConditionFlagType)0x1BA);
		obj->clearModelConditionStateForHorde((ModelConditionFlagType)0x1BB);
	}
	m_2F0 = on;
}

// ?rva0046AF85@HordeContain@@UAEXXZ @0x0046AF85: slot 34 of the primary vtable
// 0x00C45050; hands every contained Object whose ID is not a key of the
// +0x17C tree to +0x11C interface slot 11.
void HordeContain::rva0046AF85()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_17C.find(obj->getID()) == m_17C.end())
			assignSpotToUnit(obj);
	}
}

// ?rva00473ADF@HordeContain@@UAEXXZ @0x00473ADF: slot 79; runs slot 78 when
// +0x2A0 is set, then the rowed AICommandInterface rva0045003E(0, CMD_FROM_AI)
// on every contained Object's AI.
void HordeContain::rva00473ADF()
{
	if (m_2A0)
		rva00468FDC();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		AIUpdateInterface *ai = (*it)->m_ai;
		if (ai)
			ai->m_command.rva0045003E(0, CMD_FROM_AI);
	}
}

// Slot 106 (WB HordeContain::instigateQuarrel): the member nearest the centre and a random other
// one get +0x1B0 / +0x1AC, the rest a random [low, high] value in +0x24C; a null member runs slot 107.
void HordeContain::instigateQuarrel(int low, int high, QuarrelPacket packetA, QuarrelPacket packetB)
{
	m_24C.clear();
	Rva0046247DPair slotPair;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
	int count = (int)slotPair.m04->size();
	if (count < 2)
		return;
	float best = 10000.0f;
	int closest = -1;
	int index = 1;
	Coord3D center;
	center.zero();
	_STL::list<Object *>::const_iterator it;
	for (it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *member = *it;
		if (!member)
		{
			rva0046D8AE();
			return;
		}
		center.add(member->getPosition());
	}
	center.scale(1.0f / count);
	for (it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it, ++index)
	{
		Object *member = *it;
		if (!member)
		{
			rva0046D8AE();
			return;
		}
		Coord3D diff;
		diff.set(member->getPosition());
		diff.sub(&center);
		float distance = diff.x * diff.x + diff.y * diff.y;
		if (distance < best)
		{
			best = distance;
			closest = index;
		}
	}
	int leader = closest;
	if (leader == -1)
		leader = 1;
	int other = leader + GetGameLogicRandomValue(1, count - 1, HORDECONTAIN_SOURCE_FILE, 8135);
	if (other > count)
		other -= count;
	m_1B4 = packetB;
	m_200 = packetA;
	index = 1;
	for (it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it, ++index)
	{
		Object *member = *it;
		if (!member)
		{
			rva0046D8AE();
			return;
		}
		if (index == other)
			m_1AC = (ObjectID)member->getID();
		else if (index == leader)
			m_1B0 = (ObjectID)member->getID();
		else
			m_24C[(ObjectID)member->getID()] = (int)GetGameLogicRandomValueReal((float)low, (float)high, HORDECONTAIN_SOURCE_FILE, 8162);
	}
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// ?rva0046A6C1@HordeContain@@UAE_NXZ @0x0046A6C1: slot 114; whether a contained
// Object's AI +0x140 member answers its rowed rva003638BA.
bool HordeContain::rva0046A6C1()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Rva003638BA *member = obj->m_ai->m_140;
			if (member && member->rva003638BA())
				return true;
		}
	}
	return false;
}

// ?rva0046A677@HordeContain@@UAE_NXZ @0x0046A677: slot 115; false when a
// contained Object's AI has a +0x140 member and +0x1FC state 4.
bool HordeContain::rva0046A677()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai->m_140 && ai->m_1FC == 4)
				return false;
		}
	}
	return true;
}

// ?rva0046AAB8@HordeContain@@UAE_NXZ @0x0046AAB8: slot 62; whether the
// contained list is empty.
bool HordeContain::rva0046AAB8()
{
	Rva0046247DPair slotPair;
	return ((Rva00291793 *)((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair))->rva00291793() == 0 ? true : false;
}

// ?rva0046F7FF@HordeContain@@UAEAAURva0046247DPair@@AAU2@@Z @0x0046F7FF:
// slot 66; fills the argument with the contained-list pair and returns it.
Rva0046247DPair &HordeContain::rva0046F7FF(Rva0046247DPair &slotPair)
{
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
	return slotPair;
}

// ?rva0046DB6D@HordeContain@@UAEXABVAsciiString@@PAVRva2225E0Filter@@H@Z
// @0x0046DB6D: slot 118; unless the named modifier's store category is
// missing or has index 6, adds it (with the third argument) to the pool of
// every contained Object and every Object keyed in the +0x170 tree the filter
// accepts (all of them without a filter); then to this Object's own pool.
void HordeContain::rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3)
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
	Object *self = m_object;
	Rva0046DB6DCategory *category = (Rva0046DB6DCategory *)TheAttributeModifierStore->GetCategoryContainer(
		TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(name.str())));
	if (category && category->m_index != 6)
	{
		for (; it != slotPair.m04->end(); ++it)
		{
			Object *obj = *it;
			if (!filter || filter->accepts(obj, self->getControllingPlayer()))
				obj->addAttributeModifierToPool(name, a3);
		}
		for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		{
			Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
			if (obj && (!filter || filter->accepts(obj, self->getControllingPlayer())))
				obj->addAttributeModifierToPool(name, a3);
		}
	}
	AttributeModifierPoolUpdate *pool = m_object->findAttributeModifierPoolUpdate();
	if (pool)
		pool->addModifierToPool(name, a3);
}

// ?rva0046DC92@HordeContain@@UAEXABVAsciiString@@PAVRva2225E0Filter@@@Z
// @0x0046DC92: slot 119; removes the named modifier from the pool of every
// contained Object and every Object keyed in the +0x170 tree the filter
// accepts (all of them without a filter), then from this Object's own pool.
void HordeContain::rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter)
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
	Object *self = m_object;
	for (; it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (!filter || filter->accepts(obj, self->getControllingPlayer()))
			obj->removeAttributeModifierFromPool(name);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && (!filter || filter->accepts(obj, self->getControllingPlayer())))
			obj->removeAttributeModifierFromPool(name);
	}
	AttributeModifierPoolUpdate *pool = m_object->findAttributeModifierPoolUpdate();
	if (pool)
		pool->rva00403744(name);
}

// ?rva0046D158@HordeContain@@QAEPAURva0046D158Record@@VAsciiString@@@Z
// @0x0046D158: the first module data +0x198 entry named the argument, else
// null.
Rva0046D158Record *HordeContain::rva0046D158(AsciiString name)
{
	const _STL::vector<Rva0046D158Record *> &records = fields()->m_198;
	for (_STL::vector<Rva0046D158Record *>::const_iterator it = records.begin(); it != records.end(); ++it)
	{
		Rva0046D158Record *record = *it;
		if (record->m_name.compare(name) == 0)
			return record;
	}
	return 0;
}

// ?rva0046EC7C@HordeContain@@UAE?AVRva002390CB@@PAVObject@@@Z @0x0046EC7C:
// slot 137; the +8 record of the +0x198 entry named for the argument's
// template (or that of the Object its rowed rva002931F5(false) hands back),
// else a default record.
Rva002390CB HordeContain::rva0046EC7C(Object *obj)
{
	if (!obj)
		return Rva002390CB();
	Object *other = obj->rva002931F5(false);
	Object *named = other ? other : obj;
	Rva0046D158Record *record = rva0046D158(named->m_template->m_64);
	if (!record)
		return Rva002390CB();
	return record->m_08;
}

// ?rva0046D27A@HordeContain@@UAEPAVObject@@XZ @0x0046D27A: slot 68; the first
// contained Object (contain interface slot 70), else the Object of the first
// key of the +0x170 tree, else null.
Object *HordeContain::rva0046D27A()
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	if (!slotPair.m04->empty())
		return slotPair.m04->front();
	_STL::set<int>::iterator it = m_170.begin();
	if (it != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*it);
	return 0;
}

// ?rva0046D2C3@HordeContain@@UAEPAVObject@@H@Z @0x0046D2C3: slot 69; the first contained
// Object (slot 70) not of the kind, else the first contained, else the same from the +0x170 tree.
Object *HordeContain::rva0046D2C3(int kind)
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		if (!(*it)->getTemplate()->isKindOf((KindOfType)kind))
			return *it;
	}
	if (!slotPair.m04->empty())
		return slotPair.m04->front();
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->getTemplate()->isKindOf((KindOfType)kind))
			return obj;
	}
	_STL::set<int>::iterator first = m_170.begin();
	if (first != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*first);
	return 0;
}

// ?rva0046D7AF@HordeContain@@UAEXH@Z @0x0046D7AF: slot 108; for each contained
// Object not keyed in the +0x170 tree, the rowed teleportTo(argument, false).
void HordeContain::rva0046D7AF(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_170.find(obj->getID()) == m_170.end())
			obj->teleportTo((const Coord3D *)a1, false);
	}
}

// ?rva0046DDC5@HordeContain@@UAEXHH@Z @0x0046DDC5: slot 117; for each contained
// Object not keyed in the +0x170 tree, its AI's slot 134 with both arguments.
void HordeContain::rva0046DDC5(int a1, int a2)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); )
	{
		Object *obj = *it;
		int id = obj->getID();
		++it;
		if (m_170.find(id) == m_170.end())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
				ai->rva0046DDC5Slot134(a1, a2);
		}
	}
}

// ?rva0046D384@HordeContain@@UAEXPAVTeam@@@Z @0x0046D384: slot 92; the pinned
// Object::setTeam(team) on every contained Object (contain interface slot
// 70) and on the live Object of every +0x170 key.
void HordeContain::rva0046D384(Team *team)
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
			obj->setTeam(team);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			obj->setTeam(team);
	}
}

// ?rva0046B9DC@HordeContain@@UAE_NH@Z @0x0046B9DC: slot 43; whether
// Object::affectedByUpgrade(argument) holds for a contained Object or for the Object of a
// +0x170 key.
bool HordeContain::rva0046B9DC(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if ((*it)->affectedByUpgrade((const UpgradeTemplate *)a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj->affectedByUpgrade((const UpgradeTemplate *)a1))
			return true;
	}
	return false;
}

// ?rva0046B95E@HordeContain@@UAE_NH@Z @0x0046B95E: slot 44; whether the rowed
// Object::hasUpgradeMask(argument) holds for a contained Object or for the live
// Object of a +0x170 key.
bool HordeContain::rva0046B95E(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if ((*it)->hasUpgradeMask(a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->hasUpgradeMask(a1))
			return true;
	}
	return false;
}

// ?rva004730B0@HordeContain@@UAEXPAVObject@@@Z @0x004730B0: slot 86; when the
// owner has status 0x4B, every contained Object whose AI's slot 111 does not
// hold gets the rowed AICommandInterface rva0026C2D9(target, 0x7FFFFFFF,
// CMD_FROM_AI).
void HordeContain::rva004730B0(Object *target)
{
	if (!target)
		return;
	if (!m_object->testStatus((ObjectStatusTypes)0x4B))
		return;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		AIUpdateInterface *ai = (*it)->m_ai;
		if (ai && !ai->rva0046A46FSlot111())
			ai->m_command.rva0026C2D9(target, 0x7FFFFFFF, CMD_FROM_AI);
	}
}

// ?rva0046DE2D@HordeContain@@UAEXPBVFXList@@@Z @0x0046DE2D: slot 123; plays the
// FXList on every contained Object, then on the Object of every +0x170 key.
void HordeContain::rva0046DE2D(const FXList *fx)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		FXList::doFXObj(fx, *it, 0);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		FXList::doFXObj(fx, TheGameLogic->findObjectByID((ObjectID)*k), 0);
}

// ?rva0046A712@HordeContain@@UAEXH@Z @0x0046A712: slot 110 (argument unread);
// runs slot 16, then moves every contained Object to the position and angle
// slot 7 gives for it (the pinned 0x0029660C, then Thing::setOrientation).
void HordeContain::rva0046A712(int)
{
	performReform();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		float angle;
		Coord3D pos;
		pos = slot7(obj, &angle);
		obj->teleportTo(&pos, false);
		((Thing *)obj)->setOrientation(angle);
	}
}

// ?rva0046ECDE@HordeContain@@UAEXPBUCoord3D@@0HW4PathfindLayerEnum@@@Z @0x0046ECDE:
// slot 111. Sends every contained Object through a portal: its slot-7 spot
// and angle, the rowed 0x0046E6EA fix-up against our Object, then the rowed
// AIUpdateInterface::moveThroughPortalWithMicropath toward our position
// (averaged with the second point off the ground layer).
void HordeContain::rva0046ECDE(const Coord3D *a1, const Coord3D *a2, int a3, PathfindLayerEnum layer)
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			AIUpdateInterface *ai = obj->m_ai;
			float angle = 0.0f;
			Coord3D pos;
			pos = slot7(obj, &angle);
			Coord3D dest = *self->getPosition();
			if (layer != LAYER_GROUND)
			{
				dest.add(a2);
				dest.scale(0.5f);
			}
			((Rva0046E6EA *)(UpdateModule *)this)->rva0046E6EA((Rva0046E6EAObject *)obj, (const Rva0046E6EACoord *)&pos, (Rva0046E6EACoord *)*(Object *volatile *)&self, false);
			ai->moveThroughPortalWithMicropath(a1, a2, a3, layer, &dest, &pos);
		}
	}
}

// The model-condition flag set at Object +0x10C (591 bits), with the
// ClearBit WB's Object::clearModelConditionState inlines.
template <> class BitFlags<591>
{
public:
	void clear(int bit) { m_bits[bit >> 5] &= ~(1U << (bit & 31)); }
private:
	unsigned int m_bits[19];
};
// Object::clearModelConditionState (Object.h), inlined as in WB: when the flag
// is up, clear it and notify the drawable (rowed 0x0028AE6D).
static __forceinline void clearModelConditionState(Object *obj, ModelConditionFlagType flag)
{
	if (obj->testCondition(flag))
	{
		((BitFlags<591> *)obj->m_conditionWords)->clear(flag);
		obj->rva0028AE6D();
	}
}

// ?rva0046C4C0@HordeContain@@UAEXXZ
// Retail 0x0046C4C0 (279 bytes), slot 55 of the +0x11C interface. Follows its
// WorldBuilder twin 0x010C3E30: stores our AI's rowed rva00260DED at +0x19C,
// then for every contained Object and every live Object of a +0x170 key that
// the rowed Object rva00290FBB accepts: unless its AI is moving, clears model
// condition 61 when +0x110 bit 29 is up, then hands it to primary slot 32.
void HordeContain::rva0046C4C0()
{
	m_19C = getObject()->m_ai->rva00260DED();
	Rva0046247DPair slotPair;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			if (obj->rva00290FBB())
			{
				if (!obj->m_ai->isMoving() && obj->test110(29))
					clearModelConditionState(obj, (ModelConditionFlagType)61);
				slot32(obj);
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			if (obj->rva00290FBB())
			{
				if (!obj->m_ai->isMoving() && obj->test110(29))
					clearModelConditionState(obj, (ModelConditionFlagType)61);
				slot32(obj);
			}
		}
	}
}

// ?rva0046C5D7@HordeContain@@UAE_NH@Z @0x0046C5D7: slot 58; whether a contained
// Object, or the live Object of a +0x170 key, has +0x44C equal to the
// (non-zero) argument.
bool HordeContain::rva0046C5D7(int value)
{
	if (!value)
		return false;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->m_44C == value)
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->m_44C == value)
			return true;
	}
	return false;
}

// ?rva0046A2EC@HordeContain@@UAE_NPAVObject@@@Z @0x0046A2EC: slot 82; whether
// every live contained Object with an AI is attacking the target: its slot
// 111 holds and its current victim is the target, and when the target has
// KindOf bit 13 the target's +0x250 module's slot 58 accepts that victim.
bool HordeContain::rva0046A2EC(Object *target)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				if (!ai->rva0046A46FSlot111())
					return false;
				Object *victim = ai->getCurrentVictim();
				if (!victim)
					return false;
				if (victim->getID() != target->getID())
					return false;
				if (target->hordeKindMask(13) && !target->m_250->slot58(victim))
					return false;
			}
		}
	}
	return true;
}

// ?rva0046A381@HordeContain@@UAE_NPAVObject@@@Z @0x0046A381: slot 80; whether
// some live contained Object with an AI whose slot 111 holds has the target as
// its current victim, or (target KindOf bit 13) a victim the target's +0x250
// module's slot 58 accepts.
bool HordeContain::rva0046A381(Object *target)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->isEffectivelyDead())
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0046A46FSlot111())
			{
				Object *victim = ai->getCurrentVictim();
				if (victim)
				{
					if (victim->getID() == target->getID())
						return true;
					if (target->hordeKindMask(13) && target->m_250->slot58(victim))
						return true;
				}
			}
		}
	}
	return false;
}

// Retail 0x0046BC30 (320 bytes), +0x11C interface slot 50, WB twin 0x010C2930.
// Moves live members to the goal plus their rotated formation offsets while +0x2A0 is unset.
// Target evidence establishes the slot, record stride and goal calls; the original method name is unknown.
// Coord2D's donor copy/Rotate operations guide the arithmetic; the retained FSINCOS pair is the native
// x87 codegen exception after the two CRT calls. Copy, rotation and final addition must stay separate
// member operations: their composed inlining reproduces retail's sine/y register reuse.
struct Rva0046BC30Offset : public Coord2D
{
	Rva0046BC30Offset(const Coord2D &v) { x = v.x; y = v.y; }

	__forceinline void AddTo(const Coord3D &goal, Coord3D &pos) const
	{
		pos.x = goal.x + x;
		pos.y = goal.y + y;
		pos.z = goal.z;
	}
	__forceinline Rva0046BC30Offset &Rotate(float angle)
	{
		struct TrigValues
		{
			float sine;
			float cosine;
		} trig;

		trig.sine = (float)sin((double)angle);
		trig.cosine = (float)cos((double)angle);
		__asm {
			fld angle
			fsincos
			fstp trig.cosine
			fstp trig.sine
		}

		float new_x = trig.cosine * x - trig.sine * y;
		float new_y = trig.cosine * y;
		new_y += trig.sine * x;
		y = new_y;
		x = new_x;
		return *this;
	}
};


void HordeContain::rva0046BC30()
{
	if (m_2A0 != 0)
		return;
	Coord3D goal;
	if (!m_object->GetGoalPosition(&goal))
		return;
	float angle = m_object->GetGoalAngle();
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj->isEffectivelyDead())
			continue;
		int index = ((Rva0046ACF6 *)(UpdateModule *)this)->rva0046ACF6(obj->getID());
		Rva0046BC30Offset offset(*reinterpret_cast<const Coord2D *>(&m_188Begin[index].m_04));
		offset.Rotate(angle);

		Coord3D pos;
		offset.AddTo(goal, pos);
		obj->rva0028ACEE((int)&pos, m_object->GetGoalLayer());
	}
}

// ?rva0046BD70@HordeContain@@UAEXXZ @0x0046BD70: slot 51; hands every
// contained Object (taken through the +0x20 contain interface's slot 70), then
// the live Object of every +0x170 key, that lacks status 0x1C to TheAI's
// pathfinder member 0x002E718A.
void HordeContain::rva0046BD70()
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectFromPathfindMap(obj);
	}
}

// ?rva0046BE0E@HordeContain@@UAEXXZ @0x0046BE0E: slot 52; the same walk with
// the pathfinder member 0x002E719B.
void HordeContain::rva0046BE0E()
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectGoalFromPathfindMap(obj);
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->RemoveObjectGoalFromPathfindMap(obj);
	}
}

// The locomotor set's valid-surfaces mask (+0x10), as the slot-38 walk reads it.
struct LocomotorSetSurfacesView
{
	unsigned char m_pad00[0x10];
	int m_validLocomotorSurfaces; // +0x10
};
// ?rva0046BEAC@HordeContain@@UAEXPAVObject@@@Z @0x0046BEAC: slot 38 (WB twin
// 0x010C3050): averages the positions of the live +0x170 key Objects that pass
// 0x00290FBB and of every contained Object (slot 70), then moves the given
// Object to the member position closest to that center (contained members
// only where the pathfinder accepts the spot for the given Object's layer and
// locomotor surfaces) and gives it that member's layer (default ground).
void HordeContain::rva0046BEAC(Object *obj)
{
	Coord3D center;
	center.zero();
	int count = 0;
	int layer = 1;
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
		if (member && member->rva00290FBB())
		{
			center.add(member->getPosition());
			++count;
		}
	}
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *member = *it;
		if (member)
		{
			center.add(member->getPosition());
			++count;
		}
	}
	if (count > 0)
	{
		float bestDist = -1.0f;
		center.scale(1.0f / count);
		Coord3D bestPos;
		bestPos.set(obj->getPosition());
		Coord3D pos;
		Coord3D delta;
		for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		{
			Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
			if (member && member->rva00290FBB())
			{
				delta.set(member->getPosition());
				pos.set(&delta);
				delta.sub(&center);
				if (bestDist < 0.0f || delta.lengthSqr() < bestDist)
				{
					bestPos = pos;
					bestDist = delta.lengthSqr();
					layer = member->rva0028B511();
				}
			}
		}
		for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
		{
			Object *member = *it;
			pos.set(member->getPosition());
			AIUpdateInterface *ai = obj->m_ai;
			int surfaces = ((const LocomotorSetSurfacesView *)&ai->getLocomotorSet())->m_validLocomotorSurfaces;
			if (TheAI->pathfinder()->IsValidMovementPositionForObject(&pos, obj->rva0028B511(), surfaces, obj))
			{
				delta.set(&pos);
				delta.sub(&center);
				if (bestDist < 0.0f || delta.lengthSqr() < bestDist)
				{
					bestPos = pos;
					bestDist = delta.lengthSqr();
					layer = member->rva0028B511();
				}
			}
		}
		((Thing *)obj)->setPosition(&bestPos);
		obj->setLayer((PathfindLayerEnum)layer);
	}
}

// The +0x20 contain interface (vtable 0x00C44EC8) as its slots see it: this
// is HordeContain+0x20, so the member-ID set (HordeContain +0x170) is at
// +0x150. A standalone view (never a base): no layout impact elsewhere.
struct HordeContainIface20View
{
	unsigned char m_pad00[0x150];
	_STL::set<int> m_ids; // +0x150 (HordeContain +0x170)
};
// ?rva004708BC@HordeContain@@UAEPAVObject@@PBVMatrix3D@@@Z @0x004708BC:
// slot 99; replaces the horde Object (which needs its +0x250 module) by one
// built from 0x0046AF12's template through the +0xFC interface: hands over
// the name and defection (status 0x3E), places it at the matrix, carries
// weapon-set bits 0x18-0x1A, its recorded experience (+0x258 map, else 1),
// contain slot 93 with the old Object's +0x284, the attribute pool, the
// remaining lifetime and the slot-5 behavior links; then wakes the +0x250
// module's slot-31 result. The template short is volatile-read for the
// second lookup so retail's post-find reload reproduces.
Object *HordeContain::rva004708BC(const Matrix3D *mtx)
{
	Object *self = m_object;
	if (!self)
		return 0;
	Object *result = 0;
	Rva0046A2ECContain *contain = self->m_250;
	if (contain)
	{
	const ThingTemplate *thingTemplate = (const ThingTemplate *)rva0046AF12();
	if (thingTemplate)
	{
		result = ((Rva00466FE0Iface *)((char *)(UpdateModule *)this + 0xFC))->rva00466FE0(thingTemplate, contain, self, thingTemplate->m_64.str(), 0);
		if (self->testStatus((ObjectStatusTypes)0x3E))
			self->bfmeTransferReplacementState(result);
		TheGameLogic->rva0023D0C2(result, self->m_45C);
		result->rva0028D412(mtx);
		((Rva00469B73 *)(UpdateModule *)this)->rva00469B73(result);
		if (((const Rva0028D891Owner *)self)->testBit(0x18))
			result->setWeaponSetFlag((WeaponSetType)0x18);
		if (((const Rva0028D891Owner *)self)->testBit(0x19))
			result->setWeaponSetFlag((WeaponSetType)0x19);
		if (((const Rva0028D891Owner *)self)->testBit(0x1A))
			result->setWeaponSetFlag((WeaponSetType)0x1A);
		float xp = 1.0f;
		const ThingTemplate *keytmpl = result->m_template;
		if (((_STL::map<unsigned short, int> *)&m_258)->find(keytmpl->m_5D8) != ((_STL::map<unsigned short, int> *)&m_258)->end())
			xp = m_258[*(volatile short *)&keytmpl->m_5D8];
		ExperienceTracker *tracker = result->m_264;
		tracker->rva0039B3D1(xp, false);
		((ContainIface93 *)((char *)this + 0x20))->slot93(&self->m_284, 0);
		AttributeModifierPoolUpdate *pool = self->findAttributeModifierPoolUpdate();
		if (pool)
			((Rva0040334B *)pool)->rva0040334B(result);
		static NameKeyType key = TheNameKeyGenerator->nameToKey("LifetimeUpdate");
		LifetimeUpdate *oldLife = (LifetimeUpdate *)self->findModule(key);
		if (oldLife)
		{
			LifetimeUpdate *newLife = (LifetimeUpdate *)result->findModule(key);
			if (newLife)
			{
				unsigned int left = oldLife->m_20 - TheGameLogic->m_frame;
				newLife->setLifetimeRange(left, left);
			}
		}
		for (Rva004708BCBehavior **m = self->m_244; *m; ++m)
		{
			if ((*m)->slot5())
			{
				for (Rva004708BCBehavior **n = result->m_244; *n; ++n)
				{
					Rva004708BCSlot5Iface *link = (*n)->slot5();
					if (link)
						link->slot1(self->m_74);
				}
				break;
			}
		}
	}
	Rva004708BCTail *tail = ((Rva004708BCContain *)contain)->slot31();
	if (tail)
	{
		tail->slot4(0);
		((Rva004708BCTail121 *)tail)->slot121();
	}
	}
	return result;
}

// ?rva0046BA56@HordeContain@@UAEXPAVObject@@H@Z @0x0046BA56: a +0x20
// contain-interface slot (vtable 0x00C44EC8; runtime this at +0x20 like
// iterateContained): the rowed defect member 0x00298979(source, false) on
// every contained Object, then on the live Object of every +0x170 key. The
// second parameter is dead (ret 8 but only [ebp+8] is read). The pair comes
// from a direct 0x0046247D call on the UpdateModule base (this-0x20), not
// the slot-70 virtual the +0x11C slots use.
void HordeContain::rva0046BA56(Object *source, int unused)
{
	Rva0046247DPair slotPair;
	((Rva0046247D *)((char *)this - 0x20))->rva0046247D(slotPair);
	const _STL::list<Object *> *items = slotPair.m04;
	const _STL::list<Object *> *pin = (items ? items : items);
	for (_STL::list<Object *>::const_iterator it = pin->begin(); it != pin->end(); ++it)
		(*it)->defect(source, false);
	HordeContainIface20View *self = (HordeContainIface20View *)this;
	for (_STL::set<int>::iterator k = self->m_ids.begin(); k != self->m_ids.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			obj->defect(source, false);
	}
}

// ?rva0046D8AE@HordeContain@@UAEXXZ @0x0046D8AE: slot 107; hands +0x200 to the
// pinned Object member 0x001E42F2 of every contained Object, clears the map at
// +0x24C, hands +0x1B4 to the same member of the Objects the +0x1AC and +0x1B0
// IDs name, then clears +0x1AC.
void HordeContain::rva0046D8AE()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->rva001E42F2(m_200.words);
	m_24C.clear();
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(m_1AC);
	Object *second = logic->findObjectByID(m_1B0);
	if (first)
		first->rva001E42F2(m_1B4.words);
	if (second)
		second->rva001E42F2(m_1B4.words);
	m_1AC = INVALID_OBJECT_ID;
}

// ?rva0046CB2C@HordeContain@@UAEPAVObject@@XZ @0x0046CB2C: slot 19; a random
// contained Object (taken through the +0x20 contain interface's slot 70), else
// the live Object of a random +0x170 key, else null. The random calls carry
// HordeContain.cpp lines 5383 and 5377.
Object *HordeContain::rva0046CB2C()
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	if (slotPair.m04->empty())
	{
		if (m_170.size() == 0)
			return 0;
		_STL::set<int>::iterator k = m_170.begin();
		for (int n = GetGameLogicRandomValue(0, m_170.size() - 1, HORDECONTAIN_SOURCE_FILE, 5377); n != 0; --n)
			++k;
		return TheGameLogic->findObjectByID((ObjectID)*k);
	}
	_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
	for (int n = GetGameLogicRandomValue(0, slotPair.m04->size() - 1, HORDECONTAIN_SOURCE_FILE, 5383); n != 0; --n)
		++it;
	return *it;
}

// ?rva0046D80B@HordeContain@@UAE_NXZ @0x0046D80B: slot 113; whether every
// contained Object that is not a +0x170 key lies within 10 (squared 2D
// distance 100) of our Object.
bool HordeContain::rva0046D80B()
{
	const _STL::list<Object *> *items = containedItems();
	const Coord3D *src = m_object->getPosition();
	Coord3D pos;
	pos.x = src->x;
	pos.y = src->y;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_170.find(obj->getID()) == m_170.end())
		{
			float dx = pos.x - obj->getPosition()->x;
			float dy = pos.y - obj->getPosition()->y;
			if (dy * dy + dx * dx > 100.0f)
				return false;
		}
	}
	return true;
}

// ?rva0046BB6F@HordeContain@@UAE_NPAHI@Z @0x0046BB6F: slot 36; clears *out and,
// for a frame before the current one, answers +0x29C when +0x298 (unless -1)
// plus the frame reaches the current frame, else asks the rowed Object
// rva0028C264(out, 4) of every contained Object (through the +0x20 contain
// interface's slot 70) and of the live Object of every +0x170 key.
bool HordeContain::rva0046BB6F(int *out, unsigned int frame)
{
	*out = 0;
	unsigned int now = TheGameLogic->m_frame;
	if (frame >= now)
		return false;
	if (m_298 != (unsigned int)-1 && m_298 + frame >= now)
	{
		*out = m_29C;
		return true;
	}
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->rva0028C264(out, 4))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->rva0028C264(out, 4))
			return true;
	}
	return false;
}

// ?rva0046D3FC@HordeContain@@UAEHPAVRva2225E0Filter@@@Z @0x0046D3FC: slot 96;
// without a filter, the +0x170 key count plus the +0x20 contain interface's
// slot 69 (0); with one, how many contained Objects and live Objects of +0x170
// keys the rowed filter accepts for our Object's controlling player.
int HordeContain::rva0046D3FC(Rva2225E0Filter *filter)
{
	if (!filter)
		return m_170.size() + slot69(0);
	int count = 0;
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if (filter->accepts(*it, self->getControllingPlayer()))
			++count;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && filter->accepts(obj, self->getControllingPlayer()))
			++count;
	}
	return count;
}

// ?rva0046A2A7@HordeContain@@UAE_NXZ @0x0046A2A7: slot 37; whether a contained
// Object (through the +0x20 contain interface's slot 70) has bit 29 of +0x110.
bool HordeContain::rva0046A2A7()
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	const _STL::list<Object *> *items = slotPair.m04;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && obj->test110(29))
			return true;
	}
	return false;
}

// ?rva0046E2BC@HordeContain@@UAEXXZ @0x0046E2BC: slot 148; sets +0x2E8 and
// clears the map at +0x2DC.
void HordeContain::rva0046E2BC()
{
	m_2E8 = true;
	m_2DC.clear();
}

// ?isFlankedBy@HordeContain@@UAE_NPAVObject@@@Z @0x00473D55: slot 147 of the
// +0x11C interface (WB HordeContain::isFlankedBy twin 0x010D1DC0). With a flank
// arc (module data +0x25C, degrees) below 360, an attacker of kind 13 whose
// +0x250 interface answers slot 149 flanks us while its map entry at +0x2DC
// (an expiry frame) is still ahead of the current frame. Without an entry the
// attacker's 2D direction is tested against the half-arc cosine for our facing
// and each angle of the +0x2CC list: a hit records an expiry frame (now + module
// data +0x264) and clears +0x2E8, a miss records 0. The direction is built from
// a register copy of the attacker position (retail's Coord3D copies member by
// member), so no component is stored before the subtraction.
bool HordeContain::isFlankedBy(Object *attacker)
{
	const HordeContainModuleDataFields *data = fields();
	if (data->m_25C >= 360.0f)
		return false;
	if (!attacker->hordeKindMask(13))
		return false;
	Rva0028C197Slot149 *other = (Rva0028C197Slot149 *)attacker->rva0028C197();
	if (!other || !other->slot149())
		return false;
	_STL::map<int, Rva00462D35Mapped>::iterator it = m_2DC.find(attacker->getID());
	if (it != m_2DC.end())
		return TheGameLogic->m_frame < (*it).second.m_bits;
	float halfArc = cos(data->m_25C * 3.141f / 360.0f);
	const Coord3D *pos = attacker->getPosition();
	const Coord3D *ourPos = m_object->getPosition();
	Coord3D delta;
	delta.set(pos);
	delta.sub(ourPos);
	Coord3D dir;
	dir.set(delta.x, delta.y, 0.0f);
	dir.Normalize();
	const Coord3D *facing = ((const Thing *)m_object)->getUnitDirectionVector2D();
	if (facing->x * dir.x + facing->z * dir.z + facing->y * dir.y < halfArc)
	{
		int id = attacker->getID();
		unsigned int now = TheGameLogic->m_frame;
		m_2DC[id].m_bits = now + data->m_264;
		m_2E8 = false;
		return true;
	}
	for (float *angle = m_2CCBegin; angle != m_2CCEnd; ++angle)
	{
		if (Cos(*angle) * dir.x + Sin(*angle) * dir.y < halfArc)
		{
			int id = attacker->getID();
			unsigned int now = TheGameLogic->m_frame;
			m_2DC[id].m_bits = now + data->m_264;
			m_2E8 = false;
			return true;
		}
	}
	m_2DC[attacker->getID()].m_bits = 0;
	return false;
}

__declspec(noinline) bool HordeContain::rva00468F0F(Object *obj, Object *target)
{
	float dx = obj->m_position.x - target->m_position.x;
	float dy = obj->m_position.y - target->m_position.y;
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return false;
	float r = ((const float *)ai->m_1F0)[0x3C / 4];
	float distSq = dy * dy;
	distSq = distSq + dx * dx;
	return distSq < r * r;
}
// ?rva004738B6@HordeContain@@UAEXPAVObject@@@Z @0x004738B6: slot 63 of the
// +0x11C interface.
void HordeContain::rva004738B6(Object *target)
{
	unsigned int remaining = TheWritableGlobalData->m_maxNumMembersToForceToImmediatelyEnter;
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); )
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		++k;
		if (!obj)
			continue;
		if (rva00468F0F(obj, target) == true)
		{
			Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
			if (contain)
			{
				contain->slot39(obj);
				continue;
			}
		}
		if (rva0046F7F8() && remaining > 0)
		{
			unsigned int now = TheGameLogic->m_frame;
			if (now - rva0046F7F8() > (unsigned int)TheWritableGlobalData->m_waitToForceMemberToEnterDelay)
			{
				Rva0046A2ECSlot39 *contain = (Rva0046A2ECSlot39 *)target->m_250;
				if (contain)
				{
					contain->slot39(obj);
					--remaining;
					continue;
				}
			}
		}
		AIUpdateInterface *ai = obj->m_ai;
		if (ai && ai->rva0047306ESlot110())
			ai->m_command.rva0026C347(target, CMD_FROM_AI);
	}
}

// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z @0x004756C9: slot 103 of the +0x11C interface (WB twin
// 0x010CD770). Unless a chance roll skips it, each member gets a goal 10x a random distance further away.
void HordeContain::backAwaySomeMembersFrom(Object *attacker)
{
	if (!attacker)
		return;
	Coord3D attackerPos;
	attackerPos.set(attacker->getPosition());
	const _STL::list<Object *> *items = containedItems();
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	bool disabled = m_object->testStatus((ObjectStatusTypes)0x45);
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *cur = *it;
		if (!disabled && !cur->testStatus((ObjectStatusTypes)0x45) && data->m_1F0 == 0.0f)
		{
			if (GetGameLogicRandomValueReal(0.0f, 1.0f, HORDECONTAIN_SOURCE_FILE, 8016) > data->m_1EC)
				continue;
		}
		float distance = GetGameLogicRandomValueReal(data->m_1E4, data->m_1E8, HORDECONTAIN_SOURCE_FILE, 8021);
		int frames = GetGameLogicRandomValue(data->m_1DC, data->m_1E0, HORDECONTAIN_SOURCE_FILE, 8022);
		Rva00469155 &goal = m_1A0.rva00473F81(cur->getID());
		Coord3D dir;
		dir.set(cur->getPosition());
		dir.sub(&attackerPos);
		dir.normalize();
		dir.scale(distance * 10.0f);
		Coord3D pos;
		pos.set(cur->getPosition());
		pos.add(&dir);
		goal.m_pos = pos;
		goal.m_value = frames;
	}
	m_2B0 = attacker->getID();
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

// ?endMove@HordeContain@@UAEXXZ @0x0046A0B2: slot 154; while our Object's
// AI is moving, runs the rowed AIUpdateInterface rva00262D2D on every
// contained Object's AI and then on ours.
void HordeContain::endMove()
{
	AIUpdateInterface *ai = m_object->m_ai;
	if (!ai->isMoving())
		return;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->m_ai->rva00262D2D();
	ai->rva00262D2D();
}

// The callback slot 125 hands the +0x20 contain interface's slot 68: records
// the +0x5D8 value of the first template seen (KindOf bit 68 templates are
// skipped) and flags any later template whose value differs.
struct Rva004698EEData
{
	bool m_differs; // +0x00
	short m_value; // +0x02
};

// ?rva004698EE@@YAXPAVObject@@PAX@Z @0x004698EE
void rva004698EE(Object *obj, void *userData)
{
	if (!obj)
		return;
	const ThingTemplate *thingTemplate = obj->m_template;
	if (!thingTemplate || thingTemplate->hordeKindMask(68))
		return;
	Rva004698EEData *data = (Rva004698EEData *)userData;
	if (data->m_value == 0)
	{
		data->m_value = thingTemplate->m_5D8;
		return;
	}
	if (thingTemplate->m_5D8 != data->m_value)
		data->m_differs = true;
}

// ?rva0046992C@HordeContain@@UAE_NXZ @0x0046992C: slot 125; when slot 127
// holds, whether the contained Objects' templates disagree on +0x5D8.
bool HordeContain::rva0046992C()
{
	if (!rva004698BC())
		return false;
	Rva004698EEData data;
	data.m_value = 0;
	data.m_differs = false;
	iterateContained(rva004698EE, &data, 1);
	return data.m_differs;
}

// The callback slot 21 hands the +0x20 contain interface's slot 68: keeps the
// ID of the Object whose +0x264 module has the largest +0x10 value (KindOf
// bit 68 templates are skipped).
struct Rva00469689Data
{
	float m_best; // +0x00
	ObjectID m_id; // +0x04
};

// ?rva00469689@@YAXPAVObject@@PAX@Z @0x00469689
void rva00469689(Object *obj, void *userData)
{
	if (!obj)
		return;
	const ThingTemplate *thingTemplate = obj->m_template;
	if (!thingTemplate || thingTemplate->hordeKindMask(68))
		return;
	Rva00469689Data *data = (Rva00469689Data *)userData;
	if (data->m_id != INVALID_OBJECT_ID && !(obj->m_264->m_10 > data->m_best))
		return;
	data->m_best = obj->m_264->m_10;
	data->m_id = (ObjectID)obj->getID();
}

// ?rva0046CBCA@HordeContain@@UAEPAVObject@@XZ @0x0046CBCA: slot 21; the
// contained Object whose +0x264 module's +0x10 value is largest.
Object *HordeContain::rva0046CBCA()
{
	Rva00469689Data data;
	data.m_best = -1.0f;
	data.m_id = INVALID_OBJECT_ID;
	iterateContained(rva00469689, &data, 1);
	return TheGameLogic->findObjectByID(data.m_id);
}

// ?rva0046CC09@HordeContain@@UAEPAVObject@@XZ @0x0046CC09: slot 20 (vtable
// 0x00C44C58 entry 20); of the contained Objects (+0x20 interface slot 70)
// and the live Objects of the +0x170 keys, the one whose current weapon
// (pinned Object::getCurrentWeapon 0x0028AEBD) reports the largest range
// from the rowed float query 0x002C9B80, else null.
Object *HordeContain::rva0046CC09()
{
	Object *best = 0;
	float bestRange = 0.0f;
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Weapon *weapon = obj->getCurrentWeapon();
			if (weapon)
			{
				float range = ((Rva002C9B80Owner *)weapon)->rva002C9B80(obj, 0.0f);
				if (range > bestRange)
				{
					bestRange = range;
					best = obj;
				}
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Weapon *weapon = obj->getCurrentWeapon();
			if (weapon)
			{
				float range = ((Rva002C9B80Owner *)weapon)->rva002C9B80(obj, 0.0f);
				if (range > bestRange)
				{
					bestRange = range;
					best = obj;
				}
			}
		}
	}
	return best;
}

// ?slot38@HordeContain@@UAE_NPAVObject@@HH@Z @0x00469647: slot 38 of the +0x20
// contain interface (vtable 0x00C44EC8, compiled with that subobject this);
// refuses an Object whose template has KindOf bit 13, else TransportContain's
// own slot 38 (0x00466EDE).
bool HordeContain::slot38(Object *obj, int a2, int a3)
{
	if (obj->m_template->hordeKindMask(13))
		return false;
	return TransportContain::slot38(obj, a2, a3);
}

// ?rva00473799@HordeContain@@UAEXABV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z
// @0x00473799: slot 30; unless +0x198 is set first runs primary slot 33 (1);
// then for each listed Object with an AI: 0x0028AD32, slot 11 on it, records
// its experience under its template's +0x5D8 key in the +0x258 map (keeping the
// largest), 0x0046A893 and, unless the module data's +0x234 is -1, AI slot 142
// with it. The largest goes to the horde Object's tracker (0x0039B3D1), then
// 0x0046E740 (0) and slots 121 and 4 (0). As in slot 49, retail advances the
// walk only past an entry with an AI.
void HordeContain::rva00473799(const _STL::list<Object *> &items)
{
	if (!m_198)
		((UpdateModule *)this)->slot33(1);
	const HordeContainModuleDataFields *data = fields();
	float best = 1.0f;
	_STL::list<Object *>::const_iterator it = items.begin();
	while (it != items.end())
	{
		Object *obj = *it;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai)
		{
			obj->rva0028AD32();
			assignSpotToUnit(obj);
			float v = obj->m_264->m_10;
			m_258[obj->m_template->m_5D8] = v;
			if (v > best)
				best = v;
			rva0046A893(obj);
			if (data && data->m_234 != -1)
				ai->slot142(data->m_234);
			++it;
		}
	}
	m_object->m_264->rva0039B3D1(best, true);
	rva0046E740(0);
	rva0046981C();
	returnToFormation(0);
}

// The callback slot 48 hands the +0x20 contain interface's slot 68: hands the
// value to the +0x264 tracker's 0x0039B3D1 of every contained Object whose
// template's +0x5D8 matches the key.
struct Rva00468AECData
{
	float m_value; // +0x00
	short m_key; // +0x04
};

// ?rva00468AEC@@YAXPAVObject@@PAX@Z @0x00468AEC
void rva00468AEC(Object *obj, void *userData)
{
	if (!obj)
		return;
	const ThingTemplate *thingTemplate = obj->m_template;
	if (!thingTemplate)
		return;
	Rva00468AECData *data = (Rva00468AECData *)userData;
	if (thingTemplate->m_5D8 != data->m_key)
		return;
	if (obj->m_264)
		obj->m_264->rva0039B3D1(data->m_value, false);
}

// ?rva004707DB@HordeContain@@UAEXPAVObject@@M@Z @0x004707DB: slot 48; adds the
// amount to the +0x258 map entry under the Object's template +0x5D8 key (a new
// key starts at 1 plus the amount), hands the total to every contained Object
// of that key, and when it exceeds the horde Object's tracker +0x10 passes it
// on there (0x0039B3D1), calling 0x0046E740 (1) if the tracker's +0x24 rose.
void HordeContain::rva004707DB(Object *obj, float amount)
{
	if (!obj)
		return;
	unsigned short key = obj->m_template->m_5D8;
	if (m_258.find(key) == m_258.end())
		m_258[key] = amount + 1.0f;
	else
	{
		float &total = m_258[key];
		total = total + amount;
	}
	Rva00468AECData data;
	data.m_value = m_258[key];
	data.m_key = key;
	iterateContained(rva00468AEC, &data, 1);
	ExperienceTracker *tracker = m_object->m_264;
	if (data.m_value > tracker->m_10)
	{
		int level = tracker->m_24;
		tracker->rva0039B3D1(data.m_value, false);
		if (m_object->m_264->m_24 > level)
			rva0046E740(1);
	}
}

// ?rva004739B4@HordeContain@@UAEXXZ @0x004739B4: slot 49; with anything
// contained (listed or keyed in the +0x170 tree), levels every Object up once
// and records its experience under its template's +0x5D8 key in the +0x258
// map, then calls 0x0046E740 with 0. Retail advances the list walk only past a
// non-null entry (the null branch jumps back without `mov esi,[esi]`).
void HordeContain::rva004739B4()
{
	{
		Rva0046247DPair slotPair;
		((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
		_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
		if (m_170.size() == 0 && slotPair.m04->size() == 0)
			return;
		while (it != slotPair.m04->end())
		{
			Object *obj = *it;
			if (obj)
			{
				obj->m_264->rva0039B4EC(1, false, false);
				float v = obj->m_264->m_10;
				m_258[obj->m_template->m_5D8] = v;
				++it;
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			obj->m_264->rva0039B4EC(1, false, false);
			float v = obj->m_264->m_10;
			m_258[obj->m_template->m_5D8] = v;
		}
	}
	rva0046E740(0);
}

// ?rva0046C3FE@HordeContain@@UAEXPAVPlayer@@@Z @0x0046C3FE: slot 53, which
// Object 0x0029041B notifies; passes the player to 0x0029041B of every
// contained Object and of the live Object of every +0x170 key, and runs the
// pinned Drawable member 0x00274176(false) on the drawable of each one that
// is locally controlled.
void HordeContain::rva0046C3FE(Player *player)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			obj->rva0029041B(player);
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && obj->isLocallyControlled())
				draw->rva00274176(false);
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			obj->rva0029041B(player);
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && obj->isLocallyControlled())
				draw->rva00274176(false);
		}
	}
}

// ?rva0046C327@HordeContain@@UAEXXZ @0x0046C327: slot 56; when our Object is
// the local player's, runs the pinned Drawable member 0x00272BE7 on our
// drawable if TheGlobalData +0x9A6 is set, else on the drawables of every
// contained Object and of the live Object of every +0x170 key.
void HordeContain::rva0046C327()
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	Player *local = ThePlayerList->getLocalPlayer();
	bool others = false;
	if (self && self->getControllingPlayer() == local)
	{
		Drawable *draw = ((Thing *)self)->getDrawable();
		if (TheWritableGlobalData->m_useSimpleHordeDecals)
		{
			if (draw)
				draw->rva00272BE7();
		}
		else
			others = true;
	}
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BE7();
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BE7();
		}
	}
}

// ?rva0046B850@HordeContain@@UAEMXZ @0x0046B850: slot 153; the mean of slot 5
// of the +0x254 module over the contained Objects and the live Objects of the
// +0x170 keys (0 when there are none).
float HordeContain::rva0046B850()
{
	float sum = 0.0f;
	float count = 0.0f;
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			sum += obj->m_254->slot5();
			count += 1.0f;
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			sum += obj->m_254->slot5();
			count += 1.0f;
		}
	}
	if (count > 0.0f)
		sum /= count;
	return sum;
}

// ?rva0046D1F7@HordeContain@@UAEXAAV?$list@PBVObject@@V?$allocator@PBVObject@@@_STL@@@_STL@@@Z @0x0046D1F7:
// slot 67; refills the list with the contained Objects (through the +0x20
// contain interface's slot 70) and the live Objects of the +0x170 keys. The
// element type is inferred: its STLport members fold onto the list<int>
// bodies retail calls (0x0023DAA5 clear, 0x0005548F push_back).
void HordeContain::rva0046D1F7(_STL::list<const Object *> &out)
{
	out.clear();
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
		out.push_back(*it);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		const Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			out.push_back(obj);
	}
}

// ?rva0046E253@HordeContain@@UAEXXZ @0x0046E253: slot 3; runs the rowed Object
// member 0x0028B95F on our Object and on every Object slot 67 lists.
void HordeContain::rva0046E253()
{
	m_object->rva0028B95F();
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	for (_STL::list<const Object *>::iterator it = objects.begin(); it != objects.end(); ++it)
		const_cast<Object *>(*it)->rva0028B95F();
}

// ?returnToFormation@HordeContain@@UAEX_N@Z @0x00472790: slot 4. Unless our Object
// lacks an AI, gathers back up to 100 of the +0x170 Objects (an ID with no live
// Object is erased through the STLport set<int> erase at 0x0046EDEF), each
// through primary slot 38; with our
// Object at status 2 and template +0x109 bit 1 clear, a gathered member with an
// AI farther than 10 from us gets the rowed 0x0045003E command and the
// unnamed AI member 0x0026594F. Any gathered member whose 0x0028B511 is not 1
// (or ours, on entry) clears the flag. After a gather: primary slot 37 until
// it answers false, performReform and 0x0046AA85; with the flag still set, slot
// 51, then a pathfinder-adjusted position between 10 and 150 away is applied.
// +0x120 and +0x121 record whether anything was gathered.
void HordeContain::returnToFormation(bool reposition)
{
	if (getObject()->rva0028B511() != 1 && reposition)
		reposition = false;
	Object *me = getObject();
	if (!me->m_ai)
		return;
	int tries = 100;
	bool gathered = false;
	while (m_170.size() != 0)
	{
		int id = *m_170.begin();
		if (--tries < 0)
			break;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)id);
		if (!obj)
		{
			m_170.erase(id);
			continue;
		}
		if (!obj->rva00290FBB())
			continue;
		m_194.size();
		gatherUnitBack(obj);
		if (me->testStatus((ObjectStatusTypes)2) && !(me->m_template->m_109 & 2))
		{
			AIUpdateInterface *ai = obj->m_ai;
			if (ai)
			{
				ai->m_command.rva0045003E(0, CMD_FROM_AI);
				Coord3D mine;
				mine.x = me->getPosition()->x;
				mine.y = me->getPosition()->y;
				mine.z = me->getPosition()->z;
				Coord3D theirs;
				theirs.x = obj->getPosition()->x;
				theirs.y = obj->getPosition()->y;
				theirs.z = obj->getPosition()->z;
				Rva0055A627Difference diff;
				diff.x = mine.x;
				diff.y = mine.y;
				diff.z = mine.z;
				diff.x -= theirs.x;
				diff.y -= theirs.y;
				diff.z -= theirs.z;
				if (diff.length() > 10.0f)
					ai->moveThroughPortalWithMicropath(&theirs, &theirs, 0x7fffffff, (PathfindLayerEnum)obj->rva0028B511(), &mine, &mine);
			}
		}
		{
			int layer = obj->rva0028B511();
			if (layer != 1)
				reposition = false;
		}
		gathered = true;
	}
	if (gathered)
	{
		while (rva00470B21())
			;
		performReform();
		rva0046AA85();
		if (reposition)
		{
			rva0046BD70();
			Object *obj = getObject();
			Coord3D pos;
			pos.x = obj->getPosition()->x;
			pos.y = obj->getPosition()->y;
			pos.z = obj->getPosition()->z;
			AIUpdateInterface *ai = obj->m_ai;
			if (!ai)
				return;
			TheAI->m_pathfinder->AdjustDestination(obj, ai->getLocomotorSet(), &pos, 0);
			float dist;
			{
				Rva0055A627Difference diff;
				diff.x = obj->getPosition()->x;
				diff.y = obj->getPosition()->y;
				diff.z = obj->getPosition()->z;
				diff.x -= pos.x;
				diff.y -= pos.y;
				diff.z -= pos.z;
				dist = diff.length();
			}
			if (dist > 10.0f && 150.0f > dist)
				((Thing *)obj)->setPosition(&pos);
		}
	}
	m_120 = gathered;
	m_121 = gathered;
}

// ?rva0046CDC9@HordeContain@@UAE_NXZ @0x0046CDC9: slot 23; with at least one
// Object listed by slot 67 and the module data's +0x1B0 template known to
// TheThingFactory, true unless the first of that template's module data whose
// slot 21 answers has +0x1D8 clear and wants more than that many (+0x268).
bool HordeContain::rva0046CDC9()
{
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	unsigned int count = objects.size();
	if (count >= 1)
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(fields()->m_1B0);
		if (thingTemplate)
		{
			const ModuleInfo *info = &thingTemplate->m_moduleInfo;
			int n = info->getCount();
			for (int i = 0; i < n; ++i)
			{
				const ModuleData *data = info->getNthData(i);
				if (data)
				{
					const HordeContainModuleDataFields *horde = data->slot21();
					if (horde)
					{
						if (!horde->m_1D8 && count < horde->m_268)
							return false;
						return true;
					}
				}
			}
			return true;
		}
	}
	return false;
}

// ?rva0046CCEF@HordeContain@@UAE_NPBVThingTemplate@@@Z @0x0046CCEF: slot 25;
// slot 23's test, false as well unless the argument is that template.
bool HordeContain::rva0046CCEF(const ThingTemplate *want)
{
	_STL::list<const Object *> objects;
	rva0046D1F7(objects);
	unsigned int count = objects.size();
	if (count < 1)
		return false;
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(fields()->m_1B0);
	if (!thingTemplate || want != thingTemplate)
		return false;
	const ModuleInfo *info = &thingTemplate->m_moduleInfo;
	int n = info->getCount();
	for (int i = 0; i < n; ++i)
	{
		const ModuleData *data = info->getNthData(i);
		if (data)
		{
			const HordeContainModuleDataFields *horde = data->slot21();
			if (horde)
			{
				if (!horde->m_1D8 && count < horde->m_268)
					return false;
				return true;
			}
		}
	}
	return true;
}

// ?rva0046C20B@HordeContain@@UAEXXZ @0x0046C20B: slot 57; slot 56's walk with
// the pinned Drawable member 0x00272BAB: (slot 96 (no filter), slot 101) on
// our drawable, else (1, slot 101) on the contained and key drawables.
void HordeContain::rva0046C20B()
{
	const _STL::list<Object *> *items = containedItems();
	Object *self = m_object;
	Player *local = ThePlayerList->getLocalPlayer();
	bool others = false;
	if (self && self->getControllingPlayer() == local)
	{
		Drawable *draw = ((Thing *)self)->getDrawable();
		if (TheWritableGlobalData->m_useSimpleHordeDecals)
		{
			if (draw)
				draw->rva00272BAB(rva0046D3FC(0), slot101(self));
		}
		else
			others = true;
	}
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BAB(1, slot101(obj));
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw && others)
				draw->rva00272BAB(1, slot101(obj));
		}
	}
}

// ?rva0046DEA1@HordeContain@@UAE?AW4ObjectID@@W42@@Z @0x0046DEA1: slot 138;
// over the contained Objects and then the Objects of the +0x170 keys, the ID
// slot 18 of each one's +0x254 module names (taken as the argument when that
// Object's +0x274 Object has the argument's ID): the first one found, or the
// argument itself whenever it turns up.
ObjectID HordeContain::rva0046DEA1(ObjectID want)
{
	const _STL::list<Object *> *items = containedItems();
	ObjectID result = INVALID_OBJECT_ID;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Rva0046B850Module *module = (*it)->m_254;
		if (module)
		{
			ObjectID id = module->slot18();
			if (id != INVALID_OBJECT_ID)
			{
				Object *obj = TheGameLogic->findObjectByID(id);
				if (obj && obj->m_274)
				{
					ObjectID other = (ObjectID)obj->m_274->getID();
					if (other == want)
						id = other;
				}
				if (id == want || result == INVALID_OBJECT_ID)
					result = id;
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
		if (member->m_254)
		{
			Rva0046B850Module *module = member->m_254;
			ObjectID id = module->slot18();
			Object *obj = TheGameLogic->findObjectByID(id);
			if (obj && obj->m_274)
			{
				ObjectID other = (ObjectID)obj->m_274->getID();
				if (other == want)
					id = other;
			}
			if (id != INVALID_OBJECT_ID && (id == want || result == INVALID_OBJECT_ID))
				result = id;
		}
	}
	return result;
}

// ?rva0046DF9A@HordeContain@@UAE_NPAUCoord3D@@@Z @0x0046DF9A: slot 139; the
// mean Drawable position of the contained Objects and the Objects of the
// +0x170 keys that have a Drawable; false (and zero) when there are none.
bool HordeContain::rva0046DF9A(Coord3D *center)
{
	float count = 0.0f;
	center->zero();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj && ((Thing *)obj)->getDrawable())
		{
			const Coord3D *pos = ((Thing *)obj)->getDrawable()->rva00276470();
			center->x += pos->x;
			center->y += pos->y;
			center->z += pos->z;
			count += 1.0f;
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && ((Thing *)obj)->getDrawable())
		{
			const Coord3D *pos = ((Thing *)obj)->getDrawable()->rva00276470();
			center->x += pos->x;
			center->y += pos->y;
			center->z += pos->z;
			count += 1.0f;
		}
	}
	if (count == 0.0f)
		return false;
	center->x /= count;
	center->y /= count;
	center->z /= count;
	return true;
}

// ?rva0046E113@HordeContain@@UAE_NPAUCoord3D@@@Z @0x0046E113: slot 140; the
// mean position of the contained Objects and the Objects of the +0x170 keys;
// false (and zero) when there are none.
bool HordeContain::rva0046E113(Coord3D *center)
{
	float count = 0.0f;
	center->zero();
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
		{
			const Coord3D *pos = obj->getPosition();
			center->x += pos->x;
			center->y += pos->y;
			center->z += pos->z;
			count += 1.0f;
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			const Coord3D *pos = obj->getPosition();
			center->x += pos->x;
			center->y += pos->y;
			center->z += pos->z;
			count += 1.0f;
		}
	}
	if (count == 0.0f)
		return false;
	center->x /= count;
	center->y /= count;
	center->z /= count;
	return true;
}

// ?rva0046A78F@HordeContain@@UAEXPBVMatrix3D@@@Z @0x0046A78F: slot 109; runs
// slot 16, then gives every contained Object the transform with its
// translation replaced by the position slot 7 gives for it (Object
// setTransformMatrix 0x0028D412).
void HordeContain::rva0046A78F(const Matrix3D *mtx)
{
	performReform();
	const _STL::list<Object *> *items = containedItems();
	Matrix3D transform = *mtx;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		float angle;
		Coord3D pos;
		pos = slot7(obj, &angle);
		transform.Row[0].W = pos.x;
		transform.Row[1].W = pos.y;
		transform.Row[2].W = pos.z;
		obj->rva0028D412(&transform);
	}
}

// ?rva00472A24@HordeContain@@UAEXPBUCoord3D@@W4CommandSourceType@@H@Z @0x00472A24:
// slot 31; hands every contained Object (from a copy of the contained list) to
// slot 42, builds a new AIGroup of the live Objects of the +0x170 keys
// (idling, from the command source, those whose AI slot 113 holds), sends the
// group to the position through the rowed AIGroup groupMoveToPosition and hands it to
// the rowed AI destroyGroup.
void HordeContain::rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3)
{
	_STL::list<const Object *> copy;
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
		copy.push_back(*it);
	AIGroup *group = TheAI->createGroup();
	for (_STL::list<const Object *>::iterator o = copy.begin(); o != copy.end(); ++o)
		slot42(*o);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
		{
			group->add(obj);
			AIUpdateInterface *ai = obj->m_ai;
			if (ai && ai->rva0047306ESlot113())
				ai->m_command.aiIdle(cmdSource);
		}
	}
	Rva00372571Params params;
	params.m_14 = -1;
	params.m_0C = 0;
	params.m_10 = 0;
	params.m_18 = 0;
	params.m_1C = false;
	params.m_pos = pos;
	params.m_08 = a3;
	params.m_04 = false;
	group->groupMoveToPosition(&params, cmdSource);
	TheAI->destroyGroup(group);
}

// ?slot42@HordeContain@@UAEXPBVObject@@@Z @0x0046B925: slot 42; keys the
// Object's ID into the +0x170 set, then hands it to the +0x20 contain
// interface's slot 41 (second argument 0).
void HordeContain::slot42(const Object *obj)
{
	m_170.insert(obj->getID());
	slot41(obj, 0);
}

// ?assignSpotToUnit@HordeContain@@UAEXPAVObject@@@Z @0x00470D09: slot 11; unless
// +0x198 is set first runs primary slot 33 (1); then takes the first free
// +0x188 record (the +0x194 index list) whose module-data entry names a
// template the Object's is equivalent to: records the index for the Object's
// ID in +0x17C, drops it from the free list and keys the ID into +0x170.
void HordeContain::assignSpotToUnit(Object *obj)
{
	if (!m_198)
		((UpdateModule *)this)->slot33(1);
	for (_STL::list<int>::iterator it = m_194.begin(); it != m_194.end(); ++it)
	{
		int index = *it;
		char *entry = (char *)((Rva00469294 *)m_moduleData)->rva00469294(m_188Begin[index].m_key);
		if (entry && obj->m_template->isEquivalentTo(
			TheThingFactory->findTemplate(*((const AsciiString *)(entry + 4)))))
		{
			m_17C[obj->getID()] = index;
			m_194.erase(it);
			m_170.insert(obj->getID());
			return;
		}
	}
}

// ?startMeleeAttack@HordeContain@@UAEXPAVObject@@@Z @0x0046A5EF: slot 77; for a new
// target ID (+0x2A0, also clearing +0x121) turns our Object by its relative
// angle to the target (or to the target's +0x274 Object), runs slot 16 when
// that angle exceeds 0.5235 rad, and hands the target to slot 3 of the +0x2C8
// helper.
void HordeContain::startMeleeAttack(Object *target)
{
	if (!target)
		return;
	if (target->getID() == m_2A0)
		return;
	m_2A0 = target->getID();
	m_121 = false;
	Object *aim = target;
	if (target->m_274)
		aim = target->m_274;
	Object *self = m_object;
	float angle = self->GetRelativeAngle(aim->getPosition());
	((Thing *)self)->setOrientation(angle + self->m_orientation);
	if (fabs(angle) > 0.5235f)
		performReform();
	m_2C8->slot3(target);
}

// ?rva00472329@HordeContain@@UAEXPBUCoord3D@@H@Z @0x00472329: slot 0 (second
// argument unread); unless usingMeleeAttack (0x004695DA) holds, every contained Object
// with an AI whose +0x17C entry names a +0x188 record whose key is in the
// module data's +0x1B8 map is ordered to attack the position (CMD_FROM_AI).
void HordeContain::rva00472329(const Coord3D *pos, int)
{
	if (usingMeleeAttack())
		return;
	Rva0046247DPair slotPair;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
	const _STL::map<int, int> *keys = &fields()->m_1B8;
	_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
	while (it != slotPair.m04->end())
	{
		const unsigned int id = (*it)->getID();
		if (m_17C.find(id) != m_17C.end())
		{
			AIUpdateInterface *ai = (*it)->m_ai;
			if (ai)
			{
				unsigned int key = m_188Begin[m_17C.find(id)->second].m_key;
				if (keys->find(key) != keys->end())
					ai->m_command.aiAttackPosition(pos, 0x7FFFFFFF, CMD_FROM_AI);
			}
		}
		++it;
	}
}

// ?attackTargetNow@HordeContain@@UAEXPAVObject@@H@Z @0x00471FFA (571B, ret 8):
// slot 1 of the +0x11C vftable 0x00C44C58; WB 0x010BF040
// HordeContain::attackTargetNow (assert at HordeContain.cpp:3350, compiled
// out). Unless usingMeleeAttack holds: re-forms (slot 4) when the +0x170 set
// is not empty; every contained Object (only the one 0x0046D946 picks when
// select is 1) that has a +0x17C entry and an idle AI either stops (melee
// weapon) or, when its +0x188 record's key is in the module data's +0x1B8
// map and 0x00468CB6 does not refuse, attacks the victim the target's
// container (the target itself for kind bit 13) chooses, if AI::0x002FE193
// allows; otherwise +0x120 is set. Retail pushes the 0x00468CB6 target from
// its stack home and reloads it afterwards (no CSE), hence the volatile read.
void HordeContain::attackTargetNow(Object *target, int select)
{
	if (usingMeleeAttack())
		return;
	if (m_170.size() != 0)
		returnToFormation(false);
	Rva0046247DPair members;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(members);
	const _STL::map<int, int> *keys = &fields()->m_1B8;
	Object *container = target->hordeKindMask(13) ? target : target->m_274;
	Object *only = 0;
	if (select == 1)
		only = ((Rva0046D946 *)(UpdateModule *)this)->rva0046D946(target);
	for (_STL::list<Object *>::const_iterator it = members.m04->begin(); it != members.m04->end(); ++it)
	{
		Object *obj = *it;
		if (only && obj != only)
			continue;
		if (m_17C.find(obj->getID()) == m_17C.end())
			continue;
		AIUpdateInterface *ai = obj->m_ai;
		if (!ai)
			continue;
		if (ai->isMoving())
			continue;
		if (obj->getCurrentWeapon() && obj->getCurrentWeapon()->m_04->get())
		{
			if (ai->rva0047306ESlot113())
				ai->m_command.aiIdle(CMD_FROM_AI);
			if (!obj->testStatus((ObjectStatusTypes)0x1C))
				obj->rva00295F05(false);
			continue;
		}
		int key = m_188Begin[m_17C.find(obj->getID())->second].m_key;
		if (keys->find(key) == keys->end())
			continue;
		if (rva00468CB6((Rva00468CB6A *)ai, *(Object *volatile *)&target))
			continue;
		Object *victim = target;
		Weapon *weapon = obj->getCurrentWeapon();
		if (container)
		{
			Rva00471FFAVictimChooser *chooser = (Rva00471FFAVictimChooser *)container->rva0028C197();
			if (chooser)
			{
				float range = 0.0f;
				if (weapon && !weapon->m_04->get())
					range = weapon->getAttackRange(obj);
				victim = chooser->slot18(0, obj->getPosition(), range, obj, false);
				if (!victim)
					victim = chooser->slot68();
			}
		}
		if (AI::rva002FE193(obj, victim))
			ai->m_command.rva0026C2D9(victim, 0x7FFFFFFF, CMD_FROM_AI);
		else
			m_120 = true;
	}
}

// ?rva00472235@HordeContain@@UAEXXZ @0x00472235: slot 2; unless the pinned
// 0x004695DA holds, first runs slot 4 (false) when the member-ID set at +0x170
// is not empty, then every contained Object whose +0x17C entry names a +0x188
// record keyed in the module data's +0x1B8 map is ordered (CMD_FROM_AI) to
// attack the closest enemy within its vision range.
void HordeContain::rva00472235()
{
	if (usingMeleeAttack())
		return;
	if (m_170.size() != 0)
		returnToFormation(0);
	const _STL::list<Object *> *items = containedItems();
	const _STL::map<int, int> *keys = &fields()->m_1B8;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_17C.find(obj->getID()) != m_17C.end())
		{
			int key = m_188Begin[m_17C.find(obj->getID())->second].m_key;
			if (keys->find(key) != keys->end())
			{
				Object *enemy = TheAI->findClosestEnemy(obj, obj->getVisionRange(), 2, 0, 0, 0);
				if (enemy)
					obj->m_ai->m_command.rva0026C2D9(enemy, 0x7FFFFFFF, CMD_FROM_AI);
			}
		}
	}
}

// ?rva0046970D@HordeContain@@UAE_NPAVObject@@HPBURva00469851Names@@_N@Z @0x0046970D:
// slot 27; with a zero second argument, whether the Object's template shares
// its +0x5D8 value with a template named in the list. When either the Object
// or ours has status 0x3E, both must have it, agree on +0x304 and the last
// argument must be set.
bool HordeContain::rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup)
{
	if (a2 != 0)
		return false;
	bool objHas = obj->testStatus((ObjectStatusTypes)0x3E);
	Object *self = m_object;
	bool selfHas = self->testStatus((ObjectStatusTypes)0x3E);
	if (objHas || selfHas)
	{
		if (!sameGroup || obj->m_304 != self->m_304 || objHas != selfHas)
			return false;
	}
	short key = obj->m_template->m_5D8;
	for (const AsciiString *name = names->begin(); name != names->end(); ++name)
	{
		const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(*name);
		if (thingTemplate && thingTemplate->m_5D8 == key)
			return true;
	}
	return false;
}

// ?rva00468B24@HordeContain@@QAEXM@Z @0x00468B24 55B: max-then-cap on +0x2EC;
// raises to the argument when larger, then clamps to g_00BC5CD4. Offset and
// neighbour slots prove HordeContain.
void HordeContain::rva00468B24(float value)
{
	if (value > m_2EC)
		m_2EC = value;
// g_00BC5CD4 was the retail address alias (RVA 0x007C5CD4) of the constant 90.0f; the literal is the source.
	if (m_2EC > 90.0f)
		m_2EC = 90.0f;
}

// ?rva0046966C@Rva0046966C@@QAEXXZ 0x0046966C 29B StringBase-G validate then outer +0x1D8 test to +0x291. Callers none. Same // cl: as neighbours.
class Rva0046966C;
template <> class StringBase<unsigned short>
{
	friend class Rva0046966C;
	void validate() const;
};
class Rva0046966C
{
public:
	void rva0046966C();
};

void Rva0046966C::rva0046966C()
{
	((StringBase<unsigned short> *)this)->validate();
	HordeContainModuleDataFields *outer = *(HordeContainModuleDataFields **)((char *)this - 0x30);
	*(bool *)((char *)this + 0x291) = (outer->m_1D8 == 0);
}

// HordeContain::iterateContained, retail 0x0046DD67 (94 bytes), the contain
// interface override (this at +0x20): WB names it. With flag 0x10 the
// horde's member IDs (the set at +0x170) are visited, each looked up before
// the iterator advances; otherwise the base iteration runs.
void HordeContain::iterateContained(ContainIterateFunc func, void *userData, int a3)
{
	if (a3 & 0x10)
	{
		for (_STL::set<int>::iterator it = m_170.begin(); it != m_170.end(); )
		{
			Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
			++it;
			func(obj, userData);
		}
	}
	else
	{
		ContainModuleInterface::baseIterateContained(func, userData, a3);
	}
}

// Clears a special unit slot holding the dying unit's ID.
static inline bool clearSpecialUnitID(ObjectID &slot, ObjectID id)
{
	if (slot == id)
	{
		slot = INVALID_OBJECT_ID;
		return true;
	}
	return false;
}

// The banner carrier update lookup 0x00468E26 is rowed as the stdcall
// Rva00468E26Get, whose body ignores ECX; retail calls it with this in ECX.
// The union gives that call the member ABI under the row's own name.
Module *__stdcall Rva00468E26Get(Object *);
class BannerUpdateOwner {};
union NativeBannerUpdateCall {
 Module *(__stdcall *target)(Object *);
 Module *(BannerUpdateOwner::*member)(Object *);
};
typedef char BannerUpdatePointerWidth[sizeof(NativeBannerUpdateCall)==4 ? 1 : -1];

// HordeContain::checkSpecialUnitDeath, retail 0x0046936B (66 bytes): WB
// names it and asserts the banner carrier's update module exists. A dying
// special unit (+0x264, or the banner carrier at +0x26C) is forgotten; for
// the banner carrier the horde keeps its update module's value.
void HordeContain::checkSpecialUnitDeath(Object *obj)
{
	ObjectID id = (ObjectID)obj->getID();
	if (clearSpecialUnitID(*(ObjectID *)&m_264, id))
		return;
	if (clearSpecialUnitID(m_26C, id))
	{
		NativeBannerUpdateCall getter = {&Rva00468E26Get};
		HordeBannerCarrierUpdate *update = (HordeBannerCarrierUpdate *)(((BannerUpdateOwner *)this)->*getter.member)(obj);
		if (update)
			m_27C = update->m_data->m_value;
	}
}

// HordeContain::getBannerCarrierIndexToUse, retail 0x0046A521 (144 bytes):
// WB names it and asserts the index list (+0x270) is not empty. A kind-13
// member takes the first entry; otherwise the entry for its template, else
// the first; the entry's template is reported and its index returned.
int HordeContain::getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate)
{
	const ThingTemplate *thingTemplate = obj->m_template;
	const _STL::vector<BannerIndexEntry *> &indexVec = m_bannerIndices;
	if (indexVec.empty())
		return -1;
	if (thingTemplate->hordeKindMask(13))
	{
		*outTemplate = indexVec[0]->m_template;
		return indexVec[0]->m_index;
	}
	for (unsigned int i = 0; i < indexVec.size(); ++i)
	{
		if (indexVec[i]->m_template == thingTemplate)
		{
			*outTemplate = indexVec[i]->m_template;
			return indexVec[i]->m_index;
		}
	}
	*outTemplate = indexVec[0]->m_template;
	return indexVec[0]->m_index;
}

// ?rva0046AF12@HordeContain@@QAEPAXXZ @0x0046AF12 (115 bytes, unnamed in WB):
// the template named by a random free spot: a random entry of the +0x194
// free index list (HordeContain.cpp line 1148) selects a +0x188 record whose
// module-data entry names the template; null when no spot is free or the
// record has no entry.
void *HordeContain::rva0046AF12()
{
	if (m_194.empty())
		return 0;
	int n = GetGameLogicRandomValue(0, m_194.size() - 1, HORDECONTAIN_SOURCE_FILE, 1148);
	_STL::list<int>::iterator it = m_194.begin();
	for (; n > 0; --n)
		++it;
	char *entry = (char *)((Rva00469294 *)m_moduleData)->rva00469294(m_188Begin[*it].m_key);
	if (entry)
		return (void *)TheThingFactory->findTemplate(*((const AsciiString *)(entry + 4)));
	return 0;
}

// ?rva0046FE99@HordeContain@@UAEXAAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z @0x0046FE99:
// slot 17; appends the contained Objects (through the +0x20 contain
// interface's slot 70) and the live Objects of the +0x170 keys to the list,
// then hands each contained Object, from a copy of the contained list, to
// slot 42.
void HordeContain::rva0046FE99(_STL::list<Object *> &out)
{
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
		out.push_back(*it);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			out.push_back(obj);
	}
	_STL::list<const Object *> copy;
	for (_STL::list<Object *>::const_iterator c = slotPair.m04->begin(); c != slotPair.m04->end(); ++c)
		copy.push_back(*c);
	{
		void *unused = slotPair.m00;
		slotPair.m00 = unused;
		slotPair.m00 = NULL;
	}
	_STL::list<const Object *>::iterator o;
	for (o = copy.begin(); o != copy.end(); ++o)
		slot42(*o);
}

// HordeContain::ClassifyBeforeOnAfterInvalidPortal, retail 0x0046FF81 (187
// bytes; slot 135 of the +0x11C interface vtable 0x00C44C58). Name from
// WorldBuilder (HordeContain.cpp, wb-name-unverified); the before/on/after
// parameter names follow it and are not target facts. Sorts the contained
// members' IDs by their AI path's next node: with a level TheTerrainLogic
// slot 35 rejects -> `on`; else a path that passes 0x00363AD7 -> `before`;
// anything else (no AI path, no node) -> `after`.
void HordeContain::ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (!obj)
			continue;
		AIUpdateInterface *ai = obj->m_ai;
		if (!ai)
			continue;
		Rva003638BA *path = ai->m_140;
		if (path)
		{
			Rva003642DFResult point = ((Path *)path)->rva00364521((const Rva0008BB38FloatField *)ai->m_1F0);
			if (point.m_node && point.m_node->m_08)
			{
				int level = ((Rva001E3511 *)&point)->rva001E3511();
				if (level != 0x7fffffff && !TheTerrainLogic->slot35(level))
				{
					on.push_back((ObjectID)obj->getID());
					continue;
				}
				if (path->rva00363AD7())
				{
					before.push_back((ObjectID)obj->getID());
					continue;
				}
			}
		}
		after.push_back((ObjectID)obj->getID());
	}
}

// ?rva004693AD@Rva004693AD@@QAE_NPAURva004693ADArg@@@Z 0x004693AD 44B: true when
// the Object's ID (+0x74) is HordeContain's +0x264 or +0x26C, or the Object's
// +0x04 record has flag bit 3 at +0x109; callers 0x00470517 0x00470731
// 0x00474C9F. Defined here, ahead of performReform, because retail's register
// choice there needs the callee's body in the same unit.
bool Rva004693AD::rva004693AD(Rva004693ADArg *arg)
{
	int value = arg->m_74;
	if (m_264 == value || m_26C == value || (arg->m_04->m_flags & 8) != 0)
		return true;
	return false;
}

// ?rva0046ACF6@Rva0046ACF6@@QAEHH@Z 0x0046ACF6 34B: the +0x17C map lookup via
// the rowed _M_find 0x00388F63, the found second at node+0x14 else 0. 12
// callers push the Object ID (+0x74) and index the 0x1C/0x54 records with the
// result (e.g. 0x0046BCA7 0x005845D6 0x005860F6); BFME1 donor
// BfmeAODHordeContainOwner::bfmeGetMemberIndex does the same find-or-zero.
// Honest address name; owner unproven.
int Rva0046ACF6::rva0046ACF6(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it != m_map.end())
		return (*it).second;
	return 0;
}

struct Coord3DInit : public Coord3D
{
	Coord3DInit(float ix, float iy, float iz) { x = ix; y = iy; z = iz; }
	Coord3DInit(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
	void sub(const Coord3D &c) { x -= c.x; y -= c.y; z -= c.z; }
	float lengthSqr2D() const { return x * x + y * y; }
};
// ?performReform@HordeContain@@UAEXXZ @0x00474BDA: slot 16 of the +0x11C
// interface (WB HordeContain::performReform). Builds each +0x188 record's
// world position from the 0x0046A5B1 offset, collects the contained members
// that 0x004693AD does not exclude and that own a record (0x0046ACF6) into the
// +0x194 free list, then repeatedly assigns the member whose nearest
// template-compatible free record is farthest away (+0x17C), and finally runs
// the primary vtable's slot 37 (0x00470B21) until it returns false.
void HordeContain::performReform()
{
	_STL::vector<Coord3D> positions;
	for (unsigned int i = 0; i < (unsigned int)(m_188End - m_188Begin); ++i)
	{
		Coord2D offset;
		rva0046A5B1(&offset, i);
		positions.push_back(Coord3DInit(m_object->getPosition()->x + offset.x, m_object->getPosition()->y + offset.y, 0.0f));
	}

	_STL::vector<Object *> members;
	Rva0046247DPair slotPair;
	rva0046D27ASlot70(slotPair);
	for (_STL::list<Object *>::const_iterator it = slotPair.m04->begin(); it != slotPair.m04->end(); ++it)
	{
		Object *obj = *it;
		if (!((Rva004693AD *)(UpdateModule *)this)->rva004693AD((Rva004693ADArg *)obj))
		{
			int index = ((Rva0046ACF6 *)(UpdateModule *)this)->rva0046ACF6(obj->getID());
			if (index >= 0 && (unsigned int)index < (unsigned int)(m_188End - m_188Begin))
			{
				m_194.push_back(index);
				members.push_back(*it);
			}
		}
	}

	while (!members.empty())
	{
		int bestIndex = -1;
		_STL::list<int>::iterator bestSlot = m_194.end();
		float bestDist = -1.0f;
		for (unsigned int i = 0; i < members.size(); ++i)
		{
			_STL::list<int>::iterator closest = m_194.end();
			float closestDist = 1e10f;
			for (_STL::list<int>::iterator it = m_194.begin(); it != m_194.end(); ++it)
			{
				char *entry = (char *)((Rva00469294 *)m_moduleData)->findEntry(rec188(*it).m_key);
				if (!entry || members[i]->isEquivalentTemplate(
					TheThingFactory->findTemplate(*((const AsciiString *)(entry + 4)))))
				{
					Coord3DInit delta(*members[i]->getPosition());
					delta.sub(positions[*it]);
					float dist = delta.lengthSqr2D();
					if (closestDist > dist)
					{
						closest = it;
						closestDist = dist;
					}
				}
			}
			if (closest == m_194.end())
			{
				closest = m_194.begin();
				closestDist = 0.0f;
			}
			if (closestDist > bestDist)
			{
				bestIndex = i;
				bestSlot = closest;
				bestDist = closestDist;
			}
		}
		Object **victim = &members[bestIndex];
		m_17C[(*victim)->getID()] = *bestSlot;
		m_194.erase(bestSlot);
		*victim = members.back();
		members.pop_back();
	}

	while (rva00470B21())
		;
}

#include "../../../../Include/GameLogic/ContainmentListView.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned short>::operator()(unsigned short const &x,unsigned short const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool>::pair(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > const &, bool const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator++(); }
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > & _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >::operator--(); }
namespace _STL { template <> _List_iterator<Object *, _Nonconst_traits<Object *> > list<Object *, allocator<Object *> >::insert(_List_iterator<Object *, _Nonconst_traits<Object *> >, Object *const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<int, _Nonconst_traits<int> >, bool> _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::insert_unique(int const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, bool> _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(pair<int const, int> const &); }
// Call retail's hinted insert_unique (0x00422EC0) instead of emitting this unit's own copy.
namespace _STL { template <> _Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > > _Rb_tree<int, pair<int const, int>, _Select1st<pair<int const, int> >, less<int>, allocator<pair<int const, int> > >::insert_unique(_Rb_tree_iterator<pair<int const, int>, _Nonconst_traits<pair<int const, int> > >, pair<int const, int> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@W4ObjectID@@U?$pair@$$CBW4ObjectID@@H@_STL@@U?$_Select1st@U?$pai:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum ObjectID;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<ObjectID const ,int>,_Nonconst_traits<pair<ObjectID const ,int> > >,bool> _Rb_tree<ObjectID,pair<ObjectID const ,int>,_Select1st<pair<ObjectID const ,int> >,less<ObjectID>,allocator<pair<ObjectID const ,int> > >::insert_unique(pair<ObjectID const ,int> const &); }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$l:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> pair<_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::iterator, bool> _Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >, less<int>, allocator<pair<const int, int> > >::insert_unique(const pair<const int, int> &); }

// Native4726DD..472790 (179B), slot5 of +11C vftable C44C58.
// The target first updates formation when set170 nonempty, resets target2A0,
// then copies the containment descriptor via the canonical36AE51 provider.
// Target AI258, turret-check468CB6 and AI vslot113 gate command45003E.
// Public method name remains address-derived; all offsets come from retail.
void HordeContain::rva004726DD(Object *target)
{
    if(!m_170.empty()) returnToFormation(false);
    if(m_2A0) rva00468FDC();
    Rva0046247DPair descriptor;
    ContainmentList members=((Rva0036AE51ListView*)((Rva0046247D*)(UpdateModule*)this)->rva0046247D(descriptor))->rva0036AE51();
    for(ContainmentList::const_iterator i=members.begin();i!=members.end();++i) {
        Object *obj=(Object*)containmentFirstWord(*i);
        AIUpdateInterface *ai=obj->m_ai;
        if(ai && !rva00468CB6((Rva00468CB6A*)ai,target) && !ai->rva0047306ESlot113())
            ai->m_command.rva0045003E(0,CMD_FROM_AI);
    }
}

// Exact existing 463D9B tree provider. Its opaque eight-byte value name is
// kept as an ABI adapter; target caller passes only the object ID address.
struct Rva00463D9BElement { char bytes[8]; };
typedef _STL::_Rb_tree<Rva00463D9BElement,Rva00463D9BElement,_STL::_Identity<Rva00463D9BElement>,_STL::less<Rva00463D9BElement>,_STL::allocator<Rva00463D9BElement> > Rva00463D9BTree;
namespace _STL { template<> unsigned int Rva00463D9BTree::erase(const Rva00463D9BElement &); }
// Native470717..4707DB, slot14 at +11C. WB supplies removeMemberFromHorde
// role (name not independently proven); target map17C/set170/list194,
// producer clear, primary vslot37 draining and final special-unit teardown.
void HordeContain::removeMemberFromHorde(Object *obj)
{
    Rva0046247DPair slotPair;
    slotPair.m04=0;
    int id;
    Rva004693ADArg *arg=(Rva004693ADArg*)obj;
    if(!((Rva004693AD*)(UpdateModule*)this)->rva004693AD(arg)) {
        id=obj->getID();
        m_194.push_front(m_17C[id]);
    }
    id=obj->getID();
    ((Rva00463D9BTree*)&m_17C)->erase(*(const Rva00463D9BElement*)&id);
    id=obj->getID();
    m_170.erase(id);
    slot41(obj,0);
    obj->setProducer(0);
    while(((UpdateModule*)this)->rva00470B21()) {}
    const _STL::list<Object*> *items=((Rva0046247DPair*)((Rva0046247D*)(UpdateModule*)this)->rva0046247D(slotPair))->m04;
    if(items->empty() && m_170.empty()) TheGameLogic->destroyObject(m_object);
    checkSpecialUnitDeath(obj);
}

// Native 0x0046A5B1..0x0046A5E6 (53B, ret 8): the +0x188 record's Coord2D at
// +0x0C rotated by the Object orientation through 0x00468E98 (pinned
// AODHordeContain::rva00468E98: same ECX, output pointer plus a by-value
// 8-byte offset; see AODHordeContainInitOffsets.cpp for the pair and its
// inline copy constructor). Returns the output pointer through EAX.
struct AODOffset2D
{
	AODOffset2D() {}
	AODOffset2D(const AODOffset2D &other) : x(other.x), y(other.y) {}
	~AODOffset2D() {}
	float x;
	float y;
};

class AODHordeContain
{
public:
	AODOffset2D *rva00468E98(AODOffset2D *out, AODOffset2D offset);
};

// 0x00468E98 is rowed as Rva00468E98::rotate (by-value result through the
// hidden pointer). The union calls that name with this view's explicit out
// pointer, which occupies the same stack slot.
class Rva00468E98Point
{
public:
	float x, y;
	Rva00468E98Point(const Rva00468E98Point &other);
	~Rva00468E98Point();
};
class Rva00468E98
{
public:
	Rva00468E98Point rotate(Rva00468E98Point);
};
union NativeRotateCall {
	Rva00468E98Point (Rva00468E98::*target)(Rva00468E98Point);
	AODOffset2D *(AODHordeContain::*member)(AODOffset2D *out, AODOffset2D offset);
};
typedef char RotatePointerWidth[sizeof(NativeRotateCall)==4 ? 1 : -1];

struct Rva0046A5B1Record
{
	unsigned char m_pad00[0x0C];
	AODOffset2D m_offset;	// +0x0C
	unsigned char m_pad14[0x1C - 0x14];
};

Coord2D *HordeContain::rva0046A5B1(Coord2D *offset, int index)
{
	Rva0046A5B1Record *rec = (Rva0046A5B1Record *)m_188Begin + index;
	NativeRotateCall rotate = {&Rva00468E98::rotate};
	(((AODHordeContain *)this)->*rotate.member)((AODOffset2D *)offset, rec->m_offset);
	return offset;
}

// Complete native4723F2..472444,82B RET8. Unnamed WB10C0320 independently
// has the same ID-map/indexed-record/module-entry/string comparison; its
// caller WB10C03B0 corresponds to native472444 and passes the complete
// owner obtained from its contain interface at20. The existing HordeContain
// constructor and assignSpotToUnit prove map17C and record-vector188.
// The purpose is an observed member-record name filter; original method
// name remains unknown. All called bodies and layouts are existing owners.
bool HordeContain::rva004723F2(Object *obj, const AsciiString &name)
{
 int id = obj->getID();
 int index = m_17C[id];
 char *entry = (char *)((Rva00469294 *)m_moduleData)->rva00469294(m_188Begin[index].m_key);
 if (entry && ((const AsciiString *)(entry + 4))->compare(name) == 0)
  return true;
 return false;
}

// ?returnToFormation@HorseHordeContain@@UAEX_N@Z @0x004766C3 5B: slot 4 of
// HorseHordeContain's +0x11C interface table 0x00C45838 (slot 2 is the other
// override there, the shared empty body 0x000B3FD0): it only extends
// HordeContain's (0x00472790 above), so a tail jump with the same +0x11C
// subobject this.
class HorseHordeContain : public HordeContain
{
public:
	virtual void returnToFormation(bool reposition);
};

void HorseHordeContain::returnToFormation(bool reposition)
{
	HordeContain::returnToFormation(reposition);
}

// ?attemptBestFirePointPosition@HordeContain@@UAE_NPAVObject@@PAVWeapon@@0@Z @0x00468D47 54B:
// slot 78 of the +0x20 ContainModuleInterface vftable.
bool HordeContain::attemptBestFirePointPosition(Object *source, Weapon *weapon, Object *victim)
{
	if (!source || !victim || !weapon)
		return false;
	if (weapon->isWithinAttackRange(source, victim, 0.0f, 1))
		return true;
	return false;
}

// ?rva0046BACD@HordeContain@@QAEXXZ @0x0046BACD (107 B): a +0x20
// contain-interface slot like rva0046BA56 beside it: the rowed 0x0029A12B
// on every contained Object, then on the live Object of every +0x170 key.
// Retail keeps the contained list in EBX straight from the pair, which cl
// does once 0x0046247D is visible above.
void HordeContain::rva0046BACD()
{
	Rva0046247DPair slotPair;
	((Rva0046247D *)((char *)this - 0x20))->rva0046247D(slotPair);
	const _STL::list<Object *> *items = slotPair.m04;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->rva0029A12B();
	HordeContainIface20View *self = (HordeContainIface20View *)this;
	for (_STL::set<int>::iterator k = self->m_ids.begin(); k != self->m_ids.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			obj->rva0029A12B();
	}
}

// ?rva0046AA85@HordeContain@@QAEXXZ @0x0046AA85 (51 B): runs the rowed
// 0x00469F3A on every contained Object, the list taken from 0x0046247D on
// the horde itself.
void HordeContain::rva0046AA85()
{
	Rva0046247DPair slotPair;
	((Rva0046247D *)this)->rva0046247D(slotPair);
	const _STL::list<Object *> *items = slotPair.m04;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		rva00469F3A(*it);
}
// Helpers for HordeContain::notifyOfMemberDeath below (slot views and the
// death-notification callees; all callees rowed, no pins).
class HordeDeathDrawable { public: void rva00272945(unsigned); char pad[0x43c]; bool refresh; };
class HordeDeathControl : public Rva00468D11Slots<6> { public: virtual void slot6(Object *) = 0; };
class HordeDeathBody : public Rva00468D11Slots<15> { public: virtual const unsigned *slot15() = 0; };
class HordeDeathInterface : public Rva00468D11Slots<96> { public: virtual unsigned slot96(int) = 0; };
class HordeDeathHeight : public Rva00468D11Slots<7> { public: virtual float height(float, float, int, bool, bool) = 0; };
struct HordeDeathDataView { char prefix[0x248]; int deathEvent; };
enum HordeDeathKind { HORDE_DEATH_KIND = 0x1bb };
enum EvaEventID { EVA_EVENT_NONE = 0 };
class Eva { public: bool reportEvaEvent(EvaEventID, const Coord3D *, const Coord3D *); };
extern Eva *TheEva;
class Rva00265254 { public: Rva00265254(unsigned, unsigned, unsigned, unsigned); int words[19]; };
class Rva001E42F2 { public: void rva001E42F2(const int *); };
class Rva0046247DDescriptor { public: Rva0036AE51ListView rva0046247D(); };

// The WorldBuilder counterpart constructs three two-float values around Sub;
// these local operations preserve its copy/destruction lifetimes without changing
// the shared Coord2D contract. Retail proves the two-float layout and arithmetic.
struct HordeDelta2D : public Coord2D {
 HordeDelta2D(const Coord2D &p) { x=p.x; y=p.y; }
 HordeDelta2D(const HordeDelta2D &hordeDelta2D) { x=hordeDelta2D.x; y=hordeDelta2D.y; }
 ~HordeDelta2D() {}
 HordeDelta2D &Sub(const HordeDelta2D &hordeDelta2D) { x-=hordeDelta2D.x; y-=hordeDelta2D.y; return *this; }
 float lengthSq() const { return x*x+y*y; }
};
// Retail invokes slot 12 with the selected object and its new formation index.
class HordeSlotMoveCallView : public Rva00468D11Slots<12> {
public: virtual void moveMember(Object *, int) = 0;
};
inline void hordeEraseIndex(_STL::map<int,int> &map, const int &id) { ((Rva00463D9BTree *)&map)->erase(*(const Rva00463D9BElement *)&id); }
// Retail 0x004704E4 (563 B), slot 13 of the +0x11C vtable 0x00C44C58, named by WB 0x10B3BB0:
// forgets a dying member, refills formation slots and tears down an emptied horde.
void HordeContain::notifyOfMemberDeath(Object *obj)
{
	if (!obj)
		return;
	((HordeDeathControl *)m_2C8)->slot6(obj);
	if (!((Rva004693AD *)(UpdateModule *)this)->rva004693AD((Rva004693ADArg *)obj))
		m_194.push_front(m_17C[obj->getID()]);
	if (obj->isKindOf((KindOfType)HORDE_DEATH_KIND)) {
		Object *other = TheGameLogic->findObjectByID((ObjectID)obj->getID());
		if (other) {
			((Rva001E42F2 *)other)->rva001E42F2(Rva00265254(0, 0x67, 0x69, HORDE_DEATH_KIND).words);
			((Thing *)other)->setPositionZ(((HordeDeathHeight *)TheTerrainLogic)->height(obj->m_position.x, obj->m_position.y, obj->rva0028B511(), false, true));
		}
	}
	if (Rva0046B850Module *body = obj->m_254) {
		const unsigned *data = ((HordeDeathBody *)body)->slot15();
		if (data)
			m_29C = data[2];
		else
			m_29C = 0;
	}
	hordeEraseIndex(m_17C, obj->getID());
	m_170.erase(obj->getID());
	bool refilled = false;
	do {
		refilled = rva00470B21();
	} while (refilled);
	bool hordeEmpty = ((Rva0046247DDescriptor *)(UpdateModule *)this)->rva0046247D().b->empty() && m_170.empty();
	if (hordeEmpty) {
		const HordeDeathDataView *data = (const HordeDeathDataView *)m_moduleData;
		TheEva->reportEvaEvent((EvaEventID)data->deathEvent, &obj->m_position, 0);
		TheGameLogic->destroyObject(m_object);
	}
	m_298 = TheGameLogic->m_frame;
	if (TheWritableGlobalData->m_useSimpleHordeDecals) {
		Drawable *draw = ((Thing *)m_object)->getDrawable();
		if (draw && ((HordeDeathDrawable *)draw)->refresh)
			draw->rva00272945(rva0046D3FC(0));
	}
	checkSpecialUnitDeath(obj);
	const HordeContainModuleDataFields *md = fields();
	if (md && !md->m_1D8) {
		_STL::list<const Object *> contained;
		rva0046D1F7(contained);
		if (contained.size() < (unsigned)md->m_268)
			rva004696E5();
	}
}
// Primary HordeContain vtable 0x00C45050 slot 37; retail 0x00470B21..0x00470D09.
// Fills the lowest vacant formation slot from a later eligible member, choosing
// the closest formation position under the module-data rank bound. The original
// method name is unresolved; WorldBuilder 0x010B54F0 corroborates the algorithm.
bool HordeContain::rva00470B21()
{
    if (m_194.empty()) return false;
    int bestIndex = ((_STL::vector<Rva00472329Record> *)&m_188Begin)->size();
    _STL::list<int>::iterator bestSlot;
    for (_STL::list<int>::iterator it = m_194.begin(); it != m_194.end(); ++it) {
        if (*it < bestIndex) { bestIndex = *it; bestSlot = it; }
    }
    if ((unsigned)bestIndex >= (unsigned)((_STL::vector<Rva00472329Record> *)&m_188Begin)->size()) return false;
    int key = rec188(bestIndex).m_key;
    int limit = 99;
    const _STL::list<int> *ranks = (const _STL::list<int> *)((const char *)m_moduleData + 0x1b4);
    for (_STL::list<int>::const_iterator it = ranks->begin(); it != ranks->end(); ++it) {
        if (*it >= key) { limit = *it; break; }
    }
    Rva0046247DPair pair;
    ((Rva0046247D *)(UpdateModule *)this)->rva0046247D(pair);
    int bestRank = limit;
    float bestDistance = 99999.0f;
    Object *best = 0;
    for (_STL::list<Object *>::const_iterator it = pair.m04->begin(); it != pair.m04->end(); ++it) {
        Object *obj = *it;
        int index = m_17C[obj->getID()];
        if (index <= bestIndex) continue;
        int rank = rec188(index).m_key;
        if (rank <= bestRank && rank > key) {
            HordeDelta2D delta(*(const Coord2D *)&rec188(bestIndex).m_04);
            HordeDelta2D other(*(const Coord2D *)&rec188(index).m_04);
            HordeDelta2D result = delta.Sub(other);
            float distance = result.lengthSq();
            if (distance < bestDistance) {
                best = obj;
                bestRank = rank;
                bestDistance = distance;
            }
        }
    }
    if (best) {
        int oldIndex = m_17C[best->getID()];
        hordeEraseIndex(m_17C, best->getID());
        m_17C[best->getID()] = bestIndex;
        ((HordeSlotMoveCallView *)m_2C8)->moveMember(best,bestIndex);
        m_194.erase(bestSlot);
        m_194.push_back(oldIndex);
        m_120 = true;
        return true;
    }
    return false;
}

// Native46E7E3..46E8EE RET8, slot 46 of the +0x11C vftable C44C58 (also in
// the HorseHorde/derived tables 0x00C45838 / 0x00C46930). Runs the rowed
// Object upgrade step 0x00293077 on our Object, then on each contained
// member the upgrade affects (all of them when the flag is set) and on the
// live Object of every +0x170 key, flashing each one's drawable with a 0.99
// grey through the rowed Drawable 0x0027541E (4, 4, 15). Name address-derived.
void HordeContain::rva0046E7E3(const UpgradeTemplate *upgrade, bool all)
{
	Rva0046247DPair descriptor;
	ContainmentList members = ((Rva0036AE51ListView *)((Rva0046247D *)(UpdateModule *)this)->rva0046247D(descriptor))->rva0036AE51();
	ContainmentList::const_iterator i = members.begin();
	RGBColor color;
	color.red = 0.99f;
	color.green = 0.99f;
	color.blue = 0.99f;
	m_object->rva00293077(upgrade);
	for (; i != members.end(); ++i)
	{
		Object *obj = (Object *)containmentFirstWord(*i);
		if (all || obj->affectedByUpgrade(upgrade))
		{
			obj->rva00293077(upgrade);
			Drawable *draw = ((Thing *)obj)->getDrawable();
			if (draw)
				draw->colorFlash(&color, 4, 4, 15);
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		obj->rva00293077(upgrade);
		Drawable *draw = ((Thing *)obj)->getDrawable();
		if (draw)
			draw->colorFlash(&color, 4, 4, 15);
	}
}

// ?rva0046EA94@HordeContain@@UAE_NPAVObject@@@Z
// Retail 0x0046EA94 (488 bytes), slot 28 of the +0x11C interface. Follows its
// WorldBuilder twin 0x010C7070: early-out status/kind tests, then with no
// rva002931F5(false) Object two slot-27 eligibility queries and a template
// name test that fall through to the shared related-Object check, which
// builds the related template name and looks up its rva0046D158 record.
// The getObject/getExperienceTracker/getTemplate inlines are the WB calls.
bool HordeContain::rva0046EA94(Object *obj)
{
	if (!obj)
		return false;
	if (obj->isEffectivelyDead())
		return false;
	if (obj->testStatus((ObjectStatusTypes)0x3B))
		return false;
	if (obj->testStatus((ObjectStatusTypes)0x3E))
		return false;
	Object *self = getObject();
	if (self->testStatus((ObjectStatusTypes)0x3E))
		return false;
	if (obj->isDisabled())
		return false;
	if (obj->isKindOf((KindOfType)0xDA))
		return false;
	Object *other = obj->rva002931F5(false);
	if (self->getControllingPlayer() != obj->getControllingPlayer())
		return false;
	if (!other)
	{
		const HordeContainModuleDataFields *data = fields();
		if (rva0046970D(obj, (int)m_264, &data->m_1F4, false))
			return true;
		if (rva0046970D(obj, m_26C, &data->m_218, false) && getObject()->getExperienceTracker()->getVeterancyLevel() <= 1)
			return true;
		if (data->m_238 && obj->getTemplate()->testFlag108(0xB) && data->m_23C.compare(obj->getTemplate()->m_64) == 0)
			return true;
	}
	if (!other || !self || other == self)
		return false;
	AsciiString name;
	name = other->getTemplate()->m_64;
	if (!rva0046D158(name))
		return false;
	if (other->testStatus((ObjectStatusTypes)2) || other->testStatus((ObjectStatusTypes)3))
		return false;
	if (self->testStatus((ObjectStatusTypes)2) || self->testStatus((ObjectStatusTypes)3))
		return false;
	return true;
}

// HordeContain slot update (WB 0x010B73E0). The forceinline helpers stand in for
// WorldBuilder's Coord3D cross/dot/scale/add members; their inline parameters set
// cl's operand order and SSE schedule in the side, 20.0 and held branches.
struct HordeOffset3D : public Coord3D { HordeOffset3D(const Coord3D &p) { x=p.x; y=p.y; z=p.z; } };
static __forceinline bool hordeTestCondition(const Object *obj, int bit)
{
	return ((obj->m_conditionWords[bit >> 5] >> (bit & 0x1f)) & 1) != 0;
}
static __forceinline float hordeCoordY(const Coord3D *c) { return c->y; }
static __forceinline float hordeDotP(const Coord3D *a, const Coord3D *b) { return (a->x*b->x) + a->y*b->y + a->z*b->z; }
static __forceinline Coord3D &hordeCrossR(Coord3D &r, const Coord3D &a, const Coord3D &b) { r.x = a.y*b.z - a.z*b.y; r.y = a.z*b.x - a.x*b.z; r.z = a.x*b.y - a.y*b.x; return r; }
static __forceinline Coord3D &hordeScaleR(Coord3D &r, float s) { r.x = s*r.x; r.y = s*r.y; r.z = s*r.z; return r; }
static __forceinline Coord3D &hordeAddR(Coord3D &r, const Coord3D &a) { r.x += a.x; r.y += a.y; r.z += a.z; return r; }
static __forceinline void hordeScaleAdd(Coord3D &r, float s, const Coord3D &a) { hordeScaleR(r, s); hordeAddR(r, a); }
void HordeContain::rva00470DC1()
{
	Rva0046247DPair slotPair;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(slotPair);
	_STL::list<Object *>::const_iterator it = slotPair.m04->begin();
	Object *self = getObject();
	TheAI->pathfinder()->AdjustLayer(self);
	float baseAngle = self->m_orientation;
	AIUpdateInterface *ai = self->m_ai;
	if (!ai)
		return;
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	Object *leader = TheGameLogic->findObjectByID((ObjectID)m_2B0);
	while (it != slotPair.m04->end())
	{
		Object *obj = *it;
		it++;
		if (m_170.find(obj->getID()) == m_170.end())
		{
			float angle = 0.0f;
			Coord3D pos = slot7(obj, &angle);
			if (rva0046F8F4())
			{
				HordeOffset3D dir(self->m_position);
				dir.z = 0.0f;
				dir.x = pos.x - dir.x;
				dir.y = hordeCoordY(&pos) - dir.y;
				if (dir.y * dir.y + dir.x * dir.x == 0.0f)
					angle = self->m_orientation;
				else
				{
					dir.Normalize2D();
					float a = ACos(dir.x);
					if (dir.y < 0.0f)
						a = 6.2831855f - a;
					angle = a;
				}
			}
			else
			{
				angle += baseAngle;
				if (!m_24C.empty())
				{
					if (hordeTestCondition(obj, 170))
					{
						rva0046D8AE();
						break;
					}
					Object *attacker = TheGameLogic->findObjectByID(m_1B0);
					Object *target = TheGameLogic->findObjectByID(m_1AC);
					if (!target || !attacker)
					{
						rva0046D8AE();
						break;
					}
					float dist = ((Rva000CBA20 *)attacker)->distSq((const Rva000CBA20Point *)target->getPosition());
					if (obj == attacker)
					{
						if (dist < 410.0f)
						{
							((Rva001E431E *)obj)->rva001E431E(m_1B4.words);
							angle = obj->GetRelativeAngle(target->getPosition());
							angle += obj->m_orientation;
						}
					}
					else if (obj == target)
					{
						if (dist < 410.0f)
							((Rva001E431E *)obj)->rva001E431E(m_1B4.words);
						pos = obj->m_position;
						pos.sub(&attacker->m_position);
						pos.normalize();
						hordeScaleR(pos, 20.0f);
						pos.add(&attacker->m_position);
						angle = obj->GetRelativeAngle(&attacker->m_position);
						angle += obj->m_orientation;
					}
					else if (dist < 410.0f)
					{
						int slot = reinterpret_cast<_STL::map<int, int> &>(m_24C)[obj->getID()];
						((Rva001E431E *)obj)->rva001E431E(m_200.words);
						angle = obj->GetRelativeAngle(&attacker->m_position);
						angle += obj->m_orientation;
						pos = obj->m_position;
						pos.sub(&attacker->m_position);
						pos.normalize();
						pos.scale((float)slot);
						pos.add(&attacker->m_position);
						Object *closest = ((Rva0046D946 *)(UpdateModule *)this)->rva0046D946(obj);
						if (closest && ((Rva000CBA20 *)obj)->distSq((const Rva000CBA20Point *)closest->getPosition()) < 55.0f)
						{
							HordeOffset3D delta(obj->m_position);
							delta.sub(&attacker->m_position);
							Coord3D up; up.x = 0.0f; up.y = 0.0f; up.z = 1.0f;
							Coord3D side;
							hordeCrossR(side, up, delta);
							HordeOffset3D toClosest(closest->m_position);
							toClosest.sub(&obj->m_position);
							side.normalize();
							hordeScaleR(side, (float)(hordeDotP(&toClosest, &side) > 0.0f ? -4 : 4));
							hordeAddR(pos, side);
						}
					}
				}
				else if (!m_1A0.empty())
				{
					_STL::map<int, int>::iterator held = reinterpret_cast<_STL::map<int, int> &>(m_1A0).find(obj->getID());
					if (held != reinterpret_cast<_STL::map<int, int> &>(m_1A0).end())
					{
						if (leader && data->m_1F0 != 0.0f)
						{
							const Coord3D *objPos = &obj->m_position;
							HordeOffset3D offset(*objPos);
							offset.sub(&leader->m_position);
							float length = offset.length();
							if (length < data->m_1F0 * 0.9)
							{
								pos = offset;
								pos.normalize();
								hordeScaleAdd(pos, 5.0f, obj->m_position);
							}
							else if (length < data->m_1F0)
								pos = obj->m_position;
						}
						else
						{
							Rva00469155 *goal = (Rva00469155 *)&held->second;
							if (goal->m_value <= 0)
								pos = goal->m_pos;
							else
							{
								goal->m_value--;
								continue;
							}
						}
					}
					if (leader)
					{
						angle = obj->GetRelativeAngle(leader->getPosition());
						angle += obj->m_orientation;
					}
				}
				else if (m_2C4)
				{
					angle = obj->GetRelativeAngle(&m_2B8);
					angle += obj->m_orientation;
				}
			}
			rva00474842(obj, &pos, angle, !ai->isMoving());
		}
	}
	((Rva0046A024 *)(UpdateModule *)this)->rva0046A024();
}
