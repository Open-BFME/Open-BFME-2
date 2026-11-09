// cl: /D_CRTIMP= /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??0Rva0052B278@@QAE@PAX00@Z, retail 0x0052b278, 314 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
extern "C" const void *const __identifier("??_7Rva0052B3B2@@6B@")[];  // vftable 0x00C685E0

namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// The pointer-vector reserve folds to the rowed vector<const ModuleData *>
// body 0x002B712E (ModuleFactoryVectorReserve.cpp); calls bind there.
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::reserve(size_t n); }
#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"


class Rva0053947D {public:Rva0053947D(void *,const Vector3 *);virtual ~Rva0053947D();};
class Rva00539411 {
public:
 // retail calls the rowed base constructor 0x00539411 (Rva0053947DDtor.cpp)
 __declspec(dllimport) __forceinline Rva00539411(void *lookup,const int *pos) {((Rva0053947D *)this)->Rva0053947D::Rva0053947D(lookup,(const Vector3 *)pos);}
 __forceinline ~Rva00539411() {((Rva0053947D *)this)->Rva0053947D::~Rva0053947D();}
 unsigned m_vtable;
 char m_rest[0x28];
};
struct Arg1Host005C4280;
class Rva005C4230 {
public:
 Rva005C4230(void *,Arg1Host005C4280 *);
 virtual ~Rva005C4230();
 virtual void f01();virtual void f02();virtual void f03();
 virtual void f04();virtual void f05();virtual void f06();
 virtual void setPosition(const Vector3 *);
 char rest[0xc4];
};
struct IconSubTemplate {char pad[0x1c];float height;};
struct IconTemplate {void *name;_STL::vector<IconSubTemplate *> items;};
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct IconHelpRef {
 TargetRef00217D4C *ptr;
 IconHelpRef():ptr(0){}
 ~IconHelpRef() {if(ptr) ReleaseTreeHintRef00217D4C(ptr);}
};
class Rva002BF4F3 {public:bool rva002BF5B0(const Vector3 *,Vector3 *);};
class Rva002D3627Host;
class LivingWorld; extern LivingWorld *TheLivingWorld;
class Rva005392C2 {public:void rva0052B045();};
class Rva0052B278:public Rva00539411 {
 _STL::vector<Rva005C4230 *> items;
 void *parent;int id;IconHelpRef help;
public:Rva0052B278(void *,void *,void *);
};
Rva0052B278::Rva0052B278(void *lookup,void *owner,void *point)
 :Rva00539411(lookup,(const int *)&Vector3()),items((m_vtable=((unsigned int)__identifier("??_7Rva0052B3B2@@6B@")),_STL::allocator<Rva005C4230 *>())),parent(owner),id(-1)
{

 const Vector3 *xy=(const Vector3 *)point;
 Vector3 position;
 position.X=xy->X;position.Y=xy->Y;position.Z=0;
 ((Rva002BF4F3 *)((Rva002D3627Host *)TheLivingWorld))->rva002BF5B0(xy,&position);
 // Retain the original12B block copy through the existing POD storage view.
 *(Coord3D *)((char *)this+0x18)=*(const Coord3D *)&position;
 IconTemplate *source=(IconTemplate *)lookup;
 if(source) {
  ((_STL::vector<const ModuleData *> *)&items)->reserve(source->items.size());
  IconSubTemplate **it=source->items.begin();
  IconSubTemplate **end=source->items.end();
  for(;it!=end;++it) {
   Rva005C4230 *part=new Rva005C4230(*it,(Arg1Host005C4280 *)this);
   items.push_back(part);
   Vector3 offset(position.X,position.Y,position.Z);
   offset.Z+=(*it)->height;
   items.back()->setPosition(&offset);
  }
 }
 ((Rva005392C2 *)this)->rva0052B045();
}
