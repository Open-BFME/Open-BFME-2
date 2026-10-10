// cl: /O2 /G7 /MD /ICode/Libraries/Source/WWVegas/WWLib
// Twin of verified StringBase<char>::compareNoCase(char)379E0.
// Target loads16-bit length and calls canonical WideCharCompare405344.
// The verified worker definition is visible and inline: its unused receiver
// lets VC7.1 reuse the character argument home for the stateless trait, instead
// of allocating a separate four-byte local. The strong canonical worker stays
// in string_base_compare_nocase.cpp; this TU supplies an inline COMDAT copy.
// The initialized trait byte is dead because that worker never reads this.
// Reference semantic guide: existing string_base_inline.cpp and BFME1
// StringBaseWideCompareNoCaseRaw.cpp; type is independently fixed by the
// UTF16 argument and WideCharCompare ABI. Complete66B replaces the dump.
typedef unsigned short wchar_t;
#include "string_base.h"
#define _DLL
typedef unsigned short WideChar;
extern "C" __declspec(dllimport) unsigned short __cdecl towlower(unsigned short);
class WideCharCompare {char unused;public:int compareNoCase(const unsigned short*,const unsigned short*,int)const;};
static __forceinline int compareRangeNoCase(const unsigned short*a,int alen,const unsigned short*b,int blen,WideCharCompare tag){int len=alen<blen?alen:blen;int result=tag.compareNoCase(a,b,len);if(result!=0)return result;return alen-blen;}
inline int WideCharCompare::compareNoCase(const wchar_t *a, const wchar_t *b, int len) const
{
    while (len > 0) {
        const WideChar leftLower = (WideChar)towlower(*a);
        const WideChar rightLower = (WideChar)towlower(*b);
        if (leftLower != rightLower)
            return (int)leftLower - (int)rightLower;
        ++a;
        ++b;
        --len;
    }
    return 0;
}

template<typename T>int StringBase<T>::compareNoCase(T c)const{
const int len=m_data?m_data->length:0;
const T*data=m_data?m_data->data:L"";
WideCharCompare tag=WideCharCompare();return compareRangeNoCase(data,len,&c,1,tag);}
template int StringBase<unsigned short>::compareNoCase(unsigned short)const;
