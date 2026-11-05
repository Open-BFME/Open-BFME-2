// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?rva0009BF33@Rva0009BF33@@QAEXPAVRva0009BF33Point@@PAVVector3@@PAUCoord3D@@@Z, retail 0x0009BF33 (440 B).
// Screen point to camera ray: view-plane extents from the camera, the point taken
// either raw against the display size or relative to the +0x1B8/+0x1BC viewport,
// scaled into the camera matrix rows (z -1), normalized, with the ray start at the
// camera position. Shape from ZH wbview3d.cpp viewToDocCoords and the BFME1 game
// twin Rva006FE3C0CameraRay.cpp; the camera matrix is read through the real WWMath
// Matrix3D and an inline Get_Transform reference as in sibling 0x9B7EA
// (Rva0009C134HostCorners.cpp). Receiver and method names are address-derived.
#include "matrix3d.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#include "../../../../GameEngine/Include/GameClient/Display.h"
extern Display *TheDisplay;
class Rva0009BF33Point {public:int x;int y;
 Rva0009BF33Point operator-(const Rva0009BF33Point &v) const {Rva0009BF33Point r;r.x=x-v.x;r.y=y-v.y;return r;}
};
class Rva0009BF33 {public:
void rva0009BF33(Rva0009BF33Point *screen, Vector3 *rayStart, Coord3D *rayEnd);
char m_pad00[0x19];bool m_19;char m_pad1a[0xC0-0x1A];CameraClass *m_camera;
char m_padC4[0x1B0-0xC4];Rva0009BF33Point m_origin;int m_width;int m_height;
};
void Rva0009BF33::rva0009BF33(Rva0009BF33Point *screen, Vector3 *rayStart, Coord3D *rayEnd)
{
 const Matrix3D &camera_matrix = m_camera->Get_Transform();
 Vector2 min,max;
 m_camera->Get_View_Plane(min,max);
 float xscale = (max.X - min.X);
 float yscale = (max.Y - min.Y);
 float width, height;
 int x, y;
 if (!m_19) {
  width = (float)TheDisplay->getWidth();
  height = (float)TheDisplay->getHeight();
  x = screen->x; y = screen->y;
 } else {
  width = (float)m_width;
  height = (float)m_height;
  Rva0009BF33Point point = *screen - m_origin;
  x = point.x; y = point.y;
 }
 float zmod = -1.0f;
 float xmod = ((float)x / width - 0.5f) * xscale;
 float ymod = -(((float)y / height - 0.5f) * yscale);
 float rx = xmod*camera_matrix[0][0] + ymod*camera_matrix[0][1] + camera_matrix[0][2]*zmod;
 float ry = xmod*camera_matrix[1][0] + ymod*camera_matrix[1][1] + camera_matrix[1][2]*zmod;
 float rz = xmod*camera_matrix[2][0] + ymod*camera_matrix[2][1] + camera_matrix[2][2]*zmod;
 rayEnd->x = rx; rayEnd->y = ry; rayEnd->z = rz;
 rayEnd->Normalize();
 Vector3 position = m_camera->Get_Position();
 rayStart->X = position.X; rayStart->Y = position.Y; rayStart->Z = position.Z;
}
