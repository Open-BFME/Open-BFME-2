// cl: /DNDEBUG /MD /D_CRTIMP= /EHsc
// RVA 0x008B4260: compare two payload pointers, then their text after the header.
#include <string.h>

struct Rva008B4260StringRef
{
    const char *m_payload;
    int compare008B4260(const Rva008B4260StringRef &other) const;
};

int Rva008B4260StringRef::compare008B4260(const Rva008B4260StringRef &other) const
{
    const char *left = m_payload;
    const char *right = other.m_payload;
    if (left == right)
        return 0;
    return _strcmpi(left + 8, right + 8);
}
