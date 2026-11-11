// ?allow@Rva00261D2EFilter@@QAE_NPAVObject@@@Z
// cl: /O1  /arch:SSE /DNDEBUG /MD /EHsc /G7 /ICode/Libraries/Include/Lib
// Retail 00261D2E..00261F35, RET4. WB E5B6B0 is the same collision
// filter with target-specific bridge-kind and attachment geometry handling.
// Member offsets and virtual slots below are target facts. No original
// filter or module names are asserted by this address-derived view.
#include "Coord3D.h"
#include "Coord2D.h"

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
typedef float Real;
class Object;
class ModuleData;
#include "../../Include/Common/Geometry.h"
class ThingTemplate {
public:
 const ModuleData *rva0033B3D7() const;
 char data00[0xB0];
 Real radius;
 char dataB4[0x108-0xB4];
 unsigned char kinds[0x14];
};
#include "../../Include/Common/ModuleData.h"
// What ThingTemplate::rva0033B3D7 selects keeps its range at +0x2C.
class Rva0033B3D7Data { public: char data00[0x2C]; Real radius; };
#include "RTS/XYDistanceCallView.h"
#include "Region2D.h"
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
enum NameKeyType { NAMEKEY_INVALID = 0, NAMEKEY_MAX = 1 << 23 };
class Module;
class Object {
 friend class Rva00391667Filter;
protected:
 Module *findModule(NameKeyType key) const;
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
  const Rva0033B3D7Data *data=(const Rva0033B3D7Data *)otherTemplate->rva0033B3D7();
  if(data && useSpecial) {
   GeometryInfo special(GEOMETRY_CYLINDER,false,20.0f,data->radius,data->radius);
   if(geometry->CollidesWith(position,angle,special,other->position,other->angle))
    return true;
  }
 }
 const Coord3D *otherPos=&other->position;
 bool result=geometry->CollidesWith(position,angle,other->geometry,*otherPos,other->angle)==desired;
 _ReadWriteBarrier();
 // Shared result tail preserves retail's memory predicate and return home.
 if(!result) {
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
    if(bounds.lineSegmentIntersects(start,delta)) result=true;
   }
  }
 }
 }
 return result;
}

// ?allow@Rva00391667Filter@@UAE_NPAVObject@@@Z
// Retail 0x00261F35..0x00262002, RET4: slot 1 of vftable 0x00C1A068, whose
// constructor 0x00391667 copies the point to +0x0C and zeroes the radius at
// +0x08. An object with a castle behaviour (module key 0x003955DA) passes
// when its XY distance to the point is inside the castle radius 0x00395A60
// plus the filter radius; any other object passes when its own geometry
// collides with a 20-unit cylinder of the filter radius at the point.
class CastleBehavior { public: static NameKeyType rva0003955DA(); };
#include "../../Include/GameLogic/Rva00395A60.h"
class Rva00391667Filter {
public:
 virtual void slot00();
 virtual bool allow(Object *other);
 void *next;
 Real radius;
 Coord3D position;
};
bool Rva00391667Filter::allow(Object *other)
{
 Module *castle=other->findModule(CastleBehavior::rva0003955DA());
 if(castle) {
  Real distSq=((Rva000CBA20*)other)->distSq((const Rva000CBA20Point*)&position);
  Real range=((Rva00395A60*)castle)->rva00395A60()+radius;
  if(distSq<range*range)
   return true;
 } else {
  GeometryInfo area(GEOMETRY_CYLINDER,false,20.0f,radius,radius);
  Real angle=other->angle;
  const GeometryInfo &geometry=other->geometry;
  if(geometry.CollidesWith(other->position,angle,area,position,0.0f))
   return true;
 }
 return false;
}

// BuildAssistant.cpp builds this filter in isLocationClearOfObjects through its
// constructor 0x00391667 and names the class by that address (Rva00391667,
// vftable 0x00C1A068); its slot-1 reference binds to this body.
#pragma comment(linker, "/alternatename:?allow@Rva00391667@@UAE_NPAVObject@@@Z=?allow@Rva00391667Filter@@UAE_NPAVObject@@@Z")
