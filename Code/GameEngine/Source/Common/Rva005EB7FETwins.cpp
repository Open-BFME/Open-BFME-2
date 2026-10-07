// cl: /O1 /MD
// Range-34 dump lane: 39B plain method at 0x005EB7FE. It clears the slot's
// +0xC word, then, when the +0 slot's +8 word is set, forwards its +4 word
// through the Apt window manager's pinned 0x0022277D slot and clears it.
// Same extern recipe as Rva002B29BDFire.cpp. All identities unproven.
class Rva00222A8BTarget
{
public:
	void rva0022277D(void *v);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005EB7FESlot
{
	int m00;
	int m04;
	int m08;
	int m0c;
};

class Rva005EB7FE
{
public:
	Rva005EB7FESlot *m00;
	void rva005EB7FE();
};

void Rva005EB7FE::rva005EB7FE()
{
	m00->m0c = 0;
	if (m00->m08 != 0) {
		TheRva00222A8BTarget->rva0022277D((void *)m00->m04);
		m00->m08 = 0;
	}
}

// The slot at VA 0x00DFE4CC is the Apt window manager pointer, defined as
// g_bfmeAptWindowManager in Rva005832D0MapName.cpp; this TU's facade name for
// the same object binds to that definition rather than defining it twice.
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
