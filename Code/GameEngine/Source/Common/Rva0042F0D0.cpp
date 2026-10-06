// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/stringinline
// ?loadMap@GameClient@@UAE_NVAsciiString@@@Z
// Authentic one-pointer StringInline ABI audit; target's word length field is retained by the proven retail layout.
#include "StringInline.h"

struct Rva0042F0D0Buffer
{
    int m_refCount;
    short m_length;
};
// GameClient::loadMap (WorldBuilder vtable lead); never reads this, so the
// thiscall member keeps the stdcall shape.
class GameClient
{
public:
    virtual bool loadMap(AsciiString value);
};

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
