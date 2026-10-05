// ?rva002B3416@Rva002B3416@@QAEEPAX@Z
// partial score=0.97 date=2026-10-05
// partial score=0.97 date=2026-10-04
// cl: /O1 /MD /EHsc /DNDEBUG
// ?rva002B3416@Rva002B3416@@QAEEPAX@Z 110B @0x002B3416: this +0x98/+0xF4 guards then Rva002B254F guard then global Rva003B8BAA virtual slot 0x18 then arg +0x20/+0x1C plus Rva002B2B66 via g_009FEF10 and Rva003F07E5 check.
// Evidence: retail cmp [ecx+0x98] jne cmp [ecx+0xF4] jne call 0x2B254F test mov esi[esp+8] je mov ecx[g_00E02D6C] call 0x3B8BAA virtual [edx+0x18] test jne cmp [esi+0x20] jne mov ecx[g_009FEF10] mov edx[esi+0x1C] call 0x2B2B66 cmp [edx+0x13C] jne push 0 push esi mov ecx edx call 0x3F07E5 test setne. Callers at 0x002B680B 0x005754DA 0x005763A3.
// ?rva002B3416@Rva002B3416@@QAEEPAX@Z present-unmatched
class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

extern Rva003B8BAA *g_00E02D6C;

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class CreateAHeroData
{
public:
	char m_pad1C[0x1C];
	void *m_1C;
	int m_20;
};

class Rva003F07E5
{
public:
	bool rva003F07E5(CreateAHeroData *hero, int *out);
};

class LookupVirt18
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual bool check(void *a);
};

class Rva002B3416
{
public:
	unsigned char rva002B3416(void *arg);
private:
	char m_pad98[0x98];
	int m_98;
	char m_padF4[0x58];
	int m_F4;
};

unsigned char Rva002B3416::rva002B3416(void *arg)
{
	if (m_98 == 0)
		return 0;
	else
	{
		if (m_F4 != 0)
			return 0;
		if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
		{
			if (((LookupVirt18 *)g_00E02D6C->rva003B8BAA())->check(arg) == 0)
				return 0;
		}
		CreateAHeroData *hero = (CreateAHeroData *)arg;
		if (hero->m_20 != 0)
			return 0;
		int r = ((Rva002B2B66 *)g_009FEF10)->rva002B2B66();
		void *edxObj = hero->m_1C;
		if (*(int *)((char *)edxObj + 0x13C) != r)
			return 0;
		return (unsigned char)(((Rva003F07E5 *)edxObj)->rva003F07E5(hero, (int *)0) != 0);
	}
}
