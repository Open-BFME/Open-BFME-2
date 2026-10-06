// cl: /DNDEBUG /MD /EHsc
// ??0Rva003AE03D@@QAE@ABV0@@Z, retail 0x003AE03D, 64 bytes.
// Derived V3-inline copy: calls rowed base ??0Rva003ADEBF@@QAE@ABV0@@Z at
// 0x003ADEBF then rowed ??0Rva003AE07D@@QAE@ABV0@@Z at 0x003AE07D with a
// null-preserving source at +0x0C, then installs three vftables (+0 0x00C1B5E0,
// +8 0x00C1C780, +0x0C 0x00C1B5D0). Caller is 0x003AE01E. Same 64B shape as
// rowed 0x003AE1CD. Vtable dwords are DIR32 sites the gate takes from target.

class Rva003ADEBF
{
public:
	Rva003ADEBF(const Rva003ADEBF &other);
};

class Rva003AE07D
{
public:
	Rva003AE07D(const Rva003AE07D &other);
};

// Rva003AE03D_v0: matched references place it at VA 0xc1b5e0 (retail .rdata value 112).
extern "C" char Rva003AE03D_v0 = 112;
extern "C" char Rva003AE03D_v8;
// Rva003AE03D_v0C: matched references place it at VA 0xc1b5d0 (retail .rdata value 72).
extern "C" char Rva003AE03D_v0C = 72;

class Rva003AE03D
{
public:
	__declspec(noinline) Rva003AE03D(const Rva003AE03D &other);

private:
	void *m_v0;
	char m_pad04[4];
	void *m_v8;
	void *m_v0C;
};

Rva003AE03D::Rva003AE03D(const Rva003AE03D &that)
{
	const void *src = &that;
	((Rva003ADEBF *)this)->Rva003ADEBF::Rva003ADEBF(*(const Rva003ADEBF *)src);
	const void *poly_src = src ? (const char *)src + 0x0C : 0;
	((Rva003AE07D *)((char *)this + 0x0C))->Rva003AE07D::Rva003AE07D(*(const Rva003AE07D *)poly_src);
	*(void **)((char *)this + 0x0C) = &Rva003AE03D_v0C;
	*(void **)this = &Rva003AE03D_v0;
	*(void **)((char *)this + 8) = &Rva003AE03D_v8;
}
// _Rva003AE03D_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AE03D_v8=?vftable_0112B89C@@3HA")
