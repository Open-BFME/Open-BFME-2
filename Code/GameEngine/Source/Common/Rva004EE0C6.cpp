// cl: /MD
// ?rva004EE0C6@Rva004EE0C6@@QAEXHPAVLivingWorldBattle@@@Z, retail 0x004EE0C6, 77 bytes.
// Stores time(0) to +0x60; if rva003F486C(p [this+0xE4]) then rva003F4798(p
// [this+0xE4] [p+0x38]) and inc +0xC8 when >=0 else +0xCC. Evidence: time IAT
// 0x00BBA508; rowed 0x003F486C 0x003F4798 in Rva003F498ALoops; chain from
// 0x003F486C; prev Rva004EE037Div /O1 /MD; ret 8 two args.
extern "C" __declspec(dllimport) long __cdecl time(long *value);

class LivingWorldBattle
{
public:
	bool rva003F486C(int id);
	int rva003F4798(int outerIdx, int id);
};

class Rva004EE0C6
{
public:
	void rva004EE0C6(int unused, LivingWorldBattle *p);
private:
	char m_pad00[0x60];
	int m_60;
	char m_pad64[0xC8 - 0x64];
	int m_c8;
	int m_cc;
	char m_padD0[0xE4 - 0xD0];
	int m_e4;
};

void Rva004EE0C6::rva004EE0C6(int unused, LivingWorldBattle *p)
{
	(void)unused;
	m_60 = (int)time(0);
	if (!p->rva003F486C(m_e4))
		return;
	int tmp38 = *(int *)((char *)p + 0x38);
	int v = p->rva003F4798(tmp38, m_e4);
	if (v >= 0)
		++m_c8;
	else
		++m_cc;
}
