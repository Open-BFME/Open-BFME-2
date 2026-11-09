// Rva0042526Member: 0x4C bytes that its out-of-line constructor 0x00042526 clears through memset (this, 0, 0x4C) and returns this;
// Rva001DFEAABase holds four at +0x10/+0x5C/+0xA8/+0xF4. Not registered yet.
#pragma once

#ifndef BFME2_RVA0042526MEMBER_H
#define BFME2_RVA0042526MEMBER_H

class Rva0042526Member
{
public:
    Rva0042526Member() throw();     // retail's base ctor keeps no unwind state across it

    unsigned char m_bytes[0x4C];
};

#endif
