// cl: /DNDEBUG /MD
//
// ?rva00267E46@Rva00267E46@@QAEXXZ, retail 0x00267E46 72B. Chain via 0x001E42F2.
// Null-check this+8 then Rva00265254 tmp 0 0x3d 0x85 0x86 0x89 0x8a 0x87 0x88
// 0x9d via 9-arg ctor plus rva001E42F2. Slot 145 of several AIUpdate vtables.

class Rva00265254
{
public:
	Rva00265254(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, unsigned int a5, unsigned int a6, unsigned int a7, unsigned int a8, unsigned int a9);
private:
	unsigned int m_bits[19];
};

class Rva001E42F2
{
public:
	void rva001E42F2(const int *x);
};

class Rva00267E46
{
public:
	void rva00267E46();
private:
	unsigned char m_pad00[8];
	Rva001E42F2 *m_08;
};

void Rva00267E46::rva00267E46()
{
	Rva001E42F2 *p = m_08;
	if (p == 0)
		return;
	p->rva001E42F2((const int *)&Rva00265254(0, 0x3d, 0x85, 0x86, 0x89, 0x8a, 0x87, 0x88, 0x9d));
}
