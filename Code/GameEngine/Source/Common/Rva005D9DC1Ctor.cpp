// cl: /MD
// ??0Rva005D9DC1@@QAE@XZ, retail 0x005D9DCC, 26 bytes.
// ??0Rva005D9D5A@@QAE@XZ, retail 0x005D9D48, 18 bytes.
// Derived ctor for Rva005D9DC1 (vtable 0x00876464 same as rowed dtor 0x005D9DC1
// in Rva005EEDAADerived.cpp). Calls base Rva005EEDAA ctor 0x005EED92 then
// constructs member Rva0024C7B3Member at +0x20 via rowed ctor 0x0024C7B3.
// Base size 0x20 (Rva0058AD7A 0x1C plus int at +0x1C). throw() on callees
// suppresses the EH frame and is mangle-safe.

class Rva0058AD7A
{
public:
	Rva0058AD7A(int x) throw();
	virtual ~Rva0058AD7A();

private:
	int m_04;
	int m_08;
	int m_0C;
	float m_10;
	float m_14;
	unsigned char m_18;
	unsigned char m_19;
	unsigned char m_1A;
};

class Rva005EEDAA : public Rva0058AD7A
{
public:
	Rva005EEDAA() throw();
	virtual ~Rva005EEDAA();

private:
	int m_1C;
};

class Rva0024C7B3Member
{
public:
	Rva0024C7B3Member() throw();

	unsigned char m_data[0x1C];
};

class Rva005D9DC1 : public Rva005EEDAA
{
public:
	Rva005D9DC1();
	virtual ~Rva005D9DC1();

private:
	Rva0024C7B3Member m_20;
};

Rva005D9DC1::Rva005D9DC1()
	: Rva005EEDAA()
{
}

class Rva005D9D5A : public Rva005D9DC1
{
public:
	Rva005D9D5A();
	virtual ~Rva005D9D5A();
};

Rva005D9D5A::Rva005D9D5A()
{
}

class Rva005D99BD : public Rva005D9DC1
{
public:
	Rva005D99BD();
	virtual ~Rva005D99BD();
};

Rva005D99BD::Rva005D99BD()
{
}
