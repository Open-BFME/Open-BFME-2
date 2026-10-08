// cl: /MD
// ?HideButtons@Impl@AptInGameSideCommandBar@@QAEXH@Z retail 0x00528582 101B
// Evidence: loop dec count at +0xD8 elem stride 12 like sibling 0x00528309; Fire 0x00525338 via TheRva00222A8BTarget plus m_04 plus m_18 plus SetButtonState plus count plus _hide; clear +4 via 0x002BED91 plus or +8 -1; callers 0x005285EF 0x00528738
struct Rva002BED91
{
	void *m_ptr;
	void clear();
};

int __cdecl Rva00525338Fire(void *a1, void *a2, const char *a3, const char *a4, int *a5, void *a6);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva00528582Elem
{
	int m_a;
	Rva002BED91 m_b;
	int m_c;
};

class AptInGameSideCommandBar
{
public:
	class Impl;
};

class AptInGameSideCommandBar::Impl
{
public:
	void HideButtons(int v);
private:
	char m_pad00[4];
	void *m_04;
	char m_pad08[0x10];
	void *m_18;
	char m_pad1C[8];
	Rva00528582Elem m_elems[15];
	int m_count;
};

void AptInGameSideCommandBar::Impl::HideButtons(int v)
{
	while (m_count > v)
	{
		--m_count;
		_ReadWriteBarrier();
		const char *s;
		if (m_18)
			s = (const char *)m_18 + 8;
		else
			s = "";
		Rva00525338Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_04, s, "SetButtonState", &m_count, (void *)"_hide");
		Rva00528582Elem &e = m_elems[m_count];
		e.m_b.clear();
		e.m_c = -1;
	}
}
