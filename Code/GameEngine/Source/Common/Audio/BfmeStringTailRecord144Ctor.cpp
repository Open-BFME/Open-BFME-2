// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ??0BfmeStringTailRecord144@@QAE@XZ, retail 0x00052512, 86 bytes.
//
// Evidence: the same 0x90-byte record whose verified destructor is
// ??1BfmeStringTailRecord144@@UAE@XZ (0x2D9A43), whose vector destructor
// 0x56ACB frees, and whose prefix is the canonical 0x88-byte
// BfmeAudioEventPrefix136 (header comment: "the vector copy 51B40 delegates
// its prefix to 2D99E3 then copies +0x88/+0x8C"). The ctor delegates to the
// rowed BfmeAudioEventPrefix136 ctor 0x2D97D6 with a null reference element
// and 0, then initializes the float at +0x88 and the byte at +0x8C.
//
// The reference element is a temporary whose destructor releases the referent
// through the rowed OpaqueRefCounted::Release_Ref 0x50ED3 (the canonical
// OpaqueRefElement4 destructor, rowed here under the temporary's type).

#include "Common/BfmeAudioEventPrefix136.h"

class Rva00052512RefElement : public OpaqueRefElement4
{
};

class __declspec(novtable) BfmeStringTailRecord144 : public BfmeAudioEventPrefix136
{
public:
	BfmeStringTailRecord144();
	virtual ~BfmeStringTailRecord144();

private:
	float m_88; // +0x88
	unsigned char m_8c; // +0x8C
};

BfmeStringTailRecord144::BfmeStringTailRecord144()
	: BfmeAudioEventPrefix136(Rva00052512RefElement(), 0), m_88(0.0f), m_8c(0)
{
}
