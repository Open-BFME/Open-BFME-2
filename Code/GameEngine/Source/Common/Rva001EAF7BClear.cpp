// cl: /MD
// ?rva001EAF7B@Rva001EAF7B@@QAE_NXZ @0x001EAF7B 32B: honest pool clear loop
// head at +0x04 popped via *node then deleter at +0x10 called as
// __cdecl (node at +0x04 plus ctx at +0x14) with caller cleanup; returns
// true. Tail-jumped from global thunks at 0x007B6850 etc with ecx=0xDA60E8
// (behavior pool); unblocks 0x007B6850. No donor.

class Rva001EAF7B
{
public:
	bool rva001EAF7B();
private:
	int m_00;
	void *m_04;
	int m_08;
	int m_0C;
	void (__cdecl *m_10)(void *node, int ctx);
	int m_14;
};

bool Rva001EAF7B::rva001EAF7B()
{
	while (m_04 != 0) {
		void *node = m_04;
		m_04 = *(void **)node;
		m_10(node, m_14);
	}
	return true;
}
