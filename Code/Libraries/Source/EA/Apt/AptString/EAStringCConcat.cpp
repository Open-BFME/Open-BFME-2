// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??HEAStringC@@QBE?AV0@ABV0@@Z
// Retail 0x006D46C0..0x006D47EC (300 bytes).
// EAStringC concatenation returning a new string: an empty receiver returns
// a copy of the other string and an empty other string returns a copy of the
// receiver; otherwise a string reserved for the summed size (rowed
// EAStringC(unsigned) 0x006D45F0) receives both texts with intrinsic memcpy
// and a terminator and its logical size is set (rowed SetSize 0x006D3BC0)
// before it is copied out (rowed copy ctor 0x006D2FC0) and released (rowed
// FreeData 0x006D2EB0 through the inline destructor as in EAStringCMid.cpp).
// Target fact kept as found: the cached hash word (+6) that is cleared is the
// receiver's (the saved this pointer is reloaded for it) not the result's.
// The operator name is a semantic pick from the body (receiver-left
// concatenation by value; ret 8 = hidden result + other); flags follow the
// EAStringCMid.cpp sibling.
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
#pragma intrinsic(memcpy)

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
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void SetSize(int size);
	EAStringC operator+(const EAStringC &other) const;
};

EAStringC EAStringC::operator+(const EAStringC &other) const
{
	unsigned int size = m_pData->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = other.m_pData->m_uSize;
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	const char *source = (char *)m_pData + sizeof(StringDataC);
	char *text = (char *)result.m_pData + sizeof(StringDataC);
	memcpy(text, source, size);
	memcpy(text + size, (char *)other.m_pData + sizeof(StringDataC), otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	m_pData->m_uHash = 0;
	return result;
}
