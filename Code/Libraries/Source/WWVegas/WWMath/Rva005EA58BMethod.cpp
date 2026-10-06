// cl: /DNDEBUG /MD /EHs-c-
// ?rva005EA58B@Rva005EA58B@@QAEXXZ @0x005EA58B 50B thiscall validate unicode strings in 2 ranges
// Validates StringBase<G> at holder+8 for each elem in 2 ranges at this+0x1c; callees rowed validate 0x000B3FD0; caller jmp 0x005EA8DE
// ?rva005EA8C4@Rva005EA58B@@QAEXXZ @0x005EA8C4 31B thiscall slot2 plus validate plus tail 0x005EA58B caller jmp 0x005EA91D
template <typename T> class StringBase
{
	friend class Rva005EA58B;
	void validate() const;
};
struct Rva005EA58BHolder
{
	char m_pad[8];
	StringBase<unsigned short> m_str;
};
struct Rva005EA58BElem
{
	char m_pad[0x20];
	Rva005EA58BHolder *m_holder;
};
struct Rva005EA58BRange
{
	Rva005EA58BElem *m_begin;
	Rva005EA58BElem *m_end;
	int m_pad;
};
class Rva005EA58BVirtObject
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
};
struct Rva005EA58BSlotHolder
{
	Rva005EA58BVirtObject *m_ptr;
};
class Rva005EA58B
{
public:
	void rva005EA58B();
	void rva005EA8C4();
private:
	char m_pad0[0x14];
	Rva005EA58BSlotHolder m_slotHolder;
	char m_pad1[0x4];
	Rva005EA58BRange m_ranges[2];
	StringBase<unsigned short> *m_strPtr;
};
void Rva005EA58B::rva005EA58B()
{
	Rva005EA58BRange *r = m_ranges;
	int n = 2;
	do {
		Rva005EA58BElem *b = r->m_begin;
		Rva005EA58BElem *e = r->m_end;
		for (Rva005EA58BElem *p = b; p != e; ++p) {
			Rva005EA58BHolder *h = p->m_holder;
			if (h)
				h->m_str.validate();
		}
		++r;
		--n;
	} while (n != 0);
}
void Rva005EA58B::rva005EA8C4()
{
	m_slotHolder.m_ptr->f2();
	if (m_strPtr)
		m_strPtr->validate();
	return rva005EA58B();
}
