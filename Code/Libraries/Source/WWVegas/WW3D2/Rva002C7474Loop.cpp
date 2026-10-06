// cl: /DNDEBUG /MD
//
// ?rva002C7474@Rva002C7474@@QAEXXZ @0x002C7474 30B: six-member release loop.
// Retail walks six pointers at +0x08..+0x20, calling the rowed 18B Weapon
// setter ?rva002C95DE@Weapon@@QAEXH@Z at 0x002C95DE (REL32 at 0x002C7484;
// Code/GameEngine/Source/GameLogic/Object/Rva002C96D8Finish.cpp) with 0 on
// 0 on each non-null member. Countdown do-while (push 6 / pop edi, lea
// esi,[ecx+8], add esi,4, dec edi / jne) under /O1. Owner layout is
// BFME2-observed from retail offsets only (two pad words then six member
// member payload beyond the rowed setter is unclaimed. No
// Ghidra entry; boundary proven by abutting ret 0xC before and the next
// mov-eax/call factory at 0x002C7492. Honest address-derived names.

// Rowed provider (defined in Rva002C96D8Finish.cpp); declared here only.
class Weapon
{
public:
	void rva002C95DE(int offset);
};

class Rva002C7474
{
public:
	void rva002C7474();
private:
	int m_pad00[2]; // +0x00..+0x08
	Weapon *m_items[6]; // +0x08..+0x20
};

// ?rva002C7474@Rva002C7474@@QAEXXZ
void Rva002C7474::rva002C7474()
{
	Weapon **pp = m_items;
	int n = 6;
	do
	{
		Weapon *m = *pp;
		if (m)
			m->rva002C95DE(0);
		++pp;
	} while (--n);
}
