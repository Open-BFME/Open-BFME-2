// cl: -O1 -GR- -EHsc-
// ?Run@Rva005B2725@@QAEXH@Z @0x005B2725 104B: m_4 414/418 gate plus hero prep.
// If m_4 +0x414 equals +0x418, run rowed 0x5B5C02 on +0x418 and return; else
// fetch via TheHeroManager List (pinned 0x21F797), build 7-arg init via
// pinned 0x219251 (-1, 0xFF707070, -1, 0xE0C898, 0,0,0), consume m_4+0x27C
// via rowed 0x409359 Use, then run rowed 0x423A68. Fresh m_4 reloads; list
// in ebx, built in edi per retail.
struct Rva005B5C02Box
{
	void Run();
};

struct Rva005B5C02List
{
};

struct Rva005B5C02Mgr
{
	Rva005B5C02List *List();
};

extern Rva005B5C02Mgr *TheHeroManager;
struct UnicodeString;
extern UnicodeString TheEmptyString;

struct Rva005B5C02Entry
{
	void Use(void *s);
};

struct Rva00423A68
{
	void rva00423A68(const class ModuleData *p);
};

class ModuleData;

struct Rva005B2725
{
	char pad[4];
	void *m_4;

	void *rva00219251(int a1, int a2, int a3, void *a4, int a5, int a6, int a7);
	void Run(int unused);
};

void Rva005B2725::Run(int unused)
{
	(void)unused;
	void *box = *(void **)((char *)m_4 + 0x418);
	if (*(int *)((char *)m_4 + 0x414) == (int)box) {
		((Rva005B5C02Box *)box)->Run();
		return;
	}
	Rva005B5C02List *list = TheHeroManager->List();
	void *built = ((Rva005B2725 *)TheHeroManager)->rva00219251(0, 0, 0, (void *)&TheEmptyString, -1, (int)0xFF707070, -1);
	((Rva005B5C02Entry *)built)->Use((char *)m_4 + 0x27C);
	((Rva00423A68 *)list)->rva00423A68((const class ModuleData *)built);
}
