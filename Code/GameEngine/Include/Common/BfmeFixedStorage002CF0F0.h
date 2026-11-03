#pragma once
// Four-byte mask held by value (Script +0x24); its out-of-line copy constructor is 0x002CF0F0, which
// Script's copy constructor calls at 0x003B41AF and the duplicate path at 0x003B74B6.
class BfmeFixedStorage002CF0F0
{
public:
    BfmeFixedStorage002CF0F0() {}
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
    unsigned int bits() const { return *(const unsigned int *)m_bytes; }
private:
    char m_bytes[4];
};
