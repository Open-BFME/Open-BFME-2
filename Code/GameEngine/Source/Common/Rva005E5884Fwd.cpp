// cl: /O1 /DNDEBUG /MD
// ?rva005E5884@Rva005E5884@@QAEHHH@Z @0x005E5884 26B forwarder.
// If +0x40 nonzero return -1; else fetch +0x38 object; if null return -1;
// else tail-call its virtual slot +0x0C (no stack args) and return its value.
// Ret 8 takes two ignored ints. Address-derived.
class Rva005E5884Inner
{
public:
	virtual void _p0();
	virtual void _p1();
	virtual void _p2();
	virtual int rva005E5884Slot();
};

class Rva005E5884
{
public:
	int rva005E5884(int a, int b);
protected:
	unsigned char m_pad[0x38];
	Rva005E5884Inner *m_38;
	int m_3C;
	int m_40;
};

int Rva005E5884::rva005E5884(int a, int b)
{
	(void)a;
	(void)b;
	if (m_40 != 0)
		return -1;
	Rva005E5884Inner *o = m_38;
	if (o)
		return o->rva005E5884Slot();
	return -1;
}
