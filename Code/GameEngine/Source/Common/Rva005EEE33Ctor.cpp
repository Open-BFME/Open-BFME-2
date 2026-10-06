// cl: /MD
// ??0Rva005EEE33@@QAE@XZ, retail 0x005EEE1F, 20 bytes.
// Derived ctor for Rva005EEE33 (vtable 0x008787A4 same as rowed dtor 0x005EEE33
// in Rva005EE30CChain.cpp). Calls base Rva0058AD7A ctor 0x0058AD4D with 1.
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

class Rva005EEE33 : public Rva0058AD7A
{
public:
	Rva005EEE33();
	virtual ~Rva005EEE33();
};

Rva005EEE33::Rva005EEE33()
	: Rva0058AD7A(1)
{
}

class Rva005D9A1E : public Rva005EEE33
{
public:
	Rva005D9A1E();
	virtual ~Rva005D9A1E();
};

Rva005D9A1E::Rva005D9A1E()
{
}

class Rva005D9F70 : public Rva005EEE33
{
public:
	Rva005D9F70();
	virtual ~Rva005D9F70();
};

// ??0Rva005D9F70@@QAE@XZ @0x005D9F5E 18B: base ctor 0x005EEE1F then vtable
// 0x00876494. Evidence: vtable store at [this]; caller 0x0058A72D.
Rva005D9F70::Rva005D9F70()
{
}
