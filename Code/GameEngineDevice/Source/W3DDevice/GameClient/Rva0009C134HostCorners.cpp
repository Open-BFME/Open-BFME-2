// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?rva0009B7EA@Rva0009C134Host@@QAEXPAUCoord3D@@@Z retail 0x0009B7EA..0x0009BAA4 (698 B, ret 4).
// Projects the four camera-frustum corner rays of the +0xC0 camera onto z=0
// (outputs Coord3D[4]). Shape follows ZH HeightMap's visible-area projection:
// xscale/yscale from Get_View_Plane 0x00134080, zmod=-1 view-plane distance,
// per-corner xmod/ymod against the viewport Min (+0xC8/+0xCC), ray direction
// xmod*m[r][0]+ymod*m[r][1]+zmod*m[r][2] (the zmod terms are loop-invariant,
// hoisted by cl), Normalize (Inv_Sqrt 0x0004233A), Get_Position 0x0013B8A0 and
// Vector3::Find_X/Y_At_Z. Transform via virtual Validate_Transform (slot 20,
// +0x50) and the matrix at +0x18. Owner/method names not established.
#include "matrix3d.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
class Rva0009C134Host {public:void rva0009B7EA(Coord3D*);char pad[0xc0];CameraClass*camera;};
void Rva0009C134Host::rva0009B7EA(Coord3D*out){
CameraClass *cam=camera;
Vector2 lo,hi;
cam->Get_View_Plane(lo,hi);
Matrix3D tm=camera->Get_Transform();
const ViewportClass &viewport=cam->Viewport;
float xscale=(hi.X-lo.X);
float yscale=(hi.Y-lo.Y);
float zmod=-1.0f;
for(int i=0;i<4;++i){
int x,y;
switch(i){case 0:x=0;y=1;break;case 1:x=1;y=1;break;case 2:x=0;y=0;break;case 3:x=1;y=0;break;default:x=0;y=0;break;}
float xmod=(x-0.5-viewport.Min.X)*xscale;
float ymod=(y-0.5-viewport.Min.Y)*yscale;
Vector3 dir(xmod*tm[0][0]+ymod*tm[0][1]+zmod*tm[0][2],xmod*tm[1][0]+ymod*tm[1][1]+zmod*tm[1][2],xmod*tm[2][0]+ymod*tm[2][1]+zmod*tm[2][2]);
dir.Normalize();
Vector3 p=camera->Get_Position()+dir;
float xx=Vector3::Find_X_At_Z(0.0f,camera->Get_Position(),p);
float yy=Vector3::Find_Y_At_Z(0.0f,camera->Get_Position(),p);
out[i].x=xx;out[i].y=yy;out[i].z=0.0f;
}
}
