// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Native 0x001028AA..0x00102A12, 360 bytes, RET16; ECX is unused.
// Primary source guide: ZH W3DView::getPickRay in W3DView.cpp (543-559),
// through verified BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f.
// Target uses four explicit pointers and a view prefix: width/height BC/C0,
// screen origin C4/C8, camera CC. The camera depth is read at absolute F0.
// Native calls independently rowed PixelScreenToW3DLogicalScreen 101E6D,
// RenderObjClass::Get_Position 13B8A0, CameraClass::Un_Project 133BC0 and
// WWMath::Inv_Sqrt 4233A. Vector3 arithmetic follows the reference body.
// The declaration-only base and measured camera/view prefixes are used only
// through borrowed pointers; no complete allocation layout is asserted.
// The original helper and view-owner spelling remain unknown.
#include "vector3.h"
#include "vector2.h"
struct ICoord2D {int x,y;};
class RenderObjClass {public: Vector3 Get_Position() const;};
class CameraClass:public RenderObjClass {
public:
    void Un_Project(Vector3 &,const Vector2 &) const;
    char unknown00[0xF0]; float depth;
};
struct Rva001028AAView {
    char unknown00[0xBC];
    int width,height,originX,originY;
    CameraClass *camera;
};
void PixelScreenToW3DLogicalScreen(int,int,float *,float *,int,int);
void __stdcall Rva001028AAPickRay(const ICoord2D *screen,Vector3 *start,Vector3 *end,Rva001028AAView *view)
{
    float logX,logY;
    PixelScreenToW3DLogicalScreen(screen->x-view->originX,screen->y-view->originY,&logX,&logY,view->width,view->height);
    *start=view->camera->Get_Position();
    view->camera->Un_Project(*end,Vector2(logX,logY));
    *end-=*start;
    end->Normalize();
    *end*=view->camera->depth;
    *end+=*start;
}
