// cl: /O1 /MD
// ?rva005C8D17@Rva005C8D17@@QAEMXZ @0x005C8D17 23B: float getter default 1.0f.
// Evidence: caller 0x005C8D79; callee none (only global g_Va00BBB8D8 1.0f); members +0x2C chain +8 +0x10 plus +0x30 flag; neighbours RvaTreeEraseClearFamily RvaTreeDtorFamily.
extern float g_Va00BBB8D8;

struct Rva005C8D17Inner
{
	unsigned char m_pad[0x10];
	float m_10;
};

struct Rva005C8D17Mid
{
	unsigned char m_pad[8];
	Rva005C8D17Inner *m_08;
};

class Rva005C8D17
{
public:
	float rva005C8D17();
private:
	unsigned char m_pad[0x2C];
	Rva005C8D17Mid *m_2C;
	int m_30;
};

float Rva005C8D17::rva005C8D17()
{
	if (m_30 == 0)
		return g_Va00BBB8D8;
	return m_2C->m_08->m_10;
}
