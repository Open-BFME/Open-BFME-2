// cl: /O1 /MD
// ?rva00404A29@Rva004053C2@@QAEXXZ @0x00404A29 73B: tail of slot 10 of 0x008388D4 via caller 0x00405315
// Evidence: caller jmp tail with same this plus fanout 0x0056C21B donor plus pin 0x004047E3 float-pair probe.

class Rva004047E3
{
public:
	void rva004047E3(float a, float b);
};

class Rva0056C21B
{
public:
	void rva0056C21B(float a, float b);
};

class Rva004053C2
{
public:
	void rva00404A29();
private:
	char m_pad00[0x18];
	float m_18;
	float m_1C;
	char m_pad20[0x78 - 0x20];
	Rva004047E3 m_78;
	char m_pad79[0x12C - 0x78 - 1];
	Rva0056C21B *m_12C[2];
};

void Rva004053C2::rva00404A29()
{
	for (int i = 0; i < 2; ++i) {
		Rva0056C21B *p = m_12C[i];
		if (p)
			p->rva0056C21B(m_18, m_1C);
	}
	((Rva004047E3 *)((char *)this + 0x78))->rva004047E3(m_18, m_1C);
}
