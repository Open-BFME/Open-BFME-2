// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native2ED236..2ED313 RET16 complete221. Object argument and a 12-byte
// by-value position proved by the six callers (TerrainLogicBridges,
// PathfinderUpdateLayer, pathfinder, PathfinderBridgeUpdateRva0052ED74,
// ObjectRva00291A8C, ObjectScriptStatus): each builds the argument with an
// inline member-wise copy and stores its address (mov [ebp+8],esp at
// 0x002F12A3), and the WorldBuilder twin (0x00D3FA00) enters EH state 0 for
// the parameter, so its class has a user ctor and a destructor, which the
// canonical aggregate Coord3D lacks. Its real name is unknown: Rva002ED236Pos is the
// callers' placeholder spelling. Bridge scan2..15 through
// enabled layer record; packed cell layer/type and fixed integer height.
// Independently decoded float literals: BC4EB8=5.0 and C52ACC=25.0.
#include "Lib/Coord3D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
class Object;
class Rva0028B984ByteField {public:unsigned char get()const;};
unsigned char Rva002EBBFBIsOdd(void *);
struct Rva002ED236Pos {float x,y,z;Rva002ED236Pos(const Coord3D &p){x=p.x;y=p.y;z=p.z;}~Rva002ED236Pos(){}};
class Rva0036666B {public:char pad00[0x34];int word34,word38;bool rva0036666B();};
struct BridgeLayerEntry {Rva0036666B check;int height;};
struct BridgeLayerCell {char pad00[0xC];unsigned int flags;};
class Pathfinder {
public:
 PathfindLayerEnum rva002ED236(Object *,Rva002ED236Pos);
 void *rva001E3647Pos(int,const Coord3D *);
 char pad00[0xE0];BridgeLayerEntry entries[14];
};
PathfindLayerEnum Pathfinder::rva002ED236(Object *obj,Rva002ED236Pos pos)
{
 if(obj) {
  if(((Rva0028B984ByteField *)obj)->get())return GROUND_LAYER;
  if(!Rva002EBBFBIsOdd(obj)) {pos.x+=5.0f;pos.y+=5.0f;}
 }
 int layer=2;int *enabled=&entries[0].check.word38;
 for(;;) {
  Rva0036666B *check=(Rva0036666B *)(enabled-14);
  if(check->rva0036666B() && *enabled) {
   BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(layer,reinterpret_cast<const Coord3D *>(&pos));
   if(cell) {
    unsigned int flags=cell->flags;
    if(((flags>>4)&0x3F)==(unsigned int)layer && (flags&0xF)!=5) {
     float height=(float)enabled[1];float delta=height-pos.z;
     if(25.0f>delta)return (PathfindLayerEnum)layer;
    }
   }
  }
  ++layer;enabled+=16;if(layer>15)break;
 }
 BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(1,reinterpret_cast<const Coord3D *>(&pos));
 if(cell)return(PathfindLayerEnum)((cell->flags>>4)&0x3F);
 return GROUND_LAYER;
}
