// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native2ED236..2ED313 RET16 complete221. By-value Coord3D ABI and Object
// argument proved by existing TerrainLogic and UpdateLayer callers. Existing
// address-derived canonical-Coord3D pin retained. Bridge scan2..15 through
// enabled layer record; packed cell layer/type and fixed integer height.
// Independently decoded float literals: BC4EB8=5.0 and C52ACC=25.0.
#include "Lib/Coord3D.h"
enum PathfindLayerEnum {UNKNOWN_LAYER=0,GROUND_LAYER=1};
class Object;
class Rva0028B984ByteField {public:unsigned char get()const;};
unsigned char Rva002EBBFBIsOdd(void *);
class Rva0036666B {public:char pad00[0x34];int word34,word38;bool rva0036666B();};
struct BridgeLayerEntry {Rva0036666B check;int height;};
struct BridgeLayerCell {char pad00[0xC];unsigned int flags;};
class Pathfinder {
public:
 PathfindLayerEnum rva002ED236(Object *,Coord3D);
 void *rva001E3647Pos(int,const Coord3D *);
 char pad00[0xE0];BridgeLayerEntry entries[14];
};
PathfindLayerEnum Pathfinder::rva002ED236(Object *obj,Coord3D pos)
{
 if(obj) {
  if(((Rva0028B984ByteField *)obj)->get())return GROUND_LAYER;
  if(!Rva002EBBFBIsOdd(obj)) {pos.x+=5.0f;pos.y+=5.0f;}
 }
 int layer=2;int *enabled=&entries[0].check.word38;
 for(;;) {
  Rva0036666B *check=(Rva0036666B *)(enabled-14);
  if(check->rva0036666B() && *enabled) {
   BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(layer,&pos);
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
 BridgeLayerCell *cell=(BridgeLayerCell *)rva001E3647Pos(1,&pos);
 if(cell)return(PathfindLayerEnum)((cell->flags>>4)&0x3F);
 return GROUND_LAYER;
}
