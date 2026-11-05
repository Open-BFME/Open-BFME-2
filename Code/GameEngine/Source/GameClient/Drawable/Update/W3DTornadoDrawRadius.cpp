// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/bfmelist
// stlport
// Target0x000D18F8..0x000D19DD belongs to the W3DTornadoDraw family:
// adjacent destructor/vtable slot4 names the class (existing Dtor evidence).
// BF1 f989/ZH RadiusDecal creation is the semantic guide; no matching named
// Tornado source was found. Target bytes establish Drawable +FC object,
// this+8 Drawable, this+C list, template+24 radius bound and unsigned count.
#include <list>
#include "Coord3D.h"
#include "../../../../Include/GameClient/RadiusDecalTemplate.h"

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Player;
class Object { public: Player *getControllingPlayer() const; };
class Shadow;
class RadiusDecal {
public:
 RadiusDecal(); void clear();
 const void *data; Shadow *decal; bool empty; float previousFrame;
};
struct TornadoDrawableView { unsigned char pad[0xFC]; Object *object; };
class W3DTornadoDraw {
public:
 virtual ~W3DTornadoDraw();
 void rva000D18F8(const RadiusDecalTemplate*,float,const Coord3D&,unsigned);
 void *moduleData;
 TornadoDrawableView *drawable;
 // The existing destructor uses list<int>; pointer bits are the verified
 // native 32-bit list payload and the same established append ABI.
 _STL::list<int> decals;
};
void W3DTornadoDraw::rva000D18F8(const RadiusDecalTemplate *type,float radius,const Coord3D &position,unsigned count)
{
 Object *object=drawable->object;
 if(!object) return;
 if(count<=0) return;
 volatile float bound;
 float maximum=type->m_unmodelled24;
 if(maximum>radius) { bound=radius; _ReadWriteBarrier(); }
 else bound=type->m_unmodelled24;
 for(int i=0;i<count;++i) {
  RadiusDecal *decal=new RadiusDecal;
  decal->clear();
  type->createRadiusDecal(position,i*bound/count,object->getControllingPlayer(),*decal);
  decals.push_back(reinterpret_cast<const int&>(decal));
 }
}
