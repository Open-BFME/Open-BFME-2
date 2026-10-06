// cl: /DNDEBUG /MD /EHsc
// ?rva004E0BDC@Rva004E0BDC@@QAEXABURva004E0790Inner@@@Z @0x004E0BDC 109B ensure Inner at +0x3c via new plus copy ctor 0x0040D688 or assign 0x004E09FB then store +0x18 to +0xB4; chain via 0x0040D688
void *__cdecl operator new(unsigned int size);
void __cdecl operator delete(void *p);

struct BfmeAssignRecord172
{
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &other);
	char m_pad[0xAC];
};

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

struct Rva004E0790Inner
{
	BfmeAssignRecord172 m_00;
	TargetRef00217D4C m_ac;
	int m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	unsigned char m_c4;
	unsigned char m_c5;
	Rva004E0790Inner &rva004E09FB(const Rva004E0790Inner &other);
};

class Rva0040C351
{
public:
	Rva0040C351(const Rva0040C351 &o);
private:
	char m_pad[0xC8];
};

class Rva004E0790
{
public:
	void rva004E08F6(Rva004E0790Inner *p);
	Rva004E0790Inner *m_ptr;
};

class Rva004E0BDC
{
public:
	void rva004E0BDC(const Rva004E0790Inner &arg);
private:
	char m_pad00[0x18];
	int m_18;
	char m_pad1C[0x20];
	Rva004E0790 m_3c;
};

void Rva004E0BDC::rva004E0BDC(const Rva004E0790Inner &arg)
{
	if (!m_3c.m_ptr) {
		Rva0040C351 *p = new Rva0040C351(*reinterpret_cast<const Rva0040C351 *>(&arg));
		m_3c.rva004E08F6(reinterpret_cast<Rva004E0790Inner *>(p));
	}
	else {
		m_3c.m_ptr->rva004E09FB(arg);
	}
	m_3c.m_ptr->m_b4 = m_18;
}
