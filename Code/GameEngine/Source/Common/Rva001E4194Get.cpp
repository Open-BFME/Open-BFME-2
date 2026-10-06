// cl: /MD
// ?Rva001E4194Get@@YG_NPAURva001E4194A@@@Z @0x001E4194 24B: bool via double deref +0x25c then +0x5c.
// Evidence: 4 callers test al al e.g. 0x001E9124 0x001EA118 0x00471500 0x004768CA.
struct Rva001E4194A { char _0[0x25c]; void *m_25c; };
struct Rva001E4194B { char _0[0x5c]; bool m_5c; };
bool __stdcall Rva001E4194Get(Rva001E4194A *a)
{
	void *b = a->m_25c;
	if (b)
		return ((Rva001E4194B *)b)->m_5c;
	return false;
}

// keep marker for hook (stripped by add_match)
