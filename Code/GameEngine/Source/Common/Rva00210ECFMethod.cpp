// cl: /O1
// ?rva00210ECF@Rva00210ECF@@QAEXABUBfmeE8@@@Z @0x00210ECF (18B). Null-checked
// tail-jmp forwarder: member Rva003F9DDA* at +0x2C4, forwards the const
// BfmeE8& argument to rowed rva003F9DDA 0x003F9DDA. Chain from just-landed
// 0x003F9DDA. Caller at 0x0056559A.
struct BfmeE8;

class Rva003F9DDA
{
public:
	void rva003F9DDA(const BfmeE8 &x);
};

class Rva00210ECF
{
public:
	void rva00210ECF(const BfmeE8 &x);
private:
	char m_pad[0x2C4];
	Rva003F9DDA *m_ptr2C4;
};

void Rva00210ECF::rva00210ECF(const BfmeE8 &x)
{
	if (m_ptr2C4 != 0)
		m_ptr2C4->rva003F9DDA(x);
}
