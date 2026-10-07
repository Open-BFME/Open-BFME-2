// ?compareNoCase@?$StringBase@G@@QBEHG@Z
// partial score=0.97 date=2026-10-07
// cl: /O2 /G7 /MD /ICode/Libraries/Source/WWVegas/WWLib
typedef unsigned short wchar_t;
#include "string_base.h"
struct WideCharCompare
{
    char m_unused;
    int compareNoCase(const wchar_t *a, const wchar_t *b, int len) const;
};
union Rva00037AF0Storage
{
    wchar_t value;
    WideCharCompare tag;
};
template <>
int StringBase<wchar_t>::compareNoCase(wchar_t c) const
{
    const int mylen = m_data ? m_data->length : 0;
    const wchar_t *data = m_data ? &m_data->data[0] : L"";
    int len = mylen;
    if (len >= 1)
        len = 1;
    Rva00037AF0Storage &arg = *reinterpret_cast<Rva00037AF0Storage *>(&c);
    int result = arg.tag.compareNoCase(data, &arg.value, len);
    if (result != 0)
        return result;
    return mylen - 1;
}
