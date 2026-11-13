// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Oy- /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// ?rva0007E6F6@Rva0007E6F6@@QAEABUWaterRenderBox@@XZ, retail 0x0007e6f6, 231 bytes. Banked partial (score 0.97) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native7E6F6..7E7DD231B, RET0. WB73D880 reproduces lazy min/max box.
// BFME1 575ba2b04 Vector3 operators supply clean math; target proves footprint.
// Scoped donor math below keeps assignments/arithmetic inline and suppresses
// competing COMDAT copies. The complete target body/relocations are unchanged;
// the compiled unit has no imported math/helper references.
#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
static __forceinline Vector3 &copyWaterBoxVector(Vector3 &out,const Vector3 &in) {out.X=in.X;out.Y=in.Y;out.Z=in.Z;return out;}


__declspec(dllimport) __forceinline Vector3 operator+(const Vector3&a,const Vector3&b) {return Vector3(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
__declspec(dllimport) __forceinline Vector3 operator-(const Vector3&a,const Vector3&b) {return Vector3(a.X-b.X,a.Y-b.Y,a.Z-b.Z);}
__declspec(dllimport) __forceinline Vector3 operator*(float k,const Vector3&a) {return Vector3(a.X*k,a.Y*k,a.Z*k);}

#include "../../Include/Common/Rva0007E02A.h"
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
  Vector3 maximum((rectangle?rectangle:rectangle)[2],(rectangle?rectangle:rectangle)[3],float(reinterpret_cast<WaterAreaHeightView*>(scalarBase())->height()));
  copyWaterBoxVector(bounds.center,0.5f*(minimum+maximum));
  copyWaterBoxVector(bounds.extent,0.5f*(maximum-minimum));
  ready=true;
 }
 return bounds;
}
