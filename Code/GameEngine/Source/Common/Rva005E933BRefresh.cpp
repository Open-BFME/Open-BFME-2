// ?rva005E933B@Rva005E933BOwner@@QAEXXZ
// cl: /O1 /Oy /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Native5E933B..5E936A complete47B; input record at+20 and template at+24.
// The 87B LivingWorldRegion provider independently grounds the CreateAHeroData
// and template argument views. Direct short-circuit argument to owned5E1160
// keeps native AL normalization and removes the named-bool stack home.
// Existing address-derived receiver name is retained; original UI name unknown.
// When the first hero record has no flag
// at +0x20, ask its region at +0x1C for the template check and pass the verdict to 0x005E1160.
class LivingWorldRegion;
struct Rva003F1BD3TemplateView;

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

class Rva005E1160Flag { public: void rva005E1160(bool); };

class Rva005E933BOwner
{
public:
	void rva005E933B();

private:
	char m_pad00[0x08];
	Rva005E1160Flag *m_08;
	char m_pad0C[0x20 - 0x0C];
	CreateAHeroData *m_20;
	const Rva003F1BD3TemplateView *m_24;
};

// ?rva005E933B@Rva005E933BOwner@@QAEXXZ @0x005E933B
void Rva005E933BOwner::rva005E933B()
{
 CreateAHeroData *hero=m_20;
 ((Rva005E1160Flag*)((char*)this+8))->rva005E1160(hero->m_20==0 && hero->m_1C->rva003F1B7C(hero,m_24,0));
}
