// ?Rva006D4F70Plus@EAStringC@@QBE?AV1@PBD@Z
// partial score=0.9956407933 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)
extern "C" unsigned int __cdecl strlen(const char*);
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
 EAStringC(const char* text) {m_pData=0; Assign(text);}
 void Assign(const char* text);
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	EAStringC Rva006D4F70Plus(const char* other) const;
};

EAStringC EAStringC::Rva006D4F70Plus(const char* other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return EAStringC(other);
	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	char *text = (char *)result.m_pData + sizeof(StringDataC);
	memcpy(text, (char *)m_pData + sizeof(StringDataC), size);
	memcpy(text + size, other, otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}
