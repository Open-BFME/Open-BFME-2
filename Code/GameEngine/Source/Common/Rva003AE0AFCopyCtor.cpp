// cl: /DNDEBUG /MD /GX- /Ob2
// ??0Rva003AE0AF@@QAE@ABV0@@Z @0x003AE0AF 38B
// Copy ctor: base Rva003AE0D5 at +0 via rowed copy 0x003AE0D5 then own
// three vptrs. Evidence: retail base call plus stores at +0/+8/+0x10
// plus ret 4, chain after landing 0x003AE0D5. Precedent: same-file base.
class Rva003AE0D5 {
public: Rva003AE0D5(const Rva003AE0D5 &that);
private: char m_pad[0x20 - 4];
};

// Rva003AE0AF_v0: matched references place it at VA 0xc1ca04 (retail .rdata value 60).
extern "C" char Rva003AE0AF_v0 = 60;
// Rva003AE0AF_v8 gives way to the compiler table the data ledger binds there.
extern "C" char __identifier("??_7Rva003AEDE9@@6BRva003AEEB3Slot18@@@");
// Rva003AE0AF_v10: matched references place it at VA 0xc1c9f0 (retail .rdata value -117).
extern "C" char Rva003AE0AF_v10 = -117;

class Rva003AE0AF : public Rva003AE0D5 {
public: __declspec(noinline) Rva003AE0AF(const Rva003AE0AF &that);
};

Rva003AE0AF::Rva003AE0AF(const Rva003AE0AF &that)
	: Rva003AE0D5(that)
{
	*(void **)this = &Rva003AE0AF_v0;
	*(void **)((char *)this + 8) = &__identifier("??_7Rva003AEDE9@@6BRva003AEEB3Slot18@@@");
	*(void **)((char *)this + 0x10) = &Rva003AE0AF_v10;
}
