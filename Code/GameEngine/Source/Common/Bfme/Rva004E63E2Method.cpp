// cl: /MD
// ?rva004E63E2@Rva004E63E2@@QAEXXZ @ 0x004E63E2 26B chain: clears holder at +0 then guarded cleanup via 0x004E624D and operator delete. Callees rowed 0x004E624D and 0x0002FD60. Caller jmp at 0x004E668E.
struct Rva004E624D
{
	void rva004E624D();
};
void __cdecl operator delete(void *);
struct Rva004E63E2
{
	Rva004E624D *m_ptr;
	void rva004E63E2();
};
void Rva004E63E2::rva004E63E2()
{
	Rva004E624D *p = m_ptr;
	m_ptr = 0;
	if (p != 0)
	{
		p->rva004E624D();
		delete p;
	}
}
