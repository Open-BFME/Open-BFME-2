// cl: /O1 /G7 /arch:SSE /MD /EHsc /ICode/Libraries/Include
#include "Lib/Coord3D.h"
class GameClientRandomVariable {public:float getValue()const;int mode;float minimum,maximum;};
Coord3D* __cdecl Rva003AFA64FillUnitVector(Coord3D*);
class Rva00564AB8 {public:void rva00564AB8(Coord3D*,const void*,const void*);char unknown00[0x1C];GameClientRandomVariable speed;};
// Native564AB8..564B06 and WB142EFA0: sample speed at1C and normalized
// random direction; second/third stack words unused. Original owner/name unknown.
void Rva00564AB8::rva00564AB8(Coord3D*out,const void*,const void*) {
 float value=speed.getValue();
 Coord3D direction;Rva003AFA64FillUnitVector(&direction);
 direction.x*=value;direction.y*=value;direction.z*=value;
 out->x=direction.x;out->y=direction.y;out->z=direction.z;
}
