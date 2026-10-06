// cl: /O1 /MD
// ??0Rva005CE259@@QAE@PBUPayload@0@@Z, retail 0x005CE259, 30 bytes.
// vtable 0x00875124 at +0; +4 zeroed; 2-dword mov copy from src arg to +8; ret 4.
// Caller 0x005CE2BA news 0x10 and stores with refcount inc; twin pattern of
// 0x005CE327 3-dword ctor with 2-mov shape; unblocks 0x005CE2A1.
class Rva005CE259
{
public:
	struct Payload { int v[2]; };
	Rva005CE259(const Payload *src);
	virtual ~Rva005CE259() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005CE259::Rva005CE259(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

// 4 more constructors of this shape, each installing its own vtable
// (the only differing operand). One class per copy names that vtable; its
// destructor is declared inline and empty so the vtable the compiler emits
// resolves in this unit. Owners keep their addresses.

class Rva005677B9
{
public:
	struct Payload { int v[2]; };
	Rva005677B9(const Payload *src);
	virtual ~Rva005677B9() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005677B9::Rva005677B9(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva00574ABB
{
public:
	struct Payload { int v[2]; };
	Rva00574ABB(const Payload *src);
	virtual ~Rva00574ABB() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva00574ABB::Rva00574ABB(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva0057AA1F
{
public:
	struct Payload { int v[2]; };
	Rva0057AA1F(const Payload *src);
	virtual ~Rva0057AA1F() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva0057AA1F::Rva0057AA1F(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva005FAAA1
{
public:
	struct Payload { int v[2]; };
	Rva005FAAA1(const Payload *src);
	virtual ~Rva005FAAA1() {}
private:
	int m_ref; // +4
	Payload m_data; // +8
};

Rva005FAAA1::Rva005FAAA1(const Payload *src)
	: m_ref(0)
	, m_data(*src)
{
}

class Rva0056773E
{
public:
	Rva0056773E(int a, int b);
	virtual ~Rva0056773E() {}
private:
	int m_ref; // +4
	int m_8; // +8
	int m_C; // +0xC
};

Rva0056773E::Rva0056773E(int a, int b)
	: m_ref(0)
	, m_8(a)
	, m_C(b)
{
}

class Rva0057C22FByteChaseField
{
public:
	unsigned char get() const;
};

class Rva00567764Target
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual Rva0057C22FByteChaseField *f4();
};

class Rva00567764
{
public:
	int rva00567764();
private:
	char m_pad[12]; // +0..+0xB
	Rva00567764Target *m_C; // +0xC
};

int Rva00567764::rva00567764()
{
	Rva0057C22FByteChaseField *p = m_C->f4();
	if (p != 0) {
		if (p->get() != 0)
			return 1;
	}
	return 0;
}


