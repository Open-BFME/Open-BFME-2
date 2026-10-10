// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// Native2E76D3..2E7749 and2E7749..2E7875; WB D4D480/D4D280
// independently establish the cell test and diameter-fit caller. ZH
// clearCellForDiameter supplies the cell semantics; target perimeter-first
// walk and recursive diameter reduction are decoded and corroborated by WB.
// The static helper must be emitted with its caller: MSVC passes cell in EDI
// while retaining the unsigned crusher and occupants flag on the stack.
// Whole bodies and call relocations verify; no custom ABI pin is needed.
// Loop indices outside both branches plus the WB side/end ternary structure
// reproduce the caller's 1C frame and CSE allocation. Layout facts below are
// target loads; original function names and complete class extents are unknown.
typedef int Int;
enum PathfindLayerEnum { INVALID_PATHFIND_LAYER = -1 };
class Object {public: signed char rva0028CE7B() const;};
struct DiameterOccupant {DiameterOccupant *next; int unused; Object*object;};
struct DiameterCellInfo {char unused[0x20]; DiameterOccupant *occupants;
 int unused24; int unused28; unsigned int flags;};
class Rva0052DB11 {public: bool rva0052DB11(int);};
class PathfindCell {public: DiameterCellInfo *info; char m_pad[8];
 unsigned int m_flags;
 unsigned char obstacleFence()const{return info?(info->flags>>1)&1:0;}
};
class Pathfinder {public:
 PathfindCell*getCell(PathfindLayerEnum,Int,Int);
 Int rva002E7749(void*,Int,Int,Int,Int,bool);
};
// ZH AIPathfind.cpp clearCellForDiameter semantic guide; target D4D280
// separates the cell test. Native field offsets and unsigned crusher compare.
static __declspec(noinline) bool rva002E76D3(PathfindCell *cell, unsigned int crusher, bool occupants)
{
 if (occupants && reinterpret_cast<Rva0052DB11 *>(cell)->rva0052DB11(0)) {
  DiameterOccupant *it=cell->info ? cell->info->occupants : 0;
  for (; it; it=it->next) {
   if ((unsigned int)it->object->rva0028CE7B() > crusher) return false;
  }
 }
 unsigned int type=cell->m_flags & 15;
 switch (type) {
 case 0: return true;
 case 4: return crusher!=0 && cell->obstacleFence();
 default: return false;
 }
}
Int Pathfinder::rva002E7749(void *crusher, Int cellX, Int cellY, Int layer, Int diameter, bool exact)
{
 Int radius=diameter/2;
 Int above=radius;
 if (!radius) above++;
 Int i; Int j;
 if (radius>1) {
  for (i=cellX-radius; i<cellX+above; ++i) {
   bool side=i==cellX-radius || i==cellX+above-1;
   Int end=side?cellY+above-1:cellY+above;
   for (j=side?cellY-radius+1:cellY-radius; j<end; ++j) {
    PathfindCell *cell=getCell((PathfindLayerEnum)layer,i,j);
    if (!cell || !rva002E76D3(cell,(unsigned int)crusher,true)) {
     if (exact) return 0;
     return rva002E7749(crusher,cellX,cellY,layer,diameter-2,false);
    }
   }
  }
 } else {
  for (i=cellX-radius; i<cellX+above; ++i) {
   for (j=cellY-radius; j<cellY+above; ++j) {
    PathfindCell *cell=getCell((PathfindLayerEnum)layer,i,j);
    if (!cell || !rva002E76D3(cell,(unsigned int)crusher,true)) return 0;
   }
  }
 }
 if (radius==0) return 1;
 return radius*2;
}
