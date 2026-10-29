// cl: /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// LivingWorldBuilding constructor, retail 0x004E119C (288 B).
// Facts from target evidence: layout (+8 holder vector, +18 id, +1C/+20 -1, +24 region, +28 template, +2C 0,
// +30 nugget vector, +3C army-entry holder, +48 position, +50/+51 bytes), the RegionTurnObserverView base, the
// Snapshot vptrs and the callee rows 0x002E00F9 / 0x004E08F6 / 0x004E0809 / 0x005A0B4C come from the native body and the
// matched LivingWorldBuilding::DoXfer neighbour (LivingWorldBuildingDoXfer.cpp). Coord2D is the non-POD view
// (Lib/Coord2DCtorView.h: retail exports Coord2D's user copy constructor 0x005CFBC2), so m_position(position) is the
// inlined constructor's scalar copy. Structural inference, not a donor fact: the equal-arm ternaries at the
// rva002E00F9 call and the army test reproduce retail's operand and register order.
#include "ascii_string.h"
// stlport
#include <vector>
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "Common/Snapshot.h"
#include "Lib/Coord2DCtorView.h"
void Rva00030830FreeAllocation(void*);
#include "Lib/BfmeE16.h"
namespace _STL{
template<>void allocator<BfmeE16>::deallocate(pointer p,size_type)const{Rva00030830FreeAllocation(p);}
template<>__declspec(nothrow) __declspec(noinline) _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0){}
}
struct Header:public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >{
 __forceinline Header():_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()){}
};
class Rva00330757Member:public Header{public:__declspec(noinline) Rva00330757Member();__forceinline ~Rva00330757Member(){}int flag;};
inline Rva00330757Member::Rva00330757Member(){flag|=-1;}
class Rva004EDFFFDwordImmSetter {public:void apply();};
#include "../../../../Include/Common/RegionTurnObserverView.h"

class Xfer;

class Rva0052B17F
{
public:
	void rva0052B17F();
};

struct Rva004E0790Inner;
class ArmySummaryEntry
{
public:
	ArmySummaryEntry();
	char m_pad[0xC8];
};
class Rva004E0790
{
public:
	void rva004E0790();
	void rva004E08F6(Rva004E0790Inner *p);
};
struct ArmySummaryEntryRef
{
	__forceinline ArmySummaryEntryRef():m_ptr(0) {}
	~ArmySummaryEntryRef();
	Rva004E0790Inner *m_ptr;
};

struct BuildingNuggetTemplateView
{
	char m_pad00[4];
	AsciiString m_name;
};
struct BuildingNuggetView
{
	char m_pad00[8];
	BuildingNuggetTemplateView *m_template;
	BuildingNuggetTemplateView *getTemplate() const { return m_template; }
};
class LivingWorldRegion
{
public:
	char m_pad00[0x12C];
	int m_id;
};

class LivingWorldBuilding:public Snapshot,public Rva00330757Member,public RegionTurnObserverView
{
public:
	LivingWorldBuilding(LivingWorldRegion *,const Coord2D &,const struct Rva003F1BD3TemplateView *,int);
 virtual ~LivingWorldBuilding();
 virtual void BeginTurn(int,int);
 virtual void LoadPostProcess();
 virtual const char *GetSnapshotName();
 virtual void DoXfer(Xfer *xfer);
 void createIcon();
 void rva004E060C(unsigned char v);
 void rva004E0809();

	
	int m_id;
	int m_1C;
	int m_20;
	LivingWorldRegion *m_region;
	const AsciiString *m_template;
	Rva0052B17F *m_2C;
	_STL::vector<BuildingNuggetView *> m_nuggets;
	ArmySummaryEntryRef m_armyEntry;
	int word40,word44;
	Coord2D m_position;
	bool m_pad50;
	bool m_51;
};

struct Rva003F1BD3TemplateView {char opaque00[9];bool army;char pad0A[2];AsciiString armyType;};
struct Rva002BA8F1Listener;
class Rva005A0B4CList{public:void append(Rva002BA8F1Listener*);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva002E00F9 {public:void rva002E00F9(void*,void*);};
LivingWorldBuilding::LivingWorldBuilding(LivingWorldRegion *region,const Coord2D &position,const Rva003F1BD3TemplateView *definition,int id)
 :m_id(id),m_1C(-1),m_20(-1),m_region(region),m_template((const AsciiString*)definition),m_2C(0),m_nuggets(_STL::allocator<BuildingNuggetView*>()),word40(0),word44(0),m_position(position),m_pad50(false),m_51(false)
{
 createIcon();
 ((Rva002E00F9*)m_template)->rva002E00F9(this,(m_template ? &m_nuggets : &m_nuggets));
 const Rva003F1BD3TemplateView *d=(const Rva003F1BD3TemplateView*)m_template;
 if((d->army ? d->army : d->army) && !((const StringBase<char>*)&d->armyType)->isEmpty()) {
  ((Rva004E0790 *)&m_armyEntry)->rva004E08F6((Rva004E0790Inner*)new ArmySummaryEntry);
  ((StringBase<char>*)((char*)m_armyEntry.m_ptr+4))->set(*(const StringBase<char>*)&((const Rva003F1BD3TemplateView*)m_template)->armyType);
  *(int*)((char*)m_armyEntry.m_ptr+0xB4)=m_id;
 }
 rva004E0809();
 ((Rva005A0B4CList*)((char*)TheLivingWorldLogic+0x1C))->append((Rva002BA8F1Listener*)(RegionTurnObserverView*)this);
}
