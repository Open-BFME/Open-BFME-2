// cl: /MD
// ??0Rva0058AD7A@@QAE@H@Z, retail 0x0058AD4D, 45 bytes.
// Base ctor for Rva0058AD7A (vtable 0x0087091C, same as rowed dtor 0x0058AD7A
// in Rva0058AD7ABase.cpp). Called from derived ctor 0x005EE2E6 with arg 5.
// Layout from retail immediates: m_04=int arg, m_08=uninit pad, m_0C=0,
// m_10/m_14=0.0f floats, m_18/m_19/m_1A=0 bytes. Base size 0x1C.

class Rva0058AD7A
{
public:
	Rva0058AD7A(int x);
	virtual ~Rva0058AD7A() {}

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

Rva0058AD7A::Rva0058AD7A(int x)
	: m_04(x)
	, m_0C(0)
	, m_10(0.0f)
	, m_14(0.0f)
	, m_18(0)
	, m_19(0)
	, m_1A(0)
{
}
