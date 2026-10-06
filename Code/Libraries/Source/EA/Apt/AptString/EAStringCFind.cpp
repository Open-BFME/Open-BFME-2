// cl: /DNDEBUG /MD
// ?Find@EAStringC@@QAEHDH@Z, retail 0x006D38E0 (62B). Ported from Open-BFME-1
// Code/Libraries/Source/EA/Apt/AptString/EAStringCFind.cpp (BFME1 0x0089E230).
// Trimmed to the placed char-find body; the string-find overload is
// declared-only here. Callee strchr resolves via the existing ledger pin.

extern "C" char *__cdecl strchr(const char *, int);
extern "C" char *__cdecl strstr(const char *, const char *);

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC
{
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	StringDataC *m_pData;

	char *GetInternalBuffer() const
	{
		return reinterpret_cast<char *>(m_pData) + sizeof(StringDataC);
	}

public:
	int Find(const char *s, int start);
	int Find(char c, int start);
};

// ?Find@EAStringC@@QAEHDH@Z
int EAStringC::Find(char c, int start)
{
	if (start >= (int)m_pData->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strchr(GetInternalBuffer() + start, c);
	if (found)
		return found - GetInternalBuffer();
	return -1;
}

// ?Find@EAStringC@@QAEHPBDH@Z, retail 0x006D3870 (102B). EAStringC
// string-find overload ported from BFME1 EAStringCFind donor plus BFME2
// null-text assert (EAString.cpp 0x286 via shared Apt triple). Uses rowed
// strstr thunk 0x00629850; callers at 0x006D60A2/0x006D7965; neighbours
// cmp 0x006D3860 and char-find 0x006D38E0 share /O2 /DNDEBUG /MD.
int EAStringC::Find(const char *s, int start)
{
	if (!(s != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x286);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	if (start >= (int)m_pData->m_uSize)
		return -1;
	if (start < 0)
		start = 0;
	char *found = strstr(GetInternalBuffer() + start, s);
	if (found)
		return found - GetInternalBuffer();
	return -1;
}
