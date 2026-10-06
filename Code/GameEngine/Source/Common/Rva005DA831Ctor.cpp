// cl: /DNDEBUG /MD /EHsc
// ??0Rva005DA831@@QAE@PAX@Z @0x005DA831 35B evidence: base Rva005DAA36 holder void* rowed in V3PolyCopyCtors; derived vtable 0x00876518; or -1 at +0x08 and 3 at +0x0C; caller 0x00597227; cross-TU base call forces esi save

class Rva005DAA36
{
public:
	Rva005DAA36(void *held);
	virtual ~Rva005DAA36();
private:
	void *m_04;
};

class Rva005DA831 : public Rva005DAA36
{
public:
	Rva005DA831(void *held);
	virtual ~Rva005DA831();
private:
	int m_08;
	int m_0C;
};

Rva005DA831::Rva005DA831(void *held)
	: Rva005DAA36(held)
{
	m_08 = -1;
	m_0C = 3;
}
