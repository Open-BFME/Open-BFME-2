// ??HEAStringC@@QBE?AV0@PBD@Z
// partial score=0.995641 date=2026-10-10
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME 2 target 0x006D4F70..0x006D509D, 301 bytes; complete RET8.
// The existing EAStringCConcat.cpp 300-byte EAStringC overload is the
// source guide. WB17747B0 and native direct calls identify this overload
// as C-string concatenation by value, using Assign6D4BF0 in the empty case.
// Data is the target eight-byte StringDataC header. The native result copy,
// cleanup and receiver hash reset are preserved. Only source/destination
// header load scheduling at the first memcpy remains different.
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

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

	static void FreeData(StringDataC *data);

	StringDataC *m_pData;

	EAStringC(const EAStringC &other);
	EAStringC(unsigned int nSize);
	EAStringC(const char *s) : m_pData(0) { Assign(s); }
	void Assign(const char *);
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	EAStringC operator+(const char *other) const;
};

EAStringC EAStringC::operator+(const char *other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	char *text=(char *)(result.m_pData+1);
	memcpy(text,(char *)(m_pData+1),size);
	memcpy(text + size, other, otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}
