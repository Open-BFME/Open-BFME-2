// ?rva0052A804@Rva0052A804@@QAEXHH@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /G7 /MD /Oy-
// ?rva0052A804@Rva0052A804@@QAEXHH@Z @ 0x0052A804 89B: Apt SetButtonState setter with redundant-call cache
// Evidence: rowed Apt Invoke 0x005252CD; strings SetButtonState plus empty fallback g_Rva0107301CEmptyString; manager TheRva00222A8BTarget; callers 0x0052AA0B 0x0052ABD7 in 0x0052A85D; stride 0x14 with cached value at +4.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
extern const char *g_00C68508[];
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *target, void *level, const char *prefix, const char *name, const int &a, const char *const &b);

struct Rva0052A804Entry
{
	int m_00;
	int m_04;
	char m_pad08[12];
};

class Rva0052A804
{
public:
	void rva0052A804(int index, int value);
private:
	char m_00[4];
	void *m_04;
	void *m_08;
	char m_pad0C[68];
	Rva0052A804Entry m_entries[1];
};

// ?rva0052A804@Rva0052A804@@QAEXHH@Z present-unmatched
void Rva0052A804::rva0052A804(int index, int value)
{
	int t = index + 4;
	t *= 0x14;
	Rva0052A804Entry *e = (Rva0052A804Entry *)((char *)this + t);
	if (e->m_04 == value)
		return;
	++index;
	const char *prefix = m_08 != 0 ? (const char *)m_08 + 8 : g_Rva0107301CEmptyString;
	Rva005252CDInvoke(TheRva00222A8BTarget, m_04, prefix, "SetButtonState", index, g_00C68508[value]);
	e->m_04 = value;
}
