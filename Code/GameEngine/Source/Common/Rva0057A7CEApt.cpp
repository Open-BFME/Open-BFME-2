// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva0057A7CE@Rva0057A7CE@@QAEXXZ @0x0057A7CE 55B
// ?rva0057A805@Rva0057A7CE@@QAEXXZ @0x0057A805 55B
// FadeOut Apt call with level at +0xC and prefix from +0x10 (+8 name) then flag 0 at +0x24 with early-out when 0. Evidence: vslot slot 2 of 0x0086F118 class Rva0057AD6E; rowed AptCall 0x00524EF4; strings FadeOut; globals TheRva00222A8BTarget g_Rva0107301CEmptyString; sibling Rva0057A92DApt pattern.
class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);

struct Rva0057A7CEName
{
	char m_pad[8];
	char m_name[1];
};

class Rva0057A7CE
{
public:
	void rva0057A7CE();
	void rva0057A805();
private:
	char m_pad0[12];
	void *m_level0C;
	Rva0057A7CEName *m_name10;
	char m_pad14[16];
	bool m_flag24;
};

void Rva0057A7CE::rva0057A7CE()
{
	if (m_flag24 == 0)
		return;
	const char *prefix;
	if (m_name10)
		prefix = m_name10->m_name;
	else
		prefix = g_Rva0107301CEmptyString;
	Rva00524EF4AptCall(TheRva00222A8BTarget, m_level0C, prefix, "FadeOut");
	m_flag24 = 0;
}

void Rva0057A7CE::rva0057A805()
{
	if (m_flag24 != 0)
		return;
	const char *prefix;
	if (m_name10)
		prefix = m_name10->m_name;
	else
		prefix = g_Rva0107301CEmptyString;
	Rva00524EF4AptCall(TheRva00222A8BTarget, m_level0C, prefix, "FadeIn");
	m_flag24 = 1;
}
