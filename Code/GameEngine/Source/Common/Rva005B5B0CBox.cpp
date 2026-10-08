// cl: -GR- -EHsc-
// ?Run@Rva005B5B0CBox@@QAEXH@Z @0x005B5B0C 45B: manager sub-object handoff.
// Hands m_4 + 0x27C to the pinned 1-arg manager method on the 0xDFE344
// global, sets +0x16 and the +0x54 byte of the 0xE01E48 global, then runs
// the pinned arg-free callee. The int parameter is unused. Targets from
// retail REL32/DIR32; globals carried as named externs (no pins needed).
struct Rva005B5B0CMgr
{
	void UseSub(void *s);
};

extern class CreateAHeroManager *TheCreateAHeroManager;
extern class Shell *TheShell;
void Rva00513866Free();

struct Rva005B5B0CBox
{
	char pad[4];
	void *m_4;
	char pad2[0x16 - 8];
	unsigned char m_16;

	void Run(int unused);
};

void Rva005B5B0CBox::Run(int unused)
{
	(*(Rva005B5B0CMgr **)&TheCreateAHeroManager)->UseSub((char *)m_4 + 0x27c);
	m_16 = 1;
	*(unsigned char *)((char *)(*(void **)&TheShell) + 0x54) = 1;
	Rva00513866Free();
}
