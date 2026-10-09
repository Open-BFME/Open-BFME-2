// ?rva004DFCE6@Rva004DFCE6@@QAEXPAVObject@@PAX@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/Libraries/Include/Lib
// stlport
#include <vector>
#include "Coord3D.h"
class Object;
struct SpherePointValue { float x,y,z; SpherePointValue(const Coord3D &p):x(p.x),y(p.y),z(p.z){} };
class Rva004DFA43 { public: bool rva004DFA43(void*,void*); };
class Rva004DFCE6 {
public:
 void rva004DFCE6(Object*,void*);
 bool active00;
 float radius04;
 Coord3D center08;
 float padding14;
 bool selected18;
 _STL::vector<Object*> objects1C;
};
void Rva004DFCE6::rva004DFCE6(Object *object,void *callback)
{
 float padding=padding14;
 _STL::vector<Object*> *objects=&objects1C;
 if(objects->empty()) {
  radius04=padding14;
  center08=*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object);
 } else if(!reinterpret_cast<Rva004DFA43*>(this)->rva004DFA43(object,callback)) {
  SpherePointValue old(center08);
  SpherePointValue position(*reinterpret_cast<const Coord3D*(__cdecl *)(Object*)>(callback)(object));
  Coord3D direction;
  direction.x=old.x-position.x;
  direction.y=old.y-position.y;
  direction.z=old.z-position.z;
  float distance=direction.length();
  direction.normalize();
  Coord3D opposite={0.0f-direction.x,0.0f-direction.y,0.0f-direction.z};
  float oldRadius=radius04;
  Coord3D edge={old.x+direction.x*oldRadius,old.y+direction.y*oldRadius,old.z+direction.z*oldRadius};
  float radius=(oldRadius+distance+padding)*0.5f;
  Coord3D adjustment={opposite.x*radius,opposite.y*radius,opposite.z*radius};
  direction.x=edge.x+adjustment.x;
  direction.y=edge.y+adjustment.y;
  direction.z=edge.z+adjustment.z;
  radius04=radius;
  center08=direction;
 }
 objects->push_back(object);
}
