// cl: /DNDEBUG /MD /EHsc
// ??0Rva003AE1CD@@QAE@ABV0@@Z, retail 0x003AE1CD, 64 bytes.
// Derived V3-inline copy: calls rowed base ??0Rva003ADFDB@@QAE@ABV0@@Z at
// 0x003ADFDB then rowed ??0Rva005EA0D0@@QAE@ABV0@@Z at 0x003AE20D with a
// null-preserving source at +0x0C, then installs three vftables (+0 0x00C1D31C,
// +8 0x00C1C780, +0x0C 0x00C1D348). Caller is 0x003AE1AE. Vtable dwords are
// DIR32 sites the gate takes from the target.

class Rva003ADFDB
{
public:
	Rva003ADFDB(const Rva003ADFDB &other);
};

class Rva005EA0D0
{
public:
	Rva005EA0D0(const Rva005EA0D0 &other);
};

// Rva003AE1CD_v0: matched references place it at VA 0xc1d31c (retail .rdata value 112).
extern "C" char Rva003AE1CD_v0 = 112;
extern "C" char Rva003AE1CD_v8;
// Rva003AE1CD_v0C: matched references place it at VA 0xc1d348 (retail .rdata value 72).
extern "C" char Rva003AE1CD_v0C = 72;

class Rva003AE1CD
{
public:
	__declspec(noinline) Rva003AE1CD(const Rva003AE1CD &other);

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
};

Rva003AE1CD::Rva003AE1CD(const Rva003AE1CD &that)
{
	const void *src = &that;
	((Rva003ADFDB *)this)->Rva003ADFDB::Rva003ADFDB(*(const Rva003ADFDB *)src);
	const void *poly_src = src ? (const char *)src + 0x0C : 0;
	((Rva005EA0D0 *)((char *)this + 0x0C))->Rva005EA0D0::Rva005EA0D0(*(const Rva005EA0D0 *)poly_src);
	*(void **)((char *)this + 0x0C) = &Rva003AE1CD_v0C;
	*(void **)this = &Rva003AE1CD_v0;
	*(void **)((char *)this + 8) = &Rva003AE1CD_v8;
}
// _Rva003AE1CD_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AE1CD_v8=?vftable_0112B89C@@3HA")
