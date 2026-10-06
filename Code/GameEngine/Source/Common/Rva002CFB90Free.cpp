// cl: /MD
// ?rva002CFB90@Rva002CFB90@@QAEXXZ @0x002CFB90 30B.
// Destroy-range-then-free method over a two-pointer (begin/end) holder:
// calls the rowed 0x002CF891 wrapper with (m_begin, m_end), reloads m_begin,
// and frees it via the rowed C free 0x00030830 when non-null. Caller at
// 0x002D0FAD. Owner class unproven: honest Rva dummy holder (cf. Rva005E7198
// precedent); the wrapper and item types are declared only so the calls stay
// external and resolve through their ledger rows.
struct Rva002CF571Item;
void __cdecl Rva002CF891Wrap(Rva002CF571Item *first, Rva002CF571Item *last);
extern "C" void free(void *block);

struct Rva002CFB90
{
	Rva002CF571Item *m_begin;
	Rva002CF571Item *m_end;
	void rva002CFB90();
};

void Rva002CFB90::rva002CFB90()
{
	Rva002CF891Wrap(m_begin, m_end);
	if (m_begin != 0)
		free(m_begin);
}
