// cl: /DNDEBUG /MD
// Dump lane range 13: ?rva002EB448 @0x002EB448 38B. Drain-then-unlink:
// while the head slot is empty, refill via verified 0x002E8548(0,0); false
// returns null, else unlink and return the head node (next at +0).
// Identity unproven.
#include "../../../Include/Common/Rva002E8548Pool.h"
class Rva002EB448
{
public:
	void *rva002EB448();
private:
	char m_pad0[8];
	void *m_head8;
};
struct Rva002EB448Node
{
	void *m_next;
};
// ?rva002EB448@Rva002EB448@@QAEPAXXZ @0x002EB448 38B.
void *Rva002EB448::rva002EB448()
{
	// Hand-rolled retry: a while/for/do-while all spend an entry or latch
	// jmp; the goto chain lays out as cmp/jne-unlink, call/test/jne-check
	// with the xor-ret falling through, byte-exact.
check:
	if (m_head8 != 0)
		goto unlink;
	if (((Rva002E8548 *)this)->rva002E8548(0, 0))
		goto check;
	return 0;
unlink:
	Rva002EB448Node *head = (Rva002EB448Node *)m_head8;
	m_head8 = head->m_next;
	return head;
}
