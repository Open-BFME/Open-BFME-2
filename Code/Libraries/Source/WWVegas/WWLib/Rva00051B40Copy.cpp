// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHs-c- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0BfmeStringTailRecord144@@QAE@ABU0@@Z, retail 0x00051B40, 45 bytes.
// Vector copy delegates prefix to 0x002D99E3 then copies word at +0x88 and byte
// at +0x8C. Evidence: leaf lane, caller 0x00053E1A in StlportVectorOverflow,
// callee 0x002D99E3 rowed in BfmeAudioEventPrefix136, pin copy ctor,
// +0x88/+0x8C per BfmeAudioEventPrefix136 header and tail dtor TU.
#include "Common/BfmeAudioEventPrefix136.h"

struct BfmeStringTailRecord144
{
    BfmeStringTailRecord144(const BfmeStringTailRecord144 &other);
    BfmeAudioEventPrefix136 m_prefix;
    int m_88;
    unsigned char m_8c;
};

BfmeStringTailRecord144::BfmeStringTailRecord144(const BfmeStringTailRecord144 &other)
    : m_prefix(other.m_prefix), m_88(other.m_88), m_8c(other.m_8c)
{
}
