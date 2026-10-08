// ?rva005E933B@Rva005E933BOwner@@QAEXXZ
// partial score=0.6 date=2026-10-08
// cl: /MD /DNDEBUG /EHsc
// ?rva005E933B@Rva005E933BOwner@@QAEXXZ @0x005E933B 47B: when the first hero record has no flag
// at +0x20, ask its region at +0x1C for the template check and pass the verdict to 0x005E1160.
class LivingWorldRegion;
class Rva003F1BD3TemplateView;

class CreateAHeroData
{
public:
	char m_pad00[0x1C];
	LivingWorldRegion *m_1C;
	int m_20;
};

class LivingWorldRegion
{
public:
	bool rva003F1B7C(CreateAHeroData *hero, const Rva003F1BD3TemplateView *view, int *out);
};

class Rva005F8A7ESub;
void __fastcall rva005E1160(Rva005F8A7ESub *sub, bool verdict);

class Rva005E933BOwner
{
public:
	void rva005E933B();

private:
	char m_pad00[0x08];
	Rva005F8A7ESub *m_08;
	char m_pad0C[0x20 - 0x0C];
	CreateAHeroData *m_20;
	const Rva003F1BD3TemplateView *m_24;
};

// ?rva005E933B@Rva005E933BOwner@@QAEXXZ @0x005E933B
void Rva005E933BOwner::rva005E933B()
{
	bool verdict = false;
	if (m_20->m_20 == 0)
	{
		verdict = m_20->m_1C->rva003F1B7C(m_20, m_24, 0);
	}
	rva005E1160((Rva005F8A7ESub *)((char *)this + 8), verdict);
}
