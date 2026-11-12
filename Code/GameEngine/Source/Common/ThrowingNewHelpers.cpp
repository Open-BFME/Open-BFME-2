// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
//
// Wave-3 F78 shape family: throwing-new plus final. Each body allocates its
// POD helper with operator new, constructs it in place with (member, arg)
// (the null-checked call some shapes mistake for a cond call), then passes
// the helper (or null when allocation failed) to a thiscall final on the
// member's +0x1C subobject. The throwing new plus the in-place ctor is what
// requires the EH prologue and its 0/-1 state transitions. Callees pinned
// under their addresses; identities unproven.
//

struct Rva005CF22CBig;

// The owner's +0x1C member is the rowed Rva00575674 (0x00575674 set, Object* argument).
class Object;
#include "../../Include/Common/Rva00575674.h"

struct Rva005CF22CBig
{
	char m_pad[0x10];
	void *m_view10;
	char m_pad14[8];
	Rva00575674 m_sub;
};

class Rva005CF22COwner
{
public:
	void rva005CF22C(int regionAddress);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005773DB {
public:
    Rva005773DB(const int *);
    ~Rva005773DB() { if (m_impl) ReleaseTreeHintRef00217D4C(m_impl); }
private:
    TargetRef00217D4C *m_impl;
};
class Rva005CEA74 {
public:
    struct Payload { int v[2]; };
};
template <class T> class RvaCloneResult {
    TargetRef00217D4C *pointer;
public:
    ~RvaCloneResult() { if (pointer) ReleaseTreeHintRef00217D4C(pointer); }
};
RvaCloneResult<Rva005CEA74> Rva005CEC5DCreate(const Rva005CEA74::Payload *);
class Image;
struct Rva005D2355In;
namespace StrategicInGameUI { const Image *GetSelectionPortrait(Rva005D2355In *); }
int GetMaxCommandPoints(void *);
class Rva00318FBE { public: int rva00318FBE(); };
#include "../../Include/Common/Rva00319B0AOwner.h"
class Rva0042D703PtrChaseField { public: int get() const; };
#include "../../Include/Common/Rva0042D69DPtrChaseField.h"
#include "../../Include/Common/Rva0042D6B4PtrChaseField.h"
struct Rva005CF37DPortrait {
    virtual void slot0();
    virtual void setImage(const Image *);
    virtual void slot2();
    virtual void setCounts(int current, int maximum);
    virtual void slot4();
    virtual void slot5();
    virtual void setArmy(const Rva005773DB &);
    virtual void slot7();
    virtual void refresh();
};
struct Rva005CF37DCommandUI {
    virtual void slot0();
    virtual void createButton(int slot, const RvaCloneResult<Rva005CEA74> &);
};
struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"
class Rva005CE8F5 {
public:
    Rva005CE8F5(Rva005CF22CBig *owner) : m_owner(owner) {}
    virtual ~Rva005CE8F5() {}
    // Retail table 0x00C751A8 slot 1: the shared empty `ret` (0x000B3FD0).
    virtual void slot1() {}
    Rva005CF22CBig *m_owner;
};
// Existing one-vptr observer-base view: its emitted vtable is retail C3702C.
class Rva00575E4EBase2 {
public:
    Rva00575E4EBase2();
    virtual ~Rva00575E4EBase2() {}
};
// ??0Rva00575E4EBase2@@QAE@XZ @0x003F4096 9B: the default constructor, storing the
// class's own vtable (VA 0x00C3702C) and returning this.
Rva00575E4EBase2::Rva00575E4EBase2()
{
}
class Rva005CEE07 : public Rva005CE8F5, public Rva00575E4EBase2
{
public:
    Rva005CEE07(Rva005CF22CBig *owner, int armyAddress);
    virtual ~Rva005CEE07();
private:
    int m_army;
};

// Native boundary 5CF37D..5CF4A8, RET8. Existing allocating caller5CF6B5
// proves this constructor and its16B allocation. Primary/secondary vptrs at
// +0/+8; owner+4 and army+0C; WB is an unnamed StrategicInGameUI lead.
Rva005CEE07::Rva005CEE07(Rva005CF22CBig *owner, int armyAddress)
    : Rva005CE8F5(owner), m_army(armyAddress)
{
    ((Rva00319B0AOwner *)m_army)->rva00319B0A();
    void *view = m_owner->m_view10;
    Rva005CF37DPortrait *portrait = (Rva005CF37DPortrait *)
        ((Rva0042D703PtrChaseField *)view)->get();
    if (portrait) {
        portrait->setImage(StrategicInGameUI::GetSelectionPortrait((Rva005D2355In *)m_army));
        { int army = m_army; Rva005773DB ref(&army); portrait->setArmy(ref); }
        portrait->setCounts(((Rva00318FBE *)m_army)->rva00318FBE(),
                            GetMaxCommandPoints((void *)m_army));
        portrait->refresh();
    }
    Rva005CF37DCommandUI *commands = (Rva005CF37DCommandUI *)
        ((Rva0042D69DPtrChaseField *)view)->get();
    if (commands) {
        int button = ((Rva0042D6B4PtrChaseField *)view)->get();
        if (button) {
            int army = m_army;
            Rva005CEA74::Payload payload = { button, army };
            commands->createButton(1, Rva005CEC5DCreate(&payload));
        }
    }
    ((Rva005A0B4CList *)((char *)m_army + 8))->append(
        (Rva002BA8F1Listener *)static_cast<Rva00575E4EBase2 *>(this));
}

class Rva005CF6B5Owner
{
public:
	void rva005CF6B5(int armyAddress);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF6B5Owner::rva005CF6B5(int armyAddress)
{
	Rva005CEE07 *armyHelper = new Rva005CEE07(m_a, armyAddress);
	m_a->m_sub.rva00575674((Object *)armyHelper);
}

// The selection helper the 0x005CF703 allocator builds is the rowed
// Rva005CEF2F (ctor 0x005CF4A8, dtor below).
class Rva0023A128Link {public:Rva0023A128Link(){}~Rva0023A128Link(){}virtual void rva00239B94(int);virtual void v01(int);};
class Rva005E8F50 {public:void rva005E8F6A();};
class Rva005CEA51 {public:Rva005CEA51():pointer(0){}__declspec(noinline) ~Rva005CEA51();void rva005CEA51(Rva005E8F50*);void rva005CE7EA();Rva005E8F50*pointer;};
class Rva005CEF2F:public Rva005CE8F5,public Rva0023A128Link {public:Rva005CEF2F(Rva005CF22CBig *b, int x);virtual ~Rva005CEF2F();virtual void slot1();int selection;Rva005CEA51 secondary;};
typedef char Rva005CEF2FSize[(sizeof(Rva005CEF2F)==0x14)?1:-1];

class Rva005CF703Owner
{
public:
	void rva005CF703(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF703Owner::rva005CF703(int x)
{
	Rva005CEF2F *selectionHelper = new Rva005CEF2F(m_a, x);
	m_a->m_sub.rva00575674((Object *)selectionHelper);
}

#include "../../Include/Common/Rva004E0741.h"
class CreateAHeroData;
class Rva004E05F0 {public:CreateAHeroData *rva004E05F0();};
#include "../../Include/Common/Rva0042D6E6PtrChaseField.h"
class Rva005CE259 {public:struct Payload {int v[2];};};
class Rva005CE2A1 {public:~Rva005CE2A1(){if(m_p)ReleaseTreeHintRef00217D4C(m_p);}TargetRef00217D4C*m_p;};
Rva005CE2A1 Rva005CE2A1Create(const Rva005CE259::Payload*);
#define ICOORD2D_VIEW_COMPONENT_CTOR
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#undef ICOORD2D_VIEW_COMPONENT_CTOR
class Rva005CE4B2 {public:Rva005CE4B2(const int*);~Rva005CE4B2(){if(m_p)ReleaseTreeHintRef00217D4C(m_p);}TargetRef00217D4C*m_p;};
class Image;struct Rva005D232DIn;
namespace StrategicInGameUI { const Image *GetSelectionPortrait(Rva005D232DIn*); }
struct Rva005E8C54Source;
class Rva005E8CB0 {public:Rva005E8CB0(void*,int,void*,const Rva005E8C54Source*);void *m_p;};
#include "../../Include/Common/Rva005E893E.h"
class Rva005CE236 {public:Rva005CE236():m_p(0){}__declspec(noinline) ~Rva005CE236();void reset(Rva005E893E*);Rva005E893E*m_p;};
class Rva005CF07EListener {public:Rva005CF07EListener(){}virtual ~Rva005CF07EListener(){};};
class Rva005CEE9F : public Rva005CE8F5,public Rva005CF07EListener {public:Rva005CEE9F(Rva005CF22CBig*,int);virtual ~Rva005CEE9F();virtual void slot1();private:void *m_region;Rva005CE236 m_build;};
class S3RegionPanel {public:virtual void slot0();virtual void setImage(const Image*);virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void setCallback(const Rva005CE4B2&);virtual void slot7();virtual void show();virtual void slot9();virtual void hide();};
class S3CommandSlots {public:virtual void slot0();virtual void createButton(int,const Rva005CE2A1&);virtual void deleteButton(int);};
// Native374B5CF07E..5CF1F4 and WB15C2BB0 unnamed strategic region UI
// constructor. Existing dtor5CEE9F and scalar wrapper5CF1F4 own the
// primary vtableC7522C; listener at8 and regionC precede owned helper10.
// Matched299B army sibling supplies UI protocol; target calls and WB
// independently prove region callbacks and command slot5. No ZH/BF1
// clean donor exists for this BFME2 strategic UI. Field and argument
// meanings outside the target-read region and UI roles remain opaque.
Rva005CEE9F::Rva005CEE9F(Rva005CF22CBig*owner,int regionAddress):Rva005CE8F5(owner),m_region((void*)regionAddress){
 ((const Rva004E0741*)m_region)->rva004E0741();
 void *view=m_owner->m_view10;
 S3RegionPanel *panel=(S3RegionPanel*)((Rva0042D703PtrChaseField*)view)->get();
 if(panel){
  panel->setImage(StrategicInGameUI::GetSelectionPortrait((Rva005D232DIn*)m_region));
  {int region=(int)m_region;Rva005CE4B2 ref(&region);panel->setCallback(ref);}
  panel->show();
 }
 S3CommandSlots *slots=(S3CommandSlots*)((Rva0042D69DPtrChaseField*)view)->get();
 if(slots){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button)slots->createButton(5,Rva005CE2A1Create((const Rva005CE259::Payload*)&ICoord2D(button,(int)((Rva004E05F0*)regionAddress)->rva004E05F0())));
 }
 int builder=((Rva0042D6E6PtrChaseField*)view)->get();
 if(builder){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button)m_build.reset((Rva005E893E*)new Rva005E8CB0((void*)builder,button,*(void**)((char*)m_owner+8),(const Rva005E8C54Source*)m_region));
 }
 ((Rva005A0B4CList*)((char*)m_region+8))->append((Rva002BA8F1Listener*)static_cast<Rva005CF07EListener*>(this));
}

// Native5CF22C allocator retained with destructor-owned class spelling.
void Rva005CF22COwner::rva005CF22C(int regionAddress) {
 Rva005CEE9F *regionHelper=new Rva005CEE9F(m_a,regionAddress);
 m_a->m_sub.rva00575674((Object *)regionHelper);
}

#include "../../Include/Common/Rva002B7250.h"
#include "../../Include/Common/Rva004E0750.h"
Rva005CEE9F::~Rva005CEE9F(){
 ((Rva002B7250*)((char*)m_region+8))->rva002B7250((CreateAHeroData*)static_cast<Rva005CF07EListener*>(this));
 void *view=m_owner->m_view10;
 S3RegionPanel *panel=(S3RegionPanel*)((Rva0042D703PtrChaseField*)view)->get();
 if(panel)panel->hide();
 S3CommandSlots *slots=(S3CommandSlots*)((Rva0042D69DPtrChaseField*)view)->get();
 if(slots)slots->deleteButton(5);
 ((const Rva004E0750*)m_region)->rva004E0750();
}

#include "../../Include/Common/Rva004FC275.h"
Rva005CEF2F::~Rva005CEF2F(){
 ((Rva002B7250*)((char*)selection+8))->rva002B7250((CreateAHeroData*)static_cast<Rva0023A128Link*>(this));
 void *view=m_owner->m_view10;
 S3RegionPanel *panel=(S3RegionPanel*)((Rva0042D703PtrChaseField*)view)->get();
 if(panel)panel->hide();
 S3CommandSlots *slots=(S3CommandSlots*)((Rva0042D69DPtrChaseField*)view)->get();
 if(slots){for(int slot=1;slot<6;++slot)slots->deleteButton(slot);}
 ((Rva004FC275*)selection)->rva004FC2A6();
}

Rva005CEE07::~Rva005CEE07(){
 ((Rva002B7250*)((char*)m_army+8))->rva002B7250((CreateAHeroData*)static_cast<Rva00575E4EBase2*>(this));
 void *view=m_owner->m_view10;
 S3RegionPanel *panel=(S3RegionPanel*)((Rva0042D703PtrChaseField*)view)->get();
 if(panel)panel->hide();
 S3CommandSlots *slots=(S3CommandSlots*)((Rva0042D69DPtrChaseField*)view)->get();
 if(slots){for(int slot=1;slot<6;++slot)slots->deleteButton(slot);}
 ((Rva00319B0AOwner*)m_army)->rva00319B31();
}

#include <new>
// Owning-member cleanup: complete 26-byte and relocation twin of clear5CE21C.
// Keep the pointee's rowed 5E893E thunk distinct from its inner cleanup helper.
Rva005CE236::~Rva005CE236()
{
 Rva005E893E *ownedObject=m_p;
 m_p=0;
 if(ownedObject){ownedObject->Rva005E893E::~Rva005E893E();::operator delete(ownedObject);}
}

// Complete 26-byte and relocation twin of the owning-pointer clear5CE7EA.
// Preserve the rowed neutral cleanup method5E8F6A: its original name is unknown.
Rva005CEA51::~Rva005CEA51()
{
 Rva005E8F50 *ownedObject=pointer;
 pointer=0;
 if(ownedObject){ownedObject->rva005E8F6A();::operator delete(ownedObject);}
}
