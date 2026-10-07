// ?rva0046FE99@HordeContain@@UAEXAAV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct Coord3D
{
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
class BFMEPathfinderMapShim
{
public:
	void rva002E718A(Object *object);
	void rva002E719B(Object *object);
};
class AI
{
public:
	unsigned char m_pad00[0x10];
	BFMEPathfinderMapShim *m_pathfinder; // +0x10
};
extern AI *TheAI;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class Team;
class Drawable
{
public:
	void rva00272BE7();
	void rva00272BAB(int a1, int a2);
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
class Rva003638BA
{
public:
	bool rva003638BA();
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
	__forceinline unsigned int isKindOf(int kind) const
	{
		return m_kindOf[kind >> 5] & (1U << (kind & 0x1f));
	}
	unsigned char m_pad000[0x114];
	unsigned int m_kindOf[4]; // +0x114
	unsigned char m_pad124[0x2E4 - 0x124];
	ModuleInfo m_moduleInfo; // +0x2E4
	unsigned char m_pad2F0[0x5D8 - 0x2F0];
	short m_5D8; // +0x5D8
};
struct Rva00469689Body
{
	unsigned char m_pad00[0x10];
	float m_10; // +0x10
};
// The Object +0x254 module: slot 5 gives a float.
class Rva0046B850Module : public Rva00468D11Slots<5>
{
public:
	virtual float slot5() = 0;
};
// The Object +0x250 module: slot 58 answers for another Object.
class Rva0046A2ECContain : public Rva00468D11Slots<58>
{
public:
	virtual bool slot58(Object *other) = 0;
};
class Object
{
public:
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
	unsigned char m_pad044[0x74 - 0x44];
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
	const Rva00469689Body *m_264; // +0x264
	unsigned char m_pad268[0x274 - 0x268];
	Object *m_274; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_438; // +0x438
	unsigned char m_pad439[0x44C - 0x439];
	int m_44C; // +0x44C
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Object *rva002931F5(bool flag);
	bool rva0028D9E5(int a1) const;
	void rva00298AE4(Team *team);
	bool testStatus(ObjectStatusTypes bit) const;
	void rva00293955(ModelConditionFlagType flag);
	void rva00293A05(ModelConditionFlagType flag);
	void rva001E42F2(const int *value);
	void rva0028B95F();
	unsigned char rva00290FBB() const;
	void rva0028AE6D();
	bool rva0028C264(int *out, int a2);
	Player *getControllingPlayer() const;
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
extern Rva002D06CA *TheThingFactory;
struct Rva0046247DPair
{
	void *m00;
	const _STL::list<Object *> *m04;
};
struct Rva00462D35Mapped
{
	unsigned int m_bits;
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
class Rva0046247D
{
public:
	void rva0046247D(Rva0046247DPair &p);
};
// The +0x2C8 helper: slot 4 resets it, slot 14 answers for an Object.
class Rva00468FDCHelper : public Rva00468D11Slots<4>
{
public:
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
	unsigned char m_pad198[0x1A4 - 0x198];
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
	unsigned char m_pad231[0x254 - 0x231];
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
	virtual void gap1() = 0; virtual void gap2() = 0; virtual void rva0046E253() = 0; virtual void gap4() = 0; virtual void gap5() = 0;
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void rva00470D09(Object *obj) = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void slot16() = 0; virtual void rva0046FE99(_STL::list<Object *> &out) = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual void gap20() = 0; virtual Object *rva0046CBCA() = 0;
	virtual void *rva004696CD() = 0; virtual bool rva0046CDC9() = 0; virtual void rva004696E5() = 0; virtual bool rva0046CCEF(const ThingTemplate *tmpl) = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void gap30() = 0; virtual void gap31() = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual bool rva0046A2A7() = 0;
	virtual void gap38() = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void slot42(const Object *obj) = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void gap53() = 0;
	virtual void gap54() = 0; virtual void rva0046C4C0() = 0; virtual void rva0046C327() = 0; virtual void rva0046C20B() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual void gap62() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual void gap66() = 0; virtual void rva0046D1F7(_STL::list<const Object *> &out) = 0; virtual Object *rva0046D27A() = 0; virtual void gap69() = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void gap77() = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool canEngageInMelee(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(Rva2225E0Filter *filter) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual void gap99() = 0; virtual void gap100() = 0; virtual int slot101(Object *obj) = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void gap109() = 0;
	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
	virtual void rva0046DB6D(const AsciiString &name, int a2, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, int a2) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual bool rva0046992C() = 0;
	virtual void gap126() = 0; virtual bool rva004698BC() = 0; virtual const void *rva004698D6() = 0; virtual const void *rva004698E2() = 0;
	virtual void gap130() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
	virtual void gap134() = 0; virtual void gap135() = 0; virtual bool rva0046F8CD() = 0; virtual void gap137() = 0;
	virtual void gap138() = 0; virtual void gap139() = 0; virtual void gap140() = 0; virtual void rva004690D0(int value) = 0;
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
	virtual void rva0046A0B2() = 0;
};
// Primary vtable 0x00C45050: 37 gap slots, the dtor and slot 38, the matched
// HordeContainRva004725D5.cpp override (indices only matter for the calls).
class UpdateModule : public Rva00468D11Slots<32>
{
public:
	virtual void slot32(Object *obj) = 0;
	virtual void gap33() = 0;
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
	virtual void cgap39() = 0; virtual void cgap40() = 0; virtual void cgap41() = 0; virtual void cgap42() = 0; virtual void cgap43() = 0; virtual void cgap44() = 0; virtual void cgap45() = 0; virtual void cgap46() = 0; virtual void cgap47() = 0; virtual void cgap48() = 0; virtual void cgap49() = 0; virtual void cgap50() = 0; virtual void cgap51() = 0; virtual void cgap52() = 0; virtual void cgap53() = 0; virtual void cgap54() = 0; virtual void cgap55() = 0; virtual void cgap56() = 0; virtual void cgap57() = 0; virtual void cgap58() = 0; virtual void cgap59() = 0; virtual void cgap60() = 0; virtual void cgap61() = 0; virtual void cgap62() = 0; virtual void cgap63() = 0; virtual void cgap64() = 0; virtual void cgap65() = 0; virtual void cgap66() = 0; virtual void cgap67() = 0;
	virtual void iterateContained(ContainIterateFunc func, void *userData, int a3) = 0;
	virtual int slot69(int a1) = 0;
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
};
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
public:
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual void rva004725D5(Object *obj) = 0;
private:
	unsigned char m_pad024[0x11C - 0x24];
};
class HordeContain : public TransportContain, public Rva0046BB38Iface11C
{
public:
	virtual bool rva0046BB38(Object *other);
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
	virtual void rva0046D8AE();
	virtual Object *rva0046CB2C();
	virtual bool rva0046D80B();
	virtual bool rva0046BB6F(int *out, unsigned int frame);
	virtual int rva0046D3FC(Rva2225E0Filter *filter);
	virtual bool rva0046A2A7();
	virtual void rva0046E2BC();
	virtual void rva0046A0B2();
	virtual bool rva0046992C();
	virtual Object *rva0046CBCA();
	virtual void rva0046C327();
	virtual void rva0046C20B();
	virtual void rva0046FE99(_STL::list<Object *> &out);
	virtual float rva0046B850();
	virtual void rva0046D1F7(_STL::list<const Object *> &out);
	virtual void rva0046E253();
	virtual bool rva0046CDC9();
	virtual bool rva0046CCEF(const ThingTemplate *tmpl);
	virtual bool slot38(Object *obj, int a2, int a3);
	virtual bool rva0046B9DC(int a1);
	virtual bool rva0046B95E(int a1);
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
	_STL::map<int, int> m_170; // +0x170
	_STL::map<int, int> m_17C; // +0x17C
	Rva00472329Record *m_188Begin; // +0x188 (vector of 0x1C-byte records)
	Rva00472329Record *m_188End;
	Rva00472329Record *m_188Cap;
	unsigned char m_pad194[0x19C - 0x194];
	int m_19C; // +0x19C
	unsigned char m_pad1A0[0x1AC - 0x1A0];
	ObjectID m_1AC; // +0x1AC
	ObjectID m_1B0; // +0x1B0
	int m_1B4; // +0x1B4
	unsigned char m_pad1B8[0x200 - 0x1B8];
	int m_200; // +0x200
	unsigned char m_pad204[0x24C - 0x204];
	_STL::map<int, void *> m_24C; // +0x24C
	unsigned char m_pad258[0x264 - 0x258];
	void *m_264; // +0x264
	unsigned char m_pad268[0x26C - 0x268];
	ObjectID m_26C; // +0x26C
	unsigned char m_pad270[0x288 - 0x270];
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
	rva004725D5(obj);
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

// ?rva0046D372@HordeContain@@UAEPAVObject@@XZ @0x0046D372: slot 70, the Object
// whose ID is at +0x26C.
Object *HordeContain::rva0046D372()
{
	return TheGameLogic->findObjectByID(m_26C);
}

// ?rva004690A9@HordeContain@@UAEXPBUCoord3D@@@Z @0x004690A9: slot 132, stores the
// position at +0x2B8 and raises +0x2C4 and +0x120.
void HordeContain::rva004690A9(const Coord3D *pos)
{
	m_2B8 = *pos;
	m_2C4 = true;
	m_120 = true;
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

// ?rva00468BDC@HordeContain@@UAEXH@Z @0x00468BDC: slot 143, for an owner with an
// AI: setting sets model condition 0x1BA unless +0x2F0 was already set,
// clearing clears 0x1BA and 0x1BB (rowed Object rva00293A05/rva00293955);
// then stores the argument at +0x2F0.
void HordeContain::rva00468BDC(int on)
{
	Object *obj = m_object;
	if (!obj || !obj->m_ai)
		return;
	if (on)
	{
		if (!m_2F0)
			obj->rva00293A05((ModelConditionFlagType)0x1BA);
	}
	else
	{
		obj->rva00293955((ModelConditionFlagType)0x1BA);
		obj->rva00293955((ModelConditionFlagType)0x1BB);
	}
	m_2F0 = on;
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
	_STL::map<int, int>::iterator it = m_170.begin();
	if (it != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)it->first);
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
		ObjectID id = (ObjectID)obj->getID();
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
// Object::rva00298AE4(team) on every contained Object (contain interface slot
// 70) and on the live Object of every +0x170 key.
void HordeContain::rva0046D384(Team *team)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	for (_STL::list<Object *>::const_iterator it = p.m04->begin(); it != p.m04->end(); ++it)
	{
		Object *obj = *it;
		if (obj)
			obj->rva00298AE4(team);
	}
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj)
			obj->rva00298AE4(team);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
		FXList::doFXObj(fx, TheGameLogic->findObjectByID((ObjectID)k->first), 0);
}

// ?rva0046A712@HordeContain@@UAEXH@Z @0x0046A712: slot 110 (argument unread);
// runs slot 16, then moves every contained Object to the position and angle
// slot 7 gives for it (the pinned 0x0029660C, then Thing::setOrientation).
void HordeContain::rva0046A712(int)
{
	slot16();
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
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
		_STL::map<int, int>::iterator k = m_170.begin();
		for (int n = GetGameLogicRandomValue(0, m_170.size() - 1, HORDECONTAIN_SOURCE_FILE, 5377); n != 0; --n)
			++k;
		return TheGameLogic->findObjectByID((ObjectID)k->first);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj && filter->accepts(obj, self->getControllingPlayer()))
			++count;
	}
	return count;
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		const Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj)
			out.push_back(obj);
	}
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
	const ThingTemplate *tmpl = (const ThingTemplate *)TheThingFactory->rva002D06CA(&fields()->m_1B0);
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
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
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
