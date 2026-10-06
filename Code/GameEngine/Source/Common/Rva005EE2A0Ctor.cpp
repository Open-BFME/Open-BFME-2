// cl: /MD
// ??0Rva005EE2A0@@QAE@XZ, retail 0x005EE28C, 20 bytes.
// Derived ctor for Rva005EE2A0 (vtable 0x008786CC same as rowed dtor 0x005EE2A0
// in Rva005EE30CChain.cpp). Calls base Rva0058AD7A ctor 0x0058AD4D with 2.
// Base size 0x1C (see Rva0058AD7ACtor.cpp). No extra members.

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

class Rva005EE2A0 : public Rva0058AD7A
{
public:
	Rva005EE2A0();
	virtual ~Rva005EE2A0();
};

Rva005EE2A0::Rva005EE2A0()
	: Rva0058AD7A(2)
{
}
