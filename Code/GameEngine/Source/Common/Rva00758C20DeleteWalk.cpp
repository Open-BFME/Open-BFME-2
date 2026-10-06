// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00758C20 (38 B): a stdcall list-teardown walk. While the head is
// non-null it fetches the next link at +0x30, frees the head through operator
// delete (0x0002FD60) and advances. Open-BFME-1 has two byte-identical twins
// of this body (Small03fDeleteWalk.cpp, BFME 1 0x009A2CD0 / 0x009A4090, both
// address-named); game.dat holds one copy, so it lands once, under a name
// derived from its own address rather than either BFME 1 guess.
//
// The void __stdcall spelling is what emits the `ret 4` tail (the cdecl
// free-function form emits a bare `ret`); the while-loop spelling is what
// emits retail's `test esi,esi / mov eax,esi / jne +0x10` latch instead of an
// early-out. IDENTITY IS NOT RECOVERED.
void __cdecl operator delete(void *) throw();

struct Rva00758C20Node
{
	char m_pad[0x30];
	void *m_next;
};

class Rva00758C20Owner
{
public:
	static void __stdcall Rva00758C20Walk(void *head);
};

void __stdcall Rva00758C20Owner::Rva00758C20Walk(void *head)
{
	void *cur = head;
	while (cur != 0)
	{
		void *next = ((Rva00758C20Node *)cur)->m_next;
		operator delete(cur);
		cur = next;
	}
}
