// cl: /Oy- /Os /MD /arch:SSE /G7 /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// Retail 0x0007BEDA 128B: Camera-derived Rva007C454 virtual AABox plane scan.
// Same class and [this+0x3FC,this+0x400) plane-array view as the rowed sphere
// scan at 0x0007BEA7. For each plane take the far extent against its normal,
// subtract it from the box center and test the point through rowed helpers
// 0x0007B5C8 and 0x0007B638. Return true at result 1, otherwise false.
// The end pointer is captured before the loop; begin-before-end evaluation
// with /Os /Oy- reproduces retail's ECX cache and all 128 bytes.
// Original method name remains unknown; the free Box_Outside_Plane helper
// offered by the structural queue has a different ABI and is not this body.
#include "vector3.h"
#include "plane.h"
#include "aabox.h"
void get_far_extent(const Vector3&, const Vector3&, Vector3*);
class Rva007C454 {
public:
 virtual bool rva0007BEDA(const AABoxClass &box);
private:
 char pad[0x3f8];
 PlaneClass *begin;
 PlaneClass *end;
};
bool Rva007C454::rva0007BEDA(const AABoxClass &box) {
 PlaneClass *p=begin;
 PlaneClass *const stop=end;
 for (; p!=stop; ++p) {
  Vector3 farpt;
  get_far_extent(p->N,box.Extent,&farpt);
  Vector3::Subtract(box.Center,farpt,&farpt);
  if (CollisionMath::Overlap_Test(*p,farpt)==1) return true;
 }
 return false;
}
