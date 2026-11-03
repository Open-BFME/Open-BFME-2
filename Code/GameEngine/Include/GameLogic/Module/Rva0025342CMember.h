// Rva0025342CMember: Rva00253487Base's member at +8; construct (0x0025342C) clears two Rva001EAE6FHelper
// halves, writes -1/0/0 at +0x100..+0x108 and zero bytes at +0x10C..+0x10E (size 0x110).
#pragma once

#ifndef BFME2_RVA0025342CMEMBER_H
#define BFME2_RVA0025342CMEMBER_H

#include "../../Common/Rva001EAE6FHelper.h"

class Rva0025342CMember
{
public:
    Rva0025342CMember *construct();

private:
    Rva001EAE6FHelper m_sub0;
    Rva001EAE6FHelper m_sub1;
    int m_tail0;
    int m_tail1;
    int m_tail2;
    unsigned char m_tailByte0;
    unsigned char m_tailByte1;
    unsigned char m_tailByte2;
};

#endif
