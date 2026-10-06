// cl: /O1 /DNDEBUG /MD /EHs
// ??1Rva0053947D@@UAE@XZ @0x0053947D 87B:
// Virtual dtor: vtable 0x00869228, base list at +4 via rowed forEach 0x005393F3
// with forwarder 0x001FF3A9 and arg this, erase via rowed 0x002BF6B7 on
// global 0x00DFEF18, then base dtor inlines free of list buffer via 0x00030830
// with null check. Base carries the list so EH arms for forEach/erase.
// Evidence: vtable store plus chain (next row 0x005394D4 28B is ??_G calling
// this); callers 0x003FE5E1 0x0052B3FD 0x005394D7 0x0059E242; forEach row,
// erase row, free row; /EHs for or -1 before free (neighbours use /EHsc).
class Rva005393F3Listener
{
public:
	virtual void notify(void *);
};

extern "C" void __cdecl free(void *p);

class Rva005393F3List
{
public:
	void forEach(void (Rva005393F3Listener::*notify)(void *), void *arg);
	~Rva005393F3List() throw()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva005393F3Listener **m_begin;
	Rva005393F3Listener **m_end;
	Rva005393F3Listener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class Rva002BF6B7
{
public:
	void rva002BF6B7(void *obj);
};

extern Rva002BF6B7 *g_00DFEF18;

class Rva0053947D : public Rva005393F3List
{
public:
	virtual ~Rva0053947D();
	virtual void v01();
	virtual void rva005391D3();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual int v13();
	virtual void v14();
	virtual void *v15(int i);
};

Rva0053947D::~Rva0053947D()
{
	forEach((void (Rva005393F3Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
	g_00DFEF18->rva002BF6B7(this);
}

class Rva005C4B56
{
public:
	void rva005C4C95();
};

void Rva0053947D::rva005391D3()
{
	int count = v13();
	for (int i = 0; i < count; i++)
		((Rva005C4B56 *)v15(i))->rva005C4C95();
}
