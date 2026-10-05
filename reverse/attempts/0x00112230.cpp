// ?rva00112230@Rva00112230@@QAEXPAPAX@Z
// partial score=0.8 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /Oy-
//
// ?rva00112230@Rva00112230@@QAEXPAPAX@Z @0x00112230 41B leaf abutting 0x00112259.
// Retail: eax=[ecx]; if (eax==[ecx+4]) *[ebp+8]=0; else { p=[eax]; *[ebp+8]=p;
// if (p) ++[p+4]; } ret 4. Refcount at +4 of pointee (same pattern as 0x00113110).
// No calls, no pins. Names opaque address-derived.
struct Rva00112230
{
	void *m_00; // +0x00
	void *m_04; // +0x04
	void rva00112230(void **out);
};

struct Rva00112230Pointee
{
	char m_pad00[4];
	int m_ref04; // +0x04 refcount
};

void Rva00112230::rva00112230(void **out)
{
	if (m_00 == m_04)
		*out = 0;
	else {
		void *p = *(void **)m_00;
		*out = p;
		if (p)
			++((Rva00112230Pointee *)p)->m_ref04;
	}
}
