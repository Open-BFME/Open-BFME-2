// ?rva001F3B1C@Rva001F3B1C@@QAEXM@Z
// partial score=0.7598 date=2026-10-06
// ?rva001F3B1C@Rva001F3B1C@@QAEXM@Z
// partial score=0.9 date=2026-10-01
// cl: /O1 /MD /arch:SSE
// ?rva001F3B1C@Rva001F3B1C@@QAEXM@Z @0x001F3B1C 247B. Rotates three (x,y) pairs
// at +0xbc/+0xc0, +0xcc/+0xd0, +0xdc/+0xe0 by angle (cos/sin via CRT thunks
// 0x0062920A/0x00629216) then clears byte at +0x1a0. Same family as
// Rva001F38C1Slot::set bulk copy plus 0x1a0 clear; callers at
// 0x000C7351/0x001E20FD. Honest Rva name.
// (CRT prototype from the standard header)
// (CRT prototype from the standard header)
#include <math.h>
class Rva001F3B1C {
public:
    void rva001F3B1C(float angle);
    char m_lead[0xbc];
    float m_bc;
    float m_c0;
    float m_c4;
    float m_c8;
    float m_cc;
    float m_d0;
    float m_d4;
    float m_d8;
    float m_dc;
    float m_e0;
    float m_e4;
    float m_e8;
    char m_pad[0x1a0 - 0xec];
    unsigned char m_1a0;
};
// ?rva001F3B1C@Rva001F3B1C@@QAEXM@Z present-unmatched
void Rva001F3B1C::rva001F3B1C(float angle)
{
    float c = (float)cos(angle);
    float s = (float)sin(angle);
    float x0 = m_bc;
    float y0 = m_c0;
    float nx0 = x0 * c + y0 * s;
    float ny0 = y0 * c - x0 * s;
    m_bc = nx0;
    m_c0 = ny0;
    float x1 = m_cc;
    float y1 = m_d0;
    float nx1 = x1 * c + y1 * s;
    float ny1 = y1 * c - x1 * s;
    m_cc = nx1;
    m_d0 = ny1;
    float x2 = m_dc;
    float y2 = m_e0;
    float nx2 = x2 * c + y2 * s;
    float ny2 = y2 * c - x2 * s;
    m_dc = nx2;
    m_e0 = ny2;
    m_1a0 = 0;
}
