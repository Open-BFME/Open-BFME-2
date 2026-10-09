// cl: /O1 /arch:SSE /G7 /MD /EHsc /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
#include "Common/Snapshot.h"
#include "vector3.h"
#include "Lib/Coord2D.h"
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
#include <math.h>
#include "wwmath.h"
float Cos(float);
float Sin(float);
// Target facts: neutral sampler class; input three-float reference uses Vector3
// as an emitter view, not a recovered original type. GeometryInfo copy173 at
// 929E8 and its five-C extent are independently owned; canonical Snapshot
// fixes the prefix. BF1 f989 and ZH GeometryInfo guide shape/extents semantics;
// no clean sampler body found there. Actual four corner Set calls, float
// floor conversion and argument homes are established by full target bytes.
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
