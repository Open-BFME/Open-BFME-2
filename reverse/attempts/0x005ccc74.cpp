// ?rva005CCC74@Rva005CCC74@@QAEXPAURva005CCC74Arg@@PAX@Z
// partial score=0.93 date=2026-10-07
// cl: /MD /O1 /arch:SSE /G7
// ?rva005CCC74@Rva005CCC74@@QAEXPAURva005CCC74Arg@@PAX@Z @0x005CCC74 36B
// Gap between 0x005CCC69 and 0x005CCC98 in Rva005CCC69Dtor.cpp. Evidence:
// caller 0x005CD061, unblocks 0x005CD049, LINK BONUS 196B waiting, no EH no
// float no vtable, this+0 pointer this+4 arg2, refcount inc at +4.
struct Rva005CCC74Ref
{
	char m_pad[4];
	int m_refs;
};
struct Rva005CCC74Arg
{
	Rva005CCC74Ref *m_ptr;
};
class Rva005CCC74
{
public:
	void rva005CCC74(Rva005CCC74Arg *a1, void *a2);
private:
	Rva005CCC74Ref *m_p;
	void *m_q;
};
void Rva005CCC74::rva005CCC74(Rva005CCC74Arg *a1, void *a2)
{
	Rva005CCC74 *self = this;
	Rva005CCC74Arg *a1copy = a1;
	Rva005CCC74Ref *p = a1copy->m_ptr;
	self->m_p = p;
	if (p)
		++p->m_refs;
	self->m_q = a2;
}
