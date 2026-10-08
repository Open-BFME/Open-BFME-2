// ?bfmeIntersects@GeometryInfo@@QBE_NABUCoord3D@@MABV1@0M@Z
// partial score=0.7 date=2026-10-09
// cl: /O2 /G6 /MD /EHs-c- /Ireference/shims/bfme2_ascii
// Native 0x006BEB80..0x006BEEB5 (821B including ret14); inventory814 truncates epilogue.
// Target component layout follows existing GeometryInfoRva006BD9C0 and native36B steps.
// The component-pair algorithm below is reconstructed from target; ZH Geometry.cpp has no composite equivalent.
#include "ascii_string.h"
struct Coord3D { float x,y,z; };
struct GeometryShape { int type; float height,major,minor; Coord3D offset; AsciiString name; bool enabled,second; };
struct CollisionShape { GeometryShape shape; Coord3D position; float angle; };
struct Rva0087E900Coord; struct Rva0087E900Shape;
void Rva0087E900(Rva0087E900Coord *,const Rva0087E900Coord *,const Rva0087E900Shape *,float);
struct Rva00880D10Info; struct Rva00880D10Subject; struct BfmeCollisionShape;
bool rva006C0630(Rva00880D10Info *,Rva00880D10Info *);
bool rva00880D10(Rva00880D10Subject *,Rva00880D10Info *);
bool bfmeSphereOverlap(const BfmeCollisionShape *,const BfmeCollisionShape *);
extern float g_Va00BBAEAC;
class GeometryInfo { public:
 bool bfmeIntersects(const Coord3D &,float,const GeometryInfo &,const Coord3D &,float) const;
private: char before[0x2c]; GeometryShape *begin,*end,*capacity;
};
bool GeometryInfo::bfmeIntersects(const Coord3D &loc,float angle,const GeometryInfo &other,const Coord3D &otherLoc,float otherAngle) const
{
 bool intersects=false;
 for(const GeometryShape *a=begin;a!=end;++a) {
  if(!a->enabled)continue;
  if(intersects)break;
  Coord3D pa;
  Rva0087E900((Rva0087E900Coord *)&pa,(const Rva0087E900Coord *)&loc,(const Rva0087E900Shape *)a,angle);
  CollisionShape first={*a,pa,angle};
  float above=g_Va00BBAEAC;
  if(a->type==0)above=a->major;
  else if(a->type==1||a->type==2)above=a->height;
  above+=a->offset.z;
  for(const GeometryShape *b=other.begin;b!=other.end;++b) {
   if(!b->enabled)continue;
   if(intersects)break;
   Coord3D pb;
   Rva0087E900((Rva0087E900Coord *)&pb,(const Rva0087E900Coord *)&otherLoc,(const Rva0087E900Shape *)b,otherAngle);
   CollisionShape second={*b,pb,otherAngle};
   float otherAbove=g_Va00BBAEAC;
   if(b->type==0)otherAbove=b->major;
   else if(b->type==1||b->type==2)otherAbove=b->height;
   otherAbove+=b->offset.z;
   float below=g_Va00BBAEAC;
   if(b->type==0)below=otherAbove;
   if(otherLoc.z-below<=pa.z+above && pa.z<=pb.z+otherAbove) {
    switch(first.shape.type) {
     case 2:
      if(second.shape.type==2)intersects=rva006C0630((Rva00880D10Info *)&first,(Rva00880D10Info *)&second);
      else intersects=rva00880D10((Rva00880D10Subject *)&second,(Rva00880D10Info *)&first);
      break;
     case 0:case 1:
      if(second.shape.type==2)intersects=rva00880D10((Rva00880D10Subject *)&first,(Rva00880D10Info *)&second);
      else intersects=bfmeSphereOverlap((const BfmeCollisionShape *)&first,(const BfmeCollisionShape *)&second);
      break;
    }
   }
  }
 }
 return intersects;
}
