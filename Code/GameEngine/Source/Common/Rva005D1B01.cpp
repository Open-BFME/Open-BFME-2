// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native005D1B01..005D1B85 is a complete132B method, RET at1B84.
// Old boundary refusals inspected a wrong image address. The native body
// invokes two existing owner hooks, resolves regionID at nested10+4
// through Logic+B0, reads its center into two floats, obtains ground Z,
// places the point on the C subobject, then dispatches slot1C with region10.
// Purpose and owner remain address-derived; offsets and call ABIs are
// independently established from this body. Existing providers are reused.
#include "Coord3D.h"
#include "vector3.h"
class Rva000B3FD0Empty {public:void rva000B3FD0Empty();};
class Rva005CCB5B {public:void rva005CCB5B();};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C*rva0020EAF6(int);};
#include "../../../Libraries/Include/Lib/Coord2D.h"
class LivingWorldRegionManager {public:bool GetRegionCenterPoint(Rva0020E89C*,Coord2D*);};
class Rva002BF4F3 {public:bool rva002BF5B0(const Vector3*,Vector3*);};
class Rva002D3627Host {public:void rva002BF09E(const Coord3D*);};
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
struct RegionIDRecord {char unknown0[4];int id;};
class Rva005D1B01 {public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void finish(RegionIDRecord*);
 void rva005D1B01();
 char pad04[8];Rva002D3627Host*position0C;RegionIDRecord*region10;
};
void Rva005D1B01::rva005D1B01(){
 ((Rva000B3FD0Empty*)this)->rva000B3FD0Empty();
 ((Rva005CCB5B*)this)->rva005CCB5B();
 Rva0020EAF6View*manager=*(Rva0020EAF6View**)((char*)TheLivingWorldLogic+0xB0);
 Rva0020E89C*region=manager->rva0020EAF6(region10->id);
 Coord2D xy;
 if(((LivingWorldRegionManager*)manager)->GetRegionCenterPoint(region,&xy)){
  Coord3D center;center.x=xy.x;center.y=xy.y;center.z=0;
  ((Rva002BF4F3*)position0C)->rva002BF5B0((const Vector3*)&xy,(Vector3*)&center);
  position0C->rva002BF09E(&center);
 }
 finish(region10);
}
