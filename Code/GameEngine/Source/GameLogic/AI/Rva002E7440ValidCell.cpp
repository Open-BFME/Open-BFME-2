// cl: /O1 /G7 /arch:SSE /MD
// Native2E7440..2E7482 RET8 AL; getCell existing measured ABI.
// Packed word0C bit18 and types2/5/4/1 reject; missing cell accepts.
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN=0,PATHFIND_LAYER_GROUND=1 };
class PathfindCell { public: char pad[12]; unsigned int flags; };
class Pathfinder { public: PathfindCell *getCell(PathfindLayerEnum,int,int); };
class Rva002E7440 { public: bool rva002E7440(int,int); private: Pathfinder *pf; };
bool Rva002E7440::rva002E7440(int x,int y) {
 PathfindCell *cell=pf->getCell(PATHFIND_LAYER_GROUND,x,y);
 if(cell) {
  unsigned int flags=cell->flags;
  unsigned char blocked=(unsigned char)(flags>>18);
  if(blocked&1)return false;
  unsigned int type=flags&15;
  if(type==2 || type==5 || type==4 || type==1)return false;
 }
 return true;
}
