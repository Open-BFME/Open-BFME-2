// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /ICode/Libraries/Include
// NEW native397429..3974CE RET4, called by CastleBehavior route3C73E4.
// Scans GameLogic list for same template name, keeps nearest owner-relative
// GetLengthEstimate. WB EBD340 corroborates name/delta/nearest flow; original
// method name remains unproven. Target Object8, template4/name64, position38,
// next8C and 99999.0 initial bound are independently native field evidence.
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include "Common/GameLogicObjectLookupView.h"
class ThingTemplate {public:const AsciiString&getName()const{return *(const AsciiString*)((const char*)this+0x64);}};
class Object {public:
 ThingTemplate*getTemplate()const{return *(ThingTemplate*const*)((const char*)this+4);}
 const Coord3D*getPosition()const{return (const Coord3D*)((const char*)this+0x38);}
 Object*getNextObject()const{return *(Object*const*)((const char*)this+0x8C);}
};
extern GameLogic*TheGameLogic;
class CastleBehavior {public:Object*rva00397429(const AsciiString&);Object*getObject()const{return *(Object*const*)((const char*)this+8);}};
Object*CastleBehavior::rva00397429(const AsciiString&name)
{
 Object*it=TheGameLogic->getFirstObject();Object*best=0;float nearest=99999.0f;
 for(;it;it=it->getNextObject()) {
  if(it->getTemplate()->getName()==name) {
   const Coord3D*pos=getObject()->getPosition();const Coord3D*p=it->getPosition();Coord3D delta;float dx=*(volatile const float*)&p->x;float dy=*(volatile const float*)&p->y;float dz=*(volatile const float*)&p->z;dx-=pos->x;dy-=pos->y;dz-=pos->z;_WriteBarrier();delta.x=dx;delta.y=dy;delta.z=dz;
   float distance=delta.GetLengthEstimate();
   if(!best||distance<nearest){best=it;nearest=distance;}
  }
 }
 return best;
}
