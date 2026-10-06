// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ??4Rva0030ADED@@QAEAAV0@ABV0@@Z @0x0030ADED 85B evidence calls rowed StringBase set 0x000366F0 twice plus raw 12B copies and byte plus dword return this via VslotSizedForwarders neighbour layout matches Rva00985E4 tail at +0x0C
#include "ascii_string.h"

struct S12
{
    int a;
    int b;
    int c;
};

class Rva0030ADED
{
public:
    AsciiString m_00;
    AsciiString m_04;
    S12 m_08;
    S12 m_14;
    unsigned char m_20;
    char m_pad21[3];
    S12 m_24;
    S12 m_30;
    int m_3C;
    Rva0030ADED &operator=(const Rva0030ADED &other);
};

Rva0030ADED &Rva0030ADED::operator=(const Rva0030ADED &other)
{
	((StringBase<char> *)&m_00)->set(*(const StringBase<char> *)&other.m_00);
	((StringBase<char> *)&m_04)->set(*(const StringBase<char> *)&other.m_04);
    m_08 = other.m_08;
    m_14 = other.m_14;
    m_20 = other.m_20;
    m_24 = other.m_24;
    m_30 = other.m_30;
    m_3C = other.m_3C;
    return *this;
}
