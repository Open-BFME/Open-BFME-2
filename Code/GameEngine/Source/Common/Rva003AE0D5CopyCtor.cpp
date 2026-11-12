// cl: /DNDEBUG /MD /GX- /Ob2
// ??0Rva003AE0D5@@QAE@ABV0@@Z @0x003AE0D5 70B
// Copy ctor: base Rva003AE13C at +0 via rowed copy 0x003AE13C, sub
// Rva003AE11B at +0x10 via rowed copy 0x003AE11B with null-guarded source,
// then own/second/sub vptrs plus byte at +0x1C. Evidence: retail two copy
// calls plus neg/sbb/and for +0x10 plus three vptr stores plus byte copy,
// unlocks 0x003AE0AF. Precedent: V3InlineTemplateCopyCtors Rva003AE13C
// plus ParticleModuleTemplateCopyCtors guarded sub-source.
class Rva003AE13C {
public: __declspec(noinline) Rva003AE13C(const Rva003AE13C &that);
private: char m_pad[0x10 - 4];
};

class Rva003AE11B {
public: Rva003AE11B(const Rva003AE11B &that);
};

// Rva003AE0D5_v0: retail table 0x00C1D2E0 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003AE358@@UAEPAXI@Z")();
void __identifier("?rva00563F34@FXGate@@QAEXXZ")();
int __cdecl _purecall(void);
void __identifier("?xfer@Rva003AE0AF@@MAEXPAVXfer@@@Z")();
extern const void *const Rva003AE0D5_v0[4] = {
	(const void *)&__identifier("??_GRva003AE358@@UAEPAXI@Z"), //  0 0x003AE33C
	(const void *)&__identifier("?rva00563F34@FXGate@@QAEXXZ"), //  1 0x00563F34
	(const void *)&_purecall, //  2 0x0003B810
	(const void *)&__identifier("?xfer@Rva003AE0AF@@MAEXPAVXfer@@@Z")  //  3 0x00563F88
};
}
extern "C" char __identifier("??_7Rva003F498ACallback@@6B@");
// Rva003AE0D5_v10: retail table 0x00C1D2D0 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva003AE358@@WBA@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003ACA7DGet@@YAHXZ")();
void __identifier("?xfer@Rva003AE0AF@@OBA@AEXPAVXfer@@@Z")();
extern const void *const Rva003AE0D5_v10[4] = {
	(const void *)&__identifier("??_ERva003AE358@@WBA@AEPAXI@Z"), //  0 0x003ACA8B
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003ACA7DGet@@YAHXZ"), //  2 0x003ACA7D
	(const void *)&__identifier("?xfer@Rva003AE0AF@@OBA@AEXPAVXfer@@@Z")  //  3 0x003ACA83
};
}

class Rva003AE0D5 : public Rva003AE13C {
public: __declspec(noinline) Rva003AE0D5(const Rva003AE0D5 &that);
private:
	char m_10[0x0C];
	unsigned char m_1C;
};

Rva003AE0D5::Rva003AE0D5(const Rva003AE0D5 &that)
	: Rva003AE13C(that)
{
	const void *src = &that;
	const void *sub_src = src ? (const char *)src + 0x10 : 0;
	Rva003AE11B *sub = (Rva003AE11B *)((char *)this + 0x10);
	sub->Rva003AE11B::Rva003AE11B(*(const Rva003AE11B *)sub_src);
	*(void **)this = (void *)Rva003AE0D5_v0;
	*(void **)((char *)this + 8) = &__identifier("??_7Rva003F498ACallback@@6B@");
	*(void **)sub = (void *)Rva003AE0D5_v10;
	*(unsigned char *)((char *)this + 0x1C) = *(const unsigned char *)((const char *)src + 0x1C);
}
