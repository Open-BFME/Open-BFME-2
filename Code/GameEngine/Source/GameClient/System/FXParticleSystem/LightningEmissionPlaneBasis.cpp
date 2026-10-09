// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /ICode/Libraries/Include /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#include "Lib/Coord3D.h"
#include "vector3.h"
class Rva0055DBD3 {public:void rva0055DBD3(Coord3D*,const void*,float,float);char unknown[0xC];Coord3D start,end;};
// Native55DBD3..55DCBB/WB141C7E0: normalize endpoint difference; cross
// up with direction, then direction with first basis; combine two scales.
// ZH Vector3 cross implementation is the semantic guide; owner unnamed.
void Rva0055DBD3::rva0055DBD3(Coord3D*out,const void*,float a,float b){
 Coord3D direction;direction.x=end.x-start.x;direction.y=end.y-start.y;direction.z=end.z-start.z;direction.normalize();
 Vector3 first,second,up(0,0,1);
 Vector3::Cross_Product(up,*(Vector3*)&direction,&first);
 Vector3::Cross_Product(*(Vector3*)&direction,first,&second);
 out->x=a*first.X+b*second.X;out->y=a*first.Y+b*second.Y;out->z=a*first.Z+b*second.Z;
}
