// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005F92D5@Rva005F92D5@@QAEX_N@Z @0x005F92D5 91B twin of 0x005F927A SetButtonState Retreat _up/_disabled.
// Evidence: rowed AptCall 0x005F8EDA; strings _up _disabled SetButtonState Retreat; empty fallback g_Rva0107301CEmptyString; manager TheRva00222A8BTarget; flag at +0x62 vs twin +0x61.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];
int __cdecl Rva005F8EDAAptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0, void **ppA1);

struct Rva005F92D5Holder
{
	char m_pad[8];
	char m_name[1];
};

class Rva005F92D5
{
public:
	void rva005F92D5(bool flag);
private:
	char m_pad00[4];
	void *m_level04;
	Rva005F92D5Holder *m_team08;
	char m_pad0C[0x62 - 0x0C];
	bool m_flag62;
};

void Rva005F92D5::rva005F92D5(bool flag)
{
	if (m_flag62 == flag)
		return;
	const char *state = flag ? "_up" : "_disabled";
	const char *team = m_team08 ? (const char *)m_team08 + 8 : g_Rva0107301CEmptyString;
	Rva005F8EDAAptCall(TheRva00222A8BTarget, m_level04, team, "SetButtonState", "Retreat", (void **)&state);
	m_flag62 = flag;
}
