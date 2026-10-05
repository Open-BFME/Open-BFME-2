// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva003ADFDB@@QAE@ABV0@@Z, retail 0x003ADFDB, 31 bytes.
// Derived V3-inline copy: calls rowed base ??0Rva005EA430@@QAE@ABV0@@Z at
// 0x003ADDEC then installs its own two vftables (+0 0x00C1D294, +8 0x00C1C780).
// Same 31B shape as sibling 0x003ADEBF (different +0 vptr). Callers include
// 0x003AE1D7. Vtable dwords are DIR32 sites the gate takes from the target.

class Rva005EA430
{
public:
	Rva005EA430(const Rva005EA430 &other);
};

extern const void *const g_00C1D294[];
extern "C" char Rva003ADFDB_v8;

class Rva003ADFDB
{
public:
	__declspec(noinline) Rva003ADFDB(const Rva003ADFDB &other);

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
};

Rva003ADFDB::Rva003ADFDB(const Rva003ADFDB &that)
{
	const void *src = &that;
	((Rva005EA430 *)this)->Rva005EA430::Rva005EA430(*(const Rva005EA430 *)src);
	*(const void **)this = g_00C1D294;
	*(void **)((char *)this + 8) = &Rva003ADFDB_v8;
}

// ??0Rva003ADEBF@@QAE@ABV0@@Z, retail 0x003ADEBF, 31 bytes. Same 31B derived
// V3-inline copy shape via rowed base 0x003ADDEC (+0 0x00C1D2C0, +8 0x00C1C780).

extern "C" char Rva003ADEBF_v0;
extern "C" char Rva003ADEBF_v8;

class Rva003ADEBF
{
public:
	__declspec(noinline) Rva003ADEBF(const Rva003ADEBF &other);

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
};

Rva003ADEBF::Rva003ADEBF(const Rva003ADEBF &that)
{
	const void *src = &that;
	((Rva005EA430 *)this)->Rva005EA430::Rva005EA430(*(const Rva005EA430 *)src);
	*(void **)this = &Rva003ADEBF_v0;
	*(void **)((char *)this + 8) = &Rva003ADEBF_v8;
}
// _Rva003ADFDB_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003ADFDB_v8=?vftable_0112B89C@@3HA")
// _Rva003ADEBF_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003ADEBF_v8=?vftable_0112B89C@@3HA")

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_Rva003ADEBF_v0=??_7Rva005EA430@@6BV3Vt01111D90@@@")
