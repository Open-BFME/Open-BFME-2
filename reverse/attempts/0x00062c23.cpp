// ?rva00062C23@Rva00062C23Host@@QAEMPBUCoord3D@@0@Z
// partial score=0.705882 date=2026-10-09
// cl: /O1 /Oy- /DNDEBUG /MD /arch:SSE /ICode/Libraries/Include
#include "Lib/Coord3D.h"
class BaseHeightMapRenderObjClass {public:float EstimateMaxHeightAlongLine(const Coord3D&,const Coord3D&)const;};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class Rva00062C23Host {public:float rva00062C23(const Coord3D*,const Coord3D*);};
float Rva00062C23Host::rva00062C23(const Coord3D*a,const Coord3D*b){
 if(TheTerrainRenderObject)return TheTerrainRenderObject->EstimateMaxHeightAlongLine(*a,*b);
 float value=0.0f;return value;
}
