// cl: /MD
// ?rva0014DC76@Rva0014DC76@@QAEXXZ @ 0x0014DC76 17B: mov eax,g_00BC6F24 + 4 stores to [ecx+0..0xC]; caller 0x0014F438; honest address name.
extern int g_00BC6F24;
class Rva0014DC76
{
public:
	void rva0014DC76();
private:
	int m_0;
	int m_4;
	int m_8;
	int m_c;
};

void Rva0014DC76::rva0014DC76()
{
	int v = (int)&g_00BC6F24;
	m_c = v;
	m_8 = v;
	m_4 = v;
	m_0 = v;
}
