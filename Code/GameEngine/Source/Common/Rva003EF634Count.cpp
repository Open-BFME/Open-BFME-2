// cl: /MD
//
// ?Rva003EF634Count@@YGHPAURva003EF634Node@@@Z, retail 0x003EF634, 20 bytes.
// Free __stdcall function counting nodes via +0x28 next pointers starting
// from -1: single node with null next returns 0. Frameless or-eax-minus-1
// plus inc/test/jne loop needs /O1. Leaf. Callers 0x003EFB27 0x003EFC0E.
// Prev 0x003EF5DA dup / next 0x003EF676 indexOf. Honest address name; owner
// and node type unproven.
struct Rva003EF634Node
{
	char m_pad[0x28];
	struct Rva003EF634Node *m_next;
};

int __stdcall Rva003EF634Count(struct Rva003EF634Node *p)
{
	int n = -1;
	while (p) {
		p = p->m_next;
		++n;
	}
	return n;
}
