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
class ThingTemplate {
public:
 Bool isKind212()const {return (m_kinds[0x1A]&0x10)!=0;}
private:
 unsigned char m_pad[0x108];unsigned char m_kinds[24+4];
};
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
class PathfindCell {
public:
 int getType()const{return (int)m_bits.type;}
 unsigned char getAircraftByte()const{return (unsigned char)(m_packed>>18);}
 CellInfo *getInfo()const{return m_info;}
 OccupantNode *getObstacles()const{return m_info->obstacles;}
 OccupantNode *getOccupants()const{return m_info?m_info->occupants:0;}
private:
 CellInfo*m_info;unsigned int m_unused4,m_unused8;
 union{unsigned int m_packed;struct{unsigned int type:4;unsigned int other:28;}m_bits;};
};
class Pathfinder {
public:
 PathfindCell *getCell(PathfindLayerEnum,int,int);
};
class Rva002EC3CEProbes {
public:
 Bool rva002EAA41(int objectAddress,int cellX,int cellY,int layer,int radius,Bool center);
};
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
   if(cell->getType()==5)return false;
   if(cell->getAircraftByte()&1)if(obj->rva0028AFBB())return false;
   if(cell->getType()==4)return false;
   if(obj->getTemplate()->isKind212()) {
    if(cell->getInfo()) for(OccupantNode *node=cell->getObstacles();node;node=node->next) {
     if(node->object->getID()==objectID)continue;
     if(node->object->getTemplate()->isKind212())return false;
    }
   } else {
    if(!((Rva0052DB73*)cell)->rva0052DB73(objectID))return false;
   }
   for(OccupantNode *node=cell->getOccupants();node;node=node->next) {
    if(node->object==obj)continue;
    if(obj->getRelationship(node->object)==ENEMIES)return false;
   }
  }
 }
 return true;
}
