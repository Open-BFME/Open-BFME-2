// cl: /MD
// ?rva004ECE1C@Rva004ECE1C@@QAEXXZ @ 0x004ECE1C, 69 bytes.
// Early-return checks on +0x51 +0x28 +0x10 then GameLogic m_40 vs +0x54 with
// threshold g_00E044B0 then tail-jmps to vtable slots 0x18 and 0x1c.
// Evidence: xor-edx byte compares; TheGameLogic rowed name; g_ stopgap;
// 4 callers in 0x00505924 looping over object arrays; /O1 per xor-first.
class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A
extern unsigned int g_00E044B0;
// g_00E044B0: matched references place it at VA 0xe044b0 (zero-filled .bss).
unsigned int g_00E044B0;

class Rva004ECE1C
{
public:
	virtual ~Rva004ECE1C();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	void rva004ECE1C();
private:
	char m_pad04[0x0C];
	unsigned char m_10;
	char m_pad11[0x17];
	unsigned char m_28;
	char m_pad29[0x28];
	unsigned char m_51;
	char m_pad52[0x02];
	unsigned int m_54;
};

void Rva004ECE1C::rva004ECE1C()
{
	if (m_51 == 0)
		return;
	if (m_28 != 0)
		return;
	if (m_10 == 0) {
		if (m_54 == 0) {
			m_54 = TheGameLogic->m_40;
			return;
		}
		if (TheGameLogic->m_40 - m_54 < g_00E044B0)
			return;
		m_10 = 1;
		v06();
		return;
	}
	v07();
}
