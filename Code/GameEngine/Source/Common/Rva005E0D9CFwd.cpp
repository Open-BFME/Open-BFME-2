// cl: /O1 /DNDEBUG /MD
// ?rva005E0D9C@Rva005E0D9C@@QAEXXZ @0x005E0D9C 36B.
// If +0x10 null return; else call rowed no-arg int getter 0x005CB265 via +0x0C;
// if result != +0x10 return; else tail-jmp to rowed void forwarder 0x005CB260.
// Address-derived.
class Rva005CB265
{
public:
	virtual int rva005CB265();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva005E0D9C
{
public:
	void rva005E0D9C();
protected:
	unsigned char m_pad[0x0C];
	Rva005CB265 *m_0C;
	int m_10;
};

void Rva005E0D9C::rva005E0D9C()
{
	int v = m_10;
	if (v == 0)
		return;
	int r = m_0C->Rva005CB265::rva005CB265();
	if (r != v)
		return;
	((Rva005CB260 *)m_0C)->rva005CB260();
}
