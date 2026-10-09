// cl: /DNDEBUG /MD /EHsc /Oy- /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native860AF..8615B and WB991E30 prove the constrained-position helper.
// BFME1/GeneralsMD W3DView camera constraints provide the subsystem context;
// target adds a camera-minus-position horizontal quarter-offset around the
// settings24C8 slot21 constrainPosition call. WB's Vector3 operations prove
// the single reused offset object; native uses its dead Get_Position result
// slots, preserving a 12-byte frame. Camera104/positionC/constrain44/settings24C8
// are independently read from target. Original member name remains unknown.
#include "vector3.h"
#include "Coord3D.h"
class RenderObjClass {public:Vector3 Get_Position()const;};
class BfmeConstraintSettings {public:
 virtual void v00();virtual void v01();virtual void v02();virtual void v03();
 virtual void v04();virtual void v05();virtual void v06();virtual void v07();
 virtual void v08();virtual void v09();virtual void v10();virtual void v11();
 virtual void v12();virtual void v13();virtual void v14();virtual void v15();
 virtual void v16();virtual void v17();virtual void v18();virtual void v19();
 virtual void v20();virtual void constrainPosition(Coord3D*);
};
class W3DView {private:void rva000860AF(Coord3D*);private:
 char prefix[0xc];Coord3D position;char gap18[0x44-0x18];bool constrain;
 char gap45[0x104-0x45];RenderObjClass *camera;
 char gap108[0x24c8-0x108];BfmeConstraintSettings settings;
};
void W3DView::rva000860AF(Coord3D* p){
 if(!constrain)return;
 Vector3 offset=camera->Get_Position();
 offset-=Vector3(position.x,position.y,position.z);
 offset.Z=0;offset*=0.25f;
 p->x+=offset.X;p->y+=offset.Y;
 settings.constrainPosition(p);
 p->x-=offset.X;p->y-=offset.Y;
}
