// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /ICode/Libraries/Include
// NEW native397429..3974CE RET4, called by CastleBehavior route3C73E4.
// Scans GameLogic list for same template name, keeps nearest owner-relative
// GetLengthEstimate. WB EBD340 corroborates name/delta/nearest flow; original
// method name remains unproven. Target Object8, template4/name64, position38,
// next8C and 99999.0 initial bound are independently native field evidence.
//
// ?rva0039815B@CastleBehavior@@QAEPAVObject@@PAVThingTemplate@@PBUCoord3D@@H@Z
// retail 0x0039815B..0x00398243 (232 bytes, ret 0xC). Walks the castle's
// member ID list (+0x50, or +0x74 when the template has KindOf bit 0x40, as
// the sibling 0x003980BF in Common/Rva003980BFSelect.cpp picks it), skips
// members that are gone, whose template has KindOf bit 0x96 or whose
// 0x0028BCF4 interface is missing or answers true at slot 3, and keeps the
// member nearest to (mode 0, bound 9999999) or farthest from (mode 1,
// bound 0) the given position by the rowed 2D squared distance 0x002615E3.
// Any other mode returns null. The kept ID goes to the rowed cdecl helper
// 0x00397FEB (context +0x38, id, template, 0), whose result is returned.
// Target evidence: retail bytes and the caller ScriptActions 0x003C681F
// (template, position, mode parameter). The WorldBuilder twin 0x00EBC720
// (callgraph match) shows both switches on the mode, the two BitFlags tests
// (0x40 on the template, 0x96 on the member's template), the 0x4B18967F
// bound and the `best >= dist` / `best <= dist` comparisons; its member ID
// is at +0x7C where the retail layout reads +0x74. The method name stays
// address-derived; the views below cover only the fields these bodies read.
extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)
#include "Lib/Coord3D.h"
#include "ascii_string.h"
#include "Common/GameLogicObjectLookupView.h"
#include "Common/RTS/XYDistanceCallView.h"
#include "../../../../Include/Common/ThingTemplate.h"
// The interface 0x0028BCF4 returns; slot 3 answers a bool.
class CastleMemberState {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual bool slot3();};
class Object {public:
 ThingTemplate*getTemplate()const{return *(ThingTemplate*const*)((const char*)this+4);}
 const Coord3D*getPosition()const{return (const Coord3D*)((const char*)this+0x38);}
 Object*getNextObject()const{return *(Object*const*)((const char*)this+0x8C);}
 ObjectID getID()const{return *(const ObjectID*)((const char*)this+0x74);}
 void*rva0028BCF4()const;
 float distSq2D(const Coord3D*pos){return ((Rva000CBA20*)this)->distSq((const Rva000CBA20Point*)pos);}
};
extern GameLogic*TheGameLogic;
class CastleMemberList {public:const ObjectID*begin()const{return m_begin;}const ObjectID*end()const{return m_end;}
private:ObjectID*m_begin;ObjectID*m_end;ObjectID*m_capacity;};
void*__cdecl rva00397FEB(void*context,unsigned int id,void*target,int mode);
class CastleBehavior {public:Object*rva00397429(const AsciiString&);Object*getObject()const{return *(Object*const*)((const char*)this+8);}
 Object*rva0039815B(ThingTemplate*tmpl,const Coord3D*pos,int mode);
 const CastleMemberList*getNormalMembers()const{return (const CastleMemberList*)((const char*)this+0x50);}
 const CastleMemberList*getAlternateMembers()const{return (const CastleMemberList*)((const char*)this+0x74);}
};
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
Object*CastleBehavior::rva0039815B(ThingTemplate*thingTemplate,const Coord3D*pos,int mode)
{
 if(thingTemplate==0)
  return 0;
 float best;
 switch(mode) {
 case 0:best=9999999.0f;break;
 case 1:best=0.0f;break;
 default:return 0;
 }
 ObjectID bestID=INVALID_OBJECT_ID;
 const CastleMemberList*ids=getNormalMembers();
 if(((thingTemplate->m_kindof[2] & 0x1U)!=0))
  ids=getAlternateMembers();
 for(const ObjectID*it=ids->begin();it!=ids->end();++it) {
  Object*obj=TheGameLogic->findObjectByID(*it);
  if(obj==0)
   continue;
  if(((obj->getTemplate()->m_kindof[4] & 0x400000U)!=0))
   continue;
  CastleMemberState*state=(CastleMemberState*)obj->rva0028BCF4();
  if(state==0||state->slot3())
   continue;
  float dist=obj->distSq2D(pos);
  switch(mode) {
  case 0:if(best>=dist){bestID=obj->getID();best=dist;}break;
  case 1:if(best<=dist){bestID=obj->getID();best=dist;}break;
  }
 }
 return (Object*)rva00397FEB(*(void*const*)((const char*)this+0x38),bestID,thingTemplate,0);
}
