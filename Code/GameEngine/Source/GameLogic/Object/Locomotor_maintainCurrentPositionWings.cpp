// cl: /O1 /G7 /arch:SSE /MD
// Locomotor wings position-maintenance helper, retail 0x001E7CDF (326 bytes;
// WB 0x00AF0740): Zero Hour / BFME 1 Locomotor::maintainCurrentPositionWings
// adapted (no Physics argument). The unrowed minimum-speed helper 0x001E4073
// is pinned under its address-derived name. Protected, as in ZH's Locomotor.h.
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include <math.h>
#include "../../Common/Thing/thing.h"
class Object;
int __cdecl Rva001E3896Check(float);
float Cos(float); float Sin(float);
struct Rva001E3F08Arg;
struct Rva001E3F08MidA;
class Rva001E3F08
{
public:
	float rva001E3F2E(Rva001E3F08Arg *p);
	float rva001E3F08(Rva001E3F08Arg *p);
	char m_pad00[0x4];
private:
	Rva001E3F08MidA *m_p04; // +0x04
};
#include "../../../Include/GameLogic/Module/Rva001E7C2B.h"
class Rva001E4073
{
public:
	float rva001E4073(Object *obj, float *out);
};
struct WingsObjectView { char gap[0x38]; Coord3D position; float angle; float getOrientation() const { return angle; } const Coord3D *getPosition() const { return &position; } };
struct WingsTemplateView { char gap[0x64]; float radius; };
#include "../../../Include/GameLogic/LocomotorClass.h"
void Locomotor::maintainCurrentPositionWings(Object *obj) {
 if(((Thing *)obj)->isAboveTerrain()) {
  m_flags|=0x10;
  float radius=((const WingsTemplateView *)m_template)->radius;
  if(radius==0.0f) radius=((Rva001E4073 *)this)->rva001E4073(obj,0);
  WingsObjectView *object=(WingsObjectView *)obj;
  float dx=m_maintainPos.x-object->getPosition()->x;
  float dy=m_maintainPos.y-object->getPosition()->y;
  float angle=((unsigned char)Rva001E3896Check(dx) && (unsigned char)Rva001E3896Check(dy)) ? object->getOrientation() : atan2(dy,dx);
  float aimDir=(3.14159265358979323846f-3.14159265358979323846f/8);
  if(radius<0) { radius=-radius;aimDir=-aimDir; }
  angle+=aimDir;
  Coord3D desired; desired.x=m_maintainPos.x; desired.y=m_maintainPos.y; desired.z=m_maintainPos.z;
  desired.x+=Cos(angle)*radius;
  desired.y+=Sin(angle)*radius;
  ((Rva001E7C2B *)this)->rva001e7c2b((unsigned)obj,(unsigned)&desired,0,((Rva001E3F08 *)this)->rva001E3F08((Rva001E3F08Arg *)obj));
 }
}
