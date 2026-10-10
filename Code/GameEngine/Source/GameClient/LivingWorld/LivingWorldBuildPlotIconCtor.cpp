// cl: /O1 /arch:SSE /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// Target59E10F..59E240, full307B RET12. Existing CreateIcon REL32 pin and
// WB14D96C0 LivingWorldBuildPlotIcon.cpp:31..62 identify this constructor.
// Transfer guide: verified Rva0052B278 constructor, with the same base539411,
// projection2BF5B0 and pointer-vector providers. Retail proves the different
// vptrC70F88, parent38, owner guard and child constructor5DB271. No id/help
// fields or final refresh call from the sibling are carried across.
// Template fields and subobject slot1C are wire views; their source names and
// original inheritance are not claimed. The child opaque sizeC8 is independently
// established by this NEW allocation and its owned168B constructor fields.
// Vector3's empty default constructor follows WWMath source; the base argument
// is an uninitialized temporary in retail. Coord2D uses the canonical header.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "Coord2D.h"
class Vector3 {
public:
 Vector3() {}
 Vector3(float x,float y,float z):X(x),Y(y),Z(z){}
 float X,Y,Z;
};
class Rva0053947D {public:virtual ~Rva0053947D();};
class Rva00539411 {
public:
 Rva00539411(void *,const int *);
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
class Rva002BF4F3 {public:bool rva002BF5B0(const Vector3 *,Vector3 *);};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;


struct Arg1Host005DB271;
// Call-only view of the existing constructor owner.
class LivingWorldBuildPlotIconSubObject {public: LivingWorldBuildPlotIconSubObject(void *,Arg1Host005DB271 *);private:char storage[0xC8];};
class LivingWorldBuildPlotIconTemplate;
class LivingWorldBuildPlot;

class LivingWorldBuildPlotIcon:public Rva00539411 {
 _STL::vector<Rva005C4230 *> items;
 LivingWorldBuildPlot *parent;
public:LivingWorldBuildPlotIcon(LivingWorldBuildPlotIconTemplate *,LivingWorldBuildPlot *,const Coord2D &);
};
LivingWorldBuildPlotIcon::LivingWorldBuildPlotIcon(LivingWorldBuildPlotIconTemplate *lookup,LivingWorldBuildPlot *owner,const Coord2D &point)
 :Rva00539411(lookup,(const int *)&Vector3()),items((m_vtable=0x00c70f88,_STL::allocator<Rva005C4230 *>())),parent(owner)
{
 if(owner) {
 const Vector3 *xy=(const Vector3 *)&point;
 Vector3 position;
 position.X=xy->X;position.Y=xy->Y;position.Z=0;
 ((Rva002BF4F3 *)g_00DFEF18)->rva002BF5B0(xy,&position);
 *(Vector3 *)((char *)this+0x18)=position;
 IconTemplate *source=(IconTemplate *)lookup;
 if(source) {
  items.reserve(source->items.size());
  IconSubTemplate **it=source->items.begin();
  IconSubTemplate **end=source->items.end();
  for(;it!=end;++it) {
   LivingWorldBuildPlotIconSubObject *part=new LivingWorldBuildPlotIconSubObject(*it,(Arg1Host005DB271 *)this);
   // Both subobject families expose the same independently observed slot1C.
   items.push_back((Rva005C4230 *)part);
   Vector3 offset(position.X,position.Y,position.Z);
   offset.Z+=(*it)->height;
   items.back()->setPosition(&offset);
  }
 }
 }
}
