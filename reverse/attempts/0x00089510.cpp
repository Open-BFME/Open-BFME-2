// ?Rva00089510CameraPathAngles@@YIXPAVRva0089971@@PAX_NMH@Z
// partial score=0.9417590539541758 date=2026-10-10
// ?Rva00089510CameraPathAngles@@YIXPAVRva0089971@@PAX_NMH@Z
// partial score=0.951 date=2026-10-09
// cl: /O1 /G7 /ICode/Libraries/Include /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// Bank attaches to the already verified private-EAX normAngle owner.
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
class Rva0089971;
struct BfmePathWaypoint20 { Coord3D position; void *nameStorage; int lastWord; };
struct BfmePathAnglesFields {
 unsigned char pad00[0x2C]; BfmePathWaypoint20 waypoints[255], extra[4];
 Real angles[255]; unsigned char pad1864[0x2070-0x1864]; Int count;
};
void __fastcall Rva00089510CameraPathAngles(Rva0089971 *owner, void *, Bool orient, Real angle, Int firstWaypoint) {
 BfmePathAnglesFields *fields=(BfmePathAnglesFields *)owner;
 Real *cameraAngle=fields->angles;
 if(orient) {
  ++cameraAngle;
  for(Int i=2;i<fields->count+2;++i) {
   Vector2 direction;
   Real *current=&fields->waypoints[i].position.x;
   Real *next=&fields->waypoints[i+firstWaypoint].position.x;
   direction.X=*current-*next; direction.Y=current[1]-next[1];
   Real pathAngle=direction.Y*direction.Y+direction.X*direction.X;
   pathAngle=WWMath::Sqrt(pathAngle);
   pathAngle=direction.X/pathAngle;
   if(pathAngle < -1.0f) pathAngle=-1.0f;
   else if(pathAngle > 1.0f) pathAngle=1.0f;
   if(direction.Y<0.0f) pathAngle=-WWMath::Acos(pathAngle); else pathAngle=WWMath::Acos(pathAngle);
   pathAngle-=1.57079637050628662109375f;
   normAngle(pathAngle); *cameraAngle++=pathAngle;
  }
  fields->angles[1]=angle; fields->angles[0]=angle;
 } else {
  Real *end=cameraAngle+fields->count;
  for(Real *p=cameraAngle;p!=end;++p) *p=angle;
 }
}
