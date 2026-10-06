// cl: /MD /EHsc
// ?rva001F64D2@Rva001F64D2@@QAEXXZ 0x001F64D2 23B
// Evidence: chain from 0x001F5D38; null-checked virtual slot +4 at +0 then tail-jmp to rowed Rva001F5D38::rva001F5D38 on this+4.

class Helper001F64D2
{
public:
	virtual ~Helper001F64D2();
	virtual void tick();
};

class Rva001F5D38
{
public:
	void rva001F5D38();
};

class Rva001F64D2
{
public:
	void rva001F64D2();
private:
	Helper001F64D2 *m_ptr;
	Rva001F5D38 m_next;
};

void Rva001F64D2::rva001F64D2()
{
	Helper001F64D2 *p = m_ptr;
	if (p)
		p->tick();
	m_next.rva001F5D38();
}
