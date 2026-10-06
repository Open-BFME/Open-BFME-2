// cl: /DNDEBUG /MD /EHsc
// ??0Rva003ADFDB@@QAE@I@Z, retail 0x0055F821, 31 bytes.
// UInt-taking derived ctor: forwards the dword to the rowed base
// ??0Rva00563FE1@@QAE@I@Z at 0x00563FE1, then installs primary vftable
// +0 0x00C1D294 and secondary +8 0x00C1C780 (s_slot3E4first) -- the same
// vtable pair the rowed copy ctor 0x003ADFDB installs. Same 31B shape as
// the copy pair in Rva003ADFDBCopyCtor.cpp minus the flag byte that the
// 35B sibling 0x005640EC (Rva003ADEBF uint ctor) carries at +0xC.
// Callers at 0x0055F858 and 0x0056237D.

class Rva00563FE1
{
public:
	Rva00563FE1(unsigned int a);
};

extern const void *const g_00C1D294[];
extern "C" char s_slot3E4first;

class Rva003ADFDB
{
public:
	__declspec(noinline) Rva003ADFDB(unsigned int a);

private:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
};

Rva003ADFDB::Rva003ADFDB(unsigned int a)
{
	((Rva00563FE1 *)this)->Rva00563FE1::Rva00563FE1(a);
	*(const void **)this = g_00C1D294;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
}
