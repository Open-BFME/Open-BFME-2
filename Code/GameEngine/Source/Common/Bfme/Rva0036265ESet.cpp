// cl: /MD
//
// ?rva0036265E@Rva0036265E@@QAEX_N@Z retail 0x0036265E 23 bytes. Guarded byte
// store to header+0x45 when +0x18 non-null and +0xC equals 1. Evidence: caller
// 0x003627A7 pushes 0/1 bool, ret 4 one stack arg, no callees.

class Rva0036265E
{
public:
	void rva0036265E(bool value);
private:
	char m_00[0xC];
	int m_0C;
	char m_10[0x18 - 0x10];
	void *m_18;
};

struct Rva0036265ETarget
{
	char m_00[0x45];
	unsigned char m_45;
};

void Rva0036265E::rva0036265E(bool value)
{
	Rva0036265ETarget *target = (Rva0036265ETarget *)m_18;
	if (target == 0)
		return;
	if (m_0C != 1)
		return;
	target->m_45 = value;
}
