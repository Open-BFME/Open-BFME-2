// cl: /O1 /G7 /ICode/Libraries/Include /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Native89510..89658328B and caller89D1D establish thiscall RET12,
// Bool/float/int stack arguments and the waypoint-array receiver. Preserve
// the existing neutral thiscall binding used by the matched setup callers.
// ZH/BF1 camera path setup supplies the direction/orientation purpose;
// native accesses establish the20B waypoint record, angles and count2070.
// Ratio and final angle are distinct values. A same-valued Bool guard at
// the ratio's Acos use preserves separate lifetimes: retail spills ratio
// into the dead endpoint home, then angle into the dead orientation home.
// Existing file-static121B normAngle keeps its proven private EAX ABI.
#include "Lib/BaseType.h"
#include "vector2.h"
#include "wwmath.h"
#pragma auto_inline(off)
static void normAngle(float &angle)
{
	if (angle < -10*3.14159265359f) {
		angle = 0;
	}
	if (angle > 10*3.14159265359f) {
		angle = 0;
	}
	while (angle < -3.14159265359f) {
		angle += 2*3.14159265359f;
	}
	while (angle > 3.14159265359f) {
		angle -= 2*3.14159265359f;
	}
}
#pragma auto_inline(on)

// Data-only target path prefix; these are observations, not donor class names.
// Array owner Rva0089971 has this prefix, established by its ctor8990C/dtor89971.
class Rva00089510{public:void rva00089510(Bool,Real,Int);};
class Rva0089971;
struct BfmePathWaypoint20 { Coord3D position; void *nameStorage; int lastWord; };
struct BfmePathAnglesFields {
 unsigned char pad00[0x2C]; BfmePathWaypoint20 waypoints[255], extra[4];
 Real angles[255]; unsigned char pad1864[0x2070-0x1864]; Int count;
};
static __forceinline Real cameraSqrt(const Real&f){Real local=f;return WWMath::Sqrt(local);}
void Rva00089510::rva00089510(Bool orient,Real angle,Int firstWaypoint) {
 BfmePathAnglesFields *fields=(BfmePathAnglesFields *)this;
 Real *cameraAngle=fields->angles;
 if(orient) {
  ++cameraAngle;
  for(Int i=2;i<fields->count+2;++i) {
   Vector2 direction;
   Real *current=&fields->waypoints[i].position.x;
   Real *next=&fields->waypoints[i+firstWaypoint].position.x;
   direction.X=*current-*next; direction.Y=current[1]-next[1];
   Real pathAngle=direction.Y*direction.Y+direction.X*direction.X;
   pathAngle=cameraSqrt(pathAngle);
   Real ratio=direction.X/pathAngle;
   if(ratio < -1.0f) ratio=-1.0f;
   else if(ratio > 1.0f) ratio=1.0f;
   if(direction.Y<0.0f) pathAngle=-WWMath::Acos((orient?ratio:ratio)); else pathAngle=WWMath::Acos((orient?ratio:ratio));
   pathAngle=pathAngle-1.57079637050628662109375f;
   normAngle(pathAngle); *cameraAngle++=pathAngle;
  }
  fields->angles[1]=angle; fields->angles[0]=angle;
 } else {
  Real *end=cameraAngle+fields->count;
  for(Real *p=cameraAngle;p!=end;++p) *p=angle;
 }
}
