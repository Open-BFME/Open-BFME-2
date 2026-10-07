// cl: /O1 /arch:SSE /G7 /MD
// ?rva005CE130@Rva005CE130@@QAEXH@Z @0x005CE130 38B
// evidence: VTABLE slot 2 table 0x00875148; callees ?rva004E05F0@Rva004E05F0@@QAEPAVCreateAHeroData@@XZ rowed and ?fwd@Rva005E683EMid@@QAEXHH@Z rowed; callers none

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

class Rva005E683EMid
{
public:
	void fwd(int a, int b);
};

class Rva005CE130
{
public:
	void rva005CE130(int arg);
	char m_lead[0x10];
	Rva004E05F0 *m_10;
};

void Rva005CE130::rva005CE130(int arg)
{
	(void)arg;
	Rva004E05F0 *p = m_10;
	Rva003F1093 *f1 = p->m_24;
	if (f1 == 0)
		return;
	CreateAHeroData *f2 = p->rva004E05F0();
	if (f2 == 0)
		return;
	Rva005E683EMid *outer = (Rva005E683EMid *)((char *)this - 8);
	outer->fwd((int)f1, (int)f2);
}
