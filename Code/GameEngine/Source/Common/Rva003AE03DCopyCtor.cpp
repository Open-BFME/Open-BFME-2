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

// Rva003AE03D_v0: retail table 0x00C1B5E0 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003ADFB2@@UAEPAXI@Z")();
void __identifier("?update@Rva003A59C3@@UAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?DoXfer@Rva003A57A9@@UAEXAAVXfer@@@Z")();
extern const void *const Rva003AE03D_v0[4] = {
	(const void *)&__identifier("??_GRva003ADFB2@@UAEPAXI@Z"), //  0 0x003AE270
	(const void *)&__identifier("?update@Rva003A59C3@@UAEXXZ"), //  1 0x003A5A58
	(const void *)&_purecall, //  2 0x0003B810
	(const void *)&__identifier("?DoXfer@Rva003A57A9@@UAEXAAVXfer@@@Z")  //  3 0x003A57A9
};
}
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
// Rva003AE03D_v0C: retail table 0x00C1B5D0 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva003ADFB2@@WM@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003A5A42Get@@YAHXZ")();
void __identifier("?DoXfer@Rva003A57A9@@WM@AEXAAVXfer@@@Z")();
extern const void *const Rva003AE03D_v0C[4] = {
	(const void *)&__identifier("??_ERva003ADFB2@@WM@AEPAXI@Z"), //  0 0x003A5A48
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003A5A42Get@@YAHXZ"), //  2 0x003A5A42
	(const void *)&__identifier("?DoXfer@Rva003A57A9@@WM@AEXAAVXfer@@@Z")  //  3 0x003A5A50
};
}

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
	*(void **)((char *)this + 0x0C) = (void *)Rva003AE03D_v0C;
	*(void **)this = (void *)Rva003AE03D_v0;
	*(void **)((char *)this + 8) = &__identifier("??_7Rva003F498ACallback@@6B@");
}
// _Rva003AE03D_v8: the global at VA 0xc1c780 is ??_7Rva003F498ACallback@@6B@.
