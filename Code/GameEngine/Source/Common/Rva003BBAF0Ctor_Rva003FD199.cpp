// cl: -DNDEBUG -MD /Ob1 -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5: base unsigned*0.03f clamp shared by BfmeRectVNE / VNF / VNG.
// Native 0x003FD199, 44 bytes: a base constructor called by the derived
// constructors at 0x003FD348 and 0x003FD498. The vtable store and twelve-byte
// prefix are target evidence; the established BfmeBaseVNH spelling is neutral.
// This declaration view represents its vptr explicitly. Return-this precedes
// the <1 clamp, just as in the former donor-guided initializer.

extern "C" const void *const __identifier("??_7Rva002B3092@@6B@")[];
#define g_bfmeVtaVNE __identifier("??_7Rva002B3092@@6B@")

// Retail 0x003BB860 (31 bytes): the scaling as its own file static. The
// constructors inline it, but VC7.1 still emits a copy that takes w in EAX.
static unsigned rva003BB860Scale(unsigned w)
{
	return (int)((float)w * 0.03f);
}

class BfmeBaseVNH
{
public:
	BfmeBaseVNH(unsigned w, char f);

	void *volatile m_bfme00;
	unsigned m_bfme04;
	char m_bfme08;
};

// ??0BfmeBaseVNH@@QAE@ID@Z
BfmeBaseVNH::BfmeBaseVNH(unsigned w, char f)
{
	m_bfme00 = (void *)&g_bfmeVtaVNE;
	m_bfme08 = f;
	m_bfme04 = rva003BB860Scale(w);
	if (m_bfme04 < 1)
		m_bfme04 = 1;
}
