// cl: /O1 /arch:SSE /G7 /EHsc /MD
// Native 0x002B2A0A..0x002B2A95, RET0. Receiver +B0 queries the
// two-component position using +B8, then singleton DFEF18 receives a
// nontrivial pair and an independent zero height at 0x002BECCD.
// The subsequent +1C/+20 writes copy the float representations as words.
// Application field names remain unresolved. LivingWorldLogic association
// follows the surrounding established source family, not a recovered method name.
// A contiguous pair of bit views preserves the native F8/FC stack homes.
// The ordered first word read preserves retail's load before its first store
// and makes MSVC choose the observed ECX receiver/EAX value registers.
#include "../../../Common/RegionCenterPointDispatchView.h"
struct RvaFloatPair
{
    float x, y;
    RvaFloatPair() {}
    RvaFloatPair(const RvaFloatPair &rvaFloatPair) { x = rvaFloatPair.x; y = rvaFloatPair.y; }
    ~RvaFloatPair() {}
};
#include "../../../../Include/Common/Rva002BECCD.h"
class Rva002D3627Host
{
public:
    char pad[0x1c];
    unsigned x, y;
    union Bits { float f; unsigned u; };
};
class LivingWorld; extern LivingWorld *TheLivingWorld;
#include "../../../../Include/GameLogic/LivingWorldLogic.h"
void LivingWorldLogic::rva002B2A0A()
{
    RvaFloatPair pos;
    pos.x = 0.0f;
    pos.y = 0.0f;
    ((Rva0020F27EHost *)fieldB0)->rva0020F27E(fieldB8, (int)&pos);
    if (((Rva002D3627Host *)TheLivingWorld))
    {
        ((Rva002BECCD*)((Rva002D3627Host *)TheLivingWorld))->rva002BECCD(pos, 0.0f);
        Rva002D3627Host::Bits bits[2];
        bits[0].f = pos.x;
        bits[1].f = pos.y;
        ((Rva002D3627Host *)TheLivingWorld)->x = *(volatile unsigned*)&bits[0].u;
        ((Rva002D3627Host *)TheLivingWorld)->y = bits[1].u;
    }
}
