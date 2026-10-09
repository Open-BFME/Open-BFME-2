// ?allow@Rva00261D2EFilter@@QAE_NPAVObject@@@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Retail 00261D2E..00261F35, RET4. WB E5B6B0 is the same collision
// filter with target-specific bridge-kind and attachment geometry handling.
// Member offsets and virtual slots below are target facts. No original
// filter or module names are asserted by this address-derived view.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
typedef float Real;
class Object;
class ModuleData;
enum GeometryType { GEOMETRY_SPHERE, GEOMETRY_CYLINDER, GEOMETRY_BOX };
class GeometryInfo {
public:
 GeometryInfo(GeometryType, bool, Real, Real, Real);
 virtual ~GeometryInfo();
 bool bfmeIntersects(const Coord3D&, Real, const GeometryInfo&, const Coord3D&, Real) const;
private:
 char data04[0x58];
};
class ThingTemplate {
public:
 const ModuleData *rva0033B3D7() const;
 char data00[0xB0];
 Real radius;
 char dataB4[0x108-0xB4];
 unsigned char kinds[0x14];
};
class ModuleData { public: char data00[0x2C]; Real radius; };
class Rva000CBA20Point { public: Real x,y,z; };
class Rva000CBA20 { public: Real distSq(const Rva000CBA20Point*); };
struct Region2D { Coord2D lo,hi; bool rva000062FD(const Coord2D&,const Coord2D&) const; };
class Rva0087E370 { public: void method(const Coord3D&,Real,Region2D&) const; };
template<int N> class FilterSlots : public FilterSlots<N-1> {
public: virtual void unused(char(*)[N]);
};
template<> class FilterSlots<0> {};
class FilterGeometry : public FilterSlots<9> {
public: virtual bool slot24(Coord3D*,bool);
};
class FilterNested : public FilterSlots<29> {
public: virtual FilterGeometry *slot74();
};
class FilterModule : public FilterSlots<2> {
public:
 virtual FilterNested *slot08();
 virtual void s0C(); virtual void s10(); virtual void s14();
 virtual void s18(); virtual void s1C(); virtual void s20();
 virtual void s24(); virtual void s28(); virtual void s2C();
 virtual void s30(); virtual void s34(); virtual void s38();
 virtual void s3C(); virtual void s40(); virtual void s44();
 virtual void s48(); virtual void s4C();
 virtual FilterGeometry *slot50();
};
struct FilterModuleOwner { char data00[0xC]; FilterModule module; };
class Object {
public:
 virtual void unused();
 ThingTemplate *thingTemplate;
 char data08[0x38-8]; Coord3D position; Real angle;
 char data48[0xA8-0x48]; GeometryInfo geometry;
 char data104[0x244-0x104]; FilterModuleOwner **modules;
};
class Rva00261D2EFilter {
public:
 virtual void unused();
 bool allow(Object*);
 void *next;
 Coord3D position;
 const GeometryInfo *geometry;
 Real angle;
 bool desired, useSpecial;
};
bool Rva00261D2EFilter::allow(Object *other)
{
 const ThingTemplate *otherTemplate=other->thingTemplate;
 if(otherTemplate) {
  const ModuleData *data=otherTemplate->rva0033B3D7();
  if(data && useSpecial) {
   GeometryInfo special(GEOMETRY_CYLINDER,false,20.0f,data->radius,data->radius);
   if(geometry->bfmeIntersects(position,angle,special,other->position,other->angle))
    return true;
  }
 }
 const Coord3D *otherPos=&other->position;
 bool result=geometry->bfmeIntersects(position,angle,other->geometry,*otherPos,other->angle)==desired;
 _ReadWriteBarrier();
 if(result) return result;
 if((other->thingTemplate->kinds[0x11]&2) && otherTemplate) {
  Real radius=otherTemplate->radius;
  if(((Rva000CBA20*)other)->distSq((const Rva000CBA20Point*)&position)<=radius*radius*0.66f)
   return true;
 }
 if(other->thingTemplate->kinds[0]&0x80) {
  Coord3D end; end.x=0; end.y=0; end.z=0;
  FilterModuleOwner **modules=other->modules;
  for(;*modules;++modules) {
   FilterModule *module=&(*modules)->module;
   FilterGeometry *provider=module->slot50();
   if(!provider) {
    FilterNested *nested=module->slot08();
    if(nested) provider=nested->slot74();
   }
   if(provider && provider->slot24(&end,true)) {
    Region2D bounds;
    ((const Rva0087E370*)geometry)->method(position,angle,bounds);
    Coord2D delta; delta.x=end.x-otherPos->x; delta.y=end.y-otherPos->y;
    Coord2D start; start.x=otherPos->x; start.y=otherPos->y;
    if(bounds.rva000062FD(start,delta)) result=true;
   }
  }
 }
 return result;
}
