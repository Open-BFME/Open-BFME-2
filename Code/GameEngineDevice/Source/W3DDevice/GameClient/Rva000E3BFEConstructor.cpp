// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2renderobj /DNDEBUG /DBFME_SNAPSHOT_NAME_SLOT /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/shims/moduledata/Common
// stlport
// NativeE3BFE..E3CC5 complete199 RET4; base6C9CF and four derived
// vptr stores prove construction of a terrain-render-object subtype. The
// original derived name remains unknown; ZH HeightMap.cpp ctor is a semantic
// guide for terrain singleton initialization, not proof of that class name.
// Native proves parent3884, bool38A8, initialized words3884..3894,
// 12-byte headers38B4/38C4 and eight12-byte array entries38D0.
// Header38B4 uses the existing19B initializer view (no element identity
// asserted); vector-base18B contains only nonthrowing zero/proxy setup.
// Array entries remain opaque and uninitialized: the native callback is the
// 3-byte MOV EAX,ECX; RET constructor fold. Its emitted twin is rowed with
// zero unique-byte credit. Snapshot GetSnapshotName stays inherited.

#include <vector>
#include "rendobj.h"
#include "Snapshot.h"

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
struct Rva00174753Allocation:private _STL::_Vector_base<int,_STL::allocator<int> >{Rva00174753Allocation()throw();~Rva00174753Allocation();};
namespace _STL {template<>_Vector_base<int,allocator<int> >::_Vector_base(const allocator<int>&)throw();}
struct Rva000E3BFEArrayMember {Rva000E3BFEArrayMember();char data[12];};
class BfmeTaintModeView;extern BfmeTaintModeView*g_bfmeTaintModeView;
class Rva000E3B41:public BaseHeightMapRenderObjClass {
public:Rva000E3B41(bool);virtual~Rva000E3B41();
	virtual void Render(RenderInfoClass &rinfo);
	virtual void On_Frame_Update();
	virtual int initHeightData(int x, int y, WorldHeightMap *map, void *lights);
	virtual void vslot132();
	virtual void rva00069CE6(const Rva000E3A8D &cameras, int arg);
	virtual void doPartialUpdate(const IRegion2D &range, WorldHeightMap *map, RefRenderObjListIterator *iterator);
	virtual void vslot137(int forceUpdate);
	virtual void vslot139(bool value);
	virtual void vslot140(Rva00SlotQuad *out);
	virtual void vslot141(const BoundsFilterView *filter, AABoxClass *out);
	virtual void rva0006B804();
	virtual int vslot147();
	virtual void rva000E15D1();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();
void*ptr3884;void*ptr3888;void*ptr388c;void*ptr3890;void*ptr3894;
char unknown3898[0x10];bool flag38a8;char unknown38a9[11];
Rva00174753Allocation header38b4;bool flag38c0;char pad38c1[3];_STL::vector<int> header38c4;Rva000E3BFEArrayMember arr[8];bool flag3930;char pad3931[3];int word3934;void*ptr3938;
};
Rva000E3B41::Rva000E3B41(bool input):ptr3884(0),ptr3888(0),ptr388c(0),ptr3890(0),ptr3894(0),flag38a8(input),flag38c0(false){flag3930=false;word3934=0;ptr3938=0;g_bfmeTaintModeView=(BfmeTaintModeView*)this;}
__declspec(noinline) Rva000E3BFEArrayMember::Rva000E3BFEArrayMember(){}
