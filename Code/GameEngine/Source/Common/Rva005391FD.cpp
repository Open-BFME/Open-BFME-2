// cl: /MD
// ?rva005391FD@Rva005391FD@@QAEXXZ @0x005391FD 42B
// Honest address-derived loop: count via virtual slot 0x34 then for each
// index call virtual slot 0x3C to get Rva005C4B56 object then call its
// rowed rva005C4CC1. Chain lane after 0x005C4CC1. Prev 0x0053916B float
// getter and next 0x0053997D byte setter. No callers.
class Rva005C4B56
{
public:
	void rva005C4CC1();
	void rva005C4CD4();
};

class Rva005391FD
{
public:
	virtual ~Rva005391FD();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual int s13();
	virtual void s14();
	virtual Rva005C4B56 *s15(int i);
	void rva005391FD();
	void rva00539227();
};

void Rva005391FD::rva005391FD()
{
	int count = s13();
	for (int i = 0; i < count; ++i)
	{
		Rva005C4B56 *p = s15(i);
		p->rva005C4CC1();
	}
}

void Rva005391FD::rva00539227()
{
	int count = s13();
	for (int i = 0; i < count; ++i)
	{
		Rva005C4B56 *p = s15(i);
		p->rva005C4CD4();
	}
}

// ?rva005392C2@Rva005392C2@@QAEXXZ @0x005392C2 42B:
// Honest address-derived loop: count via virtual slot 0x34 then for each
// index call virtual slot 0x3C to get Rva003FC3E4 object then call its rowed
// rva003FC3E4 reset. Same shape as Rva005391FD methods above, same // cl:
// /O1 /MD, new container class since element type differs. Chain lane after
// 0x003FC3E4. Callers 0x0031929B 0x004E06F2 0x004FC26C unclaimed.
class Rva003FC3E4
{
public:
	void rva003FC3E4();
};

class Rva005392C2
{
public:
	virtual ~Rva005392C2();
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
	virtual int t13();
	virtual void t14();
	virtual Rva003FC3E4 *t15(int i);
	void rva005392C2();
};

void Rva005392C2::rva005392C2()
{
	int count = t13();
	for (int i = 0; i < count; ++i)
	{
		Rva003FC3E4 *p = t15(i);
		p->rva003FC3E4();
	}
}
