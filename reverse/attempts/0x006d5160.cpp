// ?Rva006D5160Plus@@YA?AVEAStringC@@PBDABV1@@Z
// partial score=0.985 date=2026-10-04
// cl: /O2 /DNDEBUG /MD /EHsc
// ?Rva006D5160Plus@@YA?AVEAStringC@@PBDABV1@@Z, retail 0x006D5160 (306B).
// Free PBD-plus-string concat returning by value: empty string builds via PBD
// ctor, empty text copies the string, otherwise a reserve-ctor temp gathers
// text then string via intrinsic memcpy plus terminator, then SetSize plus
// hash-zero plus copy to the hidden result. After Rva006D50A0Append;
// same /O2 /DNDEBUG /MD. Honest address name; PBD-first free overload.
// The SEH frame (push -1 / push 0x00BA87B1 / fs:0 chain) comes from /EHsc
// unwinding the EAStringC temporaries, the same idiom the Rva006C1F60 bodies
// prove for a local with a destructor.
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
extern "C" unsigned int __cdecl strlen(const char *str);

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
	// Retail inlines this ctor at the call site (result->m_pData = 0, then
	// Assign), so it is defined here rather than roved from EAStringCRefCount.cpp.
	EAStringC(const char *text) : m_pData(0) { Assign(text); }
	EAStringC(unsigned int nSize);
	// Scalar release: FreeData only. Retail keeps this inline, so the temp's
	// tail calls 0x006D2EB0 directly rather than the out-of-line dtor wrapper.
	~EAStringC() { FreeData(m_pData); }
	void Assign(const char *text);
	void SetSize(int size);
};

// ?Rva006D5160Plus@@YA?AVEAStringC@@PBDABV1@@Z present-unmatched
EAStringC Rva006D5160Plus(const char *text, const EAStringC &str)
{
	unsigned int oldSize = str.m_pData->m_uSize;
	if (oldSize == 0) {
		return EAStringC(text);
	}
	unsigned int len = strlen(text);
	if (len == 0) {
		return EAStringC(str);
	}
	EAStringC tmp(oldSize + len);
	char *dst = (char *)tmp.m_pData + 8;
	memcpy(dst, text, len);
	memcpy(dst + len, (char *)str.m_pData + 8, oldSize);
	dst[oldSize + len] = 0;
	tmp.SetSize((int)(oldSize + len));
	tmp.m_pData->m_uHash = 0;
	return tmp;
}
