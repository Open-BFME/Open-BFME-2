// cl: /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD
// Native [002BF61B,002BF652),55B, RET4. Zero a temporary point, project
// its incoming XY through owned ground helper2BF5B0, and submit through
// owned camera-view placement2BF09E. Preserve the already pinned word ABI.
#include "Coord3D.h"
class Vector3;
class Rva002BF4F3 {public: bool rva002BF5B0(const Vector3 *,Vector3 *);};
class Rva002D3627Host {public:void rva002BF09E(const Coord3D *);};
class Rva002BF6A7 {public:void rva002BF61B(int);};
void Rva002BF6A7::rva002BF61B(int input){
 Coord3D point;point.x=0.0f;point.y=0.0f;point.z=0.0f;
 ((Rva002BF4F3*)this)->rva002BF5B0((const Vector3*)input,(Vector3*)&point);
 ((Rva002D3627Host*)this)->rva002BF09E(&point);
}
