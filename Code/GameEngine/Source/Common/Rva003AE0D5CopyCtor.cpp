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

// Rva003AE0D5_v0: matched references place it at VA 0xc1d2e0 (retail .rdata value 60).
extern "C" char Rva003AE0D5_v0 = 60;
extern "C" char Rva003AE0D5_v8;
// Rva003AE0D5_v10: matched references place it at VA 0xc1d2d0 (retail .rdata value -117).
extern "C" char Rva003AE0D5_v10 = -117;

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
	*(void **)this = &Rva003AE0D5_v0;
	*(void **)((char *)this + 8) = &Rva003AE0D5_v8;
	*(void **)sub = &Rva003AE0D5_v10;
	*(unsigned char *)((char *)this + 0x1C) = *(const unsigned char *)((const char *)src + 0x1C);
}
// _Rva003AE0D5_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AE0D5_v8=?vftable_0112B89C@@3HA")
