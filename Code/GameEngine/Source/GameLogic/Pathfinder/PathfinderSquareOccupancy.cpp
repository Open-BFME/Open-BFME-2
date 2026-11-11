// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// BF1 f98983a7d PathfindCheckDestination.cpp and ZH checkDestination semantic spine.
// Target 0x002EAA41..0x002EAB6F, complete RET24, proves all tested bits,
// the 16-byte cell prefix, info list heads +0x14/+0x20 and node object +8.
// WB 0x00D5B9D0 and matched caller 0x002EC3CE support the occupancy-scan role.
// BFME 2 adds kind-bit 212 obstacles and rejects relationship value zero over
// occupant nodes. These target deltas are independently read from retail;
// the source's semantic guide does not establish the original BFME 2 name.
// Existing six-word neutral probe ABI retained for its already-matched caller.
// Pointer layouts are target-supported views, not recovered canonical classes.
typedef bool Bool;
enum PathfindLayerEnum { LAYER_INVALID=0, LAYER_GROUND=1 };
enum Relationship { ENEMIES=0, NEUTRAL=1, ALLIES=2 };
#include "../../../Include/Common/ThingTemplate.h"
class Object {
public:
 Bool rva0028AFBB()const;
 Relationship getRelationship(const Object*)const;
 int getID()const{return m_id;}
 const ThingTemplate *getTemplate()const{return m_template;}
private:
 unsigned char m_pad0[4];const ThingTemplate*m_template;
 unsigned char m_pad8[0x74-8];int m_id;
};
struct OccupantNode {OccupantNode *next,*previous;Object *object;};
struct CellInfo {
 unsigned char m_pad[0x14];OccupantNode *obstacles;
 unsigned char m_pad18[8];OccupantNode *occupants;
};
class Rva0052DB73 {
public:
 Bool rva0052DB73(int);
};
#include "../../../Include/GameLogic/PathfindCell.h"
static __forceinline unsigned char cellAircraftByte(const PathfindCell *cell){return (unsigned char)(cell->m_0C>>18);}
static __forceinline CellInfo *cellInfo(const PathfindCell *cell){return (CellInfo *)cell->m_info;}
static __forceinline OccupantNode *cellObstacles(const PathfindCell *cell){return cellInfo(cell)->obstacles;}
static __forceinline OccupantNode *cellOccupants(const PathfindCell *cell){return cellInfo(cell)?cellInfo(cell)->occupants:0;}
#include "../../../Include/GameLogic/AIPathfind.h"
#include "../../../Include/GameLogic/Rva002EC3CEProbes.h"
Bool Rva002EC3CEProbes::rva002EAA41(int objectAddress,int cellX,int cellY,int layer,int radius,Bool center)
{
 int cellsAbove=radius;
 if(center)++cellsAbove;
 const Object *obj=(const Object*)objectAddress;
 int objectID=obj->getID();
 for(int i=cellX-radius;i<cellX+cellsAbove;++i) {
  for(int j=cellY-radius;j<cellY+cellsAbove;++j) {
   PathfindCell *cell=((Pathfinder*)this)->getCell((PathfindLayerEnum)layer,i,j);
   if(!cell)return false;
   if(cell->getType()==PathfindCell::CELL_BRIDGE_IMPASSABLE)return false;
   if(cellAircraftByte(cell)&1)if(obj->rva0028AFBB())return false;
   if(cell->getType()==PathfindCell::CELL_OBSTACLE)return false;
   if(((obj->getTemplate()->m_kindof[6] & (1U << 20))!=0)) {
    if(cellInfo(cell)) for(OccupantNode *node=cellObstacles(cell);node;node=node->next) {
     if(node->object->getID()==objectID)continue;
     if(((node->object->getTemplate()->m_kindof[6] & (1U << 20))!=0))return false;
    }
   } else {
    if(!((Rva0052DB73*)cell)->rva0052DB73(objectID))return false;
   }
   for(OccupantNode *node=cellOccupants(cell);node;node=node->next) {
    if(node->object==obj)continue;
    if(obj->getRelationship(node->object)==ENEMIES)return false;
   }
  }
 }
 return true;
}
