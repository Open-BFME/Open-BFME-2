// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0040ADFA@Rva0040ADFA@@QBE_NPBX@Z @0x0040ADFA 50B
// Evidence: unlock lane; +4/+8 int sorted array searched via rowed
// binary_search int 0x40AD75 for key from rowed NameKeyGenerator::nameToKey
// 0x9FA65 via TheNameKeyGenerator on AsciiString at arg+0x64; caller 0x40B143;
// LINK BONUS none.
#include "ascii_string.h"

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const AsciiString &name);
};

extern class NameKeyGenerator *TheNameKeyGenerator;

namespace _STL
{
    template <class _ForwardIter, class _Tp>
    bool binary_search(_ForwardIter __first, _ForwardIter __last, const _Tp &__val);
}

class Rva0040ADFA
{
public:
    bool rva0040ADFA(const void *arg) const;
private:
    char m_pad[4];
    int *m_first;
    int *m_last;
};

bool Rva0040ADFA::rva0040ADFA(const void *arg) const
{
    NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((const char *)arg + 0x64));
    return _STL::binary_search(m_first, m_last, (int)key);
}

// ?rva0040AE2C@Rva0040AE2C@@QBE_NPBX@Z @0x0040AE2C 50B
// Evidence: unlock lane; same shape as rva0040ADFA above in this TU but
// +0x10/+0x14 int sorted array; same rowed nameToKey 0x9FA65 and binary_search
// 0x40AD75 on AsciiString at arg+0x64; caller 0x40B113; LINK BONUS none.
class Rva0040AE2C
{
public:
    bool rva0040AE2C(const void *arg) const;
private:
    char m_pad[0x10];
    int *m_first;
    int *m_last;
};

bool Rva0040AE2C::rva0040AE2C(const void *arg) const
{
    NameKeyType key = TheNameKeyGenerator->nameToKey(*(const AsciiString *)((const char *)arg + 0x64));
    return _STL::binary_search(m_first, m_last, (int)key);
}
