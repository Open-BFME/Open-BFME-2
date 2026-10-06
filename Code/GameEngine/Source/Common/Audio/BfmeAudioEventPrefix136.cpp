// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
#include "Common/BfmeAudioEventPrefix136.h"

// Native boundary2D97D6-2D982A. Six owned members default-initialize before
// the shared259B initializer; native ret8 consumes reference and the value stored at +0x30.
BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const OpaqueRefElement4 &arg, int value30)
{
    rva002D96D3(arg);
    m_int30 = value30;
}
