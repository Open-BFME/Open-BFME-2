// ?rva001F3A25@Rva001F3A25@@QAEXM@Z
// partial score=0.7539 date=2026-10-06
// ?rva001F3A25@Rva001F3A25@@QAEXM@Z
// partial score=0.9 date=2026-10-01
// cl: /O1 /MD /arch:SSE
// ?rva001F3A25@Rva001F3A25@@QAEXM@Z @0x001F3A25 247B. Rotates three (x,y) pairs
// at +0xbc/+0xc4 +0xcc/+0xd4 +0xdc/+0xe4 by angle (sin first via
// 0x00629216 then cos via 0x0062920A) then clears byte at +0x1a0. Sibling of
// 0x001F3B1C with swapped call order and +4 shifted second element. Caller at
// 0x001E20CB. Honest Rva name.
// (CRT prototype from the standard header)
// (CRT prototype from the standard header)
#include <math.h>
class Rva001F3A25 {
public:
    void rva001F3A25(float angle);
    char m_lead[0xbc];
    float m_bc;
    float m_c0pad;
    float m_c4;
    float m_c8pad;
    float m_cc;
    float m_d0pad;
    float m_d4;
    float m_d8pad;
    float m_dc;
    float m_e0pad;
    float m_e4;
    float m_e8;
    char m_pad[0x1a0 - 0xec];
    unsigned char m_1a0;
};
// ?rva001F3A25@Rva001F3A25@@QAEXM@Z present-unmatched
void Rva001F3A25::rva001F3A25(float angle)
{
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    float x = m_bc;
    float y = m_c4;
    float nx = x * c - y * s;
    float ny = y * c + x * s;
    m_bc = nx;
    m_c4 = ny;
    x = m_cc;
    y = m_d4;
    nx = x * c - y * s;
    ny = y * c + x * s;
    m_cc = nx;
    m_d4 = ny;
    x = m_dc;
    y = m_e4;
    nx = x * c - y * s;
    ny = y * c + x * s;
    m_dc = nx;
    m_e4 = ny;
    m_1a0 = 0;
}
