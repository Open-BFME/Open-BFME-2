// cl: /Oy- /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Citadel contain-interface slot38 at C48B38 (+20), 48071D..4807C7.
// Reuses the proven Slaughter complete-object/secondary-interface layout.
// WB11B6C00 provides independent fallback/path-check structural evidence.
// BFME1 f989 slaughter hierarchy is a semantic lead, not target layout proof.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Player;
class Object {
public:
 Player *getControllingPlayer() const;
 const Coord3D *getPosition() const { return reinterpret_cast<const Coord3D*>(reinterpret_cast<const char*>(this)+0x38); }
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00 {
 virtual void primary0();
 virtual void primary1();
 virtual void primary2();
 virtual void primary3();
 virtual void primary4();
 virtual void primary5();
 virtual void primary6();
 virtual void primary7();
 virtual void primary8();
 virtual void primary9();
 virtual void primary10();
 virtual void primary11();
 virtual void primary12();
 virtual void primary13();
 virtual void primary14();
 virtual void primary15();
 virtual void primary16();
 virtual void primary17();
 virtual void primary18();
 virtual void primary19();
 virtual void primary20();
 virtual void primary21();
 virtual void primary22();
 virtual void primary23();
 virtual void primary24();
 virtual void primary25();
 virtual void primary26();
 virtual void primary27();
 virtual void primary28();
 virtual void primary29();
 virtual void primary30();
 virtual void primary31();
 virtual void primary32();
 virtual bool rva004807C7(Object*);
 const void *m_moduleData; Object *m_object;
};
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	virtual void g24(); virtual void g25(); virtual void g26();
	virtual void rva0050B238(Object *obj, bool flag);
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void rva00465011(Object *obj);
	virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
 virtual void g39();
 virtual void g40();
 virtual void g41();
 virtual void g42();
 virtual void g43();
 virtual void g44();
 virtual void g45();
 virtual void g46();
 virtual void g47();
 virtual void g48();
 virtual void g49();
 virtual void g50();
 virtual void g51();
 virtual void g52();
 virtual void g53();
 virtual void g54();
 virtual void g55();
 virtual void g56();
 virtual void g57();
 virtual void g58();
 virtual void g59();
 virtual void g60();
 virtual void g61();
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
 virtual const Coord3D *rva00479F62();
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
};

class HordeGarrisonContain : public GarrisonContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};


class Pathfinder {
public:
 bool QuickDoesPathExist(Object*,const Coord3D*,const Coord3D*,int);
 bool QuickDoesPathExistToStructure(Object*,const Coord3D*,Object*,int);
};
class AI {public:char unknown00[0x10];Pathfinder *pathfinder;};
extern AI *TheAI;
class CitadelSlaughterHordeContain : public SlaughterHordeContain {
public:virtual bool isValidContainerFor(Object*,bool,bool);
};
// ?isValidContainerFor@CitadelSlaughterHordeContain@@UAE_NPAVObject@@_N1@Z
// Native 48071D..4807C7 RET12; C48B38 contain-interface slot38 (+20).
// BFME1 f989 Slaughter hierarchy and WB11B6C00 guide fallback semantics.
// Target primary slot33 rejects candidates; contain slot87 supplies an exit.
// Native479F62 RET0 proves slot87 takes no arguments; the preceding PUSH0
// belongs to QuickDoesPathExist and must occur before the nested virtual call.
// TheAI is the established target global (data ledger 9FF0F8), not a new pin.
bool CitadelSlaughterHordeContain::isValidContainerFor(Object *object,bool checkCapacity,bool testPath)
{
 if (!object) return false;
 if (!SlaughterHordeContain::isValidContainerFor(object,checkCapacity,testPath)) {
  Player *ownerPlayer=m_object->getControllingPlayer();
  if (object->getControllingPlayer()!=ownerPlayer) return false;
  if (rva004807C7(object)) return false;
  if (testPath) {
   Object *owner=m_object;
   if (owner) {
    Pathfinder *pathfinder=TheAI->pathfinder;
    const Coord3D *from=object->getPosition();
    if (!pathfinder->QuickDoesPathExist(object,from,rva00479F62(),0)
        && !TheAI->pathfinder->QuickDoesPathExistToStructure(object,from,owner,0)) return false;
   }
  }
 }
 return true;
}
