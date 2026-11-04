// cl: /MD
// ?rva00041D03@Rva00041D03@@QAEXXZ @0x00041D03 31B
// Flag-gated audio notify: if +0 set and TheAudio non-null call slot 0x198
// virtual then clear +0. Evidence: TheAudio VA 0x00DFE6E8 mangled
// ?TheAudio@@3PAVAudioManager@@A; callers at 0x000421A2; neighbours share
// /O1 shape; honest address-derived name.
#include "../../Include/Common/GameAudio.h"

class Rva00041D03
{
public:
    void rva00041D03();
    void rva00041D22();
private:
    bool m_flag; // +0
};

void Rva00041D03::rva00041D03()
{
    if (!m_flag)
        return;
    if (TheAudio == 0)
        return;
    TheAudio->slot102();
    m_flag = 0;
}

void Rva00041D03::rva00041D22()
{
    if (m_flag)
        return;
    if (TheAudio == 0)
        return;
    TheAudio->slot101();
    m_flag = 1;
}
