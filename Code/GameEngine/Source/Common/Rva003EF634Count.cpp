// cl: /MD /O1 /G7 /arch:SSE
//
// ?Rva003EF634Count@Rva003EF8E1@@QAEHPAURva003EF634Node@@@Z retail 0x003EF634, 20 bytes.
// Unused-receiver member function counting nodes via +0x28 next pointers starting
// from -1: single node with null next returns 0. Frameless or-eax-minus-1
// plus inc/test/jne loop needs /O1. Leaf. Callers 0x003EFB27 0x003EFC0E.
// Prev 0x003EF5DA dup / next 0x003EF676 indexOf. Honest address name; owner
// and node type unproven.
struct Rva003EF634Node
{
	char m_pad[0x28];
	struct Rva003EF634Node *m_next;
};

class Rva003EF8E1 { public: int Rva003EF634Count(Rva003EF634Node*); };
int Rva003EF8E1::Rva003EF634Count(struct Rva003EF634Node *p)
{
	int n = -1;
	while (p) {
		p = p->m_next;
		++n;
	}
	return n;
}

// Retail3EFA0A/3EFB2E sets same-owner ECX before the reached-goal branch,
// then calls this helper without changing ECX; that move is shared with
// the relaxation call on the other arm. Both caller bodies prove the ABI.
