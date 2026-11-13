// cl: /MD
//
// ?rva004D9596@Rva004D9596@@QAE_NXZ @0x004D9596 28B
// Mode-plus-triple predicate: true when m00 != -1, or m04 != 0 with
// (m18 == 0 or m0C != 0). Frameless __thiscall bool method with shared
// true/false tails (mov al,1 / xor al,al). No donor; honest Rva class with
// only the witnessed offsets modelled. Evidence: 26 callers including
// 0x004D990E and 0x004D9CF3 families; &&-chain shares the single false
// block where separate early returns give setne shape.

#include "../../Include/Common/Rva004D9596.h"

// The 28-byte rva004D9596 owner now lives in the genuine voice unit.

int Rva004D9596::rva004D9586()
{
    int result = 0;
    if (m_04 != 0 || m_00 != -1)
        result = 1;
    return result;
}
