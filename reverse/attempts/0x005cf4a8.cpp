// ??0Rva005CF4A8Helper@@QAE@PAURva005CF22CBig@@H@Z
// partial score=0.773 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /Oy- /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
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

class Rva00575674Sub
{
public:
	void rva00575674(void *h);
};

struct Rva005CF22CBig
{
	char m_pad[0x10];
	void *m_view10;
	char m_pad14[8];
	Rva00575674Sub m_sub;
};

class Rva005CF07EHelper
{
public:
	Rva005CF07EHelper(Rva005CF22CBig *b, int x);
	unsigned char m_data[0x14];
};

class Rva005CF22COwner
{
public:
	void rva005CF22C(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF22COwner::rva005CF22C(int x)
{
	Rva005CF07EHelper *h = new Rva005CF07EHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

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
const Image *Rva005D2355Get(Rva005D2355In *);
int GetMaxCommandPoints(void *);
class Rva00318FBE { public: int rva00318FBE(); };
class Rva00319B0AOwner { public: void rva00319B0A(); };
class Rva0042D703PtrChaseField { public: int get() const; };
class Rva0042D69DPtrChaseField { public: int get() const; };
class Rva0042D6B4PtrChaseField { public: int get() const; };
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
class Rva005A0B4CList { public: void append(Rva002BA8F1Listener *); };
class Rva005CF37DBase0 {
public:
    Rva005CF37DBase0(Rva005CF22CBig *b) : m_owner(b) {}
    virtual ~Rva005CF37DBase0() {}
    Rva005CF22CBig *m_owner;
};
// Existing one-vptr observer-base view: its emitted vtable is retail C3702C.
class Rva00575E4EBase2 {
public:
    Rva00575E4EBase2() {}
    virtual ~Rva00575E4EBase2() {}
};
class Rva005CF37DHelper : public Rva005CF37DBase0, public Rva00575E4EBase2
{
public:
    Rva005CF37DHelper(Rva005CF22CBig *b, int x);
    virtual ~Rva005CF37DHelper();
private:
    int m_army;
};

// Native boundary 5CF37D..5CF4A8, RET8. Existing allocating caller5CF6B5
// proves this constructor and its16B allocation. Primary/secondary vptrs at
// +0/+8; owner+4 and army+0C; WB is an unnamed StrategicInGameUI lead.
Rva005CF37DHelper::Rva005CF37DHelper(Rva005CF22CBig *b, int x)
    : Rva005CF37DBase0(b), m_army(x)
{
    ((Rva00319B0AOwner *)m_army)->rva00319B0A();
    void *view = m_owner->m_view10;
    Rva005CF37DPortrait *portrait = (Rva005CF37DPortrait *)
        ((Rva0042D703PtrChaseField *)view)->get();
    if (portrait) {
        portrait->setImage(Rva005D2355Get((Rva005D2355In *)m_army));
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
	void rva005CF6B5(int x);
private:
	unsigned char m_pad00[0xC];
	Rva005CF22CBig *m_a;
};

void Rva005CF6B5Owner::rva005CF6B5(int x)
{
	Rva005CF37DHelper *h = new Rva005CF37DHelper(m_a, x);
	m_a->m_sub.rva00575674(h);
}


class Rva004FC275 {public:void rva004FC299();};
struct Rva005D23BBSelection;
namespace StrategicInGameUI {const Image *__cdecl GetSelectionPortrait(const Rva005D23BBSelection *);}
class Rva005CED37 {
public:Rva005CED37(const int*);
 ~Rva005CED37(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
 TargetRef00217D4C *pointer;
};
enum ScienceType { SCIENCE_INVALID=0 };
enum NameKeyType { NAMEKEY_INVALID=0,FORCE_NAMEKEYTYPE_LONG=0x7fffffff };
class ArmorTemplate;
class Rva002E02F0 {public:void rva002E02F0(int,_STL::vector<ScienceType>*);};
class Rva002B6498 {public:ArmorTemplate *rva002B6498(NameKeyType);};
class Rva0022C0CDSubsystem;
extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct LivingWorldActivePlayerView {char gap[0x98];void *player;};
struct LivingWorldPlayerKeyView {char gap[0x40];int key;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public:Rva002E2903Player *find(int,unsigned*);};
class Rva0042D6E6PtrChaseField {public:int get()const;};
struct ICoord3D {ICoord3D(int,int,int);int x,y,z;};
class Rva005CEAE6 {public:struct Payload{int v[3];};};
class Rva005CEC8F {public:TargetRef00217D4C *pointer;
 ~Rva005CEC8F(){if(pointer)ReleaseTreeHintRef00217D4C(pointer);}
};
Rva005CEC8F *__cdecl Rva005CEC8FCreate(Rva005CEC8F*,const Rva005CEAE6::Payload*);
typedef Rva005CEC8F (__cdecl *SelectionFactory)(const Rva005CEAE6::Payload*);
class Rva005E8F50;
struct Rva005E8FECOwner;
struct Rva005E8FECSource;
class Rva005E90EC {public:Rva005E90EC(void*,int,void*,Rva005E8FECOwner*,Rva005E8FECSource*);void *pointer;};
class Rva005CEA51 {public:
 Rva005CEA51():pointer(0){}
 ~Rva005CEA51(){rva005CE7EA();}
 void rva005CEA51(Rva005E8F50*);
 void rva005CE7EA();
 Rva005E8F50 *pointer;
};
class Rva005CF4A8Helper: public Rva005CF37DBase0,public Rva00575E4EBase2 {
public:Rva005CF4A8Helper(Rva005CF22CBig*,int);virtual ~Rva005CF4A8Helper();
 int selection;Rva005CEA51 secondary;
};
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
	Rva005CF4A8Helper *h = new Rva005CF4A8Helper(m_a, x);
	m_a->m_sub.rva00575674(h);
}

Rva005CF4A8Helper::Rva005CF4A8Helper(Rva005CF22CBig*b,int value):Rva005CF37DBase0(b),selection(value) {
 ((Rva004FC275*)selection)->rva004FC299();
 void *view=m_owner->m_view10;
 Rva005CF37DPortrait *portrait=(Rva005CF37DPortrait*)((Rva0042D703PtrChaseField*)view)->get();
 if(portrait){
  portrait->setImage(StrategicInGameUI::GetSelectionPortrait((const Rva005D23BBSelection*)selection));
  {int copy=selection;Rva005CED37 ref(&copy);portrait->setArmy((const Rva005773DB&)ref);}
  portrait->refresh();
 }
 Rva005CF37DCommandUI *commands=(Rva005CF37DCommandUI*)((Rva0042D69DPtrChaseField*)view)->get();
 if(commands){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button){
   _STL::vector<ScienceType> keys;
   void *player=((LivingWorldActivePlayerView*)TheLivingWorldLogic)->player;
   ((Rva002E02F0*)TheLivingWorldBuildingTemplateStore)->rva002E02F0(((LivingWorldPlayerKeyView*)player)->key,&keys);
   int slot=1;
   _STL::vector<ScienceType>::iterator end=keys.end();
   for(_STL::vector<ScienceType>::iterator it=keys.begin();it!=end;++it){
    ArmorTemplate *building=((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)*it);
    if(building){
     commands->createButton(slot,(const RvaCloneResult<Rva005CEA74>&)((SelectionFactory)Rva005CEC8FCreate)((const Rva005CEAE6::Payload*)&ICoord3D(button,selection,(int)building)));
     if(++slot>=6)break;
    }
   }
  }
 }
 int alternate=((Rva0042D6E6PtrChaseField*)view)->get();
 if(alternate){
  int button=((Rva0042D6B4PtrChaseField*)view)->get();
  if(button){
   Rva002E2903Player*player=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(*(int*)((char*)m_owner+0xc),0);
   if(player){
    Rva005E90EC *item=new Rva005E90EC((void*)alternate,button,*(void**)((char*)m_owner+8),(Rva005E8FECOwner*)selection,(Rva005E8FECSource*)player);
    secondary.rva005CEA51((Rva005E8F50*)item);
   }
  }
 }
 ((Rva005A0B4CList*)((char*)selection+8))->append((Rva002BA8F1Listener*)static_cast<Rva00575E4EBase2*>(this));
}
