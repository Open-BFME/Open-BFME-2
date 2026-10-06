// cl: /MD
// ?rva005F8FCC@Rva005F8FCC@@QAEPAXI@Z @0x005F8FCC 34B.
// Deleting-dtor shape: releases holder at +0 via rowed fastcall Release at
// 0x0007DEEF then conditionally deletes this when flag bit0 is set and
// returns this. Same shape as Rva005F0647Deleting 37B.
// Evidence: push esi mov esi ecx mov ecx [esi] test je call Release test
// flag je push esi call delete pop ecx mov eax esi ret 4; callers 6 including
// 0x004F70CB 0x004F72F8; LINK 1 file 7B.
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
void operator delete(void *);
struct Rva005F8FCC
{
	TargetRef00217D4C *m_00;
	void *rva005F8FCC(unsigned int flags);
};
void *Rva005F8FCC::rva005F8FCC(unsigned int flags)
{
	if (m_00)
		ReleaseTreeHintRef00217D4C(m_00);
	if (flags & 1)
		::operator delete(this);
	return this;
}
