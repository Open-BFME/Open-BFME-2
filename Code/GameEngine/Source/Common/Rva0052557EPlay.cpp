// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /Oy-
// ?OnHeroAttacked@Impl@InGameHeroSelectInterface@@QAEXPAX@Z, retail 0x0052557E 100B chain via 0x0052519D Fire.
// Searches 16-entry table at +0x48 for p->+0x74 matching entry+8 skipping sentinel [[+0x10]+0x10].
// Evidence: callee rowed Rva0052519DFire 0x0052519D; callers 0x005258B2 jmp thunk plus 0x002D3756 guard; data PlayButtonAttackedEffect plus g_Rva0107301CEmptyString plus TheRva00222A8BTarget.
#include "ascii_string.h"

int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class InGameHeroSelectInterface
{
public:
	class Impl;
};

class InGameHeroSelectInterface::Impl
{
public:
	void *m_00;
	void *m_04;
	void *m_08;
	AsciiString m_name;
	void *m_10;
	unsigned char m_pad[0x48 - 0x14];
	struct Slot
	{
		void *obj;
		unsigned char pad[0x14];
	} m_slots[16];
	void OnHeroAttacked(void *p);
};

void InGameHeroSelectInterface::Impl::OnHeroAttacked(void *p)
{
	void *sentinel = *(void **)((char *)m_10 + 0x10);
	for (int i = 0; i < 16; ++i)
	{
		void *cur = m_slots[i].obj;
		if (cur == sentinel)
			continue;
		int want = *(int *)((char *)p + 0x74);
		int have = *(int *)((char *)cur + 8);
		if (want != have)
			continue;
		void *raw = *(void **)&m_name;
		int idx = i + 1;
		*(int *)&p = idx;
		const char *s = raw ? (const char *)raw + 8 : "";
		Rva0052519DFire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_08, s, "PlayButtonAttackedEffect", (int *)&p);
		return;
	}
}
