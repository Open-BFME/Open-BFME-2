// ?rva0046D2C3@HordeContain@@UAEPAVObject@@H@Z
// partial score=0.95 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
};
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
// Retail's random calls carry this source path literal.
#define HORDECONTAIN_SOURCE_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp"
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
class Thing
{
public:
	void setOrientation(float angle);
};
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
class ThingTemplate
{
public:
	int rva000456AC(int kind) const;
	unsigned char m_pad000[0x114];
	unsigned int m_kindOf[4]; // +0x114
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
	unsigned char m_padBC[0x110 - 0xBC];
	unsigned int m_110; // +0x110
	unsigned char m_pad114[0x250 - 0x114];
	Rva0046A2ECContain *m_250; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
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
	bool rva0028C264(int *out, int a2);
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
	unsigned char m_pad1B4[0x1D8 - 0x1B4];
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
	unsigned char m_pad255[0x26C - 0x255];
	float m_26C; // +0x26C
	float m_270; // +0x270
};
class ModuleData;
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
class Rva0046BB38Iface6 : public Rva0046BB38Slots<6>
{
public:
	virtual bool rva0046BB38(Object *other) = 0;
	virtual Coord3D slot7(Object *obj, float *angle) = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void rva00470D09(Object *obj) = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void slot16() = 0; virtual void gap17() = 0;
	virtual void gap18() = 0; virtual Object *rva0046CB2C() = 0; virtual void gap20() = 0; virtual void gap21() = 0;
	virtual void *rva004696CD() = 0; virtual void gap23() = 0; virtual void rva004696E5() = 0; virtual void gap25() = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void gap30() = 0; virtual void gap31() = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual bool rva0046BB6F(int *out, unsigned int frame) = 0; virtual void gap37() = 0;
	virtual void gap38() = 0; virtual bool rva0046C65C() = 0; virtual bool rva0046C71E() = 0; virtual bool rva0046C6E7() = 0;
	virtual void gap42() = 0; virtual bool rva0046B9DC(int a1) = 0; virtual bool rva0046B95E(int a1) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0;
	virtual void gap50() = 0; virtual void rva0046BD70() = 0; virtual void rva0046BE0E() = 0; virtual void gap53() = 0;
	virtual void gap54() = 0; virtual void gap55() = 0; virtual void gap56() = 0; virtual void gap57() = 0;
	virtual bool rva0046C5D7(int value) = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual void gap62() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual void gap66() = 0; virtual void gap67() = 0; virtual Object *rva0046D27A() = 0; virtual Object *rva0046D2C3(int kind) = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void gap77() = 0;
	virtual void rva00468FDC() = 0; virtual void rva00473ADF() = 0; virtual bool rva0046A381(Object *target) = 0; virtual bool rva0046A46F() = 0;
	virtual bool rva0046A2EC(Object *target) = 0; virtual bool rva0046A416() = 0; virtual bool rva0047306E(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void rva004730B0(Object *target) = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void rva0046D384(Team *team) = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(int which) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual void gap99() = 0; virtual void gap100() = 0; virtual void gap101() = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void rva0046D8AE() = 0; virtual void rva0046D7AF(int a1) = 0; virtual void gap109() = 0;
	virtual void rva0046A712(int unused) = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual bool rva0046D80B() = 0;
	virtual bool rva0046A6C1() = 0; virtual bool rva0046A677() = 0; virtual void gap116() = 0; virtual void rva0046DDC5(int a1, int a2) = 0;
	virtual void rva0046DB6D(const AsciiString &name, int a2, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, int a2) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void rva0046DE2D(const FXList *fx) = 0; virtual void gap124() = 0; virtual void gap125() = 0;
	virtual void gap126() = 0; virtual bool rva004698BC() = 0; virtual const void *rva004698D6() = 0; virtual const void *rva004698E2() = 0;
	virtual void gap130() = 0; virtual void gap131() = 0; virtual void rva004690A9(const Coord3D *pos) = 0; virtual void gap133() = 0;
	virtual void gap134() = 0; virtual void gap135() = 0; virtual bool rva0046F8CD() = 0; virtual void gap137() = 0;
	virtual void gap138() = 0; virtual void gap139() = 0; virtual void gap140() = 0; virtual void gap141() = 0;
	virtual bool rva00468C37() = 0; virtual void rva00468BDC(int on) = 0;
	virtual float rva00468B5B(float value) = 0;
	virtual void rva00468C60(const Coord3D *pos) = 0;
	virtual bool rva00468C7B(Coord3D *pos) = 0;
	virtual void gap147() = 0;
	virtual void gap148() = 0;
	virtual void gap149() = 0;
	virtual float rva0046F8DA() = 0;
	virtual float rva0046F8E7() = 0;
};
// Primary vtable 0x00C45050: 37 gap slots, the dtor and slot 38, the matched
// HordeContainRva004725D5.cpp override (indices only matter for the calls).
class UpdateModule : public Rva00468D11Slots<34>
{
public:
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
class ContainModuleInterface : public Rva00468D11Slots<70>
{
public:
	virtual void rva0046D27ASlot70(Rva0046247DPair &p) = 0;
};
class TransportContain : public UpdateModule, public BehaviorModuleInterface, public UpdateModuleInterface, public ContainModuleInterface
{
public:
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
	virtual bool rva0047306E(Object *obj, int a2);
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
	virtual Object *rva0046D2C3(int kind);
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
	unsigned char m_pad188[0x1AC - 0x188];
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
	unsigned char m_pad2CC[0x2EC - 0x2CC];
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

// ?rva0046979B@HordeContain@@UAEHXZ @0x0046979B: slot 10, module data +0x98.
int HordeContain::rva0046979B()
{
	return fields()->m_98;
}

// ?rva004696CD@HordeContain@@UAEPAXXZ @0x004696CD: slot 22, TheThingFactory's
// lookup of the module data's +0x1B0 name.
void *HordeContain::rva004696CD()
{
	return TheThingFactory->rva002D06CA(&fields()->m_1B0);
}

// ?rva004696E5@HordeContain@@UAEXXZ @0x004696E5: slot 24, the same lookup handed
// to slot 26 when found.
void HordeContain::rva004696E5()
{
	void *thingTemplate = TheThingFactory->rva002D06CA(&fields()->m_1B0);
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
	for (_STL::map<int, int>::iterator it = m_170.begin(); it != m_170.end(); ++it)
	{
		if (TheGameLogic->findObjectByID((ObjectID)it->first))
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

// ?rva0047306E@HordeContain@@UAE_NPAVObject@@H@Z @0x0047306E: slot 84, for the
// argument's AI: idles it (CMD_FROM_AI) and answers true when its slot 113
// does, else answers its slot 110; false without an AI. The second argument
// is not read.
bool HordeContain::rva0047306E(Object *obj, int)
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
			rva00470D09(obj);
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
			TheAI->m_pathfinder->rva002E718A(obj);
	}
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->rva002E718A(obj);
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
			TheAI->m_pathfinder->rva002E719B(obj);
	}
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj && !obj->testStatus((ObjectStatusTypes)0x1C))
			TheAI->m_pathfinder->rva002E719B(obj);
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

// ?rva0046D2C3@HordeContain@@UAEPAVObject@@H@Z @0x0046D2C3: slot 69; the first
// contained Object (through the +0x20 contain interface's slot 70) whose
// template fails the rowed ThingTemplate rva000456AC(kind) test (retail tests
// the low byte of its result), else the first contained Object, else the
// first such live Object of a +0x170 key, else the Object of the first key.
Object *HordeContain::rva0046D2C3(int kind)
{
	Rva0046247DPair p;
	rva0046D27ASlot70(p);
	_STL::list<Object *>::const_iterator end = p.m04->end();
	_STL::list<Object *>::const_iterator it;
	for (it = p.m04->begin(); it != end; ++it)
	{
		if (!(unsigned char)(*it)->m_template->rva000456AC(kind))
			return *it;
	}
	it = end;
	++it;
	if (it != end)
		return *it;
	for (_STL::map<int, int>::iterator k = m_170.begin(); k != m_170.end(); ++k)
	{
		Object *obj = TheGameLogic->findObjectByID((ObjectID)k->first);
		if (obj && !(unsigned char)obj->m_template->rva000456AC(kind))
			return obj;
	}
	if (m_170.begin() != m_170.end())
		return TheGameLogic->findObjectByID((ObjectID)m_170.begin()->first);
	return 0;
}
