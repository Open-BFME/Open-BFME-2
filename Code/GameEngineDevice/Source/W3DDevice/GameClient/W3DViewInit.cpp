// cl: /DNDEBUG /MD /EHsc /Oy- /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Reference-first recovery of GeneralsMD W3DView::init (GPLv3), reviewed at
// BFME1 revision 874e38488c7dcf8cf3343452e8e5371bb3a0e64c.
// Target evidence: native 0x0008C224..0x0008C3AC, "W3DView" name,
// CameraClass constructors and viewport calls; WorldBuilder 0x00988E40
// agrees on initialization purpose, camera offsets 0x104/0x108, and settings
// at 0x24C8. BFME2 adds settings.reload/reset and the 0x24C4 clear.
// All offsets below are target observations; BFG/settings names preserve
// the existing ledger's address-derived identities rather than new claims.
#include "vector3.h"
#include "vector2.h"
#include "ascii_string.h"
class SubsystemInterface {public:void setName(AsciiString);};
class BfmeThingBFG {public:void bfmeGoBFG();};
class CameraClass {public:
 CameraClass();
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();
 virtual void s04();virtual void s05();virtual void s06();virtual void s07();
 virtual void s08();virtual void s09();virtual void s10();virtual void s11();
 virtual void s12();virtual void s13();virtual void s14();virtual void s15();
 virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void s20();virtual void s21();virtual void Set_Position(const Vector3&);
 void Set_View_Plane(const Vector2&,const Vector2&);void Set_Clip_Planes(float,float);
 char pad[0x3fc-4];
};
#include "Coord3D.h"
class Rva00BCF670CameraSettings {
public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();
 virtual void v04();virtual void v05();virtual void v06();virtual void v07();
 virtual void v08();virtual void v09();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void reload();void reset();
};
class GlobalData {public:char prefix[0xaac];float scrollCutoff;};
extern GlobalData *TheWritableGlobalData;
class W3DView {public:
 virtual void init();private:void setCameraTransform();
 char prefix[0xc-4];Coord3D position;
 char gap18[0xb4-0x18];SubsystemInterface subsystem;
 char gapb5[0x104-0xb5];CameraClass *camera3d;CameraClass *camera2d;
 char gap10c[0x2404-0x10c];float scrollCutoff;
 char gap2408[0x241c-0x2408];bool constraintValid;
 char gap241d[0x24c4-0x241d];int value24c4;
 Rva00BCF670CameraSettings settings;
};
void W3DView::init(){
 reinterpret_cast<BfmeThingBFG*>(this)->bfmeGoBFG();subsystem.setName("W3DView");
 Coord3D pos;pos.x=87.0f;pos.y=77.0f;pos.z=0;pos.x*=10.0f;pos.y*=10.0f;position=pos;
 camera3d=new CameraClass;settings.reload();setCameraTransform();
 camera2d=new CameraClass;camera2d->Set_Position(Vector3(0,0,1));
 Vector2 min(-1,-0.75f),max(1,0.75f);camera2d->Set_View_Plane(min,max);camera2d->Set_Clip_Planes(0.995f,2.0f);
 constraintValid=false;scrollCutoff=TheWritableGlobalData->scrollCutoff;value24c4=0;settings.reset();
}
