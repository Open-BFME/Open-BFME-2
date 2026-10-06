// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Existing105B position overload at2D982A; use the canonical136-byte layout.
#include "Common/BfmeAudioEventPrefix136.h"

BfmeAudioEventPrefix136::BfmeAudioEventPrefix136(const OpaqueRefElement4 &arg, const BfmeEventPositionView &pos, int value30)
{
	rva002D96D3(arg);
	m_position = pos;
	m_int38 = 0;
	m_int30 = value30;
	m_b48 = 1;
}
