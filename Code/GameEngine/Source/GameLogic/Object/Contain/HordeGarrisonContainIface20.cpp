// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// HordeGarrisonContain's overrides in the +0x20 interface vftable 0x00C463E8
// (installed at +0x20 by the rowed ctor 0x0047A040; SlaughterHordeContain and
// CitadelSlaughterHordeContain inherit them). Each forwards to a member of
// the empty second base at +0x9E0 (pinned by address, the
// HordeGarrisonContainCtor base name). Slot names: as in
// HordeSiegeEngineContainRiders, each override is named after the OpenContain
// implementation it replaces (OpenContain's +0x20 vftable 0x00C433B0), which
// cl 7.1 needs to compile it with the +0x20 subobject this; the names
// themselves are not established.
//
// ?rva0050B238@HordeGarrisonContain@@UAEXPAVObject@@_N@Z, retail 0x00479C2A, 11 bytes.
// Slot 27: tail-forwards both arguments to the base member 0x00588BA8.
//
// ?rva00465011@HordeGarrisonContain@@UAEXPAVObject@@@Z, retail 0x00479BF3, 25 bytes.
// Slot 32: the base member 0x00588F61 with the contain, the owner and the
// argument.
//
// ?rva004632E0@HordeGarrisonContain@@UAEXPAVObject@@@Z, retail 0x00479BDD, 22 bytes.
// Slot 61: the base member 0x00588C4E with the contain and the argument.

// Native479E62 and WB11A7F20 prove the +20 interface ABI and slot38.
// Native478629 is the primary-view admission helper; its purpose follows
// the ZH GarrisonContain health/damage checks while native adds status19.
// Native offsets: Object position38 AI250 Body254; template111 bit80.
// Names and exact helper identity remain neutral where WB is unnamed.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
enum ObjectStatusTypes { Status19=19, Status38=38 };
class AdmissionBodyView { public:
 virtual void b0(); virtual void b1();virtual void b2();virtual void b3();
 virtual float health();virtual void b5();virtual void b6();virtual void b7();virtual int damageState();
};
class AdmissionAIView {public:
 virtual void a0();
 virtual void a1();
 virtual void a2();
 virtual void a3();
 virtual void a4();
 virtual void a5();
 virtual void a6();
 virtual void a7();
 virtual void a8();
 virtual void a9();
 virtual void a10();
 virtual void a11();
 virtual void a12();
 virtual void a13();
 virtual void a14();
 virtual void a15();
 virtual void a16();
 virtual void a17();
 virtual void a18();
 virtual void a19();
 virtual void a20();
 virtual void a21();
 virtual void a22();
 virtual void a23();
 virtual void a24();
 virtual void a25();
 virtual void a26();
 virtual void a27();
 virtual void a28();
 virtual void a29();
 virtual void a30();
 virtual void *query7C();
};
class Object {public:
 bool testStatus(ObjectStatusTypes) const;
 char opaque00[0x38]; Coord3D position;
 char opaque44[0x250-0x44]; AdmissionAIView *ai;AdmissionBodyView *body;
};
class Pathfinder {public:
 bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int);
 bool QuickDoesPathExistToStructure(Object*,const Coord3D*,Object*,int);
};
class AI {public: char opaque00[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
class OpenContain {public: virtual bool isValidContainerFor(Object*,bool,bool);};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00 { virtual void f00();
 virtual void p1();
 virtual void p2();
 virtual void p3();
 virtual void p4();
 virtual void p5();
 virtual void p6();
 virtual void p7();
 virtual void p8();
 virtual void p9();
 virtual void p10();
 virtual void p11();
 virtual void p12();
 virtual void p13();
 virtual void p14();
 virtual void p15();
 virtual void p16();
 virtual void p17();
 virtual void p18();
 virtual void p19();
 virtual void p20();
 virtual void p21();
 virtual void p22();
 virtual void p23();
 virtual void p24();
 virtual void p25();
 virtual void p26();
 virtual void p27();
 virtual bool rvaPrimary70(Object*);
 const void *m_moduleData;Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	virtual void g24(); virtual void g25(); virtual void g26();
	virtual void rva0050B238(Object *obj, bool flag) = 0;
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void rva00465011(Object *obj) = 0;
	virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36();virtual void g37();virtual bool isValidContainerFor(Object*,bool,bool);
 virtual void g39(); virtual void g40();virtual void g41();virtual void g42();virtual void g43();
	SLOT08(g44,g45,g46,g47,g48,g49,g50,g51)
	SLOT08(g52,g53,g54,g55,g56,g57,g58,g59)
	virtual void g60();
	virtual void rva004632E0(Object *obj) = 0;
 virtual void g62();
 virtual void g63();
 virtual void g64();
 virtual void g65();
 virtual void g66();
 virtual void g67();
 virtual void g68();
 virtual void g69();
 virtual void g70();
 virtual void g71();
 virtual void g72();
 virtual void g73();
 virtual void g74();
 virtual void g75();
 virtual void g76();
 virtual void g77();
 virtual void g78();
 virtual void g79();
 virtual void g80();
 virtual void g81();
 virtual void g82();
 virtual void g83();
 virtual void g84();
 virtual void g85();
 virtual void g86();
 virtual const Coord3D *rvaExitPosition();
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x9E0 - 0x38]; };

class GarrisonContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public: bool rva00478629(Object*,bool,bool);
};

class Rva0047A040Base9E0
{
public:
	void rva00588BA8(Object *obj, bool flag);
	void rva00588C4E(void *contain, Object *obj);
	void rva00588F61(void *contain, Object *owner, Object *obj);
 void *rva00588BF3(void*,Object*);
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	virtual void rva0050B238(Object *obj, bool flag);
	virtual void rva00465011(Object *obj);
	virtual void rva004632E0(Object *obj);
 virtual bool isValidContainerFor(Object*,bool,bool);
private:
	int m_9E0;
};

// ?rva004632E0@HordeGarrisonContain@@UAEXPAVObject@@@Z @0x00479BDD
void HordeGarrisonContain::rva004632E0(Object *obj)
{
	rva00588C4E(this, obj);
}

// ?rva00465011@HordeGarrisonContain@@UAEXPAVObject@@@Z @0x00479BF3
void HordeGarrisonContain::rva00465011(Object *obj)
{
	rva00588F61(this, m_object, obj);
}

// ?rva0050B238@HordeGarrisonContain@@UAEXPAVObject@@_N@Z @0x00479C2A
void HordeGarrisonContain::rva0050B238(Object *obj, bool flag)
{
	rva00588BA8(obj, flag);
}

struct GarrisonTemplateView {char opaque00[0x111];unsigned char kindBit111;};
struct GarrisonObjectTemplateView {void *vtable;const GarrisonTemplateView *templ;};
__declspec(noinline) bool GarrisonContain::rva00478629(Object *obj,bool checkCapacity,bool testPath)
{
 if(!reinterpret_cast<OpenContain*>(reinterpret_cast<char*>(this)+0x20)->OpenContain::isValidContainerFor(obj,checkCapacity,testPath))return false;
 if(m_object->body->health()<=0.0f)return false;
 Object *owner=m_object;
 if(owner->testStatus(Status19))return false;
 if(owner->body->damageState()==2 &&
    !(reinterpret_cast<GarrisonObjectTemplateView*>(m_object)->templ->kindBit111 & 0x80))return false;
 return true;
}


