// ?rva0046D2C3@HordeContain@@UAEPAVObject@@H@Z
// partial score=0.88 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /G7
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
// The +0x258 map's comparator: a per-RVA stand-in for less<unsigned short>,
// so its instance names (operator[] 0x00470041 and the folded callees it
// reaches) stay placeholders.
struct Rva00470041Less : public _STL::less<unsigned short> {};
struct Coord3D
{
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
	void scale(float s) { x *= s; y *= s; z *= s; }
	float x;
	float y;
	float z;
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
class Pathfinder
{
public:
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
	unsigned char m_pad144[0x1F0 - 0x144];
	Rva00468C37Holder *m_1F0; // +0x1F0
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
	int rva000456AC(int bit) const;
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x64];
	AsciiString m_64; // +0x64 (template name)
	unsigned char m_pad068[0x114 - 0x68];
	unsigned int m_kindOf[4]; // +0x114
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo; // +0x2E4
	unsigned char m_pad2F0[0x5D8 - 0x2F0];
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
	void rva0028AE6D();
	void setTransformMatrix(const Matrix3D *mtx);
	float GetRelativeAngle(const Coord3D *pos) const;
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
	float getVisionRange() const;
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
struct Rva0046D2C3ListNode
{
	Rva0046D2C3ListNode *m_next;
	Rva0046D2C3ListNode *m_previous;
	Object *m_value;
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
};
// A +0x188 record: the key the module data's +0x1B8 map is searched for.
struct Rva00472329Record
{
	int m_key; // +0x00
	unsigned char m_pad04[0x1C - 0x04];
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
	virtual void gap1() = 0; virtual void rva00472235() = 0; virtual void rva0046E253() = 0; virtual void rva00472790(int a1) = 0; virtual void gap5() = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void assignSpotToUnit(Object *obj) = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void slot16() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual Object *rva0046CC09() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual bool rva0046970D(Object *obj, int a2, const Rva00469851Names *names, bool sameGroup) = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void rva00473799(const _STL::list<Object *> &items) = 0; virtual void rva00472A24(const Coord3D *pos, CommandSourceType cmdSource, int a3) = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void gap38() = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void gap48() = 0; virtual void rva004739B4() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void rva0046C3FE(Player *player) = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual bool rva0046AAB8() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual Rva0046247DPair &rva0046F7FF(Rva0046247DPair &p) = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual Object *rva0046D2C3(int kind) = 0;
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
	virtual void gap130() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
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
// Primary vtable 0x00C45050: 37 gap slots, the dtor and slot 38, the matched
// HordeContainRva004725D5.cpp override (indices only matter for the calls).
class UpdateModule : public Rva00468D11Slots<32>
{
public:
	virtual void slot32(Object *obj) = 0;
	virtual void slot33(int a1) = 0;
	virtual void rva0046AF85() = 0;
	virtual void gap35() = 0;
	virtual void gap36() = 0;
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
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
	virtual Object *rva0046D2C3(int kind);
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
Object *HordeContain::rva0046D2C3(int kind)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	Rva0046D2C3ListNode *head = *(Rva0046D2C3ListNode **)p.m04;
	Rva0046D2C3ListNode *node = head->m_next;
	while (node != head)
	{
		if (!node->m_value->m_template->rva000456AC(kind))
			return node->m_value;
		node = node->m_next;
	}
	node = head->m_next;
	if (node != head)
		return node->m_value;
	for (_STL::set<int>::iterator it = m_170.begin(); it != m_170.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
		if (obj && !obj->m_template->rva000456AC(kind))
			return obj;
	}
	_STL::set<int>::iterator it = m_170.begin();
	if (it != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)*it);
	return 0;
}
