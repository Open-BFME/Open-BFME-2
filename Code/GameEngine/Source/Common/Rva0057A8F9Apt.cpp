// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0057A8F9@Rva0057A8F9@@QAEXXZ @0x0057A8F9 52B
// CloseList Apt call: prefix from +0x10 name+8 or empty string then AptCall with CloseList set +0x14 to 3. Evidence: sibling Rva0057A92DApt OpenList pattern; rowed AptCall 0x00524EF4; strings CloseList; globals TheRva00222A8BTarget g_Rva0107301CEmptyString; caller 0x0057AC14.
class Rva00222A8BTarget
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);

struct Rva0057A8F9Name
{
	char m_pad[8];
	char m_name[1];
};

class Rva0057A8F9
{
public:
	void rva0057A8F9();
private:
	char m_pad0[12];
	void *m_level0C;
	Rva0057A8F9Name *m_name10;
	int m_14;
};

void Rva0057A8F9::rva0057A8F9()
{
	const char *prefix;
	if (m_name10)
		prefix = m_name10->m_name;
	else
		prefix = "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level0C, prefix, "CloseList");
	m_14 = 3;
}
