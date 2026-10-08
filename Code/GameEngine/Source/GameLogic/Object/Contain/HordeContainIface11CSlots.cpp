// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /D_CRTIMP= /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
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
#include "ascii_string.h"
#include <list>
#include <map>
#include <set>
#include <vector>
#include <math.h>
#include "../../../Common/PartitionRangeQueryCallView.h"
// The +0x258 map's comparator: a per-RVA stand-in for less<unsigned short>,
// so its instance names (operator[] 0x00470041 and the folded callees it
// reaches) stay placeholders.
struct Rva00470041Less : public _STL::less<unsigned short> {};
struct Coord3D
{
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
	float GetLengthEstimate2D() const;
	float x;
	float y;
	float z;
};
// The float triple whose length is the address-owned copy 0x00003571.
class Rva0055A627Difference
{
public:
	float x, y, z;
	float length() const;
};
// class-gate: allow Coord2D the canonical data-only header cannot declare BFME 2's out-of-line toAngle (rowed 0x00005923) that slot 130 calls; same two floats
class Coord2D
{
public:
	float x;
	float y;
	float toAngle() const;
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};
enum ObjectID
{
	INVALID_ID = 0
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
extern const int g_009BA4E4;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
class Object;
class AttributeModifierPoolUpdate
{
public:
	bool addModifierToPool(const AsciiString &name, int a2);
	void removeModifierFromPool(const AsciiString &name);
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
class AICommandInterface
{
public:
	virtual void aiCommandInterfaceAnchor();
	void rva0037379B(Object *obj, CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);
	void rva0045003E(int a1, CommandSourceType cmdSource);
	void rva0026C2D9(Object *obj, int a2, CommandSourceType cmdSource);
	void aiAttackPosition(const Coord3D *pos, int maxShotsToFire, CommandSourceType cmdSource);
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
// Retail's random calls carry this source path literal.
#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
class Player;
class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};
struct Rva002A8AB1Record
{
	void rva002C6AA8(int value, Object *obj);
};
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;
class LocomotorSet;
class Pathfinder
{
public:
	bool IsPointOnWall(int pos, bool flag);
	bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
	bool IsPointOnRamp(const Coord3D *pos);
	void RemoveObjectFromPathfindMap(Object *object);
	void RemoveObjectGoalFromPathfindMap(Object *object);
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
	void rva00372571(Rva00372571Params *params, int source);
};
class AttackPriorityInfo;
class PartitionFilter;
class AI
{
public:
	AIGroup *createGroup();
	void destroyGroup(AIGroup *group);
	Object *findClosestEnemy(const Object *me, float range, unsigned int qualifiers, const AttackPriorityInfo *info, PartitionFilter *optionalFilter, int a6);
	unsigned char m_pad00[0x10];
	Pathfinder *m_pathfinder; // +0x10
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
	__forceinline Matrix3D(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
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
};
class Thing
{
public:
	void setOrientation(float angle);
	void setPosition(const Coord3D *pos);
	Drawable *getDrawable() const;
};
class GlobalData
{
public:
	unsigned char m_pad000[0x9A6];
	bool m_9A6; // +0x9A6
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
class BfmeThingTFB
{
public:
	void bfmeTwoTFB(int a1, int a2);
};
class BfmeArg985
{
public:
	char bfmeHas985C(int a1);
};
struct Rva003642DFNode;
struct Rva003642DFResult;
struct Rva00468C37Holder;
// The AI's +0x140 path.
class Rva003638BA
{
public:
	bool rva003638BA();
	bool rva00363AD7();
	// 0x00364521: the path point for the +0x1F0 member's distance
	// (unnamed; returns the 16-byte node+position value of 0x003642DF).
	Rva003642DFResult rva00364521(Rva00468C37Holder *holder);
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
	const LocomotorSet &getLocomotorSet() const { return *(const LocomotorSet *)m_1CC; }
	void rva0026594F(const Coord3D *a1, const Coord3D *a2, int a3, int layer, const Coord3D *a5, const Coord3D *a6);
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
	int getCount() const { return m_end - m_begin; }
	const ModuleData *getNthData(int i) const;
	Entry *m_begin; // vector<Entry>
	Entry *m_end;
	Entry *m_cap;
};
class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x64];
	AsciiString m_64; // +0x64 (template name)
	unsigned char m_pad068[0x109 - 0x68];
	unsigned char m_109; // +0x109 (bit 1 keeps slot 4 from re-commanding members)
	unsigned char m_pad10A[0x114 - 0x10A];
	unsigned int m_kindOf[4]; // +0x114
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo; // +0x2E4
	unsigned char m_pad2F0[0x528 - 0x2F0];
	float m_528; // +0x528 (an angle slot 130 adds to a wall's orientation)
	unsigned char m_pad52C[0x5D8 - 0x52C];
	short m_5D8; // +0x5D8
};
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
// The weapon's float range query is the rowed 0x002C9B80 (its row names the
// owner Rva002C9B80Owner).
class Weapon;
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
class Object
{
public:
	Weapon *getCurrentWeapon(WeaponSlotType *slot = 0);	// pinned 0x0028AEBD
	int getID() const { return m_74; }
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
	bool isEquivalentTemplate(const ThingTemplate *t) const { return m_template->isEquivalentTo(t); }
	__forceinline unsigned int isKindOf(int kind) const
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
	unsigned char m_pad114[0x250 - 0x114];
	Rva0046A2ECContain *m_250; // +0x250
	Rva0046B850Module *m_254; // +0x254
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x264 - 0x25C];
	ExperienceTracker *m_264; // +0x264
	unsigned char m_pad268[0x274 - 0x268];
	Object *m_274; // +0x274
	unsigned char m_pad278[0x304 - 0x278];
	int m_304; // +0x304
	unsigned char m_pad308[0x438 - 0x308];
	unsigned char m_438; // +0x438
	unsigned char m_pad439[0x44C - 0x439];
	int m_44C; // +0x44C
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	void rva0028AD32();
	Object *rva002931F5(bool flag);
	bool rva0028D9E5(int a1) const;
	void setTeam(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void clearModelConditionStateForHorde(ModelConditionFlagType flag);
	void setModelConditionStateForHorde(ModelConditionFlagType flag);
	void rva001E42F2(const int *value);
	void rva0028B95F();
	unsigned char rva00290FBB() const;
	int rva0028B511() const;
	void rva0028AE6D();
	void rva0028CFB2(const int *a, const int *b);
	void setTransformMatrix(const Matrix3D *mtx);
	float GetRelativeAngle(const Coord3D *pos) const;
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
	float getVisionRange() const;
	Module *findModule(NameKeyType key) const;
	bool addAttributeModifierToPool(const AsciiString &name, int a2);
	void rva0029041B(Player *player);
	bool isLocallyControlled() const;
	void removeAttributeModifierFromPool(const AsciiString &name);
private:
	friend class HordeContain;
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	unsigned char m_pad00[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);
};
extern class ThingFactory *TheThingFactory;
struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};
struct Rva00462D35Mapped
{
	unsigned int m_bits;
};
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
	unsigned char m_pad04[0x1C - 0x04];
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
class Rva004695DA
{
public:
	unsigned char rva004695DA();
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
	void *rva0046247D(Rva0046247DPair &p);
};
// The rowed 0x0046E740 on the HordeContain base (slots 30 and 49 pass 0).
class Rva0046E740
{
public:
	void rva0046E740(int a1);
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
	unsigned char m_pad1D9[0x224 - 0x1D9];
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
	unsigned char m_pad238[0x254 - 0x238];
	bool m_254; // +0x254
	unsigned char m_pad255[0x268 - 0x255];
	unsigned int m_268; // +0x268
	float m_26C; // +0x26C
	float m_270; // +0x270
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
// HordeContain's +0x11C interface (vtable 0x00C44C58), 152 slots; named ones are
// the overrides below plus slot 144 (banked) and the slots they call.
class Rva0046BB38Iface6 : public Rva0046BB38Slots<0>
{
public:
	virtual void rva00472329(const Coord3D *pos, int unused) = 0;
	virtual void gap1() = 0; virtual void rva00472235() = 0; virtual void rva0046E253() = 0; virtual void rva00472790(bool reposition) = 0; virtual void gap5() = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void assignSpotToUnit(Object *obj) = 0; virtual void rva00469F2F(Object *obj) = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void performReform() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual Object *rva0046CC09() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup) = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void rva00473799(const _STL::list<Object *> &items) = 0; virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3) = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void gap38() = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void rva004707DB(Object *obj, float amount) = 0; virtual void rva004739B4() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void rva0046C3FE(Player *player) = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual bool rva0046AAB8() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p) = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual void gap69() = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void startMeleeAttack(Object *target) = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool canEngageInMelee(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual void gap99() = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void rva0046A78F(const Matrix3D *mtx) = 0;
	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
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
	virtual void gap147() = 0;
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
	virtual void gap35() = 0;
	virtual void gap36() = 0;
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
class ContainModuleInterface : public Rva00468D11Slots<38>
{
public:
	virtual bool slot38(Object *obj, int a2, int a3) = 0;
	virtual void cgap39() = 0; virtual void cgap40() = 0; virtual void slot41(const Object *obj, int a2) = 0; virtual void cgap42() = 0; virtual void cgap43() = 0; virtual void cgap44() = 0; virtual void cgap45() = 0; virtual void cgap46() = 0; virtual void cgap47() = 0; virtual void cgap48() = 0; virtual void cgap49() = 0; virtual void cgap50() = 0; virtual void cgap51() = 0; virtual void cgap52() = 0; virtual void cgap53() = 0; virtual void cgap54() = 0; virtual void cgap55() = 0; virtual void cgap56() = 0; virtual void cgap57() = 0; virtual void cgap58() = 0; virtual void cgap59() = 0; virtual void cgap60() = 0; virtual void cgap61() = 0; virtual void cgap62() = 0; virtual void cgap63() = 0; virtual void cgap64() = 0; virtual void cgap65() = 0; virtual void cgap66() = 0; virtual void cgap67() = 0;
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);	// slot 68; the base body is 0x004635EC
	virtual int slot69(int a1) = 0;
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
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

class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	void rva00468B24(float value);
	void rva0046A893(Object *obj);
	void checkSpecialUnitDeath(Object *obj);
	void *rva0046AF12();
	int getBannerCarrierIndexToUse(const Object *obj, const ThingTemplate **outTemplate);
	HordeBannerCarrierUpdate *rva00468E26(Object *obj);	// 0x00468E26, banner carrier update lookup
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3);
	virtual bool rva0046BB38(Object *other);
	virtual void rva0046FE99(_STL::list<Object *> &out);
	virtual void ClassifyBeforeOnAfterInvalidPortal(_STL::vector<ObjectID> &before, _STL::vector<ObjectID> &on, _STL::vector<ObjectID> &after);
	virtual AsciiString rva0046D1AC();
	virtual void rva0046F7C9(Object *obj);
	virtual void rva00469F2F(Object *obj);
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
	virtual bool rva004698BC();
	virtual const void *rva004698D6();
	virtual const void *rva004698E2();
	virtual void rva00469967();
	virtual void rva004690A9(const Coord3D *pos);
	virtual bool rva0046F8CD();
	virtual bool rva00468C37();
	virtual void rva00468C60(const Coord3D *pos);
	virtual bool rva00468C7B(Coord3D *pos);
	virtual float rva0046F8DA();
	virtual float rva0046F8E7();
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
	virtual void rva0046D7AF(int a1);
	virtual void rva0046DDC5(int a1, int a2);
	virtual void rva0046D384(Team *team);
	virtual void rva004730B0(Object *target);
	virtual void rva0046DE2D(const FXList *fx);
	virtual void rva0046A712(int unused);
	virtual bool rva0046C5D7(int value);
	virtual bool rva0046A2EC(Object *target);
	virtual bool rva0046A381(Object *target);
	virtual void rva0046BD70();
	virtual void rva0046BE0E();
	virtual void rva0046C3FE(Player *player);
	virtual void rva004707DB(Object *obj, float amount);
	virtual void rva004739B4();
	virtual void rva00473799(const _STL::list<Object *> &items);
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
	virtual float rva0046B850();
	virtual void rva0046D1F7(_STL::list<const Object *> &out);
	virtual void rva0046E253();
	virtual void rva00472790(bool reposition);
	void rva0046AA85();
	virtual bool rva0046CDC9();
	virtual bool rva0046CCEF(const ThingTemplate *tmpl);
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual bool rva0046B9DC(int a1);
	virtual bool rva0046B95E(int a1);
	virtual bool rva0046AAB8();
	virtual void rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3);
	virtual void rva0046DC92(const AsciiString &name, Rva2225E0Filter *filter);
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p);
	virtual Rva002390CB rva0046EC7C(Object *obj);
	Rva0046D158Record *rva0046D158(AsciiString name);
	virtual void performReform();
	virtual bool rva00470B21();
	Coord2D *rva0046A5B1(Coord2D *offset, int index);
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
	unsigned char m_pad1A0[0x1AC - 0x1A0];
	ObjectID m_1AC; // +0x1AC
	ObjectID m_1B0; // +0x1B0
	int m_1B4; // +0x1B4
	unsigned char m_pad1B8[0x200 - 0x1B8];
	int m_200; // +0x200
	unsigned char m_pad204[0x24C - 0x204];
	_STL::map<int, void *> m_24C; // +0x24C
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
	unsigned char m_pad2A5[0x2B8 - 0x2A5];
	Coord3D m_2B8; // +0x2B8
	bool m_2C4; // +0x2C4
	unsigned char m_pad2C5[0x2C8 - 0x2C5];
	Rva00468FDCHelper *m_2C8; // +0x2C8
	unsigned char m_pad2CC[0x2DC - 0x2CC];
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
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
}

// ?rva004696E5@HordeContain@@UAEXXZ @0x004696E5: slot 24, the same lookup handed
// to slot 26 when found.
void HordeContain::rva004696E5()
{
	void *thingTemplate = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
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
			((Thing *)obj)->setOrientation(wall->m_orientation + wall->m_template->m_528);
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
// at +0x288, sets +0x28C to the logic frame g_009BA4E4 * 3 frames from now.
// Retail computes the delay (imul esi,esi,3) before the call; /G7, which this
// unit is compiled with, is what selects that form over lea.
void HordeContain::rva00468D7D(Object *obj)
{
	if (!obj)
		return;
	int id = obj->m_74;
	unsigned int delay = g_009BA4E4 * 3;
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
	Rva0046247DPair p;
	return ((Rva00291793 *)((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p))->rva00291793() == 0 ? true : false;
}

// ?rva0046F7FF@HordeContain@@UAEAAURva0046247DPair@@AAU2@@Z @0x0046F7FF:
// slot 66; fills the argument with the contained-list pair and returns it.
Rva0046247DPair &HordeContain::rva0046F7FF(Rva0046247DPair &p)
{
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
	return p;
}

// ?rva0046DB6D@HordeContain@@UAEXABVAsciiString@@PAVRva2225E0Filter@@H@Z
// @0x0046DB6D: slot 118; unless the named modifier's store category is
// missing or has index 6, adds it (with the third argument) to the pool of
// every contained Object and every Object keyed in the +0x170 tree the filter
// accepts (all of them without a filter); then to this Object's own pool.
void HordeContain::rva0046DB6D(const AsciiString &name, Rva2225E0Filter *filter, int a3)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	Object *self = m_object;
	Rva0046DB6DCategory *category = (Rva0046DB6DCategory *)TheAttributeModifierStore->GetCategoryContainer(
		TheAttributeModifierStore->rva00214713(TheNameKeyGenerator->nameToKey(name.str())));
	if (category && category->m_index != 6)
	{
		for (; it != p.m04->end(); ++it)
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	Object *self = m_object;
	for (; it != p.m04->end(); ++it)
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
		pool->removeModifierFromPool(name);
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	if (!p.m04->empty())
		return p.m04->front();
	_STL::set<int>::iterator it = m_170.begin();
	if (it != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*it);
	return 0;
}

// ?rva0046D7AF@HordeContain@@UAEXH@Z @0x0046D7AF: slot 108; for each contained
// Object not keyed in the +0x170 tree, the pinned bfmeTwoTFB(argument, 0).
void HordeContain::rva0046D7AF(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (m_170.find(obj->getID()) == m_170.end())
			((BfmeThingTFB *)obj)->bfmeTwoTFB(a1, 0);
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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

// ?rva0046B9DC@HordeContain@@UAE_NH@Z @0x0046B9DC: slot 43; whether the pinned
// bfmeHas985C(argument) holds for a contained Object or for the Object of a
// +0x170 key.
bool HordeContain::rva0046B9DC(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if (((BfmeArg985 *)*it)->bfmeHas985C(a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (((BfmeArg985 *)obj)->bfmeHas985C(a1))
			return true;
	}
	return false;
}

// ?rva0046B95E@HordeContain@@UAE_NH@Z @0x0046B95E: slot 44; whether the rowed
// Object::rva0028D9E5(argument) holds for a contained Object or for the live
// Object of a +0x170 key.
bool HordeContain::rva0046B95E(int a1)
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		if ((*it)->rva0028D9E5(a1))
			return true;
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj && obj->rva0028D9E5(a1))
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
		((BfmeThingTFB *)obj)->bfmeTwoTFB((int)&pos, 0);
		((Thing *)obj)->setOrientation(angle);
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
				if (target->isKindOf(13) && !target->m_250->slot58(victim))
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
					if (target->isKindOf(13) && target->m_250->slot58(victim))
						return true;
				}
			}
		}
	}
	return false;
}

// ?rva0046BD70@HordeContain@@UAEXXZ @0x0046BD70: slot 51; hands every
// contained Object (taken through the +0x20 contain interface's slot 70), then
// the live Object of every +0x170 key, that lacks status 0x1C to TheAI's
// pathfinder member 0x002E718A.
void HordeContain::rva0046BD70()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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

// ?rva0046D8AE@HordeContain@@UAEXXZ @0x0046D8AE: slot 107; hands +0x200 to the
// pinned Object member 0x001E42F2 of every contained Object, clears the map at
// +0x24C, hands +0x1B4 to the same member of the Objects the +0x1AC and +0x1B0
// IDs name, then clears +0x1AC.
void HordeContain::rva0046D8AE()
{
	const _STL::list<Object *> *items = containedItems();
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
		(*it)->rva001E42F2(&m_200);
	m_24C.clear();
	GameLogic *logic = TheGameLogic;
	Object *first = logic->findObjectByID(m_1AC);
	Object *second = logic->findObjectByID(m_1B0);
	if (first)
		first->rva001E42F2(&m_1B4);
	if (second)
		second->rva001E42F2(&m_1B4);
	m_1AC = INVALID_ID;
}

// ?rva0046CB2C@HordeContain@@UAEPAVObject@@XZ @0x0046CB2C: slot 19; a random
// contained Object (taken through the +0x20 contain interface's slot 70), else
// the live Object of a random +0x170 key, else null. The random calls carry
// HordeContain.cpp lines 5383 and 5377.
Object *HordeContain::rva0046CB2C()
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	if (p.m04->empty())
	{
		if (m_170.size() == 0)
			return 0;
		_STL::set<int>::iterator k = m_170.begin();
		for (int n = GetGameLogicRandomValue(0, m_170.size() - 1, HORDECONTAIN_SOURCE_FILE, 5377); n != 0; --n)
			++k;
		return TheGameLogic->findObjectByID((ObjectID)*k);
	}
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	for (int n = GetGameLogicRandomValue(0, p.m04->size() - 1, HORDECONTAIN_SOURCE_FILE, 5383); n != 0; --n)
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	const _STL::list<Object *> *items = p.m04;
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
	const ThingTemplate *tmpl = obj->m_template;
	if (!tmpl || tmpl->isKindOf(68))
		return;
	Rva004698EEData *data = (Rva004698EEData *)userData;
	if (data->m_value == 0)
	{
		data->m_value = tmpl->m_5D8;
		return;
	}
	if (tmpl->m_5D8 != data->m_value)
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
	const ThingTemplate *tmpl = obj->m_template;
	if (!tmpl || tmpl->isKindOf(68))
		return;
	Rva00469689Data *data = (Rva00469689Data *)userData;
	if (data->m_id != INVALID_ID && !(obj->m_264->m_10 > data->m_best))
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
	data.m_id = INVALID_ID;
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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
	if (obj->m_template->isKindOf(13))
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
	((Rva0046E740 *)(UpdateModule *)this)->rva0046E740(0);
	rva0046981C();
	rva00472790(0);
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
	const ThingTemplate *tmpl = obj->m_template;
	if (!tmpl)
		return;
	Rva00468AECData *data = (Rva00468AECData *)userData;
	if (tmpl->m_5D8 != data->m_key)
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
			((Rva0046E740 *)(UpdateModule *)this)->rva0046E740(1);
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
		Rva0046247DPair p;
		((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
		_STL::list<Object *>::const_iterator it = p.m04->begin();
		if (m_170.size() == 0 && p.m04->size() == 0)
			return;
		while (it != p.m04->end())
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
	((Rva0046E740 *)(UpdateModule *)this)->rva0046E740(0);
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
		if (TheWritableGlobalData->m_9A6)
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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

// ?rva00472790@HordeContain@@UAEX_N@Z @0x00472790: slot 4. Unless our Object
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
void HordeContain::rva00472790(bool reposition)
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
					ai->rva0026594F(&theirs, &theirs, 0x7fffffff, obj->rva0028B511(), &mine, &mine);
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
			TheAI->m_pathfinder->adjustDestination(obj, ai->getLocomotorSet(), &pos, 0);
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
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
		if (tmpl)
		{
			const ModuleInfo *info = &tmpl->m_moduleInfo;
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
	const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&fields()->m_1B0);
	if (!tmpl || want != tmpl)
		return false;
	const ModuleInfo *info = &tmpl->m_moduleInfo;
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
		if (TheWritableGlobalData->m_9A6)
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
	ObjectID result = INVALID_ID;
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Rva0046B850Module *module = (*it)->m_254;
		if (module)
		{
			ObjectID id = module->slot18();
			if (id != INVALID_ID)
			{
				Object *obj = TheGameLogic->findObjectByID(id);
				if (obj && obj->m_274)
				{
					ObjectID other = (ObjectID)obj->m_274->getID();
					if (other == want)
						id = other;
				}
				if (id == want || result == INVALID_ID)
					result = id;
			}
		}
	}
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *member = TheGameLogic->findObjectByID((ObjectID)*k);
		Rva0046B850Module *module = member->m_254;
		if (module)
		{
			ObjectID id = module->slot18();
			Object *obj = TheGameLogic->findObjectByID(id);
			if (obj && obj->m_274)
			{
				ObjectID other = (ObjectID)obj->m_274->getID();
				if (other == want)
					id = other;
			}
			if (id != INVALID_ID && (id == want || result == INVALID_ID))
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
		obj->setTransformMatrix(&transform);
	}
}

// ?rva00472A24@HordeContain@@UAEXPBUCoord3D@@W4CommandSourceType@@H@Z @0x00472A24:
// slot 31; hands every contained Object (from a copy of the contained list) to
// slot 42, builds a new AIGroup of the live Objects of the +0x170 keys
// (idling, from the command source, those whose AI slot 113 holds), sends the
// group to the position through the rowed AIGroup rva00372571 and hands it to
// the rowed AI destroyGroup.
void HordeContain::rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3)
{
	_STL::list<const Object *> copy;
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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
	group->rva00372571(&params, cmdSource);
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
			(const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)(entry + 4))))
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
// argument unread); unless the pinned 0x004695DA holds, every contained Object
// with an AI whose +0x17C entry names a +0x188 record whose key is in the
// module data's +0x1B8 map is ordered to attack the position (CMD_FROM_AI).
void HordeContain::rva00472329(const Coord3D *pos, int)
{
	if (((Rva004695DA *)(UpdateModule *)this)->rva004695DA())
		return;
	Rva0046247DPair p;
	((Rva0046247D *)(UpdateModule *)this)->rva0046247D(p);
	const _STL::map<int, int> *keys = &fields()->m_1B8;
	_STL::list<Object *>::const_iterator it = p.m04->begin();
	while (it != p.m04->end())
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

// ?rva00472235@HordeContain@@UAEXXZ @0x00472235: slot 2; unless the pinned
// 0x004695DA holds, first runs slot 4 (false) when the member-ID set at +0x170
// is not empty, then every contained Object whose +0x17C entry names a +0x188
// record keyed in the module data's +0x1B8 map is ordered (CMD_FROM_AI) to
// attack the closest enemy within its vision range.
void HordeContain::rva00472235()
{
	if (((Rva004695DA *)(UpdateModule *)this)->rva004695DA())
		return;
	if (m_170.size() != 0)
		rva00472790(0);
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
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(name);
		if (tmpl && tmpl->m_5D8 == key)
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
	extern float g_00BC5CD4;
	if (m_2EC > g_00BC5CD4)
		m_2EC = g_00BC5CD4;
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
		ContainModuleInterface::iterateContained(func, userData, a3);
	}
}

// Clears a special unit slot holding the dying unit's ID.
static inline bool clearSpecialUnitID(ObjectID &slot, ObjectID id)
{
	if (slot == id)
	{
		slot = INVALID_ID;
		return true;
	}
	return false;
}

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
		HordeBannerCarrierUpdate *update = rva00468E26(obj);
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
	const ThingTemplate *tmpl = obj->m_template;
	const _STL::vector<BannerIndexEntry *> &indexVec = m_bannerIndices;
	if (indexVec.empty())
		return -1;
	if (tmpl->isKindOf(13))
	{
		*outTemplate = indexVec[0]->m_template;
		return indexVec[0]->m_index;
	}
	for (unsigned int i = 0; i < indexVec.size(); ++i)
	{
		if (indexVec[i]->m_template == tmpl)
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
		return ((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)(entry + 4));
	return 0;
}

// ?rva0046FE99@HordeContain@@UAEXAAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z @0x0046FE99:
// slot 17; appends the contained Objects (through the +0x20 contain
// interface's slot 70) and the live Objects of the +0x170 keys to the list,
// then hands each contained Object, from a copy of the contained list, to
// slot 42.
void HordeContain::rva0046FE99(_STL::list<Object *> &out)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
		out.push_back(*it);
	for (_STL::set<int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*k);
		if (obj)
			out.push_back(obj);
	}
	_STL::list<const Object *> copy;
	for (_STL::list<Object *>::const_iterator c = p.m04->begin(); c != p.m04->end(); ++c)
		copy.push_back(*c);
	{
		void *unused = p.m00;
		p.m00 = unused;
		p.m00 = NULL;
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
			Rva003642DFResult point = path->rva00364521(ai->m_1F0);
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
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
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
					(const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA((const AsciiString *)(entry + 4))))
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
