// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "Common/BfmeAudioEventPrefix136.h"

// Native boundary2D97D6-2D982A. Six owned members default-initialize before
// the shared259B initializer; native ret8 consumes reference and the value stored at +0x30.
BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const OpaqueRefElement4 &arg, int value30)
{
    rva002D96D3(arg);
    m_int30 = value30;
}

// Native boundary2D99E3-2D9A31 (ret4). The same six default member stores as
// 2D97D6, then the rowed copy worker2D9893; the vector copy51B40 and the
// derived copy constructor51D62 call it for the prefix.
BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const BfmeAudioEventPrefix136 &other)
{
    rva002D9893(other);
}
