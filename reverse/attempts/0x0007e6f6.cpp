// ?rva0007E6F6@Rva0007E6F6@@QAEABUWaterRenderBox@@XZ
// partial score=0.97 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Native7E6F6..7E7DD231B, RET0. WB73D880 reproduces lazy min/max box.
// BFME1 575ba2b04 Vector3 operators supply clean math; target proves footprint.
#include "vector3.h"
class Rva0007E02A { public: void *rva0007E02A(void*); };
class WaterAreaHeightView { public: virtual void f0();virtual void f1();virtual int height(); };
struct WaterRenderBox {Vector3 center,extent;};
class Rva0007E6F6 {
 char unknown00[0xC];char *area;char unknown10[0x10];bool ready;
 WaterRenderBox bounds;
 __forceinline char *scalarBase() {return area+0x18+reinterpret_cast<int*>(*reinterpret_cast<void**>(area+0x18))[1];}
public: const WaterRenderBox &rva0007E6F6();
};
const WaterRenderBox &Rva0007E6F6::rva0007E6F6() {
 if(!ready) {
  float rectangle[4];
  reinterpret_cast<Rva0007E02A*>(scalarBase())->rva0007E02A(rectangle);
  Vector3 minimum(rectangle[0],rectangle[1],float(reinterpret_cast<WaterAreaHeightView*>(scalarBase())->height()));
  Vector3 maximum(rectangle[2],rectangle[3],float(reinterpret_cast<WaterAreaHeightView*>(scalarBase())->height()));
  bounds.center=0.5f*(minimum+maximum);
  bounds.extent=0.5f*(maximum-minimum);
  ready=true;
 }
 return bounds;
}
