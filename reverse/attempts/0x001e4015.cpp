// ?rva001E4015@Rva001E46E1@@QAE_NPAVObject@@PBUCoord3D@@@Z
// partial score=0.8788606726 date=2026-10-09
// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD /arch:SSE /G7
// Native1E4015..1E4073 RET8 complete94; Path365E98 call proves entry
// receiver plus Object*/destination pointer and AL Bool. Only settings mode74
// equal1 and nonzeroD8 permit the direction test. Rowed Thing30A2A2 fills
// canonical Coord3D; destination-minus-Object position38/3C dot heading<0.
// Original method and mode names remain unknown; target facts are offsets,
// call shape and arithmetic. No new callee pins or class layout assertions.
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
typedef bool Bool;
class Object;
class Thing {public:void getUnitDirectionVector2D(Coord3D &)const;};
struct Direction4015Template {char pad00[0x74];int mode74;char pad78[0xD8-0x78];int flagD8;};
struct Direction4015Entry {void *word0;Direction4015Template *settings;};
struct Direction4015Object {char pad00[0x38];Coord3D pos;};
class Rva001E46E1 {public:Bool rva001E4015(Object *,const Coord3D *);};
Bool Rva001E46E1::rva001E4015(Object *obj,const Coord3D *dest)
{
 Direction4015Entry *entry=(Direction4015Entry *)this;
 if(entry->settings->mode74==1) {
  if(entry->settings->flagD8) {
   Coord3D direction;((const Thing *)obj)->getUnitDirectionVector2D(direction);
   const Coord3D *pos=&((const Direction4015Object *)obj)->pos;
   float x=dest->x-pos->x;float y=dest->y-pos->y;direction.x*=x;direction.y*=y;float dot=direction.y+direction.x;
   if(dot<0.0f)return true;
  }
 }
 return false;
}
