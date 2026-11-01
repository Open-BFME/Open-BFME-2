// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native 002F6F90..002F70E5, thiscall RET8 AL. WB D6A690 and target
// diagnostics support adjustment predicate role; original context name unknown.
// Clean BFME1 IsCheckForAdjust003F2B60 donor revision 9cbfb551 supplies the
// predicate control flow; field offsets, kind bit and ABI come from retail.
struct Rva002F600CCoord { float x, y, z; };
class Object;
class LocomotorSet;
struct Coord3D;
// Use the existing provider's layer view; full layer identity is unresolved.
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN = 0, PATHFIND_LAYER_GROUND = 1 };
#include "../../../Include/GameLogic/AIPathfind.h"
typedef bool (Pathfinder::*Rva002F52A7Shape)(unsigned int, unsigned int, unsigned char, unsigned int, unsigned int, unsigned int,
    unsigned int, unsigned char, Rva002F600CCoord *, unsigned int, float, unsigned int *, unsigned int);

struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
struct Rva002F6F90Template { unsigned char pad[0x114]; unsigned int flags; };
struct Rva002F6F90Object { unsigned int word0; Rva002F6F90Template *objectTemplate; };
class Rva002F6F90Context {
public: bool rva002F6F90(unsigned int first,int second);
private:
 Pathfinder *query;
 Rva002F6F90Object *object;
 unsigned int word08;
 bool mode0C,option0D; unsigned char pad0E[2];
 unsigned int word10,word14,word18;
 float value1C;
 unsigned int saved20;
 int saved24,minimum28;
 unsigned int word2C;
 Rva002F600CCoord position30;
};
// ?rva002F6F90@Rva002F6F90Context@@QAE_NIH@Z
bool Rva002F6F90Context::rva002F6F90(unsigned int first,int second)
{

 if(g_00E03745 && theLogicRandomLogFile)
  fprintf((PathfinderLogFile*)theLogicRandomLogFile,"\t\t  Pathfinder_IsCheckForAdjust() called with cell=%d,%d",first,second);
 int count;
 if(!query->CheckForAdjust((Object *)object,*(const LocomotorSet *)word08,mode0C,first,second,(PathfindLayerEnum)word18,word10,option0D,(Coord3D *)&position30,(const Coord3D *)word14,value1C,&count,word2C)) {
  if(g_00E03745 && theLogicRandomLogFile)
   fprintf((PathfinderLogFile*)theLogicRandomLogFile,"\t\t  Pathfinder_IsCheckForAdjust() checkAdjust failed");
  return false;
 }

 if(!count || (object->objectTemplate->flags & 0x20000000)) {
  if(g_00E03745 && theLogicRandomLogFile)
   fprintf((PathfinderLogFile*)theLogicRandomLogFile,"\t\t  Pathfinder_IsCheckForAdjust() allyCount=%s, isInfantry=%s, returning true",count?"TRUE":"FALSE",(object->objectTemplate->flags&0x20000000)?"TRUE":"FALSE");
  return true;
 }
 if(count<minimum28 || !minimum28) {
  minimum28=count;saved20=first;saved24=second;
  if(g_00E03745 && theLogicRandomLogFile)
   fprintf((PathfinderLogFile*)theLogicRandomLogFile,"\t\t  Pathfinder_IsCheckForAdjust() allyCount=%d, m_foundWithAllies=%d",count,minimum28);
 }
 if(g_00E03745 && theLogicRandomLogFile)
  fprintf((PathfinderLogFile*)theLogicRandomLogFile,"\t\t  Pathfinder_IsCheckForAdjust() total failure, return false",count,minimum28);
 return false;
}
