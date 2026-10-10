// cl: /O1 /G7 /DNDEBUG /MD
//
// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00395B66, 73 bytes.
// CastleMemberBehavior behavior ctor over the rowed BehaviorModule base
// (0x253330, thing plus data): forwards both args to the base, stores the
// first +0x10 slot value, zeroes +0x14/+0x18/+0x1C and the bytes at
// +0x24/+0x25, then re-stores the primary vtable slot and the +0x0C/+0x10
// secondary slots (address-of TU-local dummies, DIR32-masked) and stores 1
// at +0x20. The double +0x10 store uses the ToggleMounted union-plus-barrier
// shape so retail keeps both. The rowed instance factory 0x24AAEE
// (news 0x28) is the sole raw caller. Row supersedes the ctor pin.

class Xfer;
class Thing;
class ModuleData;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

static int s_slotFirst;
static int s_vtable;
static int s_secondary0C;
static int s_secondary10;

// Opaque BehaviorModule base; ctor resolves to its row. The explicit
// m_vtable member stands in for the inherited vptr so body order is source
// order.
class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer*);

protected:
	const void *m_vtable;
	Thing *m_owner;
	int m_pad08;
	const void *m_p0C;
	const void *m_p10;
};

class CastleMemberBehavior : public BehaviorModule
{
public:
	CastleMemberBehavior(Thing *thing, const ModuleData *moduleData);
	void rva003957C6(Xfer*);

private:
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	unsigned char m_24;
	unsigned char m_25;
	unsigned char m_pad26[0x28 - 0x26];
};

// ??0CastleMemberBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x395B66
CastleMemberBehavior::CastleMemberBehavior(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData)
{
	*(const void **)((char *)this + 0x10) = &s_slotFirst;
	_ReadWriteBarrier();
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_24 = 0;
	m_25 = 0;
	m_vtable = &s_vtable;
	m_p0C = &s_secondary0C;
	m_p10 = &s_secondary10;
	m_20 = 1;
}

// Native3957C6..39585A is the complete148B snapshot transfer. The named
// factory/constructor/pool-key and literal getter independently establish
// CastleMemberBehavior; field14/18 IDs,1C unsigned,24/25 flags and20 audio
// handle are native access facts. Pre/base/post order is target-specific.
// Existing XferObjectID3060B2 and BehaviorModule4C9C7D supply owned calls.
// The following vtable slot views describe only the invoked ABI; original
// transfer method name and the unaccessed virtual slots remain unknown.
class Xfer { public: struct Version {unsigned char loaded,current; Version():loaded(1),current(1){} };
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual void pad7();
virtual void pad8();
virtual void pad9();
virtual void version(Version*);
virtual void pad11();
virtual void pad12();
virtual void pad13();
virtual void pad14();
virtual void pad15();
virtual void pad16();
virtual void pad17();
virtual void pad18();
virtual void pad19();
virtual void pad20();
virtual void pad21();
virtual void pad22();
virtual void pad23();
virtual void pad24();
virtual void pad25();
virtual void pad26();
virtual void pad27();
virtual void pad28();
virtual void pad29();
virtual void xferUnsignedInt(unsigned*);
virtual void pad31();
virtual void pad32();
virtual void pad33();
virtual void pad34();
virtual void pad35();
virtual void xferBool(bool*);
};
class AudioManager {public:
virtual void audioPad0();
virtual void audioPad1();
virtual void audioPad2();
virtual void audioPad3();
virtual void audioPad4();
virtual void audioPad5();
virtual void audioPad6();
virtual void audioPad7();
virtual void audioPad8();
virtual void audioPad9();
virtual void audioPad10();
virtual void audioPad11();
virtual void audioPad12();
virtual void audioPad13();
virtual void audioPad14();
virtual void audioPad15();
virtual void audioPad16();
virtual void audioPad17();
virtual void audioPad18();
virtual void audioPad19();
virtual void audioPad20();
virtual void audioPad21();
virtual void audioPad22();
virtual void audioPad23();
virtual void audioPad24();
virtual void audioPad25();
virtual void audioPad26();
virtual void audioPad27();
virtual void audioPad28();
virtual void audioPad29();
virtual void audioPad30();
virtual void audioPad31();
virtual void audioPad32();
virtual void audioPad33();
virtual void audioPad34();
virtual void audioPad35();
virtual void audioPad36();
virtual void audioPad37();
virtual void audioPad38();
virtual void audioPad39();
virtual void audioPad40();
virtual void audioPad41();
virtual void audioPad42();
virtual void audioPad43();
virtual void audioPad44();
virtual void audioPad45();
virtual void audioPad46();
virtual void audioPad47();
virtual void audioPad48();
virtual void audioPad49();
virtual void audioPad50();
virtual void audioPad51();
virtual void audioPad52();
virtual void audioPad53();
virtual void audioPad54();
virtual void audioPad55();
virtual void audioPad56();
virtual void audioPad57();
virtual void audioPad58();
virtual void audioPad59();
virtual void audioPad60();
virtual void audioPad61();
virtual void audioPad62();
virtual void audioPad63();
virtual void audioPad64();
virtual void audioPad65();
virtual void audioPad66();
virtual void audioPad67();
virtual void audioPad68();
virtual void audioPad69();
virtual void audioPad70();
virtual void audioPad71();
virtual void audioPad72();
virtual void audioPad73();
virtual void audioPad74();
virtual void audioPad75();
virtual void audioPad76();
virtual void audioPad77();
virtual void audioPad78();
virtual void audioPad79();
virtual void audioPad80();
virtual void audioPad81();
virtual void audioPad82();
virtual void audioPad83();
virtual void audioPad84();
virtual void audioPad85();
virtual void audioPad86();
virtual void audioPad87();
virtual void xferAudioHandle(Xfer*,unsigned*);
};
extern AudioManager* TheAudio;
enum ObjectID { INVALID_ID=0 };
void XferObjectID(Xfer*, ObjectID*);
void CastleMemberBehavior::rva003957C6(Xfer* xfer) {
 Xfer::Version v; xfer->version(&v);
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_14));
 xfer->xferBool(reinterpret_cast<bool*>(&m_24));
 xfer->xferUnsignedInt(reinterpret_cast<unsigned*>(&m_1C));
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_18));
 BehaviorModule::xfer(xfer);
 XferObjectID(xfer,reinterpret_cast<ObjectID*>(&m_18));
 xfer->xferUnsignedInt(reinterpret_cast<unsigned*>(&m_1C));
 xfer->xferBool(reinterpret_cast<bool*>(&m_25));
 TheAudio->xferAudioHandle(xfer,reinterpret_cast<unsigned*>(&m_20));
}
