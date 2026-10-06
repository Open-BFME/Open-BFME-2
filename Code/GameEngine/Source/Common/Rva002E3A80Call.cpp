// cl: /MD
// ?call@Rva002E3A80Holder@@QAEXXZ, retail 0x002E3A80, 13 bytes.
// Leaf null-guarded virtual slot-0 call with 1. Callers are 12x unwind
// jmp thunks plus 0x002E3907 0x00330C29. Owning class unproven so honest
// Rva holder. No donor.
struct Rva002E3A80Target
{
	virtual void virt(int x);
};
struct Rva002E3A80Holder
{
	Rva002E3A80Target *m_ptr;
	void call(void);
};

void Rva002E3A80Holder::call(void)
{
	if (m_ptr != 0)
		m_ptr->virt(1);
}
