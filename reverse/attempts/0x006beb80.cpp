// ?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z
// partial score=0.7 date=2026-10-09
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c- /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// Correct native extent6BEB80..6BEEB5=821, old814 cuts ADD ESP/RET20.
// Target enabled32, second flag33, shape36B and nested vector walks2C/30.
// Transform provider's existing pointer-return pin agrees with native EAX use;
// its current void ledger provider is an independently observed ABI discrepancy.
#include "ascii_string.h"
#include "Coord3D.h"
struct Rva0087E900Coord { float x,y,z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord offset; };
Rva0087E900Coord *Rva0087E900(Rva0087E900Coord *,const Rva0087E900Coord *,const Rva0087E900Shape *,float);
struct Rva00880D10Subject;
struct Rva00880D10Info;
struct BfmeCollisionShape;
bool rva00880D10(Rva00880D10Subject *,Rva00880D10Info *);
bool rva006C0630(Rva00880D10Info *,Rva00880D10Info *);
bool bfmeSphereOverlap(const BfmeCollisionShape *,const BfmeCollisionShape *);
struct GeometryShape {
 int type; float height,major,minor; Coord3D offset; AsciiString name;
 bool enabled,flag;
};
struct GeometryContact {
 GeometryShape shape; Rva0087E900Coord position; float angle;
 GeometryContact(const GeometryShape &s,const Rva0087E900Coord &p,float a):shape(s),position(p),angle(a){}
};
class GeometryInfo {
public:
 bool bfmeIntersects(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
private:
 void *vptr; char prefix[0x28]; GeometryShape *begin,*end,*limit;
};
static inline float topExtent(const GeometryShape &s) {
 float extent=0.0f;
 switch(s.type) { case 0: extent=s.major; break; case 1: case 2: extent=s.height; break; }
 return extent+s.offset.z;
}
static __forceinline bool overlap(GeometryContact &a,GeometryContact &b) {
 switch(a.shape.type) {
 case 0: case 1:
  if(b.shape.type==2) return rva00880D10((Rva00880D10Subject *)&a,(Rva00880D10Info *)&b);
  return bfmeSphereOverlap((const BfmeCollisionShape *)&a,(const BfmeCollisionShape *)&b);
 case 2:
  if(b.shape.type==2) return rva006C0630((Rva00880D10Info *)&a,(Rva00880D10Info *)&b);
  return rva00880D10((Rva00880D10Subject *)&b,(Rva00880D10Info *)&a);
 }
 return false;
}
bool GeometryInfo::bfmeIntersects(const Coord3D &p,float angle,const GeometryInfo &other,const Coord3D &q,float otherAngle) const {
 bool found=false;
 for(GeometryShape *s=begin;s!=end;++s) {
  if(!s->enabled) continue;
  if(found) break;
  Rva0087E900Coord temp;
  Rva0087E900Coord ownCenter=*Rva0087E900(&temp,(const Rva0087E900Coord *)&p,(const Rva0087E900Shape *)s,angle);
  GeometryContact a(*s,ownCenter,angle);
  float h=topExtent(*s);
  for(GeometryShape *t=other.begin;t!=other.end;++t) {
   if(!t->enabled) continue;
   if(found) break;
   Rva0087E900Coord temp2;
   Rva0087E900Coord otherCenter=*Rva0087E900(&temp2,(const Rva0087E900Coord *)&q,(const Rva0087E900Shape *)t,otherAngle);
   GeometryContact b(*t,otherCenter,otherAngle);
   float ht=topExtent(*t);
   float lower=0.0f;
   if(b.shape.type==0) lower=ht;
   if(ownCenter.z+h<q.z-lower) continue;
   if(otherCenter.z+ht<ownCenter.z) continue;
   found=overlap(a,b);
  }
 }
 return found;
}
