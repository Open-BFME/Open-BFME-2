// cl: /MD
// ?rva00109DCF@Rva00109DCF@@QAEXXZ retail 0x00109DCF 66 bytes.
// Calls rowed Rva00108AD8 finish at this+0x24C then releases two refcounted
// members at +0x258 and +0x254 via dec [ecx+4] with virtual slot-0 call and
// zeroes them with and [m],0. Evidence: rowed callee 0x00108AD8 plus callers
// at 0x0009A406 and 0x0010C7B3. Precedent: /O1 and-zero shape.
class Rva00108AD8
{
public:
	void rva00108AD8();
};

struct Rva00109DCFRef
{
	virtual void Release();
	int m_ref;
};

class Rva00109DCF
{
public:
	void rva00109DCF();
private:
	char m_pad[0x24C];
	Rva00108AD8 *m_24C;
	char m_pad250[0x254 - 0x24C - 4];
	Rva00109DCFRef *m_254;
	Rva00109DCFRef *m_258;
};

void Rva00109DCF::rva00109DCF()
{
	m_24C->rva00108AD8();
	Rva00109DCFRef *p258 = m_258;
	if (p258 != 0)
	{
		if (--p258->m_ref == 0)
			p258->Release();
		m_258 = 0;
	}
	Rva00109DCFRef *p254 = m_254;
	if (p254 != 0)
	{
		if (--p254->m_ref == 0)
			p254->Release();
		m_254 = 0;
	}
}
