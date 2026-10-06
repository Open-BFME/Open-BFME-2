// cl: /MD
//
// ?rva004EE540@Rva004EE540@@QAEXXZ @0x004EE540 30B
// Vector clear: destroys [m_start, m_finish) via rowed
// ?Rva0052C37ADestroyRange then frees storage via rowed _free.
// Evidence: chain lane, 5 callers including 0x004EE5A2/0x004EE76C,
// non-EH twin of blocked 0x004EE501. Owning class unproven.

struct Rva0052BFB5Elem;
void __cdecl Rva0052C37ADestroyRange(Rva0052BFB5Elem *first, Rva0052BFB5Elem *last);
extern "C" void free(void *block);

class Rva004EE540
{
public:
	void rva004EE540();

private:
	Rva0052BFB5Elem *m_start;
	Rva0052BFB5Elem *m_finish;
};

void Rva004EE540::rva004EE540()
{
	Rva0052C37ADestroyRange(m_start, m_finish);
	Rva0052BFB5Elem *start = m_start;
	if (start != 0)
		free(start);
}
