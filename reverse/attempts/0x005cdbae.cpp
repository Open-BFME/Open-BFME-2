// ?make@Rva005CDBAEFactory@@QAE?AVRva005CDBAERefPtr@@PAX0@Z
// partial score=0.64 date=2026-10-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Five 106-byte wide-family factory candidates. Target evidence: each body
// allocates the observed concrete size, invokes its matching constructor call
// target, adjusts the returned interface pointer by the observed base offset,
// then increments the shared virtual-base reference count. The virtual-base
// offsets and constructor/vftable stores agree with the neighboring dtor
// views in VslotVbaseDeletingDtors.cpp. Factory owner and interface names are
// address-derived; their semantic identities remain unresolved.

class Rva005CDBAERefBase
{
public:
	virtual void slot00();
	virtual void slot04();
	int m_refCount;
	__forceinline void addRef() { ++m_refCount; }
};

class Rva005CDBAERefViewA : public virtual Rva005CDBAERefBase
{
};

class Rva005CDBAERefViewB : public virtual Rva005CDBAERefBase
{
};

class __declspec(novtable) Rva005CDBAEViewGap4
{
public:
	virtual void slot00();
};

class Rva005CDBAERefPtr
{
public:
	void *m_ptr;

	template <class View>
	__forceinline Rva005CDBAERefPtr(View *p) : m_ptr(p)
	{
		if (p)
			static_cast<Rva005CDBAERefBase *>(p)->addRef();
	}

	~Rva005CDBAERefPtr() {}
};

template <int Size>
class __declspec(novtable) Rva005CDBAEFactoryPrefix
{
public:
	virtual void slot00();
	char m_pad[Size - 4];
};

class Rva005CD9C0
{
public:
	Rva005CD9C0(void *, void *, void *, int);
	char m_pad[0x28];
};

class Rva005CDCEE
{
public:
	Rva005CDCEE(void *, void *, void *, int);
	char m_pad[0x30];
};

class Rva005E6F9D
{
public:
	Rva005E6F9D(void *, void *, void *, int);
	char m_pad[0x2c];
};

class Rva005E54F7
{
public:
	Rva005E54F7(void *, void *, void *, int);
	char m_pad[0x24];
};

class __declspec(novtable) Rva005CD9C0Layout : public Rva005CDBAEFactoryPrefix<8>,
	public Rva005CDBAERefViewA, public Rva005CDBAERefViewB
{
	char m_pad[8];
};

class __declspec(novtable) Rva005CDCEELayout : public Rva005CDBAEFactoryPrefix<12>,
	public Rva005CDBAERefViewA, public Rva005CDBAERefViewB
{
	char m_pad[12];
};

class __declspec(novtable) Rva005E6F9DLayout : public Rva005CDBAEFactoryPrefix<12>,
	public Rva005CDBAERefViewA, public Rva005CDBAEViewGap4, public Rva005CDBAERefViewB
{
	char m_pad[8];
};

class __declspec(novtable) Rva005E54F7Layout : public Rva005CDBAEFactoryPrefix<8>,
	public Rva005CDBAERefViewA, public Rva005CDBAEViewGap4, public Rva005CDBAERefViewB
{
	char m_pad[4];
};

class Rva005CDBAEFactory
{
public:
	Rva005CDBAERefPtr make(void *, void *);
};

class Rva005CDF8BFactory
{
public:
	Rva005CDBAERefPtr make(void *, void *);
};

class Rva005F4C8EFactory
{
public:
	Rva005CDBAERefPtr make(void *, void *);
};

class Rva005F4CF8Factory
{
public:
	Rva005CDBAERefPtr make(void *, void *);
};

class Rva005FAB34Factory
{
public:
	Rva005CDBAERefPtr make(void *, void *);
};

Rva005CDBAERefPtr Rva005CDBAEFactory::make(void *p1, void *p2)
{
	Rva005CD9C0 *object = 0;
	object = new Rva005CD9C0(p1, p2, reinterpret_cast<char *>(this) + 8, 1);
	Rva005CDBAERefPtr result(static_cast<Rva005CDBAERefViewA *>(
		reinterpret_cast<Rva005CD9C0Layout *>(object)));
	return result;
}

Rva005CDBAERefPtr Rva005CDF8BFactory::make(void *p1, void *p2)
{
	Rva005CDCEE *object = 0;
	object = new Rva005CDCEE(p1, p2, reinterpret_cast<char *>(this) + 8, 1);
	Rva005CDBAERefPtr result(static_cast<Rva005CDBAERefViewA *>(
		reinterpret_cast<Rva005CDCEELayout *>(object)));
	return result;
}

Rva005CDBAERefPtr Rva005F4C8EFactory::make(void *p1, void *p2)
{
	Rva005E6F9D *object = 0;
	object = new Rva005E6F9D(p1, p2, reinterpret_cast<char *>(this) + 8, 1);
	Rva005CDBAERefPtr result(static_cast<Rva005CDBAERefViewB *>(
		reinterpret_cast<Rva005E6F9DLayout *>(object)));
	return result;
}

Rva005CDBAERefPtr Rva005F4CF8Factory::make(void *p1, void *p2)
{
	Rva005E54F7 *object = 0;
	object = new Rva005E54F7(p1, p2, reinterpret_cast<char *>(this) + 8, 1);
	Rva005CDBAERefPtr result(static_cast<Rva005CDBAERefViewB *>(
		reinterpret_cast<Rva005E54F7Layout *>(object)));
	return result;
}

Rva005CDBAERefPtr Rva005FAB34Factory::make(void *p1, void *p2)
{
	Rva005E6F9D *object = 0;
	object = new Rva005E6F9D(p1, p2, reinterpret_cast<char *>(this) + 8, 1);
	Rva005CDBAERefPtr result(static_cast<Rva005CDBAERefViewA *>(
		reinterpret_cast<Rva005E6F9DLayout *>(object)));
	return result;
}
