// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0040A424@Rva0040A424@@QAE_NPAVCreateAHeroData@@@Z @0x0040A424 29B
// Evidence: unlock lane; ecx is StringBase (caller 0x0040A46F passes ebp+0x10
// which later calls releaseBuffer 0x36410, and this calls compareNoCase 0x6A00);
// The complete29B predicate only reads string contents; nonthrowing compare
// restores the caller40A46F native exception-state shape.
// arg+0x4c passed as StringBase&; null returns false else compare==0.
#include "ascii_string.h"

class CreateAHeroData;

class Rva0040A424
{
    AsciiString m_data;
public:
    bool rva0040A424(CreateAHeroData *value) throw();
};

bool Rva0040A424::rva0040A424(CreateAHeroData *value) throw()
{
    if (value == 0)
        return false;
    return ((StringBase<char> *)this)->compareNoCase(*(const StringBase<char> *)((const char *)value + 0x4c)) == 0;
}
