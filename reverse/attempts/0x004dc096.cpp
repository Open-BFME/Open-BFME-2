// ?rva004DC096@Rva004DC1BF@@QAE_NPAVCoord2D@@@Z
// partial score=0.9722097413820393 date=2026-10-10
// ?rva004DC096@Rva004DC1BF@@QAE_NPAVCoord2D@@@Z
// partial score=0.97 date=2026-10-09
// cl: /I.  /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#include "Common/Snapshot.h"
#include "vector3.h"
#include "/mnt/titan_nv3/open-bfme2-agent-fleet/gemini200/writer-005/Code/Libraries/Include/Lib/Coord2D.h"
class GeometryInfo:public Snapshot {
public:
 GeometryInfo(const GeometryInfo &);
 virtual ~GeometryInfo();
 virtual void loadPostProcess();
 virtual void crc(Xfer*);
 virtual void xfer(Xfer*);
 char prefix[0xC]; float radius; char gap14[0x10]; float extentX,extentY; char remaining[0x30];
};
class BfmeThingTemplateShadowSelector {
public: bool usePluralShadowName() const;
};
bool Point_In_Triangle_2D(const Vector3&,const Vector3&,const Vector3&,const Vector3&,int,int,unsigned char&);
static __forceinline float gridCoordinate(int value) { return (float)value*10.0f; }
class Rva004DC1BF {
public:
 GeometryInfo geometry;
 float angle;
 Vector3 position;
 int xMin,yMin,xMax,yMax;
 Vector3 corner0,corner1,corner2,corner3;
 int x,y;
 Rva004DC1BF(const GeometryInfo &,float,const Vector3 &);
 bool rva004DC096(Coord2D *out);
};
// Target next297/WB113A490: lexicographic grid traversal at 10-unit steps.
// Box discrimination retains the owned provider's earlier neutral ABI view;
// native count of the 36B shape vector and sole type2 establish its purpose.
bool Rva004DC1BF::rva004DC096(Coord2D *out)
{
 for (;;) {
  ++y;
  while (y>yMax) {
   ++x;
   if(x>xMax) return false;
   y=yMin;
  }
  Vector3 point;
  point.X=(float)x*10.0f;point.Y=(float)y*10.0f;_ReadWriteBarrier();point.Z=0.0f;
  bool accepted=false;
  if(reinterpret_cast<const BfmeThingTemplateShadowSelector *>(&geometry)->usePluralShadowName()) {
   unsigned char onEdge;
   if(Point_In_Triangle_2D(corner0,corner1,corner3,point,0,1,onEdge)) accepted=true;
   if(!accepted && Point_In_Triangle_2D(corner1,corner2,corner3,point,0,1,onEdge)) accepted=true;
  } else {
   float dx=point.X-position.X;
   float dy=point.Y-position.Y;
   float r=geometry.radius;
   accepted=dx*dx+dy*dy<r*r;
  }
  if(accepted) {out->x=point.X;out->y=point.Y;return true;}
 }
}

#include <math.h>
#include "wwmath.h"
float Cos(float);
float Sin(float);
static __forceinline int gridBound(float value) { return WWMath::Float_To_Long((float)floor(value*0.1f)); }
// Constructor boundary: native4DC1BF..4DC5EF RET12; the old served1126
// extent included four following routines. Target owns a5C GeometryInfo copy
// then angle5C/position60/bounds6C..78/corners7C..A8/cursorsAC,B0.
Rva004DC1BF::Rva004DC1BF(const GeometryInfo &source,float a,const Vector3 &p)
 :geometry(source),angle(a),position(p)
{
 if(reinterpret_cast<const BfmeThingTemplateShadowSelector *>(&source)->usePluralShadowName()) {
  float minor,major;
  major=source.extentX; minor=source.extentY;
  float c=Cos(a),s=Sin(a);
  corner0.Set(p.X-major*c-minor*s,p.Y+minor*c-major*s,0.0f);
  corner1.Set(major*c+p.X-minor*s,p.Y+major*s+minor*c,0.0f);
  corner2.Set(minor*s+major*c+p.X,p.Y-minor*c+major*s,0.0f);
  corner3.Set(p.X-major*c+minor*s,p.Y-minor*c-major*s,0.0f);
  float minX=corner0.X;
  if(minX>corner1.X) minX=corner1.X;
  if(minX>corner2.X) minX=corner2.X;
  if(minX>corner3.X) minX=corner3.X;
  float maxX=corner0.X;
  if(maxX<corner1.X) maxX=corner1.X;
  if(maxX<corner2.X) maxX=corner2.X;
  if(maxX<corner3.X) maxX=corner3.X;
  float minY=corner0.Y;
  if(minY>corner1.Y) minY=corner1.Y;
  if(minY>corner2.Y) minY=corner2.Y;
  if(minY>corner3.Y) minY=corner3.Y;
  float maxY=corner0.Y;
  if(maxY<corner1.Y) maxY=corner1.Y;
  if(maxY<corner2.Y) maxY=corner2.Y;
  if(maxY<corner3.Y) maxY=corner3.Y;
  xMin=WWMath::Float_To_Long((float)floor(minX*0.1f)); yMin=WWMath::Float_To_Long((float)floor(minY*0.1f));
  xMax=WWMath::Float_To_Long((float)floor(maxX*0.1f)); yMax=WWMath::Float_To_Long((float)floor(maxY*0.1f));
 } else {
  float r=source.radius;
  {float scaled=(p.X-r)*0.1f; xMin=WWMath::Float_To_Long((float)floor(scaled));}
  {float scaled=(p.Y-r)*0.1f; yMin=WWMath::Float_To_Long((float)floor(scaled));}
  {float scaled=(p.X+r)*0.1f; xMax=WWMath::Float_To_Long((float)floor(scaled));}
  {float scaled=(p.Y+r)*0.1f; yMax=WWMath::Float_To_Long((float)floor(scaled));}
 }
 x=xMin; y=yMin-1;
}
