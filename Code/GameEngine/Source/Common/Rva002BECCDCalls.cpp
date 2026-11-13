// cl: /MD
// Native 0x002BECCD..0x002BED10. Caller 0x002B2A0A constructs a
// nontrivial eight-byte float pair in the first two argument words, then
// supplies a separate scalar in the third word. A three-scalar declaration
// reproduced this callee but could not reproduce that caller's copy ABI.
// The pair copy constructor and destructor recover the observed argument
// construction. The callee builds {pair.x, pair.y, 0} for virtual slot 0x58
// and passes the independent height to virtual slot 0x7c; ret 0x0c.
// Application-level names remain unknown; the pair is a partial value view.

struct RvaFloatPair {
 float x,y;
 RvaFloatPair(){}
 RvaFloatPair(const RvaFloatPair&rvaFloatPair){x=rvaFloatPair.x;y=rvaFloatPair.y;}
 ~RvaFloatPair(){}
};
struct Rva002BECCDVec {float x,y,z;};
#include "../../Include/Common/Rva002BECCD.h"

void Rva002BECCD::rva002BECCD(RvaFloatPair pair, float height)
{
    Rva002BECCDVec local;
    local.x = pair.x;
    local.y = pair.y;
    local.z = 0.0f;
    virt58(&local);
    virt7c(height);
}
