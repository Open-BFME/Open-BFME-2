// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
// Target0x000D18F8..0x000D19DD belongs to the W3DTornadoDraw family:
// adjacent destructor/vtable slot4 names the class (existing Dtor evidence).
// BF1 f989/ZH RadiusDecal creation is the semantic guide; no matching named
// Tornado source was found. Target bytes establish Drawable +FC object,
// this+8 Drawable, this+C list, template+24 radius bound and unsigned count.
#include <list>
#include "Coord3D.h"
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
class RadiusDecalTemplate {
public:
 void createRadiusDecal(const Coord3D&,float,const Player*,RadiusDecal&) const;
 unsigned char pad[0x24]; float maxRadius;
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
 float maximum=type->maxRadius;
 if(maximum>radius) { bound=radius; _ReadWriteBarrier(); }
 else bound=type->maxRadius;
 for(int i=0;i<count;++i) {
  RadiusDecal *decal=new RadiusDecal;
  decal->clear();
  type->createRadiusDecal(position,i*bound/count,object->getControllingPlayer(),*decal);
  decals.push_back(reinterpret_cast<const int&>(decal));
 }
}
