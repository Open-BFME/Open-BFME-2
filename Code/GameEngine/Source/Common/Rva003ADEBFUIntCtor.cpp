// cl: /DNDEBUG /MD /EHsc
// ??0Rva003ADEBF@@QAE@I@Z, retail 0x005640EC, 35 bytes.
// UInt-taking derived ctor: forwards the dword to the rowed base
// ??0Rva00563FE1@@QAE@I@Z at 0x00563FE1, then sets the +0xC flag byte,
// primary vftable +0 0x00C1D2C0 and secondary +8 0x00C1C780 -- the same
// vtable pair the rowed copy ctor 0x003ADEBF installs. Callers at
// 0x00564152 and 0x005646D1; unblocks 0x0056413D and 0x005646BC.

class Rva00563FE1
{
public:
	Rva00563FE1(unsigned int a);
};

extern "C" char Rva003ADEBF_v0;
extern "C" char Rva003ADEBF_v8;

class Rva003ADEBF
{
public:
	__declspec(noinline) Rva003ADEBF(unsigned int a);

private:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
	bool m_flagC;
};

Rva003ADEBF::Rva003ADEBF(unsigned int a)
{
	((Rva00563FE1 *)this)->Rva00563FE1::Rva00563FE1(a);
	m_flagC = true;
	m_v0 = &Rva003ADEBF_v0;
	m_v8 = &Rva003ADEBF_v8;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_Rva003ADEBF_v0=??_7Rva005EA430@@6BV3Vt01111D90@@@")
