// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /O1 /EHs /MD /arch:SSE /ICode/Libraries/Include/Lib /D_STLP_USE_STATIC_LIB
// stlport
// Complete334B constructor3F3967..3F3AB5 RET12. Target parser210620
// independently allocates1B4 and passes definition owner/id/name. Existing
// scalar deleting dtor3F36EC and four-slot Snapshot vtableC36FA4 establish
// the LivingWorldRegion receiver. Region14 owns the118B descriptor,
// whose constructor542 and destructor545 are independently verified.
// BF1 f989 region constructor is a semantic guide only; BF2 MI observer
// base4/id12C/owner130 and six tail headers are all target evidence.
// Visible actual29B header init and23B observer ctor are byte/relocation
// twins of existing owners, enabling removal of a redundant base vptr.
// Header stand-in types describe three-pointer storage only. The native
//63B destructors at180/18C and1A8 remain their existing neutral owners.
// Child ctor76 only stores and erases pointers, supporting nothrow.
// Destructor234 adds the target-proven child30 cleanup and owned-list74
// reset before automatic reverse member/base teardown. Outer header frees
// use the existing C++ allocator spelling for four native EH transitions;
// child cleanup preserves the observed C-call context. Full ctor334 stays exact.
// The name getter in slot 2 identifies the region; member names remain neutral.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport, and <stddef.h> with it so
// their _errno declarations agree. /EHs lets free throw, preserving
// retail's unwind states.
#define _CRTIMP
#include <stddef.h>
#include <stdlib.h>
#undef _CRTIMP

#include <vector>
#include "ascii_string.h"
#include "Coord2D.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define xfer DoXfer
#include "Common/Snapshot.h"
#undef xfer
void Rva00030830FreeAllocation(void*);
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
namespace _STL{template<>void allocator<BfmeE16>::deallocate(pointer p,size_type)const{Rva00030830FreeAllocation(p);}template<>__declspec(nothrow) __declspec(noinline) _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&a):_M_start(0),_M_finish(0),_M_end_of_storage(a,0){}}
struct Header:public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >{using _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_M_start;using _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_M_finish;__forceinline Header():_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()){} };
class Rva00330757Member:public Header{public:__declspec(noinline) Rva00330757Member();__forceinline ~Rva00330757Member(){}int flag;};
inline Rva00330757Member::Rva00330757Member(){flag|=-1;}
class Rva003F2D03{public:Rva003F2D03(const AsciiString&);~Rva003F2D03();char bytes[0x118];};
class Gen_uwm_003f30d1:public Header{public:__forceinline Gen_uwm_003f30d1(){}~Gen_uwm_003f30d1();};
class Rva003F1797:public Header{public:__forceinline Rva003F1797(){}~Rva003F1797();};
struct RegionChildHeader{void*start,*finish,*end;~RegionChildHeader(){if(start)free(start);}};
class Rva003F1F6A{public:__declspec(nothrow) Rva003F1F6A(void*);void*owner;RegionChildHeader header;int value10,value14,id;float x,y,z;int value28;bool flag2c;};
enum ScienceType{RegionOpaqueScienceValue=0};
namespace _STL{template<>ScienceType*vector<ScienceType>::erase(ScienceType*,ScienceType*);}
struct RegionZeroCoord:public Coord2D{__forceinline RegionZeroCoord(){x=0;y=0;}};
class LivingWorldRegion:public Snapshot,public Rva00330757Member{
public:LivingWorldRegion(void*owner,int id,const AsciiString&name);virtual~LivingWorldRegion();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void DoXfer(Xfer*);
Rva003F2D03 definition;
int id;void*owner;int value134,value138;int ownerID,otherID;RegionZeroCoord position;int value14c,value150,value154;
Header values158,values164,plots;int plotIndex;Gen_uwm_003f30d1 values180,values18c;Rva003F1F6A *child;int value19c;bool flag1a0,flag1a1,flag1a2,flag1a3,flag1a4;Rva003F1797 values1a8;
};
typedef char SizeCheck[sizeof(LivingWorldRegion)==0x1b4?1:-1];
LivingWorldRegion::LivingWorldRegion(void*owner_,int id_,const AsciiString&name):definition(name),id(id_),owner(owner_),value134(0),value138(0),ownerID(-1),otherID(-1),value14c(0),value150(0),value154(0),plotIndex(0),value19c(0),flag1a0(false),flag1a1(false),flag1a2(false),flag1a3(false),flag1a4(false){
child=new Rva003F1F6A((void*)id_);
_STL::vector<ScienceType>*v=(_STL::vector<ScienceType>*)&values158;v->erase(v->begin(),v->end());
}

// 0x003F2106 is rowed as Rva003F2106::rva003F2106 (Rva002B7B71DeleteAll.cpp).
#include "../../../../Include/Common/Rva003F2106.h"
LivingWorldRegion::~LivingWorldRegion(){delete child;child=0;((Rva003F2106*)this)->rva003F2106();}
