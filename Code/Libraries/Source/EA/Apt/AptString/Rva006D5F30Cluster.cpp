// cl: /DNDEBUG /MD /EHsc
//
// EAStringC UTF-8 cursor workers on the 0x006D5F30 row, next to the rowed
// EAStringC::Mid bodies (EAStringCMid.cpp) they forward to. Flags match
// Rva006D5E70Cluster.cpp and EAStringCMid.cpp.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

void *__cdecl rva006d4d40(void *pBuffer, int count);
int __cdecl rva006d4ca0(const char *pBuffer);

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	StringDataC *m_pData;

public:
	static void FreeData(StringDataC *data);

	EAStringC()
	{
		extern StringDataC g_eaEmptyStringData;
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}
	EAStringC(const EAStringC &other);
	~EAStringC()
	{
		FreeData(m_pData);
	}
	EAStringC Mid(int start) const;
	EAStringC Mid(int start, int count) const;
	int Find(const char *s, int start);
	EAStringC rva006d5f30(int start, int count) const;
};

extern EAStringC::StringDataC g_eaEmptyStringData;

// ?rva006d5f30@EAStringC@@QBE?AV1@HH@Z @0x006D5F30 (174B). Codepoint substring:
// converts a codepoint start/count to byte offsets through rva006d4d40 and
// forwards to the byte-based Mid overloads, or the empty singleton. Donor is
// open-bfme-1 EAStringCUtf8Mid.cpp utf8Mid0089FBC0.
EAStringC EAStringC::rva006d5f30(int start, int count) const
{
	int effectiveStart = start;
	int adjustedCount = count;
	if (start < 0)
	{
		adjustedCount -= start;
		effectiveStart = 0;
	}
	if (adjustedCount <= 0)
		return EAStringC();
	const unsigned char *buffer = reinterpret_cast<const unsigned char *>(m_pData) + 8;
	const unsigned char *first = (const unsigned char *)rva006d4d40((void *)buffer, effectiveStart);
	if (first == 0)
		return EAStringC();
	const unsigned char *last = (const unsigned char *)rva006d4d40((void *)first, adjustedCount);
	if (last == 0)
		return Mid((int)(first - buffer));
	return Mid((int)(first - buffer), (int)(last - first));
}
