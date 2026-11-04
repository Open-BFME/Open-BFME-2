// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/bfme2_ascii
// Clean donor: Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da,
// game/GameEngine/Source/GameLogic/Object/Update/AIUpdateInterfaceFindNearestLabeledContactPoint.cpp.
// Donor supplies labeled-contact iteration and diagnostic behavior. Independent
// WB E59600 identity plus complete native0026872B..00268902 RET16 support target.
// Native owner8/moduleData4, label begin58/end5C, Object ID74/template4/name64
// are measured target accesses; target consumes template directly. Canonical
// Coord3D and existing fprintf/contact-query providers reproduce all471 bytes.
#include "Lib/Coord3D.h"
#include "ascii_string.h"
typedef bool Bool; typedef int Int;
#include "../../../../Include/Common/ThingTemplate.h"
class Object { public:
 void *vtable; const ThingTemplate *m_template; char pad08[0x6c]; unsigned id;
 const ThingTemplate*getTemplate()const{return m_template;} unsigned getID()const{return id;}
 Bool getWorldspaceBestContactPoint(Coord3D*,const Coord3D*,const char*,Int,Int,Bool)const;
};
// The docking-diagnostic trace flag, retail VA 0x00E03CA8 (RVA 0x00A03CA8).
// The rowed body tests it twice and writes it once (retail 0x0026872F
// `cmpb $0x0,0xe03ca8`, 0x002687F4 the same test, 0x00268854 `cmp
// %al,0xe03ca8`). RVA 0x00A03CA8 is past .data's raw end (0x009DE008) but
// inside its virtual size, so retail's image holds false -- the flag is turned
// on only by the docking diagnostics, which also read it. Five units spell it
// this way (?g_bfmeDockingTraceActive@@3_NA; the ledger binds the same object to
// the byte spelling ?g_00E03CA8@@3EA, so the two are one object, not two), and
// exactly one strong definition is needed -- this unit is the sole reader the
// fix unblocks.
bool g_bfmeDockingTraceActive = false;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void*,const char*,...);
struct ContactPointModuleData { char pad[0x58]; AsciiString *begin,*end; };
class AIUpdateInterface { public:
 char pad0[4]; ContactPointModuleData *moduleData; Object *owner;
 Bool findNearestLabeledContactPointOnTarget(Object*,Coord3D*,const Coord3D*,Bool);
};
Bool AIUpdateInterface::findNearestLabeledContactPointOnTarget(Object *target,Coord3D *result,const Coord3D *workingPosition,Bool skipCollideTest)
{
 Object *me;
 if(g_bfmeDockingTraceActive&&(me=owner,theLogicRandomLogFile)) {
  fprintf(theLogicRandomLogFile,"      AIUpdateInterface::findNearestLabeledContactPointOnTarget BEGIN: Object %s(%d), target %s(%d), workingPos %g,%g,%g, skipCollideTest=%s",
   me->getTemplate()->getName().str(),me->getID(),target?target->getTemplate()->getName().str():"NULL",target?target->getID():0,
   workingPosition->x,workingPosition->y,workingPosition->z,skipCollideTest?"TRUE":"FALSE");
 }
 ContactPointModuleData *data=moduleData;
 for(AsciiString *name=data->begin;name!=data->end;++name) {
  if(g_bfmeDockingTraceActive&&theLogicRandomLogFile)
   fprintf(theLogicRandomLogFile,"        handling contactPointName %s",name->str());
  if(target->getWorldspaceBestContactPoint(result,workingPosition,name->str(),0,0,skipCollideTest)) {
   if(g_bfmeDockingTraceActive&&theLogicRandomLogFile)
    fprintf(theLogicRandomLogFile,"        handling contactPointName %s succeeded - result=%g,%g,%g, RETURN TRUE",name->str(),result->x,result->y,result->z);
   return true;
  }
  if(g_bfmeDockingTraceActive&&theLogicRandomLogFile)
   fprintf(theLogicRandomLogFile,"        handling contactPointName %s failed",name->str());
 }
 if(g_bfmeDockingTraceActive&&theLogicRandomLogFile)
  fprintf(theLogicRandomLogFile,"        end of contactPoints. return FALSE");
 return false;
}
