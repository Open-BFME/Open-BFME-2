// ?DoXfer@Player@@QAEXPAVXfer@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// Native 2B1522..2B212A, 3080 bytes, WB C205C0 Player::DoXfer.
// Semantic guide: BFME1 6c1e0b51 Player.cpp xfer; native version10,
// LightCRC branches, accessed fields and helper ABIs supersede donor layout.
// Complete partial reconstruction, not a matched ledger claim: 3083/3080B.
// Prologue and112B frame agree. Remaining: upgrade count guard CMP/store
// ordering; build-head clearing; legacy team/rank/count temporary stack slots;
// holder creation common-branch temporary; timer save argument register order.
// Float/int table helpers2AF236/2AF33B remain unrowed (their complete banks
// exist independently). No new pin or extent change was made for this trial.
// G6 and Ox/Os did not improve G7/O1; reference argument and pool-glue forms
// regressed. Native lifetime proof repaired the8B360BFE constructor owner.
// Callback storage is refreshed between bonus-field transfers. The tracker
// is embedded at738; version consists of format1 and transferred value10.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
#include <list>
#include <new>
class Xfer;
struct PlayerVersion { unsigned char format, value; PlayerVersion():format(1),value(10){} };
class PlayerXferView {
public:
 virtual void s0(); virtual bool loading(); virtual bool saving();
 virtual bool crc(); virtual bool lightCRC();
 virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
 virtual void version(PlayerVersion*); virtual void s11(); virtual void snapshot(void*);
 virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
 virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
 virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
 virtual void wide(UnicodeString*); virtual void ascii(AsciiString*); virtual void real(float*);
 virtual void s29(); virtual void word(unsigned*); virtual void integer(int*);
 virtual void ushort(unsigned short*); virtual void s33(); virtual void s34(); virtual void s35();
 virtual void boolean(bool*);
};
enum ScienceType { SCIENCE_NATIVE_ZERO=0 };
enum ObjectID { OBJECT_NATIVE_ZERO=0 };
enum UpgradeStatusType { UPGRADE_NATIVE_INVALID=0 };
class UpgradeTemplate;
class Upgrade;
class UpgradeCenter { public: const UpgradeTemplate *findUpgrade(const AsciiString&) const; };
extern UpgradeCenter *TheUpgradeCenter;
class TeamPrototype;
class Team;
static __forceinline unsigned playerTeamID(Team *team) {
 return team?*reinterpret_cast<unsigned*>(reinterpret_cast<char*>(team)+0x34):0;
}
class TeamFactory { public: Team *findTeamByID(unsigned); };
extern TeamFactory *TheTeamFactory;
class Rva0039FE6COwner { public: TeamPrototype *rva0039F72C(unsigned); };
class Rva002AAC74PoolList { public: void clear(); };
class Rva00291440;
void rva003064CB(Xfer*,Rva00291440*);
Xfer *Rva001ECA2DXfer(Xfer*,void*);
void XferObjectID(Xfer*,ObjectID*);
void XferOrderMode(Xfer*,int*);
class Rva00380200 { public: void rva00380499(Xfer*); };
class Rva002AE71D { public: void rva002AE71D(Xfer*); };
class Rva00360BFEWordView { public: Rva00360BFEWordView(unsigned); unsigned bits; };
class Rva002AC3BE { public: Rva002AC3BE(void*); char bytes[0x18]; };
class BuildListInfo {
public: BuildListInfo(); virtual ~BuildListInfo();
 char pad04[0x28]; BuildListInfo *next; char pad30[0x50];
};
class PlayerBuildDestructorView {public: virtual void *destroy(unsigned);};
class Squad { public: Squad(); char bytes[0x1C]; };
template<int N> class BitFlags { public: void xfer(Xfer*); unsigned bits[(N+31)/32]; };
class Rva002AA14DBonuses {
public: Rva002AA14DBonuses(); float armor; int bombard,search,hold; float sight;
 BitFlags<218> valid,invalid;
};
struct BfmeSpecialPowerTimer8 { unsigned templateID,readyFrame; };
struct BfmeVectorRecord002AF478 { char bytes[36]; };
class Rva002AF55A { public: Rva002AF55A(); char bytes[36]; };
class Rva002AF1EC { public: ~Rva002AF1EC(); };
class Rva002B0A05 { public: void rva002B0A05(Xfer*); };
struct PlayerTransferRecord:public Rva002AF55A {
 ~PlayerTransferRecord(){reinterpret_cast<Rva002AF1EC*>(this)->~Rva002AF1EC();}
};
class PlayerTrackerView { public: virtual void transfer(Xfer*); };
struct BfmeFormattedText { char *text; int tag; };
extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText*,int,const char*,...);
struct _s__ThrowInfo;
extern int g_guardTargetTypeThrowInfo;
extern "C" void __stdcall _CxxThrowException(void*,const _s__ThrowInfo*);
static __forceinline void badPlayerTransfer() {
 BfmeFormattedText error; bfmeFormatText(&error,5,0);
 _CxxThrowException(&error,reinterpret_cast<const _s__ThrowInfo*>(&g_guardTargetTypeThrowInfo));
 __assume(0);
}
class Rva001FDE3F;
class Rva002AE4C5;
class Player {
public:
 void DoXfer(Xfer*);
 Upgrade *rva002AE329(const UpgradeTemplate*,UpgradeStatusType,int);
 void rva002AF236(Xfer*,Rva001FDE3F*);
 void rva002AF33B(Xfer*,Rva002AE4C5*);
 template<class T> T &at(unsigned offset){return *reinterpret_cast<T*>(reinterpret_cast<char*>(this)+offset);}
};
namespace _STL {
 template<> ScienceType *vector<ScienceType>::erase(ScienceType*,ScienceType*);
 template<> void list<TeamPrototype*>::push_back(TeamPrototype*const&);
 template<> void list<int>::push_back(const int&);
 template<> void list<BfmeSpecialPowerTimer8>::push_back(const BfmeSpecialPowerTimer8&);
 template<> void vector<BfmeVectorRecord002AF478>::push_back(const BfmeVectorRecord002AF478&);
}
Xfer *Rva002AC1A9XferList(Xfer*,_STL::list<short>*);
struct PlayerUpgradeNode { char pad00[4]; char *tmplate; char pad08[4]; PlayerUpgradeNode *next; };
struct PlayerListNode { PlayerListNode *next,*prev; void *value; };
struct PlayerListView {
 PlayerListNode *head;
 unsigned size()const { unsigned n=0; for(PlayerListNode*p=head->next;p!=head;p=p->next)++n; return n; }
};
// Native allocates these blocks without a deallocation guard around construction.
// Placement construction states that actual failure behavior explicitly.
struct PlayerConstructInStorage {};
static __forceinline void *operator new(unsigned size, PlayerConstructInStorage*,void *storage) {return storage;}
template<class T> static __forceinline T *allocatePlayerPart() {
 void *storage=::operator new(sizeof(T));
 return storage?new((PlayerConstructInStorage*)0,storage)T:0;
}
static __forceinline Rva002AC3BE *allocatePlayerHolder(void *state) {
 void *storage=::operator new(sizeof(Rva002AC3BE));
 return storage?new((PlayerConstructInStorage*)0,storage)Rva002AC3BE(state):0;
}
#define FIELD(T,O) at< T >(O)
#define SNAP(O) xfer->snapshot(&FIELD(char,O))
#define BOOL(O) xfer->boolean(&FIELD(bool,O))
#define INT(O) xfer->integer(&FIELD(int,O))
void Player::DoXfer(Xfer *raw)
{
 PlayerXferView *xfer=reinterpret_cast<PlayerXferView*>(raw);
 unsigned i;
 bool full=!xfer->lightCRC();
 PlayerVersion version;
 xfer->version(&version);
 if(xfer->crc()) BOOL(0x33E);
 if(full) {
  SNAP(0x60); SNAP(0x90);
  PlayerUpgradeNode *upgrade=FIELD(PlayerUpgradeNode*,0x9C);
  unsigned short upgradeCount=0;
  for(;upgrade;upgrade=upgrade->next)++upgradeCount;
  xfer->ushort(&upgradeCount); BOOL(0x33B);
  if(xfer->loading()) {
   _STL::vector<ScienceType>&disabled=FIELD(_STL::vector<ScienceType>,0x2FC);
   disabled.erase(disabled.begin(),disabled.end());
   _STL::vector<ScienceType>&hidden=FIELD(_STL::vector<ScienceType>,0x308);
   hidden.erase(hidden.begin(),hidden.end());
  }
  Rva001ECA2DXfer(raw,&FIELD(char,0x2FC)); Rva001ECA2DXfer(raw,&FIELD(char,0x308));
  AsciiString upgradeName;
  if(xfer->saving()) {
   for(upgrade=FIELD(PlayerUpgradeNode*,0x9C);upgrade;upgrade=upgrade->next) {
    upgradeName=*reinterpret_cast<AsciiString*>(upgrade->tmplate+8);
    xfer->ascii(&upgradeName); xfer->snapshot(upgrade);
   }
  } else {
   FIELD(unsigned,0x6F0)=0;
   for(unsigned short i=0;i<upgradeCount;++i) {
    xfer->ascii(&upgradeName);
    const UpgradeTemplate *tmplate=TheUpgradeCenter->findUpgrade(upgradeName);
    if(!tmplate)badPlayerTransfer();
    upgrade=reinterpret_cast<PlayerUpgradeNode*>(rva002AE329(tmplate,UPGRADE_NATIVE_INVALID,0));
    xfer->snapshot(upgrade);
   }
  }
  INT(0xA0); BOOL(0x734); INT(0xA4); BOOL(0xA8);
  rva003064CB(raw,&FIELD(Rva00291440,0xBC)); rva003064CB(raw,&FIELD(Rva00291440,0x13C));
  SNAP(0x1BC); if(version.value>=9)BOOL(0x33F);
  PlayerListView&prototypes=FIELD(PlayerListView,0x32C);
  unsigned short prototypeCount=(unsigned short)FIELD(_STL::list<TeamPrototype*>,0x32C).size(); xfer->ushort(&prototypeCount);
  unsigned short modifierCount,timerCount,squadCount;
  unsigned prototypeID;
  if(xfer->saving()) {
   for(PlayerListNode*p=prototypes.head->next;p!=prototypes.head;p=p->next) {
    prototypeID=*reinterpret_cast<unsigned*>(reinterpret_cast<char*>(p->value)+0xC); xfer->word(&prototypeID);
   }
  } else {
   FIELD(Rva002AAC74PoolList,0x32C).clear();
   for(unsigned short i=0;i<prototypeCount;++i) {
    xfer->word(&prototypeID);
    TeamPrototype *prototype=reinterpret_cast<Rva0039FE6COwner*>(TheTeamFactory)->rva0039F72C(prototypeID);
    if(!prototype)badPlayerTransfer();
    FIELD(_STL::list<TeamPrototype*>,0x32C).push_back(prototype);
   }
  }
  BuildListInfo *build=FIELD(BuildListInfo*,0x278); unsigned short buildCount=0;
  for(;build;build=build->next)++buildCount;
  xfer->ushort(&buildCount);
  if(xfer->saving()) {
   for(build=FIELD(BuildListInfo*,0x278);build;build=build->next)xfer->snapshot(build);
  } else {
   if(FIELD(BuildListInfo*,0x278))::operator delete(reinterpret_cast<PlayerBuildDestructorView*>(FIELD(BuildListInfo*,0x278))->destroy(0));
   unsigned short i=0;
   FIELD(BuildListInfo*,0x278)=0;
   for(;i<buildCount;++i) {
    build=new BuildListInfo; build->next=0;
    BuildListInfo *tail=FIELD(BuildListInfo*,0x278);
    if(!tail)FIELD(BuildListInfo*,0x278)=build;
    else {while(tail->next)tail=tail->next;tail->next=build;}
    xfer->snapshot(build);
   }
  }
  bool hasAI=FIELD(void*,0x2DC)!=0; xfer->boolean(&hasAI);
  if((hasAI==true&&!FIELD(void*,0x2DC))||(hasAI==false&&FIELD(void*,0x2DC)))badPlayerTransfer();
  if(FIELD(void*,0x2DC))xfer->snapshot(FIELD(void*,0x2DC));
  bool hasResources=FIELD(void*,0x2E4)!=0; xfer->boolean(&hasResources);
  if((hasResources==true&&!FIELD(void*,0x2E4))||(hasResources==false&&FIELD(void*,0x2E4)))badPlayerTransfer();
  if(FIELD(void*,0x2E4))xfer->snapshot(FIELD(void*,0x2E4));
  bool hasTunnel=FIELD(void*,0x2E8)!=0; xfer->boolean(&hasTunnel);
  if((hasTunnel==true&&!FIELD(void*,0x2E8))||(hasTunnel==false&&FIELD(void*,0x2E8)))badPlayerTransfer();
  if(FIELD(void*,0x2E8))xfer->snapshot(FIELD(void*,0x2E8));
  unsigned teamID=playerTeamID(FIELD(Team*,0x2EC));
  xfer->word(&teamID); if(xfer->loading())FIELD(Team*,0x2EC)=TheTeamFactory->findTeamByID(teamID);
  if(xfer->loading()) {
   _STL::vector<ScienceType>&sciences=FIELD(_STL::vector<ScienceType>,0x2F0);
   sciences.erase(sciences.begin(),sciences.end());
  }
  Rva001ECA2DXfer(raw,&FIELD(char,0x2F0));
  if(version.value>=8)FIELD(Rva00380200,8).rva00380499(raw);
  else {
   int rank=FIELD(int,0x1C); xfer->integer(&rank);
   float progress;
   int points;
   if(version.value>=3){points=FIELD(int,0x20);progress=FIELD(float,0x14);xfer->real(&progress);}
   else points=0;
   xfer->integer(&points);
   int a=FIELD(int,0x24);xfer->integer(&a);
   int b=FIELD(int,0x28);xfer->integer(&b);
   int c=FIELD(int,0x2C);xfer->integer(&c);
   UnicodeString oldName;xfer->wide(&oldName);
  }
  xfer->snapshot(FIELD(void*,0x330)); xfer->snapshot(FIELD(void*,0x334));
  BOOL(0x338);BOOL(0x735);BOOL(0x339);BOOL(0x33A);INT(0x27C);
  if(version.value<8){float progress=FIELD(float,0x18);xfer->real(&progress);}
  BOOL(0x33C);
  int *relations=&FIELD(int,0x358);
  for(int relationIndex=0;relationIndex<20;++relationIndex){xfer->boolean(&FIELD(bool,0x340+relationIndex));xfer->integer(relations++);}
  xfer->word(&FIELD(unsigned,0x3A8)); SNAP(0x3BC);
  PlayerListView&modifiers=FIELD(PlayerListView,0x6F4);
  modifierCount=(unsigned short)FIELD(_STL::list<int>,0x6F4).size();xfer->ushort(&modifierCount);
  if(xfer->saving()) {
   for(PlayerListNode*p=modifiers.head->next;p!=modifiers.head;p=p->next)
    reinterpret_cast<Rva002AE71D*>(p->value)->rva002AE71D(raw);
  } else {
   if(FIELD(_STL::list<int>,0x6F4).size()!=0)badPlayerTransfer();
   for(i=0;i<modifierCount;++i) {
    Rva00360BFEWordView *state=new Rva00360BFEWordView(1);
    int entryWord=reinterpret_cast<int>(allocatePlayerHolder(state));
    reinterpret_cast<Rva002AE71D*>(entryWord)->rva002AE71D(raw);
    FIELD(_STL::list<int>,0x6F4).push_back(entryWord);
   }
  }
  if(version.value<2) {
   unsigned short count=0;xfer->ushort(&count);
   if(!xfer->saving())for(i=0;i<count;++i){float oldValue;ObjectID oldID;xfer->real(&oldValue);XferObjectID(raw,&oldID);}
  } else {
   if(version.value>4){xfer->real(&FIELD(float,0x6F8));INT(0x6FC);}
   if(version.value>5&&version.value<10){unsigned short count;xfer->ushort(&count);AsciiString oldName;while(count--)xfer->ascii(&oldName);}
   if(version.value<10){float oldValue;int oldID;xfer->real(&oldValue);xfer->integer(&oldID);}
  }
  PlayerListView&timers=FIELD(PlayerListView,0x704);
  timerCount=(unsigned short)FIELD(_STL::list<BfmeSpecialPowerTimer8>,0x704).size();xfer->ushort(&timerCount);
  if(xfer->saving()) {
   _STL::list<BfmeSpecialPowerTimer8>&timerList=FIELD(_STL::list<BfmeSpecialPowerTimer8>,0x704);
   for(_STL::list<BfmeSpecialPowerTimer8>::iterator it=timerList.begin();it!=timerList.end();++it){xfer->word(&it->templateID);xfer->word(&it->readyFrame);}
  } else {
   if(FIELD(_STL::list<BfmeSpecialPowerTimer8>,0x704).size()!=0)badPlayerTransfer();
   for(i=0;i<timerCount;++i){BfmeSpecialPowerTimer8 timer;timer.readyFrame=~0u;timer.templateID=0;xfer->word(&timer.templateID);xfer->word(&timer.readyFrame);FIELD(_STL::list<BfmeSpecialPowerTimer8>,0x704).push_back(timer);}
  }
  squadCount=10;xfer->ushort(&squadCount);if(squadCount!=10)badPlayerTransfer();
  for(unsigned short i=0;i<squadCount;++i){void *squad=FIELD(void*,0x708+4*i);if(!squad)badPlayerTransfer();xfer->snapshot(squad);}
  bool hasSelection=FIELD(Squad*,0x730)!=0;xfer->boolean(&hasSelection);
  if(hasSelection){if(!FIELD(Squad*,0x730)&&xfer->loading())FIELD(Squad*,0x730)=allocatePlayerPart<Squad>();xfer->snapshot(FIELD(Squad*,0x730));}
 }
 bool hasBonuses=FIELD(Rva002AA14DBonuses*,0xB8)!=0;xfer->boolean(&hasBonuses);
 if(xfer->loading()){if(FIELD(Rva002AA14DBonuses*,0xB8))delete FIELD(Rva002AA14DBonuses*,0xB8);FIELD(Rva002AA14DBonuses*,0xB8)=0;if(hasBonuses)FIELD(Rva002AA14DBonuses*,0xB8)=allocatePlayerPart<Rva002AA14DBonuses>();}
 if(FIELD(Rva002AA14DBonuses*,0xB8)){
  xfer->real(&FIELD(Rva002AA14DBonuses*,0xB8)->armor);xfer->real(&FIELD(Rva002AA14DBonuses*,0xB8)->sight);
  xfer->integer(&FIELD(Rva002AA14DBonuses*,0xB8)->bombard);xfer->integer(&FIELD(Rva002AA14DBonuses*,0xB8)->hold);xfer->integer(&FIELD(Rva002AA14DBonuses*,0xB8)->search);
  FIELD(Rva002AA14DBonuses*,0xB8)->valid.xfer(raw);FIELD(Rva002AA14DBonuses*,0xB8)->invalid.xfer(raw);
 }
 INT(0xAC);INT(0xB0);INT(0xB4);
 if(!xfer->lightCRC()) {
  BOOL(0x33D);SNAP(0x318);xfer->real(&FIELD(float,0x314));FIELD(PlayerTrackerView,0x738).transfer(raw);
  Rva002AC1A9XferList(raw,&FIELD(_STL::list<short>,0x700));xfer->word(&FIELD(unsigned,0x354));
  if(version.value>=4){rva002AF236(raw,&FIELD(Rva001FDE3F,0x294));rva002AF236(raw,&FIELD(Rva001FDE3F,0x2A8));rva002AF33B(raw,&FIELD(Rva002AE4C5,0x2BC));}
  if(version.value>=7)XferOrderMode(raw,&FIELD(int,0x750));
  if(version.value>=10) {
   _STL::vector<BfmeVectorRecord002AF478>&records=FIELD(_STL::vector<BfmeVectorRecord002AF478>,0x3B0);
   unsigned count=records.size();xfer->word(&count);
   for(i=0;i<count;++i) {
    if(xfer->loading()){PlayerTransferRecord record;reinterpret_cast<Rva002B0A05*>(&record)->rva002B0A05(raw);records.push_back(*reinterpret_cast<BfmeVectorRecord002AF478*>(&record));}
    else reinterpret_cast<Rva002B0A05*>(&records[i])->rva002B0A05(raw);
   }
  }
 }
}
