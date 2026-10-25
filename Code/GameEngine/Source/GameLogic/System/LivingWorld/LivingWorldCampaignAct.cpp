// cl: /ICode/Libraries/Include/Lib /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /Ireference/shims/iniexception
// Native 566BF6..566D7B (389B), named act parser 566D83 and its WB
// twin 1438E40 establish the 184B act record and constructor relationship.
// Existing destructor 56616B independently supplies the 16 member cleanup
// offsets. The original record name remains unproven: keep its address name.
// BF1 9cbfb551fe20 ParseLivingWorldCampaignAct.cpp is a semantic lead only;
// its 220B record and unadmitted ctor do not establish the BF2 layout.
// Fourteen 12B vector headers initialize through the existing 211E58 owner.
// Storage views retain actual cleanup owners; element identities are not
// inferred from an empty header. The ten clears call existing rowed providers.
#include "ascii_string.h"
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
namespace _STL {
template<class T>class allocator{public:allocator(){}};
 template<class T,class A>class _Vector_base{public:_Vector_base(const A&)throw(); T *begin,*end,*capacity;};
 template<class T,class A>class vector{public:~vector();T *erase(T*,T*); __forceinline void clear(){erase(begin,end);} T *begin,*end,*capacity;};
}
typedef _STL::allocator<BfmeE16> Alloc; typedef _STL::_Vector_base<BfmeE16,Alloc> Header;
struct Rva0052CB26:Header{__forceinline Rva0052CB26()throw():Header(Alloc()){} ~Rva0052CB26();};
struct Rva0052CA6C:Header{__forceinline Rva0052CA6C()throw():Header(Alloc()){} ~Rva0052CA6C();};
// LivingWorldAIBuildingTypes views the same address-named header over 88-byte
// elements and emits its copy first: dllimport keeps this ctor inline-only.
struct Rva004FABE2:Header{__declspec(dllimport) __forceinline Rva004FABE2()throw():Header(Alloc()){} ~Rva004FABE2();};
struct Rva0052CC25:Header{__forceinline Rva0052CC25()throw():Header(Alloc()){} ~Rva0052CC25();};
struct Rva0052CCC4:Header{__forceinline Rva0052CCC4()throw():Header(Alloc()){} ~Rva0052CCC4();};
struct Rva0052CD03:Header{__forceinline Rva0052CD03()throw():Header(Alloc()){} ~Rva0052CD03();};
struct Rva0052CD42:Header{__forceinline Rva0052CD42()throw():Header(Alloc()){} ~Rva0052CD42();};
struct Rva0052CDE1:Header{__forceinline Rva0052CDE1()throw():Header(Alloc()){} ~Rva0052CDE1();};
struct Rva0052D1CD:Header{__forceinline Rva0052D1CD()throw():Header(Alloc()){} ~Rva0052D1CD();};
struct Rva0052D20C:Header{__forceinline Rva0052D20C()throw():Header(Alloc()){} ~Rva0052D20C();};
struct AsciiVec:Header{__forceinline AsciiVec()throw():Header(Alloc()){} __forceinline ~AsciiVec(){reinterpret_cast<_STL::vector<AsciiString,_STL::allocator<AsciiString> >*>(this)->~vector();}};
struct Rva00565865Element;
struct Rva00566A42Element;
struct Rva005658CBElement;
struct Rva00565964Element;
struct Rva00565931Element;
struct Rva005658FEElement;
struct Rva00565997Element;
class Rva00564B1A; class Rva00565898{public:Rva00564B1A *rva00565898(Rva00564B1A*,Rva00564B1A*);__forceinline void clear(){rva00565898(begin,end);} Rva00564B1A *begin,*end,*capacity;}; class Rva00566695;class Rva00566B81Vector{public:Rva00566695 *EraseRange(Rva00566695*,Rva00566695*);__forceinline void clear(){EraseRange(begin,end);} Rva00566695 *begin,*end,*capacity;};
struct FieldParse;
class Rva0056616B {
public:
 Rva0056616B(const AsciiString&);
 void rva005666C5();
 static const FieldParse m_fieldParseTable[];
 virtual ~Rva0056616B();
AsciiString m_04;
Rva0052CB26 m_08;
Rva0052CA6C m_14;
Rva004FABE2 m_20;
Rva0052CC25 m_2C;
Rva0052CCC4 m_38;
AsciiVec m_callActSubroutine;
AsciiString m_jumpToAct;
Rva0052CD03 m_54;
Rva0052CD42 m_60;
Rva0052CCC4 m_6C;
Rva0052CDE1 m_78;
Rva0052CDE1 m_84;
Rva0052D1CD m_90;
Rva0052D20C m_9C;
Rva0052CC25 m_A8;
bool m_endAct;
};
Rva0056616B::Rva0056616B(const AsciiString &name):m_04(name),m_endAct(false) {
reinterpret_cast<_STL::vector<Rva00565865Element,_STL::allocator<Rva00565865Element> >*>(&m_08)->clear();
reinterpret_cast<_STL::vector<Rva00566A42Element,_STL::allocator<Rva00566A42Element> >*>(&m_20)->clear();
reinterpret_cast<Rva00565898*>(&m_2C)->clear();
reinterpret_cast<_STL::vector<Rva005658CBElement,_STL::allocator<Rva005658CBElement> >*>(&m_38)->clear();
reinterpret_cast<_STL::vector<Rva00565964Element,_STL::allocator<Rva00565964Element> >*>(&m_78)->clear();
reinterpret_cast<_STL::vector<Rva00565931Element,_STL::allocator<Rva00565931Element> >*>(&m_6C)->clear();
reinterpret_cast<_STL::vector<Rva005658FEElement,_STL::allocator<Rva005658FEElement> >*>(&m_54)->clear();
reinterpret_cast<Rva00566B81Vector*>(&m_60)->clear();
reinterpret_cast<_STL::vector<AsciiString,_STL::allocator<AsciiString> >*>(&m_callActSubroutine)->clear();
reinterpret_cast<_STL::vector<Rva00565997Element,_STL::allocator<Rva00565997Element> >*>(&m_A8)->clear();
}

Rva0056616B::~Rva0056616B() {}

// Complete native act parser 566D83/232B and its 256-byte field table
// C6CD50. Target and WB establish the act name, 184-byte record, constructor
// and append relationship. BFME1 9cbfb551fe20 supplies the semantic lead;
// its different record layout and callback addresses are not imported.
// Every table string, callback, member offset, zero userdata and null
// terminator is independently checked against retail. Callback providers
// all use the registered four-argument ABI, with no casts or extra pins.
struct FieldParse;
class INI { public: const char *getNextToken(const char *seps=0); void initFromINI(void*,const FieldParse*);
 static void parseAsciiStringVectorAppend(INI*,void*,void*,const void*);
 static void parseAsciiString(INI*,void*,void*,const void*);
 static void parseBool(INI*,void*,void*,const void*);
};
#include "Common/INIException.h"
struct Rva0052D801Record;
class Rva0052D83B { public:void rva0052D83B(const Rva0052D801Record &); };
void ParseEnableRegion(INI*,void*,void*,const void*);
void ParseForceBattle(INI*,void*,void*,const void*);
void Rva004E324DParse(INI*,void*,void*,const void*);
void Rva004E1BFCParse(INI*,void*,void*,const void*);
void Rva004E17EBParse(INI*,void*,void*,const void*);
void Rva004E141DParse(INI*,void*,void*,const void*);
void SplineCameraParseINIBlock(INI*,void*,void*,const void*);
void ParseWorldTextBlock(INI*,void*,void*,const void*);
void ParseAudioEventBlock(INI*,void*,void*,const void*);
void Rva004E1A33Parse(INI*,void*,void*,const void*);
void ParseEyeTowerPointData(INI*,void*,void*,const void*);
void Rva004E1C7BParse(INI*,void*,void*,const void*);
struct FieldParse { const char *name; void (*parse)(INI*,void*,void*,const void*); const void *userData; int offset; };
const FieldParse Rva0056616B::m_fieldParseTable[]={
 {"EnableRegion",ParseEnableRegion,0,0},
 {"ForceBattle",ParseForceBattle,0,0},
 {"SpawnArmy",Rva004E324DParse,0,0},
 {"MoveArmy",Rva004E1BFCParse,0,0},
 {"SpawnBuilding",Rva004E17EBParse,0,0},
 {"CallActSubroutine",INI::parseAsciiStringVectorAppend,0,0x44},
 {"JumpToAct",INI::parseAsciiString,0,0x50},
 {"MoveCamera",Rva004E141DParse,0,0},
 {"SplineCamera",SplineCameraParseINIBlock,0,0},
 {"WorldText",ParseWorldTextBlock,0,0},
 {"AudioEvent",ParseAudioEventBlock,0,0},
 {"EndAct",INI::parseBool,0,0xb4},
 {"UpdateAnimObject",Rva004E1A33Parse,0,0},
 {"EyeTowerPoints",ParseEyeTowerPointData,0,0},
 {"SetPlayerControlOfArmy",Rva004E1C7BParse,0,0},
 {0,0,0,0}
};

void ParseLivingWorldCampaignAct(INI *ini,void *instance,void*,const void*) {
 if(!ini || !instance) throw INIException(3,"ParseLivingWorldCampaignAct::Invalid data passed in.");
 AsciiString name(ini->getNextToken());
 if(!name.getLength()) throw INIException(3,"ParseLivingWorldCampaignAct::No act name specified.");
 Rva0056616B record(name);
 ini->initFromINI(&record,Rva0056616B::m_fieldParseTable);
 ((Rva0052D83B*)instance)->rva0052D83B((const Rva0052D801Record&)record);
}

// Native5666C5..5668E9 (548B), complete RET0; WB1439F00 identifies
// SpawnArmies. Requests are 88-byte spawn records; typed names/player views
// retain their independently observed strides. The explicit request-buffer
// load in at() preserves the native reload after each size calculation.
// Its separate index copy retains the target LEA and late ESI save. This is
// a local access-order constraint, not a claim that the member is volatile.
// Target318E8C returns the coordinate pointer; a scoped zero coordinate
// preserves the release-lifetime boolean shape. No new dependency pins.
#include "Coord2D.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Xfer; class Image;
class SpawnArmy:public Snapshot { public:
 SpawnArmy(int); virtual ~SpawnArmy();
 virtual void loadPostProcess(); virtual const char *GetSnapshotName()const; virtual void xfer(Xfer*);
 AsciiString m_04,m_08,m_0c,m_10,m_14,m_18,m_1c;
 float m_20,m_24; AsciiString m_28,m_2c,m_30,m_34;
 _STL::vector<AsciiString,_STL::allocator<AsciiString> > m_38;
 float m_callActSubroutine; int m_48,m_4c; AsciiString m_jumpToAct; bool m_54,m_55;
};
struct Rva004FAFF2 { Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2&); };
struct Rva00318E8COut {float f;int i;};
class Rva00318E8C {public:Rva00318E8COut *rva00318E8C(Rva00318E8COut*);};
class Rva002E18C3Lookup {public:AsciiString *find(const AsciiString&);};
extern Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
class Rva002E2903Player {public:char pad[0x40];AsciiString *template40;};
class Rva002BA8F1Logic {public:Rva002E2903Player *GetPlayerAtIndex(int);};
struct Rva002B86AAKey; struct Rva002B86AAVal;
class Rva002B86AA {public:bool rva002B86AA(Rva002B86AAKey*,Rva002B86AAVal*)const;};
class Rva002104B6 {public:void *rva002104B6(void*);};
class Rva0020E89C;
class LivingWorldRegionManager {public:bool GetRegionCenterPoint(Rva0020E89C*,Coord2D*);};
struct Rva002B6A04Player; struct LivingWorldArmy;
class LivingWorldLogic {public:
 void spawnCity(SpawnArmy*);
 LivingWorldArmy *spawnArmy(SpawnArmy*,Rva002B6A04Player*,bool);
 char pad[0x8c]; Rva002E2903Player **playersBegin,**playersEnd; char pad94[0xB0-0x94]; Rva002104B6 *regions;
};
extern LivingWorldLogic *TheLivingWorldLogic;
struct SpawnZero:Coord2D{SpawnZero(){x=0.0f;y=0.0f;}~SpawnZero(){}};
__forceinline bool spawnEqual(const Coord2D &lhs,const Coord2D &rhs){return lhs.x==rhs.x && lhs.y==rhs.y;}

template<class T>struct SpawnVectorView {
 T *first,*last,*capacity;
 unsigned size()const{return unsigned(last-first);}
 bool empty()const{return first==last;}
 T &operator[](unsigned n){return first[n];} T & at(unsigned n){unsigned offset=n; T *p=(*(T *const volatile *)&first); return *(p+offset);}
};

void Rva0056616B::rva005666C5() {
 SpawnVectorView<SpawnArmy> &requests=*reinterpret_cast<SpawnVectorView<SpawnArmy> *>(&m_20);
 for(unsigned int index=0;index<requests.size();++index) {
  SpawnArmy *request=&requests.at(index);
  if(request->m_55) {
   if(reinterpret_cast<SpawnVectorView<AsciiString> *>(&request->m_38)->empty()) TheLivingWorldLogic->spawnCity(request);
   else { SpawnVectorView<AsciiString> &names=*reinterpret_cast<SpawnVectorView<AsciiString> *>(&request->m_38); for(unsigned int t=0;t<names.size();++t) {
    AsciiString *playerTemplate=TheLivingWorldPlayerTemplateStore->find(names[t]);
    if(playerTemplate) for(unsigned int p=0;p<reinterpret_cast<SpawnVectorView<Rva002E2903Player *> *>(&TheLivingWorldLogic->playersBegin)->size();++p) {
     Rva002E2903Player *player=reinterpret_cast<Rva002BA8F1Logic*>(TheLivingWorldLogic)->GetPlayerAtIndex(p);
     if(playerTemplate==player->template40 && !reinterpret_cast<Rva002B86AA*>(TheLivingWorldLogic)->rva002B86AA(reinterpret_cast<Rva002B86AAKey*>(request),reinterpret_cast<Rva002B86AAVal*>(player))) {
      Rva00318E8COut position;
      if(!spawnEqual(*reinterpret_cast<Coord2D*>(reinterpret_cast<Rva00318E8C*>(request)->rva00318E8C(&position)),SpawnZero()))
       TheLivingWorldLogic->spawnArmy(request,reinterpret_cast<Rva002B6A04Player*>(player),true);
      else {
       Rva002104B6 *regionManager=TheLivingWorldLogic->regions;
       void *region=regionManager->rva002104B6(reinterpret_cast<char*>(player)+0x2c);
       if(region) {
        SpawnArmy temporary(0);
        reinterpret_cast<Rva004FAFF2*>(&temporary)->rva004FAFF2(*reinterpret_cast<const Rva004FAFF2*>(request));
        Coord2D center;
        LivingWorldRegionManager *centers=reinterpret_cast<LivingWorldRegionManager*>(TheLivingWorldLogic->regions);
        if(!centers->GetRegionCenterPoint((Rva0020E89C *)region,&center)) return;
        *reinterpret_cast<unsigned int *>(&temporary.m_20)=*reinterpret_cast<const unsigned int *>(&center.x); *reinterpret_cast<unsigned int *>(&temporary.m_24)=*reinterpret_cast<const unsigned int *>(&center.y);
        TheLivingWorldLogic->spawnArmy(&temporary,reinterpret_cast<Rva002B6A04Player*>(player),true);
       }
      }
     }
    }
   }}
  }

 }
}
