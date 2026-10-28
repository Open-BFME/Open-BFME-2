// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c- /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// GeometryInfo bodies, one retail unit: the shape transform 0x006BE190 (132 B),
// GeometryInfo::CollidesWith 0x006BEB80..0x006BEEB5 (821 bytes, RET 0x14) and
// GeometryInfo::getBestContactPoint 0x006BEF80 (1082 bytes, RET 0x18).
//
// Target evidence: WB assert strings name GeometryInfo::CollidesWith; the
// shape vector is begin/end at +0x2C/+0x30 of 36-byte GeometryShape records
// (type, height, major, minor, offset, AsciiString name, enabled, flag), each
// placed through the transform 0x006BE190 and copied with the AsciiString
// copy constructor 0x004365F0 into a 52-byte contact (shape, position, angle).
// Pair tests are the rowed circle/box 0x006C0710, box/box 0x006C0630 and
// sphere/sphere 0x006C0790. The vertical rules are asymmetric in retail: the
// own top is compared against the other position's z less the other's extent
// (only for spheres), and the own centre against the other placed top.
// A shape type outside 0..2 leaves the running result untouched.
//
// Structural inference: the two vertical rejections are one combined
// condition. Two separate continues lay the x87 pop for the first rejection
// inline, which lets the compiler merge the four pair-test result stores;
// retail keeps that pop ahead of the join and duplicates the stores per case.
// ZH Geometry.cpp is a semantic guide only (enum order SPHERE, CYLINDER, BOX).
//
// getBestContactPoint: the trace string names it and its arguments (callerPos,
// label, pref, seed, skipCollideTest, m_innermostContactPoint). Contact records
// are 16-byte (Coord3D, AsciiString label) entries in an STLport vector at
// +0x38, the preferred point is at +0x44 and the innermost point at +0x50.
// Collision tests run against the static sphere GeometryInfo at RVA 0x00A0C150
// (constructed by 0x007B6640) placed at the zero point RVA 0x00A0C140, which
// only this body references. Codegen evidence: the transform's body must be in
// this unit (its &position receivers then do not escape, so the pos copy loads
// group as retail), the label test binds a reference per arm (one lea per arm,
// as retail), and the case-3 blend factor is converted before the divide.
#include "ascii_string.h"
#include "Coord3D.h"
#include <float.h>
extern "C" int fprintf(void*,const char*,...);
extern "C" void *theLogicRandomLogFile;
extern bool g_bfmeDockingTraceActive;
struct GeometryContactRecord {Coord3D position; AsciiString label;};
struct GeometryContactVector {
 GeometryContactRecord *_M_start,*_M_finish,*_M_end_of_storage;
 const GeometryContactRecord *begin() const {return _M_start;}
 const GeometryContactRecord *end() const {return _M_finish;}
 unsigned int size() const {return (unsigned int)(end()-begin());}
 const GeometryContactRecord &operator[](unsigned int n) const {return *(begin()+n);}
};

// Native 006BE190/132 returns the output-coordinate address in EAX.
// The rowed 006BE220 consumer copies through that returned address.
// This neutral pointer-return ABI view reconciles provider and consumer;
// pointer return versus hidden aggregate return in the original source is unproved.
struct Rva0087E900Coord { float x,y,z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord offset; };
extern "C" double __cdecl sin(double angle);
extern "C" double __cdecl cos(double angle);
Rva0087E900Coord *Rva0087E900(Rva0087E900Coord *out,
    const Rva0087E900Coord *position,
    const Rva0087E900Shape *shape,
    float angle)
{
    // Volatile accesses preserve retail x87 scheduling; storage itself is ordinary.
    float raw[6];
    volatile float *scratch = raw;
    float sine = (float)sin(angle);
    scratch[1] = shape->offset.y;
    scratch[2] = shape->offset.z;
    float cosine = (float)cos(angle);
    float shapeX = shape->offset.x;
    volatile float &angleRef = angle;
    angleRef = shapeX;
    float rotatedX = cosine * shapeX;
    rotatedX -= scratch[1] * sine;
    scratch[4] = position->y;
    raw[5] = position->z;
    scratch[0] = rotatedX;
    float rotatedY = angleRef * sine + scratch[1] * cosine;
    float outputX = position->x;
    outputX += scratch[0];
    scratch[3] = outputX;
    float outputY = rotatedY + scratch[4];
    float outputZ = scratch[5] + raw[2];
    out->x = scratch[3];
    out->y = outputY;
    out->z = outputZ;
    return out;
}

struct Rva00880D10Subject;
struct Rva00880D10Info;
struct BfmeCollisionShape;
bool circleIntersectsBox(Rva00880D10Subject *,Rva00880D10Info *);
bool rva006C0630(Rva00880D10Info *,Rva00880D10Info *);
bool bfmeSphereOverlap(const BfmeCollisionShape *,const BfmeCollisionShape *);
struct Rva006BEB80Point:Rva0087E900Coord{Rva006BEB80Point(){} Rva006BEB80Point(const Rva0087E900Coord&r){x=r.x;y=r.y;z=r.z;} };
struct Rva006BEB80Offset:Coord3D{Rva006BEB80Offset(){} Rva006BEB80Offset(const Rva006BEB80Offset&r){x=r.x;y=r.y;z=r.z;} };
struct GeometryShape {
 int type; float height,major,minor; Rva006BEB80Offset offset; AsciiString name;
 bool enabled,flag;
 __declspec(dllimport) __forceinline GeometryShape(const GeometryShape &r):type(r.type),height(r.height),major(r.major),minor(r.minor),offset(r.offset),name(r.name),enabled(r.enabled),flag(r.flag) {}
};
struct GeometryContact {
 GeometryShape shape; Rva006BEB80Point position; float angle;
 __declspec(dllimport) __forceinline GeometryContact(const GeometryShape &s,const Rva0087E900Coord &p,float a):shape(s),position(p),angle(a){}
};
class GeometryInfo {
public:
 bool getBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 float getMaxHeightAbovePosition()const;
 bool CollidesWith(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
private:
 void *vptr; char prefix[0x28]; GeometryShape *begin,*end,*limit;
 GeometryContactVector contacts;
 Coord3D preferredPosition,defaultPosition;
};
static inline float topExtent(const GeometryShape &geometryShape) {
 float extent=0.0f;
 switch(geometryShape.type) { case 0: extent=geometryShape.major; break; case 1: case 2: extent=geometryShape.height; break; }
 return extent+geometryShape.offset.z;
}
static __forceinline bool overlap(GeometryContact &geometryContact,GeometryContact &otherContact,bool cur) {
 switch(geometryContact.shape.type) {
 case 0: case 1:
  if(otherContact.shape.type==2) return circleIntersectsBox((Rva00880D10Subject *)&geometryContact,(Rva00880D10Info *)&otherContact);
  return bfmeSphereOverlap((const BfmeCollisionShape *)&geometryContact,(const BfmeCollisionShape *)&otherContact);
 case 2:
  if(otherContact.shape.type==2) return rva006C0630((Rva00880D10Info *)&geometryContact,(Rva00880D10Info *)&otherContact);
  return circleIntersectsBox((Rva00880D10Subject *)&otherContact,(Rva00880D10Info *)&geometryContact);
 }
 return cur;
}
bool GeometryInfo::CollidesWith(const Coord3D &pos,float angle,const GeometryInfo &other,const Coord3D &otherPos,float otherAngle) const {
 bool found=false;
 for(GeometryShape *geometryShape=begin;geometryShape!=end;++geometryShape) {
  if(!geometryShape->enabled) continue;
  if(found) break;
  Rva0087E900Coord transformedPosition;
  Rva006BEB80Point ownCenter=*Rva0087E900(&transformedPosition,(const Rva0087E900Coord *)&pos,(const Rva0087E900Shape *)geometryShape,angle);
  GeometryContact a(*geometryShape,ownCenter,angle);
  float h=topExtent(*geometryShape);
  for(GeometryShape *otherShape=other.begin;otherShape!=other.end;++otherShape) {
   if(!otherShape->enabled) continue;
   if(found) break;
   Rva0087E900Coord otherTransformedPosition;
   Rva006BEB80Point otherCenter=*Rva0087E900(&otherTransformedPosition,(const Rva0087E900Coord *)&otherPos,(const Rva0087E900Shape *)otherShape,otherAngle);
   GeometryContact b(*otherShape,otherCenter,otherAngle);
   float ht=topExtent(*otherShape);
   float lower=0.0f;
   if(b.shape.type==0) lower=ht;
   if(ownCenter.z+h<otherPos.z-lower || ownCenter.z>otherCenter.z+ht) continue;
   found=overlap(a,b,found);
  }
 }
 return found;
}

Coord3D GeometryContactOrigin;	// retail RVA 0x00A0C140 (.bss), defined here
extern unsigned GeometryContactSphere;
struct ContactPoint:Coord3D { ContactPoint(const Coord3D&r) {x=r.x;y=r.y;z=r.z;} };
static inline void contactCopy(Coord3D &out,const Coord3D &in){out=in;}
bool GeometryInfo::getBestContactPoint(Coord3D*out,const Coord3D*caller,const char*label,int preference,int seed,bool ignoreCollision)const {
 if(g_bfmeDockingTraceActive&&caller&&theLogicRandomLogFile)
  fprintf(theLogicRandomLogFile,"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",caller->x,caller->y,caller->z,label?label:"NONE",preference,seed,ignoreCollision?"TRUE":"FALSE",defaultPosition.x,defaultPosition.y,defaultPosition.z);
 contactCopy(*out,defaultPosition);
 switch(preference){
 case 3:{
  int count=(int)contacts.size();
  if(count>=2){
   int index=seed%(count-1);
   ContactPoint first=contacts[index].position;
   ContactPoint second=contacts[index+1].position;
   float blendFactor=(float)((seed>>8)&255);blendFactor/=255.0f;
   first.x*=blendFactor;first.y*=blendFactor;first.z*=blendFactor;
   float inverse=1.0f-blendFactor;second.x*=inverse;second.y*=inverse;second.z*=inverse;
   first.x+=second.x;first.y+=second.y;first.z+=second.z;
   contactCopy(*out,first);
  }
  float height=getMaxHeightAbovePosition();
  if(out->z>height)out->z=height;
  if(!ignoreCollision&&!CollidesWith(GeometryContactOrigin,0.0f,*(const GeometryInfo *)&GeometryContactSphere,*out,0.0f)){
   for(GeometryShape*shape=begin;shape!=end;++shape){
    if(!shape->enabled)continue;
    out->x=shape->offset.x;out->y=shape->offset.y;out->z=shape->height*0.5f+shape->offset.z;break;
   }
  }
  if(out->z>height){out->z=height;return true;}
  if(out->z<height*0.1f)out->z=height*0.1f;
  return true;
 }
 case 1:
  contactCopy(*out,preferredPosition);
  if(out->z>getMaxHeightAbovePosition())out->z=getMaxHeightAbovePosition();
  return true;
 case 0:{
  if(caller){
  int count=(int)contacts.size();
  int best=count;float bestDistance=FLT_MAX;
  for(int i=0;i<count;++i){
   const GeometryContactRecord *geometryContactRecord;
   if(label){const AsciiString &asciiString=contacts[i].label;geometryContactRecord=&contacts[i];if(asciiString.compare(label)!=0)continue;}
   else{const AsciiString &asciiString=contacts[i].label;geometryContactRecord=&contacts[i];if(asciiString.compare("")!=0)continue;}
   Coord3D pos=geometryContactRecord->position;
   if(pos.z>getMaxHeightAbovePosition())pos.z=getMaxHeightAbovePosition();
   if(!ignoreCollision&&!CollidesWith(GeometryContactOrigin,0.0f,*(const GeometryInfo *)&GeometryContactSphere,pos,0.0f))continue;
   float dx=pos.x-caller->x,dy=pos.y-caller->y,dz=pos.z-caller->z;
   float d=dz*dz+(dx*dx+dy*dy);
   if(d<bestDistance){bestDistance=d;best=i;}
  }
  if(best!=count){
  contactCopy(*out,contacts[best].position);
  if(out->z>getMaxHeightAbovePosition()){out->z=getMaxHeightAbovePosition();}
  else if(out->z<getMaxHeightAbovePosition()*0.1f)out->z=getMaxHeightAbovePosition()*0.1f;
  return true;
 }
 }
 break;
 }
 default:break;
 }
 return false;
}
