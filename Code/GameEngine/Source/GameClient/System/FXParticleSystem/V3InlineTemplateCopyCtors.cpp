// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// V3-inline module template copy constructors (retail 0x003AE13C cluster).
// Each copy constructs the V3 inline two-base at 0x003ADDEC, copies its
// flag byte through a null-preserving source at +0x0C, and installs its own
// two vftables. All vftable dwords are DIR32 sites the gate takes from the
// target; the call resolves through the ledger.

class Rva005EA430
{
public:
	Rva005EA430(const Rva005EA430 &other);
};

extern "C" char Rva003AE13C_v0;
extern "C" char Rva003AE13C_v8;

class Rva003AE13C
{
public:
	__declspec(noinline) Rva003AE13C(const Rva003AE13C &other);

private:
	void *m_v0; // +0x00
	char m_pad04[4]; // +0x04, owned by the base copy
	void *m_v8; // +0x08
	unsigned char m_flag0c; // +0x0C
};

// ??0Rva003AE13C@@QAE@ABV0@@Z
Rva003AE13C::Rva003AE13C(const Rva003AE13C &that)
{
	const void *src = &that;
	((Rva005EA430 *)this)->Rva005EA430::Rva005EA430(*(const Rva005EA430 *)src);
	const void *flag_src = src ? (const char *)src + 0x0C : 0;
	unsigned char flag = *(const unsigned char *)flag_src;
	*(unsigned char *)((char *)this + 0x0C) = flag;
	*(void **)this = &Rva003AE13C_v0;
	*(void **)((char *)this + 8) = &Rva003AE13C_v8;
}
