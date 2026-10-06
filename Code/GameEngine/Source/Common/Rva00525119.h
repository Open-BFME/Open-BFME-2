#pragma once
// Native comparator525119 (29B) dereferences a one-word record and compares
// inner float10. The inner declaration describes only its accessed prefix;
// the original application types and the full inner allocation remain unknown.
struct Rva00525119Inner
{
    unsigned char m_pad[0x10];
    float m_10;
};
class Rva00525119
{
public:
    Rva00525119Inner *m_ptr;
    int rva00525119(Rva00525119 *other);
};
