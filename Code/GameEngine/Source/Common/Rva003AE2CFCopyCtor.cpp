// cl: /DNDEBUG /MD /GX- /Ob2
// ??0Rva003AE2CF@@QAE@ABV0@@Z @0x003AE2CF 70B
// Copy ctor: base Rva003AE13C at +0 via rowed copy 0x003AE13C, sub
// Rva003AE315 at +0x10 via rowed copy 0x003AE315 with null-guarded source,
// then own/second/sub vptrs plus byte at +0x20. Evidence: retail two copy
// calls plus neg/sbb/and for +0x10 plus three vptr stores plus byte copy,
// unlocks 0x003AE2A9. Sibling of landed 0x003AE0D5 (Rva003AE11B sub).
class Rva003AE13C {
public: __declspec(noinline) Rva003AE13C(const Rva003AE13C &that);
private: char m_pad[0x10 - 4];
};

class Rva003AE315 {
public: Rva003AE315(const Rva003AE315 &that);
};

extern "C" char Rva003AE2CF_v0;
extern "C" char Rva003AE2CF_v8;
extern "C" char Rva003AE2CF_v10;

class Rva003AE2CF : public Rva003AE13C {
public: __declspec(noinline) Rva003AE2CF(const Rva003AE2CF &that);
private:
	char m_10[0x10];
	unsigned char m_20;
};

Rva003AE2CF::Rva003AE2CF(const Rva003AE2CF &that)
	: Rva003AE13C(that)
{
	const void *src = &that;
	const void *sub_src = src ? (const char *)src + 0x10 : 0;
	Rva003AE315 *sub = (Rva003AE315 *)((char *)this + 0x10);
	sub->Rva003AE315::Rva003AE315(*(const Rva003AE315 *)sub_src);
	*(void **)this = &Rva003AE2CF_v0;
	*(void **)((char *)this + 8) = &Rva003AE2CF_v8;
	*(void **)sub = &Rva003AE2CF_v10;
	*(unsigned char *)((char *)this + 0x20) = *(const unsigned char *)((const char *)src + 0x20);
}
// _Rva003AE2CF_v8: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_Rva003AE2CF_v8=?vftable_0112B89C@@3HA")
