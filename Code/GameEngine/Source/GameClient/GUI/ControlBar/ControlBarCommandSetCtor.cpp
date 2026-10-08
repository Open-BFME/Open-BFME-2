// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f CommandSetLifetime.cpp
// provides the creation algorithm, not BFME2 layout proof.
// Native 0x00409FFA..0x0040A057 and paired WB 0x00C288A0 establish the
// name at +0x10, 32 pointer slots +0x14, count +0x94, and second arg +0x98.
// Rowed siblings 0x00409F83/0x00409FA0 compare +0x98 as a dword mode with 1;
// retain its meaning as unknown instead of borrowing BFME1's list link.
// Preserve the target vtable/base owners' existing address-derived identities.
#include "ascii_string.h"
class Rva001E3624 {
public:
    Rva001E3624() : m_next(0), m_override(false), m_stale(-1) {}
    virtual ~Rva001E3624();
private:
    Rva001E3624 *m_next;
    bool m_override;
    int m_stale;
};
class Rva00409FFA : public Rva001E3624 {
public:
    Rva00409FFA(const AsciiString &name, int mode98);
    virtual ~Rva00409FFA();
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};
Rva00409FFA::Rva00409FFA(const AsciiString &name, int mode98) : m_name(name), m_count(32), m_mode98(mode98)
{
    for(int i=0;i<32;++i) m_buttons[i]=0;
}
