// cl: /DNDEBUG /MD /EHsc
// ?rva0021397C@Rva0021397C@@QAEXXZ, RVA 0x0021397C, 30B. Chain lane: calls
// rowed 0x00212AD6 range destroy with first/last at this+0/+4 then frees
// first via rowed free 0x00030830 when non-null; push-esi this plus
// pop-cleaned pushes. Callers at 0x00213ED1/0x002145D1. Owner unknown so
// honest address-derived names.
struct Rva002115C5;
void __cdecl Rva00212AD6Get(Rva002115C5 *first, Rva002115C5 *last);
extern "C" void __cdecl free(void *p);
struct Rva0021397C
{
	Rva002115C5 *m_first;
	Rva002115C5 *m_last;
	void rva0021397C();
};

void Rva0021397C::rva0021397C()
{
	Rva00212AD6Get(m_first, m_last);
	if (m_first != 0)
		free(m_first);
}
