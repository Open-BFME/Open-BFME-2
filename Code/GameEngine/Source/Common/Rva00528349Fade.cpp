// cl: /O1 /G7 /MD
// ?rva00528349@Rva00528349@@QAEXXZ @0x00528349 64B: FadeIn Apt setter with state at +0x14 plus prefix at +0x18 plus level at +0x4.
// Evidence: rowed AptCall 0x00524EF4 plus strings FadeIn plus empty plus TheRva plus caller 0x00528868; neighbours Rva00528309Clear.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

struct Rva00528349Inner
{
	char m_pad8[8];
	char m_name[1];
};

class __declspec(novtable) Rva00528349
{
public:
	virtual ~Rva00528349();
	void rva00528349();
private:
	int m_04;
	char m_pad08[0x14 - 0x08];
	int m_14;
	Rva00528349Inner *m_18;
};

void Rva00528349::rva00528349()
{
	int state = m_14;
	if (state == 0)
		return;
	if (state == 2)
		return;
	const char *prefix = m_18 ? m_18->m_name : g_Rva0107301CEmptyString;
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_04, prefix, "FadeIn");
	m_14 = 2;
}
