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
};
class AIUpdateInterface : public AIUpdateInterfaceSlots
{
public:
	unsigned char m_pad004[0x20 - 0x04];
	AICommandInterface m_command; // +0x20
	void aiIdle(CommandSourceType cmdSource) { m_command.aiIdle(cmdSource); }
	unsigned char m_pad024[0x1F0 - 0x24];
	Rva00468C37Holder *m_1F0; // +0x1F0
};
class Object
{
public:
	int getID() const { return m_74; }
	unsigned char m_pad000[0x74];
	int m_74; // +0x74
	unsigned char m_pad078[0xB8 - 0x78];
	float m_B8; // +0xB8
	unsigned char m_padBC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_274; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_438; // +0x438
	bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
	Object *rva002931F5(bool flag);
	bool testStatus(ObjectStatusTypes bit) const;
	void rva00293955(ModelConditionFlagType flag);
	void rva00293A05(ModelConditionFlagType flag);
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
	virtual void gap7() = 0;
	virtual void rva0046F7C9(Object *obj) = 0;
	virtual AsciiString rva0046D1AC() = 0;
};
class Rva0046BB38Iface11C : public Rva0046BB38Iface6
{
public:
	virtual int rva0046979B() = 0; virtual void rva00470D09(Object *obj) = 0; virtual void gap12() = 0; virtual void gap13() = 0;
	virtual void gap14() = 0; virtual void gap15() = 0; virtual void gap16() = 0; virtual void gap17() = 0;
	virtual void gap18() = 0; virtual void gap19() = 0; virtual void gap20() = 0; virtual void gap21() = 0;
	virtual void *rva004696CD() = 0; virtual void gap23() = 0; virtual void rva004696E5() = 0; virtual void gap25() = 0;
	virtual void rva00472D43(void *thingTemplate) = 0; virtual void gap27() = 0; virtual void gap28() = 0; virtual void gap29() = 0;
	virtual void gap30() = 0; virtual void gap31() = 0; virtual void gap32() = 0; virtual void rva00472C8E(Object *obj, CommandSourceType cmdSource) = 0;
	virtual bool rva00468D11() = 0; virtual bool rva00468D2C() = 0; virtual void gap36() = 0; virtual void gap37() = 0;
	virtual void gap38() = 0; virtual void gap39() = 0; virtual void gap40() = 0; virtual bool rva0046C6E7() = 0;
	virtual void gap42() = 0; virtual void gap43() = 0; virtual void rva0046B95E(void *value) = 0; virtual void rva00468CA3(const Rva00468CA3Arg *arg) = 0;
	virtual void gap46() = 0; virtual void gap47() = 0; virtual void gap48() = 0; virtual void gap49() = 0;
	virtual void gap50() = 0; virtual void gap51() = 0; virtual void gap52() = 0; virtual void gap53() = 0;
	virtual void gap54() = 0; virtual void gap55() = 0; virtual void gap56() = 0; virtual void gap57() = 0;
	virtual void gap58() = 0; virtual bool rva0046F8A5() = 0; virtual bool rva0046F8F4() = 0; virtual void gap61() = 0;
	virtual void gap62() = 0; virtual void gap63() = 0; virtual void gap64() = 0; virtual void gap65() = 0;
	virtual void gap66() = 0; virtual void gap67() = 0; virtual void gap68() = 0; virtual void gap69() = 0;
	virtual Object *rva0046D372() = 0; virtual void gap71() = 0; virtual void gap72() = 0; virtual void gap73() = 0;
	virtual void rva0046F8B2() = 0; virtual void gap75() = 0; virtual void gap76() = 0; virtual void gap77() = 0;
	virtual void rva00468FDC() = 0; virtual void gap79() = 0; virtual void gap80() = 0; virtual bool rva0046A46F() = 0;
	virtual void gap82() = 0; virtual bool rva0046A416() = 0; virtual bool rva0047306E(Object *obj, int a2) = 0; virtual bool rva00468DCD(Object *obj) = 0;
	virtual void gap86() = 0; virtual bool rva0046A4C8() = 0; virtual void gap88() = 0; virtual void rva00468D7D(Object *obj) = 0;
	virtual void gap90() = 0; virtual void gap91() = 0; virtual void gap92() = 0; virtual void gap93() = 0;
	virtual void gap94() = 0; virtual int rva004697CD() = 0; virtual int rva0046D3FC(int which) = 0; virtual int rva00468F68() = 0;
	virtual int rva00468F7E() = 0; virtual void gap99() = 0; virtual void gap100() = 0; virtual void gap101() = 0;
	virtual void gap102() = 0; virtual void gap103() = 0; virtual void gap104() = 0; virtual void gap105() = 0;
	virtual void gap106() = 0; virtual void gap107() = 0; virtual void gap108() = 0; virtual void gap109() = 0;
	virtual void gap110() = 0; virtual void gap111() = 0; virtual void gap112() = 0; virtual void gap113() = 0;
	virtual void gap114() = 0; virtual void gap115() = 0; virtual void gap116() = 0; virtual void gap117() = 0;
	virtual void rva0046DB6D(const AsciiString &name, int a2, int a3) = 0; virtual void rva0046DC92(const AsciiString &name, int a2) = 0; virtual void gap120() = 0; virtual void rva0046981C() = 0;
	virtual void rva00469851() = 0; virtual void gap123() = 0; virtual void gap124() = 0; virtual void gap125() = 0;
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
class TransportContain : public UpdateModule
{
public:
	virtual void rva004725D5(Object *obj) = 0;
private:
	unsigned char m_pad00C[0x11C - 0x0C];
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
	unsigned char m_pad188[0x264 - 0x188];
	void *m_264; // +0x264
	unsigned char m_pad268[0x26C - 0x268];
	ObjectID m_26C; // +0x26C
	unsigned char m_pad270[0x288 - 0x270];
	int m_288; // +0x288 (an Object ID)
	unsigned int m_28C; // +0x28C (a logic frame)
	unsigned char m_pad290[0x294 - 0x290];
	bool m_294; // +0x294
	unsigned char m_pad295[0x2A0 - 0x295];
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
