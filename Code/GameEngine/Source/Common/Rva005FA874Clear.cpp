// cl: /MD
// ?rva005FA874@Rva005FA874@@QAEXXZ, RVA 0x005FA874, 30 bytes.
// Guarded delete of pointer at +0 (three-AsciiString record): if non-null run rowed ??1Rva005FEBC8 then rowed ??3 delete then null the slot.
// Evidence: callees rowed 0x005FEBC8 in RvaAsciiStringTripleDtors.cpp and 0x0002FD60 in mem_ops.cpp; callers 0x005E9625 0x005EC09B; neighbours 0x005FA393 0x005FA8F5 share /O1 /MD.
struct Rva005FEBC8
{
	~Rva005FEBC8();
};
void __cdecl operator delete(void *);
struct Rva005FA874
{
	Rva005FEBC8 *m_ptr00;
	void rva005FA874();
};
void Rva005FA874::rva005FA874()
{
	if (m_ptr00) {
		delete m_ptr00;
		m_ptr00 = 0;
	}
}
