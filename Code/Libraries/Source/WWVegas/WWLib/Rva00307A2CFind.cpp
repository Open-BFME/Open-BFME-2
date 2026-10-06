// ?rva00307A2C@Rva00307A2C@@QAEPAXABVAsciiString@@@Z @0x00307A2C 39B
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Linked-list find by string: head at +0, node next at +4, AsciiString at +8.
// Evidence: 39B frameless loop, mov ecx,[esp+8] then lea eax,[esi+8] push + call
// 0x000069D6 ?compare@?$StringBase@D@@QBEHABV1@@Z row, je found, mov esi,[esi+4],
// test/jne, xor eax ret 4 vs mov eax,esi; callers 0x00307A57/0x00307A72 unclaimed.
#include "ascii_string.h"

class Rva00307A2C
{
	struct Node
	{
		void *m_unk00;
		Node *m_next;
		AsciiString m_name;
	};
	Node *m_head;
public:
	void *rva00307A2C(const AsciiString &s);
};

void *Rva00307A2C::rva00307A2C(const AsciiString &s)
{
	Node *n = m_head;
	while (n != 0) {
		if (s.compare(n->m_name) == 0)
			return n;
		n = n->m_next;
	}
	return 0;
}
