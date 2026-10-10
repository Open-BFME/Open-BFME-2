// ?getBestContactPoint@GeometryInfo@@QBE_NPAUCoord3D@@PBU2@PBDHH_N@Z
// partial score=0.585187 date=2026-10-10
// cl: /O2 /G6 /MD /GX- /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib
// Target 006BEF80..006BF3B7 RET24; WB 006F91B0 names GeometryInfo::getBestContactPoint.
// ZH Geometry.cpp guides the geometry subsystem; this contact algorithm is BFME2-specific.
#include "ascii_string.h"
#include "Coord3D.h"
#include <float.h>
extern "C" int fprintf(void*,const char*,...);
extern "C" void *theLogicRandomLogFile;
extern bool g_bfmeDockingTraceActive;
struct GeometryContactRecord { Coord3D position; AsciiString label; };
struct GeometryShape {int type;float height,majorRadius,minorRadius;Coord3D offset;AsciiString name;bool enabled;char tail[3];};
class GeometryInfo {
public:
 bool getBestContactPoint(Coord3D*,const Coord3D*,const char*,int,int,bool) const;
 float getMaxHeightAbovePosition()const;
 bool bfmeIntersects(const Coord3D&,float,const GeometryInfo&,const Coord3D&,float)const;
private:
 char prefix[0x2c];GeometryShape *shapesBegin,*shapesEnd,*shapesCapacity;
 GeometryContactRecord *contactsBegin,*contactsEnd,*contactsCapacity;
 Coord3D preferredPosition;
 Coord3D defaultPosition;
};
extern Coord3D GeometryContactOrigin;
extern GeometryInfo GeometryContactProbe;
static inline void contactCopy(Coord3D &out,const Coord3D &in){out.x=in.x;out.y=in.y;out.z=in.z;}
bool GeometryInfo::getBestContactPoint(Coord3D*out,const Coord3D*caller,const char*label,int preference,int seed,bool ignoreCollision)const {
 if(g_bfmeDockingTraceActive&&caller&&theLogicRandomLogFile)
  fprintf(theLogicRandomLogFile,"        GeometryInfo::getBestContactPoint, callerPos=%g,%g,%g, label=%s, pref=%d, seed=%d, skipCollideTest=%d, m_innermostContactPoint=%g,%g,%g",caller->x,caller->y,caller->z,label?label:"NONE",preference,seed,ignoreCollision?"TRUE":"FALSE",defaultPosition.x,defaultPosition.y,defaultPosition.z);
 contactCopy(*out,defaultPosition);
 switch(preference){
 case 3:{
  int count=contactsEnd-contactsBegin;
  if(count>=2){
   int index=seed%(count-1);float t=((seed>>8)&255)/255.0f;
   Coord3D first=contactsBegin[index].position;
   first.x*=t;first.y*=t;first.z*=t;
   Coord3D second=contactsBegin[index+1].position;
   float inverse=1.0f-t;second.x*=inverse;second.y*=inverse;second.z*=inverse;
   first.x+=second.x;first.y+=second.y;first.z+=second.z;
   contactCopy(*out,first);
  }
  float height=getMaxHeightAbovePosition();
  if(out->z>height)out->z=height;
  if(!ignoreCollision&&!bfmeIntersects(GeometryContactOrigin,0.0f,GeometryContactProbe,*out,0.0f)){
   for(GeometryShape*shape=shapesBegin;shape!=shapesEnd;++shape){
    if(!shape->enabled)continue;
    out->x=shape->offset.x;out->y=shape->offset.y;out->z=shape->height*0.5f+shape->offset.z;break;
   }
  }
  if(out->z>height)out->z=height;
  else if(out->z<height*0.1f)out->z=height*0.1f;
  return true;
 }
 case 1:
  contactCopy(*out,preferredPosition);
  if(out->z>getMaxHeightAbovePosition())out->z=getMaxHeightAbovePosition();
  return true;
 case 0:{
  if(!caller)return false;
  int count=contactsEnd-contactsBegin;
  int best=count;float bestDistance=FLT_MAX;
  for(int i=0;i<count;++i){
   if(contactsBegin[i].label.compare(label?label:"")!=0)continue;
   Coord3D pos=contactsBegin[i].position;
   if(pos.z>getMaxHeightAbovePosition())pos.z=getMaxHeightAbovePosition();
   if(!ignoreCollision&&!bfmeIntersects(GeometryContactOrigin,0.0f,GeometryContactProbe,pos,0.0f))continue;
   float dx=pos.x-caller->x,dy=pos.y-caller->y,dz=pos.z-caller->z;
   float d=dx*dx+dy*dy+dz*dz;
   if(d<bestDistance){bestDistance=d;best=i;}
  }
  if(best==count)return false;
  contactCopy(*out,contactsBegin[best].position);
  if(out->z>getMaxHeightAbovePosition())out->z=getMaxHeightAbovePosition();
  else if(out->z<getMaxHeightAbovePosition()*0.1f)out->z=getMaxHeightAbovePosition()*0.1f;
  return true;
 }
 default:return false;
 }
}
