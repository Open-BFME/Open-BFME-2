// cl: /MD
//
// ?Rva001E3FFDGet@@YAPAXPAURva001E3FFDOuter@@@Z @0x001E3FFD (24B).
// Two-level ptr-chase getter: outer+0x258 then inner+0x140 else null.
// Evidence: 11 callers in 0x1E6007 0x1E7389 0x1E756D 0x1E9083; frameless
// test-je plus mov plus xor shape; honest outer struct.

struct Rva001E3FFDInner
{
	char m_pad00[0x140];
	void *m_p140;
};

struct Rva001E3FFDOuter
{
	char m_pad00[0x258];
	Rva001E3FFDInner *m_p258;
};

void *__cdecl Rva001E3FFDGet(Rva001E3FFDOuter *p)
{
	Rva001E3FFDInner *q = p->m_p258;
	return q ? q->m_p140 : 0;
}
