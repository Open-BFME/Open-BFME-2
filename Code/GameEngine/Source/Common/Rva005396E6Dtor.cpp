// cl: /DNDEBUG /MD /EHsc
// ??1Rva005396E6@@QAE@XZ @0x005396E6 89B:
// Non-virtual dtor: frees void* at +0x0C and +0x10 via DisplayManager global
// 0x009FEAD8 slot 0x3C (FreeEntry) then wide StringBase members at +4/+8 via
// inlined releaseBuffer 0x00036E70. Deleting-dtor callers 0x005397DB (28B)
// and 0x005398B3 (26B). Evidence: ??_G shape caller; DisplayManager
// FreeEntry precedent Rva001EE3DEDtor; string-dtor precedent Rva005B72E7Dtor.
class DisplayManager
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void FreeEntry(void *p);
};

// ?g_009FEAD8@@3PAVDisplayManager@@A: the global at this VA is ?TheDisplayStringManager@@3PAVDisplayStringManager@@A; this name is an alias for it.
extern DisplayManager * g_009FEAD8;
#pragma comment(linker, "/alternatename:?g_009FEAD8@@3PAVDisplayManager@@A=?TheDisplayStringManager@@3PAVDisplayStringManager@@A")

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

class Rva005396E6
{
public:
	~Rva005396E6();
private:
	int m_00;
	StringBase<unsigned short> m_04;
	StringBase<unsigned short> m_08;
	void *m_0C;
	void *m_10;
};

Rva005396E6::~Rva005396E6()
{
	g_009FEAD8->FreeEntry(m_0C);
	g_009FEAD8->FreeEntry(m_10);
}

// ?rva005398B3@Rva005398B3@@QAEXXZ @0x005398B3 26B:
// Frees owned Rva005396E6: take ptr at +0, clear slot, delete it (dtor row
// 0x005396E6 plus operator delete 0x0002FD60). Caller 0x00539944.
// Evidence: chain after 0x005396E6; and [ecx],0 plus test-je-delete shape.
class Rva005398B3
{
public:
	void rva005398B3();
private:
	Rva005396E6 *m_00;
};

void Rva005398B3::rva005398B3()
{
	Rva005396E6 *p = m_00;
	m_00 = 0;
	delete p;
}

// ??1Rva00539926@@UAE@XZ @0x00539926 59B:
// Virtual dtor: vtable 0x00869268 then member at +8 via rowed rva005398B3
// then base dtor pinned at 0x004E84A4 (ICF twin of rowed apply 7B mov plus
// ret setting vptr to 0x00BC6F20). Caller 0x00539964 (??_G 28B). Evidence:
// vtable store plus chain after 0x005398B3 plus base call; EH frame.
class Rva00539926Base
{
public:
	virtual ~Rva00539926Base();
};

class Rva00539926 : public Rva00539926Base
{
public:
	virtual ~Rva00539926();
private:
	int m_04;
	Rva005398B3 m_08;
};

Rva00539926::~Rva00539926()
{
	m_08.rva005398B3();
}
