// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// LivingWorldPlayer physical owner retained as Rva002E2AAE for existing
// callers. Native constructor calls and table C04B50's
// LivingWorldPlayer name slot establish identity. Retail supplies all member
// offsets and 0x3C8 size; donor names alone do not establish target layout.
// Both constructors, destructor, serializer and complete primary table share
// this one physical view. EH cleanup names resolve to whole verified owners:
// LWPlayerDef, RegionBonusInfo, LivingWorldScoreKeeper, record vector and sets.
// C memset is nothrow: /EHs retains native member-destructor transitions while
// omitting a spurious state before its final nonthrowing initialization calls.
// See reverse/attempt_evidence/player-owners-astra-high-d-20261012.txt.
// cl: /O1 /G7 /arch:SSE /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /ICode/Libraries/Include/Lib /Ireference/shims/bfmealloc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// stlport
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include <vector>
#include "ascii_string.h"
#include <set>
#include <string.h>
extern "C" __declspec(nothrow) void *__cdecl memset(void*,int,unsigned int);
void Rva00030830FreeAllocation(void*);
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/FixedStorage128.h"
class AsciiString; class UnicodeString; class PooledString; class Coord3DBase; class ICoord3D; class Region3D; class IRegion3D; class Coord2D; class ICoord2D; class Region2D; class IRegion2D; class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot; class XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
#include "RGBColor.h"
namespace _STL{
template<>__declspec(dllimport) __forceinline void allocator<BfmeE16>::deallocate(pointer p,size_type)const{Rva00030830FreeAllocation(p);}
template<>__declspec(dllimport) __forceinline void _STLP_alloc_proxy<BfmeE16*,BfmeE16,allocator<BfmeE16> >::deallocate(BfmeE16*p,size_t n){allocator<BfmeE16>::deallocate(p,n);}
template<>__declspec(nothrow) __declspec(noinline) _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0){}
}
struct Header:public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >{
 __forceinline Header():_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()){}
};
class Rva00330757Member:public Header{public:__declspec(noinline) Rva00330757Member();__forceinline ~Rva00330757Member(){}int flag;};
inline Rva00330757Member::Rva00330757Member(){flag|=-1;}

struct Rva002BA8F1Input { char unknown00[36]; bool flag; };

class LWPlayerDef:public Snapshot {public:__declspec(nothrow) LWPlayerDef();LWPlayerDef(const LWPlayerDef&);virtual ~LWPlayerDef();protected:virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);private:char bytes[36];};
class LivingWorldAI { public: LivingWorldAI(); ~LivingWorldAI(); char bytes[308]; };
class Rva001EAE6FHelper { public: __declspec(nothrow) Rva001EAE6FHelper*clear80(); };
struct ClearStorage { char bytes[128]; ClearStorage(){ ((Rva001EAE6FHelper*)this)->clear80(); } };
struct LivingWorldArmy;
// Storage-only three-pointer header; application element identity stays at the consumer.
struct PlayerPointerArray:public Header {__forceinline PlayerPointerArray():Header(){} };
struct Color { float x,y,z; Color(float v):x(v),y(v),z(v){} };
class RegionBonusInfo:public Snapshot { public:__declspec(nothrow) RegionBonusInfo();virtual ~RegionBonusInfo(){};protected:virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);private:char bytes[24]; };

class LivingWorldPlayer;
class LivingWorldScoreKeeper:public Snapshot {public:
 LivingWorldScoreKeeper(int,LivingWorldPlayer*);virtual ~LivingWorldScoreKeeper();
 protected:virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);
 private:char bytes[248];};
struct Rva002E2690Element
{
public:
	char bytes[216]; // +0x00
};
namespace _STL {template<> vector<Rva002E2690Element>::~vector();}
class Rva002B317CBumpCounter {public:int bump();};
class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E15E6 {public:~Rva002E15E6();void rva002E15E6();};
typedef _STL::set<int> PlayerSetCtor;
class Rva002E1F83 {public:__forceinline Rva002E1F83(){((PlayerSetCtor*)this)->PlayerSetCtor::set();}__forceinline ~Rva002E1F83(){((Rva002E15E6*)this)->Rva002E15E6::~Rva002E15E6();}char bytes[12];};
class Rva002E2AAE : public Snapshot, public Rva00330757Member {
public:
 Rva002E2AAE(); Rva002E2AAE(Rva002BA8F1Input*,void*);
 virtual ~Rva002E2AAE();
 virtual void loadPostProcess(); virtual const char*GetSnapshotName()const; virtual void xfer(Xfer*);
 int id;
 LWPlayerDef input;
 void *p40; int kind; AsciiString zero48;
 LivingWorldAI ai;
 int colorIndex;Color color1,color2,color3;
 _STL::vector<Rva002E2690Element> records;AsciiString zero1B4;
 PlayerPointerArray armies;int zero1C4;float value1C8;
 _STL::vector<int> list1CC;
 ClearStorage storage;
 RegionBonusInfo member258,member274;
 int zero290,zero294,zero298;
 Rva002E1F83 set29C,set2A8;
 char zero2B4[16];unsigned int zero2C4;
 LivingWorldScoreKeeper member2C8;
 bool flag3C4,flag3C5;
};
Rva002E2AAE::Rva002E2AAE()
 : id(-1),p40(0),kind(0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,(LivingWorldPlayer*)(Rva00330757Member*)this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}
Rva002E2AAE::Rva002E2AAE(Rva002BA8F1Input*src,void*context)
 : id(((Rva002B317CBumpCounter*)TheLivingWorldLogic)->bump()),input(*(const LWPlayerDef*)src),p40(context),kind(src->flag?2:0),colorIndex(-1),color1(1.0f),color2(1.0f),color3(1.0f),zero1C4(0),value1C8(1.0f),zero290(0),zero294(0),zero298(0),zero2C4(0),member2C8(id,(LivingWorldPlayer*)(Rva00330757Member*)this),flag3C4(false),flag3C5(false)
 {memset(&storage,0,128);memset(zero2B4,0,16);}

class Rva002E1E51Listener {public:virtual void slot0(void*);virtual void slot1(void*);virtual void slot2(void*);virtual void notify(void*);};
class Rva002E1E51List {public:void forEach(void(Rva002E1E51Listener::*)(void*),void*);};
class Rva002E21D1 {public:void rva002E21D1();};
Rva002E2AAE::~Rva002E2AAE(){((Rva002E21D1*)this)->rva002E21D1();((Rva002E1E51List*)((char*)this+4))->forEach(&Rva002E1E51Listener::notify,this);}
class Rva002E18C3Lookup
{
public:
	AsciiString *find(const AsciiString &name);
};
extern Rva002E18C3Lookup *TheLivingWorldAITemplateStore;
struct Rva004FB303Target;
class Rva004FB222Owner {public:void rva004FB222(Rva004FB303Target*,int);};
void Rva002E2AAE::loadPostProcess(){AsciiString*asciiString=TheLivingWorldAITemplateStore->find(zero48);if(!asciiString)return;((Rva004FB222Owner*)&ai)->rva004FB222((Rva004FB303Target*)this,(int)asciiString);}
const char *Rva002E2AAE::GetSnapshotName()const{return "LivingWorldPlayer";}
typedef char PlayerSize[sizeof(Rva002E2AAE)==0x3c8?1:-1];


class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class XferException {
public:
 XferException(int,const char*,...);
 XferException(const XferException&);
 ~XferException();
 char *text; int tag;
};
Xfer *Rva002E07FAXfer(Xfer*,unsigned int*);
class INIException {public: INIException(int,const char*,...); INIException(const INIException&); ~INIException(); char *text; int tag;};

extern Rva002E18C3Lookup *TheLivingWorldPlayerTemplateStore;
class ModuleData;
class Rva00291440;
void XferLivingWorldPlayerID(Xfer*,int*);
void XferOwningLivingWorldArmyVec(Xfer*,std::vector<const ModuleData*>*);
Xfer *Rva001ECA2DXfer(Xfer*,void*);
void xferUpgradeMask(Xfer*,Rva00291440*);

Xfer *Rva002E208AXfer(Xfer*,std::set<int>*);
enum ScienceType {SCIENCE_INVALID=-1};

struct Rva002E26E1Record
{
public:
	char m_pad00[0xD8];
};
struct Rva002E2D10Record
{
public:
	char m_pad00[0xD8];
};
struct BfmeFixedStorage128;
class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(const UnitRevivalEntry &);
	~UnitRevivalEntry();
	void *getThingTemplate();
	void rva0037E473(Xfer*);
	char m_pad00[0x8];
	float experience; // +0x08
	int rank; // +0x0C
	int level; // +0x10
	BfmeFixedStorage128 upgrades; // +0x14
	unsigned int cost; // +0x94
	int startFrame; // +0x98
	unsigned int time; // +0x9C
	bool revival; // +0xA0
	bool flagA1; // +0xA1
	char m_padA2[0x2];
	int productionID; // +0xA4
	int armyID; // +0xA8
	int key; // +0xAC
	char record[0x18]; // +0xB0
	int valueC8; // +0xC8
	float factor; // +0xCC
	char textD0[8]; // +0xD0
};
namespace _STL {
 template<> ScienceType *vector<ScienceType>::erase(ScienceType*,ScienceType*);
 template<> Rva002E2690Element *vector<Rva002E2690Element>::erase(Rva002E2690Element*,Rva002E2690Element*);
 template<> void vector<Rva002E26E1Record>::reserve(unsigned int);
 template<> void vector<Rva002E2D10Record>::push_back(const Rva002E2D10Record&);
}

void Rva002E2AAE::xfer(Xfer *xfer) {
 Xfer::Version version(1,5); *xfer == version;
 XferLivingWorldPlayerID(xfer,&id);
 *xfer == *reinterpret_cast<Snapshot*>(&input);
 if(xfer->IsLoading()) {
  AsciiString name;
  *xfer == name;
  p40=TheLivingWorldPlayerTemplateStore->find(name);
  if(!p40) throw INIException(3,"A Player template for this LivingWorldPlayer could not be found (was it removed from an INI?)");
 } else {
  AsciiString name=*(AsciiString*)p40;
  *xfer == name;
 }
 *xfer == flag3C4;
 int stateValue=kind; *xfer == stateValue; kind=stateValue;
 *xfer == zero48;
 XferOwningLivingWorldArmyVec(xfer,reinterpret_cast<std::vector<const ModuleData*>*>(&armies));
 {
  std::vector<ScienceType> &scienceVec=*reinterpret_cast<std::vector<ScienceType>*>(&list1CC);
  Xfer::Version sv(1,1); *xfer == sv;
  if(xfer->IsLoading()) scienceVec.erase(scienceVec.begin(),scienceVec.end());
  Rva001ECA2DXfer(xfer,&scienceVec);
 }
 *xfer == zero1B4; *xfer == value1C8; *xfer == zero1C4;
 xferUpgradeMask(xfer,reinterpret_cast<Rva00291440*>(&storage));
 *xfer == zero290; *xfer == zero294;
 *xfer == *reinterpret_cast<Snapshot*>(&member258);
 *xfer == *reinterpret_cast<Snapshot*>(&member274);
 if(version.m_minimum>=4) *xfer == zero298;
 *xfer == colorIndex;
 *xfer == *reinterpret_cast<RGBColor*>(&color1); *xfer == *reinterpret_cast<RGBColor*>(&color2); *xfer == *reinterpret_cast<RGBColor*>(&color3);
 if(version.m_minimum>=2) {
  *xfer == *reinterpret_cast<Snapshot*>(&member2C8);
  if(version.m_minimum>=3) {
   *xfer == zero2C4;
   if(xfer->IsLoading() && kind==1) zero2C4=0;
  }
 }
 if(xfer->IsLoading()) {
  int count=0; *xfer == count;
  std::vector<Rva002E2690Element> &eraseView=*reinterpret_cast<std::vector<Rva002E2690Element>*>(&records);
  eraseView.erase(eraseView.begin(),eraseView.end());
  reinterpret_cast<std::vector<Rva002E26E1Record>*>(&records)->reserve(count);
  for(int i=0;i<count;++i) {
   UnitRevivalEntry entry;
   entry.rva0037E473(xfer);
   reinterpret_cast<std::vector<Rva002E2D10Record>*>(&records)->push_back(reinterpret_cast<const Rva002E2D10Record&>(entry));
  }
 } else {
  int count=records.size(); *xfer == count;
  for(int i=0;i<count;++i) reinterpret_cast<UnitRevivalEntry*>(&records[i])->rva0037E473(xfer);
 }
 Rva002E07FAXfer(xfer,(unsigned int*)zero2B4);
 if(version.m_minimum>=5) {
  if(xfer->IsLoading()) {
   reinterpret_cast<Rva002E15E6*>(&set29C)->rva002E15E6();
   reinterpret_cast<Rva002E15E6*>(&set2A8)->rva002E15E6();
  }
  Rva002E208AXfer(xfer,reinterpret_cast<std::set<int>*>(&set29C)); Rva002E208AXfer(xfer,reinterpret_cast<std::set<int>*>(&set2A8));
 }
}

// --- 0x002E25D9 (57 B, RET 0): the science-vector transfer block of
// Rva002E2AAE::xfer above as its own file-static helper (version 1,1; clear on
// load; Rva001ECA2DXfer). Retail passes the Xfer in ESI and the vector in EDI,
// the private convention cl 7.1 picks for a file-static noinline function; no
// retail call reaches this copy (its caller was folded away), so a source-only
// caller emits it.
static __declspec(noinline) void Rva002E25D9XferScienceVec(Xfer *xfer, std::vector<ScienceType> *sciences)
{
 Xfer::Version version(1,1); *xfer == version;
 if(xfer->IsLoading()) sciences->erase(sciences->begin(),sciences->end());
 Rva001ECA2DXfer(xfer,sciences);
}

// ?Rva002E25D9XferScienceVecCaller absent-from-retail
void Rva002E25D9XferScienceVecCaller(Xfer *xfer, std::vector<ScienceType> *sciences)
{
 Rva002E25D9XferScienceVec(xfer,sciences);
}
