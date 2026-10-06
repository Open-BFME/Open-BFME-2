// cl: /DNDEBUG /MD /EHsc
// ?rva000D1C83@Rva000D1C83@@QAEXXZ @0x000D1C83 158B
// VB/IB container init: releases existing pair via rowed Rva0074011F,
// allocates BfmeDynamicNativeVB(0x142,0x7534,1,0) and DX8IndexBuffer(0xea64,1),
// zeroes +0x08/+0x0C, stamps +0x10=0x7530 +0x14=0xea60.
// Evidence: retail EH_prolog, dual new plus rowed 0x0013AC00 0x00138980,
// rowed release 0x0074011F, callers 0x000669E7 0x000D3B0A.

class Rva0074011F
{
public:
	void rva0074011F();

protected:
	void *m_p0; // +0x00
	void *m_p1; // +0x04
};

class BfmeDynamicNativeVB
{
public:
	BfmeDynamicNativeVB(unsigned fvf, unsigned short count, unsigned usage, unsigned fvfSize);

private:
	unsigned char m_pad[0x20]; // sizeof 0x20 per BfmeDynamicNativeVBSize check
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};
	DX8IndexBufferClass(unsigned indexCount, UsageType usage);

private:
	unsigned char m_pad[0x18]; // sizeof 0x18 (new 0x18)
};

class Rva000D1C83 : public Rva0074011F
{
public:
	void rva000D1C83();

private:
	void *m_08; // +0x08
	void *m_0C; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
};

void Rva000D1C83::rva000D1C83()
{
	if (m_p0 || m_p1)
		Rva0074011F::rva0074011F();
	BfmeDynamicNativeVB *vb = new BfmeDynamicNativeVB(0x142, 0x7534, 1, 0);
	m_p0 = vb;
	DX8IndexBufferClass *ib = new DX8IndexBufferClass(0xea64, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_08 = 0;
	m_0C = 0;
	m_p1 = ib;
	m_14 = 0xea60;
	m_10 = 0x7530;
}
