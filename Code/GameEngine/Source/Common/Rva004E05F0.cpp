// cl: /O1 /arch:SSE /G7 /MD
// ?rva004E05F0@Rva004E05F0@@QAEPAVCreateAHeroData@@XZ @0x004E05F0 21B
// evidence: callee pin ?rva003F083A@Rva003F1093@@QAEPAVCreateAHeroData@@PAX@Z; callers at 0x005CE13E 0x005CE61D 0x005CE698 0x005CF147; between Disp getters 0x004E05E9 and 0x004E0605

class CreateAHeroData;

class Rva003F1093
{
public:
	CreateAHeroData *rva003F083A(void *arg);
};

class Rva004E05F0
{
public:
	CreateAHeroData *rva004E05F0();
	char m_lead[0x18];
	void *m_18;
	char m_mid[0x08];
	Rva003F1093 *m_24;
};

CreateAHeroData *Rva004E05F0::rva004E05F0()
{
	if (m_24 != 0)
		return m_24->rva003F083A(m_18);
	return 0;
}
