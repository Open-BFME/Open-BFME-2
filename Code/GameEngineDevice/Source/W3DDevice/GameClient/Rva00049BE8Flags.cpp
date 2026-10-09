// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /arch:SSE /G7 /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BF1 2f243e26d Rva006EFF30BitFlagsDiffDescription.cpp semantic donor.
// Target uses591 model-condition bits; canonical string calls are direct
// char formatting and string/string concatenation. All five literals are
// independently decoded; ModelConditionNames is the existing single owner.
#include "ascii_string.h"

extern const char *const ModelConditionNames[];

class Rva00049BE8
{
public:
    void buildDescription(AsciiString *str, const Rva00049BE8 &other, bool includeSame, int maxPerLine) const;
    // ?test@Rva00049BE8@@QBE_NI@Z absent-from-retail
    __forceinline bool test(unsigned index) const { return (m_bits[index >> 5] & (1u << (index & 31))) != 0; }

private:
    unsigned m_bits[19];
};

// ?buildDescription@Rva00049BE8@@QBEXPAVAsciiString@@ABV1@_NH@Z
void Rva00049BE8::buildDescription(AsciiString *str, const Rva00049BE8 &other, bool includeSame, int maxPerLine) const
{
    AsciiString description;
    if (str == 0)
        return;
    str->clear();
    int count = 0;
    bool first = true;
    for (int i = 0; i < 591; ++i)
    {
        bool oldSet = other.test(i);
        bool newSet = test(i);
        if (oldSet != newSet || (newSet && includeSame))
        {
            if (!first)
                str->concat(", ");
            if (count >= maxPerLine)
            {
                count = 0;
                str->concat("\n");
            }
            if (newSet && !oldSet)
            {
                description.format("+%s", ModelConditionNames[i]);
                str->concat(description);
            }
            else if (includeSame && newSet)
            {
                description.format("%s", ModelConditionNames[i]);
                str->concat(description);
            }
            else
            {
                description.format("-%s", ModelConditionNames[i]);
                str->concat(description);
            }
            first = false;
            ++count;
        }
    }
}
