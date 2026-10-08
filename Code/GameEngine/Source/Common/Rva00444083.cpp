// cl: /GX-
//
// ?rva00444083@Rva00444083@@QAEXH@Z, retail 0x00444083, 113 bytes.
// __thiscall void method with 1 int arg firing EnableCreateGame and
// EnableJoinGame via rowed Rva00222A8BTarget::invoke when flag bits
// 1 and 2 are set and not already in +0x6bc. Owner at +0x274.
// Evidence: leaf callers 0x00444727 0x00444741; strings 0x83DFCC 0x83DFBC.

class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};

extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00444083
{
public:
	void rva00444083(int flags);
	void rva004440F4(int flags);
private:
	char m_pad00[0x274];
	void *m_owner274;
	char m_pad278[0x6bc - 0x278];
	int m_flags6bc;
};

void Rva00444083::rva00444083(int flags)
{
	if ((flags & 1) != 0)
	{
		if ((m_flags6bc & 1) == 0)
		{
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner274, "EnableCreateGame", 0, 0, 0, 0, 0, 0);
			m_flags6bc |= 1;
		}
	}
	if ((flags & 2) != 0)
	{
		if ((m_flags6bc & 2) == 0)
		{
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner274, "EnableJoinGame", 0, 0, 0, 0, 0, 0);
			m_flags6bc |= 2;
		}
	}
}

void Rva00444083::rva004440F4(int flags)
{
	if ((flags & 1) != 0)
	{
		if ((m_flags6bc & 1) != 0)
		{
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner274, "DisableCreateGame", 0, 0, 0, 0, 0, 0);
			m_flags6bc &= ~1;
		}
	}
	if ((flags & 2) != 0)
	{
		if ((m_flags6bc & 2) != 0)
		{
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(m_owner274, "DisableJoinGame", 0, 0, 0, 0, 0, 0);
			m_flags6bc &= ~2;
		}
	}
}
