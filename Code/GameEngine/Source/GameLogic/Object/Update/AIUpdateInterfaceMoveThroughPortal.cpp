// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /ICode/Libraries/Include
// WB E3AAE0 names moveThroughPortalWithMicropath in AIUpdate.cpp;
// native 26594F..265AAB is the complete EH-framed 348B RET24 body.
// Prepend order: final, optional mid, portal end, portal start, current
// position. Native Path allocation0x28, object8/position38, path140 and goal1FC/
// 200 are measured accesses, not a full AIUpdateInterface reconstruction.
// BFME1 575ba2b0 and ZH AIUpdate.cpp have no corresponding portal body.
// Existing Path/terrain/pathfinder providers and canonical Coord3D supply
// the verified ABI. Original inline getObject is needed for argument order.
#include <new>
#include "Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_INVALID=0,LAYER_GROUND=1 };
class Object {public:char pad[0x38];Coord3D position;};
class Path {public:Path();void prependNode(const Coord3D*,PathfindLayerEnum,int);char before[0xc];bool optimized;char after[0x28-0xd];};
#include "../../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
struct Rva002EDEABArg;
class Pathfinder {public:void SetDebugPath(Rva002EDEABArg*);};
#include "../../../../Include/GameLogic/AI.h"
extern AI *TheAI;
class GlobalData {public:char before[0x9b8];int debugPath;};
extern GlobalData *TheWritableGlobalData;
#include "../../../../Include/GameLogic/Module/AIUpdate.h"
void AIUpdateInterface::moveThroughPortalWithMicropath(const Coord3D *portalStart,const Coord3D *portalEnd,int id,PathfindLayerEnum layer,const Coord3D *midPos,const Coord3D *finalPos) {
 destroyPath();m_path=new Path;
 m_path->prependNode(finalPos,TheTerrainLogic->getLayerForDestination(getObject(),finalPos),id);
 if(!const_cast<Coord3D*>(midPos)->operator==(*finalPos))m_path->prependNode(midPos,TheTerrainLogic->getLayerForDestination(getObject(),midPos),id);
 m_path->prependNode(portalEnd,layer,id);
 m_path->prependNode(portalStart,TheTerrainLogic->getLayerForDestination(getObject(),portalStart),0x7fffffff);
 Coord3D position;position.x=m_object->position.x;position.y=m_object->position.y;position.z=m_object->position.z;
 m_path->prependNode(&position,TheTerrainLogic->getLayerForDestination(getObject(),&position),0x7fffffff);
 m_path->optimized=true;
 if(TheWritableGlobalData->debugPath==1)TheAI->m_pathfinder->SetDebugPath(reinterpret_cast<Rva002EDEABArg*>(m_path));
 m_field1FC=4;m_field200=*finalPos;
}
