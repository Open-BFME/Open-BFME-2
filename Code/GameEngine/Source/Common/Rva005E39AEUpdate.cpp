// cl: /O1 /MD
struct Rva005E39AEInner
{
	virtual int f0();
	virtual int f1();
};
class Rva005F2A32
{
public:
	void rva005F2F5C(int v);
	void rva005F2A4A();
	void rva005F2A32();
	void rva005F2A3A();
	void rva005F2A42();
};
class Rva005E39AE
{
public:
	void rva005E39AE();
	void rva005E3AAA(int v);
private:
	char m_00[8];
	Rva005E39AEInner *m_08;
	char m_0C[0x18 - 0x0C];
	Rva005F2A32 *m_18;
	char m_1C[0x28 - 0x1C];
	int m_28;
	char m_2C;
	bool m_2D;
};
void Rva005E39AE::rva005E39AE()
{
	if (m_28 != 0) {
		m_2D = false;
		return;
	}
	int v = m_08->f1();
	if (v > 0)
		m_18->rva005F2F5C(v);
	else
		m_18->rva005F2A4A();
	m_2D = false;
}
void Rva005E39AE::rva005E3AAA(int v)
{
	if (v != m_28)
		return;
	m_18->rva005F2A32();
	m_18->rva005F2A3A();
	m_18->rva005F2A42();
	m_28 = 0;
	m_2D = true;
	rva005E39AE();
}
