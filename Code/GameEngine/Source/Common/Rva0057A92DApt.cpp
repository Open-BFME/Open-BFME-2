// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva0057A92D@Rva0057A92D@@QAEXXZ @0x0057A92D 52B
// OpenList Apt call: prefix from +0x10 name+8 or empty string, then AptCall with OpenList, set +0x14 to 1. Evidence: sibling Rva0057A961Apt pattern, callee row Rva00524EF4AptCall, strings OpenList, globals TheRva00222A8BTarget g_Rva0107301CEmptyString, callers 0x0057AC1F 0x0057B4D5.
class Rva00222A8BTarget
{
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function);

struct Rva0057A92DName
{
	char m_pad[8];
	char m_name[1];
};

class Rva0057A92D
{
public:
	void rva0057A92D();
private:
	char m_pad0[12];
	void *m_level;
	Rva0057A92DName *m_namePtr;
	int m_14;
};

void Rva0057A92D::rva0057A92D()
{
	const char *prefix;
	if (m_namePtr)
		prefix = m_namePtr->m_name;
	else
		prefix = "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "OpenList");
	m_14 = 1;
}
