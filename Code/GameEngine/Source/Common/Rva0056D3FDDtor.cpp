// cl: /O1 /DNDEBUG /MD /EHsc
// ??1Rva0056D3FD@@UAE@XZ @0x0056D3FD 59B
// Opaque dtor called by the rowed ??_G 0x0056D61F (vtable 0x00C6DAA4#0).
// Same shape as the rowed ??1Rva00539926 (Rva005396E6Dtor.cpp): store own
// vtable 0x00C6DAA4, release the member at +0x08 through the rowed
// ?rva0056D3E3@Rva0056D3E3 0x0056D3E3 (its sole caller) under EH state 0, then
// call the out-of-line base dtor pinned as ??1Rva00539926Base at 0x004E84A4
// (resets to 0x00BC6F20). Identity unproven; address-derived names.

class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
};

class Rva0056D3E3
{
public:
	void rva0056D3E3();

private:
	void *m_00;
};

class Rva0056D3FD : public Rva00539926Base
{
public:
	virtual ~Rva0056D3FD();

private:
	int m_04;
	Rva0056D3E3 m_08;
};

Rva0056D3FD::~Rva0056D3FD()
{
	m_08.rva0056D3E3();
}
