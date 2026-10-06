// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva004181F5@@QAE@ABV0@@Z @0x004181F5 61B
// Copy ctor with AsciiString at +0 via pinned StringBase copy 0x000365F0
// plus Rva004181A6 at +4 via rowed copy 0x004181A6 (other+4 via add).
// No vptrs. AsciiString inline copy/dtor gives EH state after first call.
// Evidence: chain lane after landing 0x004181A6; unblocks 0x0041826B.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva004181A6 {
public:
    Rva004181A6(const Rva004181A6 &other);
private:
    char m_pad[0x18];
};
class Rva004181F5 {
public:
    Rva004181F5(const Rva004181F5 &other);
private:
    AsciiString m_str;
    Rva004181A6 m_rva;
};
Rva004181F5::Rva004181F5(const Rva004181F5 &other)
    : m_str(other.m_str)
    , m_rva(other.m_rva)
{
}
