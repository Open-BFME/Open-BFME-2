// cl: /DNDEBUG /MD /EHsc
// ?rva001164AA@Rva001164AA@@QAEXXZ, retail 0x001164AA (12B).
// Evidence: unlock lane (unblocks 0x00101EC3); caller jmp at 0x00101EC9;
// vtable slot 0x10 tail-jmp with byte flag at +4; neighbours Disp0DwordImmSetters
// (no cl) and SurfaceByteSize (/O2 /Ob2 /G7). /G7 selects cmp-mem over mov+test;
// /O1 gives tail jmp for return-virtual in this 12B shape.
class Rva001164AA
{
public:
	virtual void s00() = 0;
	virtual void s04() = 0;
	virtual void s08() = 0;
	virtual void s0C() = 0;
	virtual void s10() = 0;
	void rva001164AA();
private:
	bool m_flag;
};

void Rva001164AA::rva001164AA()
{
	if (m_flag)
		return s10();
}
// ?rva00101EC3@Rva00101EC3@@QAEXXZ @0x00101EC3 12B leaf via rowed 0x001164AA tail jmp plus caller 0x000880EB
class Rva00101EC3
{
public:
	void rva00101EC3();
private:
	Rva001164AA *m_ptr;
};
void Rva00101EC3::rva00101EC3()
{
	if (m_ptr != 0)
		m_ptr->rva001164AA();
}
