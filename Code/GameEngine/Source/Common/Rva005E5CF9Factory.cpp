// cl: /EHsc /Oy- /Ob2
// ?rva005E5CF9@Rva005E5CF9@@QAE?AURvaF1Handle@@H@Z, retail 0x005E5CF9 (84B).
// Factory method returning RvaF1Handle by value: allocates 0x28 bytes, runs
// rowed ??0Rva005F589E@@QAE@HPAX@Z with (int arg, this+8), null-checked AddRef
// (inc [eax+4]) and hidden-pointer return (ret 8). Evidence: callee row
// 0x005F589E, new row 0x0002FDA0, EH_prolog row 0x00629188, ret-8 + hidden
// pointer shape matching RvaFamily1Clones clones, this+8 as second ctor arg.
struct RvaF1Handle
{
	void *m_p;
	__forceinline RvaF1Handle(void *p) : m_p(p)
	{
		if (p)
			++((int *)p)[1];
	}
	~RvaF1Handle();
};

class Rva005F589E
{
	char m_pad[0x28];
public:
	Rva005F589E(int a1, void *a2);
};

struct Rva005E5CF9In
{
	void *m_00;
	int m_04;
	void *m_08;
};

struct Rva005E5CF9
{
	char m_pad08[8];
	Rva005E5CF9In m_in;
	RvaF1Handle rva005E5CF9(int a1);
};

RvaF1Handle Rva005E5CF9::rva005E5CF9(int a1)
{
	return RvaF1Handle(new Rva005F589E(a1, (void *)&m_in));
}

// Widened queue: three independently witnessed members of this factory
// pattern. Each has a hidden one-word result, AddRef at object +4 and a
// context pointer at receiver +8. Constructor arguments are opaque words:
// target callees forward them without interpreting them here. These names
// and storage-only views do not claim an application class or enum identity.
class Rva005E8DCF
{
	char m_pad[0x24];
public:
	Rva005E8DCF(unsigned int argument, void *context);
};
class Rva005E91ED
{
	char m_pad[0x20];
public:
	Rva005E91ED(unsigned int argument, void *context);
};
class Rva006004C1
{
	char m_pad[0x28];
public:
	Rva006004C1(unsigned int first, unsigned int second, void *context);
};
struct Rva005CE2D3
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005CE2D3(unsigned int argument);
};
struct Rva005CEA92
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005CEA92(unsigned int argument);
};
struct Rva005FB418
{
	char m_prefix[8];
	Rva005E5CF9In m_context;
	RvaF1Handle rva005FB418(unsigned int first, unsigned int second);
};

RvaF1Handle Rva005CE2D3::rva005CE2D3(unsigned int argument)
{
	return RvaF1Handle(new Rva005E8DCF(argument, &m_context));
}
RvaF1Handle Rva005CEA92::rva005CEA92(unsigned int argument)
{
	return RvaF1Handle(new Rva005E91ED(argument, &m_context));
}
RvaF1Handle Rva005FB418::rva005FB418(unsigned int first, unsigned int second)
{
	return RvaF1Handle(new Rva006004C1(first, second, &m_context));
}

// Native 005E5D4D..005E5DA1 and 005E5DA1..005E5DF5 each return a
// one-word handle through a hidden pointer (ret 8). Both allocate 40 bytes,
// forward the explicit pointer and receiver+8 to the independently rowed
// constructors, and increment the result's reference count at +4.
// The constructor providers establish the three-word context layouts;
// factory/application names remain unknown. Earlier attempts lacked these
// providers; no donor identity is inferred from the matching instruction shape.
class Rva005A0B4CList;
struct Rva005F5C77In
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};
struct Rva005F5F2BIn
{
	void *m_00;
	int m_04;
	Rva005A0B4CList *m_08;
};
class Rva005F5C77
{
	char m_storage[0x28];
public:
	Rva005F5C77(void *argument, Rva005F5C77In *context);
};
class Rva005F5F2B
{
	char m_storage[0x28];
public:
	Rva005F5F2B(void *argument, Rva005F5F2BIn *context);
};
struct Rva005E5D4D
{
	char m_prefix[8];
	Rva005F5C77In m_context;
	RvaF1Handle rva005E5D4D(void *argument);
};
struct Rva005E5DA1
{
	char m_prefix[8];
	Rva005F5F2BIn m_context;
	RvaF1Handle rva005E5DA1(void *argument);
};

RvaF1Handle Rva005E5D4D::rva005E5D4D(void *argument)
{
	return RvaF1Handle(new Rva005F5C77(argument, &m_context));
}
RvaF1Handle Rva005E5DA1::rva005E5DA1(void *argument)
{
	return RvaF1Handle(new Rva005F5F2B(argument, &m_context));
}
