// cl: /DNDEBUG /MD
//
// ?rva002CF1E2@Rva002CF1E2@@QAEXXZ @0x002CF1E2 25B: intrusive list walk.
// Retail reads the head at +0x0C, then while non-null calls the pinned
// ?rva0033B217@Rva002CF1E2Node@@QAEXXZ at 0x0033B217 (REL32 read at
// 0x002CF1EA; Ghidra 315B FUN_0073b217 factory family; thiscall no-stack-args
// void return per the call site) on each node and advances via +0x484.
// While loop (initial jmp to test, test esi / jne) under /O1. Layouts are
// BFME2-observed from retail offsets only; node payload beyond the +0x484
// link is unclaimed. Boundary abuts the next mov-body at 0x002CF1FB.
// Honest address-derived names.

class Rva002CF1E2Node
{
public:
	void rva0033B217();
};

class Rva002CF1E2
{
public:
	void rva002CF1E2();
private:
	int m_pad00[3]; // +0x00..+0x0C
	Rva002CF1E2Node *m_head; // +0x0C
};

// ?rva002CF1E2@Rva002CF1E2@@QAEXXZ
void Rva002CF1E2::rva002CF1E2()
{
	Rva002CF1E2Node *n = m_head;
	while (n)
	{
		n->rva0033B217();
		n = *(Rva002CF1E2Node **)((char *)n + 0x484);
	}
}
