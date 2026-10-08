// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003193EC@Rva003193EC@@QAE_NH@Z @0x003193EC 39B: thiscall bool method
// adding BfmeY1038 value at +0x78 to its int arg then comparing against the
// rowed free helper 0x003192B9 result. Evidence: packet disasm with pinned
// bfmeVal1038 0x0040CF91 plus rowed GetMaxCommandPoints plus ret-4 single int arg
// plus setle bool return, callers 0x002B6CD6 0x002B6D6F 0x00319422.
// class-gate: allow StringBase private validate for row ?validate@?$StringBase@G@@ABEXXZ at 0x000B3FD0

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
template <typename T> class StringBase
{
	friend class Rva003193EC;
	void validate() const;
};

class BfmeY1038
{
public:
	int bfmeVal1038();
};

class Rva0037DCA5
{
public:
	int rva0037DCA5();
};

class Rva002BA8F1Logic;

class Rva002B2B5B
{
public:
	int rva002B2B5B(int v);
};

class Rva00318CA4Owner
{
public:
	unsigned char rva00318CA4();
};

class Rva00318BC6Owner
{
public:
	void rva00318BC6(int v);
};

class Rva0031980CListener
{
public:
	virtual void notify(void *, int);
};

class Rva0031980CList
{
public:
	void forEach(void (Rva0031980CListener::*notify)(void *, int), void *arg, int value);
private:
	Rva0031980CListener **m_begin;
	Rva0031980CListener **m_end;
	Rva0031980CListener **m_capacity;
	unsigned int m_index;
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class Rva0040DDD6
{
public:
	int rva0040DDD6();
};

class Rva003FDEAD
{
public:
	void rva003FDEAD();
};

void *GetMaxCommandPoints(void *key);

class Rva003193EC
{
public:
	bool rva003193EC(int x);
	bool rva00319413(Rva0037DCA5 *p);
	void rva003190E7(bool flag);
	void rva003198B8(Rva003193EC *other);
	void rva003191B1();
	void rva003192B1();
private:
	char m_pad00[8];
	Rva0031980CList m_list08;
	char m_pad18[0x78 - 0x18];
	BfmeY1038 *m_78;
	char m_pad7C[0x88 - 0x7C];
	StringBase<unsigned short> *m_88;
};

bool Rva003193EC::rva003193EC(int x)
{
	int v = m_78->bfmeVal1038();
	int total = v + x;
	void *got = GetMaxCommandPoints(this);
	return total <= (int)got;
}

bool Rva003193EC::rva00319413(Rva0037DCA5 *p)
{
	return rva003193EC(p->rva0037DCA5());
}

void Rva003193EC::rva003190E7(bool flag)
{
	if (!flag)
	{
		if (((Rva00318CA4Owner *)this)->rva00318CA4())
			return;
	}
	int v = m_78->bfmeVal1038();
	if (v == -1)
		return;
	int w = ((Rva002B2B5B *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->rva002B2B5B(v);
	((Rva00318BC6Owner *)this)->rva00318BC6(w);
}

void Rva003193EC::rva003198B8(Rva003193EC *other)
{
	if (other->m_88 != 0)
		other->m_88->validate();
	if (m_88 != 0)
		m_88->validate();
	other->rva003190E7(false);
	rva003190E7(false);
	m_list08.forEach((void (Rva0031980CListener::*)(void *, int))&Rva005CB260::rva005CB260, this, (int)other);
}

void Rva003193EC::rva003191B1()
{
	if (((Rva0040DDD6 *)m_78)->rva0040DDD6() <= 0)
		return;
	if (((Rva003FDEAD *)m_88) != 0)
		((Rva003FDEAD *)m_88)->rva003FDEAD();
	rva003190E7(false);
}

void Rva003193EC::rva003192B1()
{
	rva003190E7(false);
}
