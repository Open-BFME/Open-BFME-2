// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc
// ?loadMap@GameClient@@UAE_NVAsciiString@@@Z
// The by-value AsciiString's buffer keeps retail's word length field at +4.

struct Rva0042F0D0Buffer
{
    int m_refCount;
    short m_length;
};
// GameClient::loadMap (WorldBuilder vtable lead); never reads this, so the
// thiscall member keeps the stdcall shape.
#include "../../Include/GameClient/GameClientClass.h"

bool GameClient::loadMap(AsciiString value)
{
    const Rva0042F0D0Buffer *buffer = *(const Rva0042F0D0Buffer **)&value;

    if (!buffer)
        goto zero;
    if (!buffer->m_length)
        goto zero;
    goto one;
zero:
    return false;
one:
    return true;
}
