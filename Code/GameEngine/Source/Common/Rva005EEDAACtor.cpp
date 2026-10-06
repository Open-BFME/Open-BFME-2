// cl: /MD
// ??0Rva005EEDAA@@QAE@XZ, retail 0x005EED92, 24 bytes.
// Derived ctor for Rva005EEDAA (vtable 0x00878788 same as rowed dtor 0x005EEDAA
// in Rva005EE30CChain.cpp). Calls base Rva0058AD7A ctor 0x0058AD4D with 3
// then zeroes member at +0x1C. Base size 0x1C.

class Rva0058AD7A
{
public:
	Rva0058AD7A(int x);
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
	Rva005EEDAA();
	virtual ~Rva005EEDAA();

private:
	int m_1C;
};

Rva005EEDAA::Rva005EEDAA()
	: Rva0058AD7A(3)
	, m_1C(0)
{
}
