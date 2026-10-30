// BF1 donor9cbfb551fe20dae985f91f2319d8997287b6a705 Rva003A3A90.cpp and
// Rva003A3B50RecordAppend.cpp supply the184B record/vector semantic lead.
// Native312EDA..313008 proves this complete302B linked-input import operation:
// clear vector2C then reset/append first node; merge nodes within squared100
// into the last record otherwise append. Existing record constructor3118DF
// reset311431 assignment311537 destructor89851 and vector providers all rowed.
// Target destructor8B77D stores BC7514 with slot1=312EDA; retain its existing
// address owner. Prefix and input-node views are partial, no allocating layout.
// Input next20/count4C and coordinateC/10/14 are direct target facts; spline
// role inferred from matched184B family. Original application names unknown.
// Full bytes plus EH verified. No corresponding clean ZH spline service body.
// cl: /O1 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /DWIN32 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc/stl
// stlport
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
// The bfmealloc allocator of the Rva003A35A0Element.cpp sibling, which emits the retail
// vector<Rva003A35A0Element> allocator and _M_clear copies.
#include <cstddef>
#include "_alloc.h"
#include <vector>
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
struct Rva00311431Arg {
 unsigned unknown00,word04,word08;float x,y,z;char pad18[8];Rva00311431Arg *next20;char pad24[0x4c-0x24];int count4c;
 Rva00311431Arg *next()const{return count4c>0?next20:0;}
};
struct Rva003A35A0Element {
 Rva003A35A0Element();Rva003A35A0Element(const Rva003A35A0Element&);~Rva003A35A0Element();
 Rva003A35A0Element &operator=(const Rva003A35A0Element&);
 Rva003A35A0Element *rva00311431(const Rva00311431Arg*);
 char bytes[184];
};
class Rva008B77D {public:
 virtual void rva00312EDA(const Rva00311431Arg*);
 char m_pad04[0x2c - 4];_STL::vector<Rva003A35A0Element>records;

};
void Rva008B77D::rva00312EDA(const Rva00311431Arg*node) {
 records.clear();
 if(node){
 Rva003A35A0Element record;
 record.rva00311431(node);records.push_back(record);
 while(1) {
  float x=node->x,y=node->y,z=node->z;
  node=node->next();if(!node)break;
  x-=node->x;y-=node->y;z-=node->z;
  float distance=z*z+y*y+x*x;
  if(100.0f>distance)records[records.size()-1]=*record.rva00311431(node);
  else{record.rva00311431(node);records.push_back(record);}
 }
 }
}
