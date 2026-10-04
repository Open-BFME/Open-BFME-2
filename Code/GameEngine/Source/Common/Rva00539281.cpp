// cl: /O1 /MD
//
// ?rva00539281@Rva00539281@@QAEXHH@Z @0x00539281 65B
// Evidence: virtual count via slot 0x34 plus per-index slot 0x3C plus element slot 0x38 with two int args; byte at +0x28 vs first arg; callers 0x003FE549; neighbours Rva005391FD.
class Rva00539281Elem
{
public:
	virtual ~Rva00539281Elem();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14(int a0, int a1);
};

class Rva00539281
{
public:
	virtual ~Rva00539281();
	virtual void u01();
	virtual void u02();
	virtual void u03();
	virtual void u04();
	virtual void u05();
	virtual void u06();
	virtual void u07();
	virtual void u08();
	virtual void u09();
	virtual void u10();
	virtual void u11();
	virtual void u12();
	virtual int u13();
	virtual void u14();
	virtual Rva00539281Elem *u15(int i);
	void rva00539281(int a0, int a1);
private:
	char m_pad04[0x24];
	unsigned char m_28;
};

void Rva00539281::rva00539281(int a0, int a1)
{
	if (m_28 == (unsigned char)a0)
		return;
	m_28 = (unsigned char)a0;
	int count = u13();
	for (int i = 0; i < count; ++i)
	{
		Rva00539281Elem *p = u15(i);
		p->t14(a0, a1);
	}
}
