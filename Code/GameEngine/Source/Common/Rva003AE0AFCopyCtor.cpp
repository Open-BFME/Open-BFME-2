// cl: /DNDEBUG /MD /GX- /Ob2
// ??0Rva003AE0AF@@QAE@ABV0@@Z @0x003AE0AF 38B
// Copy ctor: base Rva003AE0D5 at +0 via rowed copy 0x003AE0D5 then own
// three vptrs. Evidence: retail base call plus stores at +0/+8/+0x10
// plus ret 4, chain after landing 0x003AE0D5. Precedent: same-file base.
class Rva003AE0D5 {
public: Rva003AE0D5(const Rva003AE0D5 &that);
private: char m_pad[0x20 - 4];
};

// Rva003AE0AF_v0: retail table 0x00C1CA04 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_GRva003AE358@@UAEPAXI@Z")();
void __identifier("?rva00563F34@FXGate@@QAEXXZ")();
void __identifier("?clone@Rva003AE0AF@@QBEPAV1@XZ")();
void __identifier("?xfer@Rva003AE0AF@@MAEXPAVXfer@@@Z")();
extern const void *const Rva003AE0AF_v0[4] = {
	(const void *)&__identifier("??_GRva003AE358@@UAEPAXI@Z"), //  0 0x003AE33C
	(const void *)&__identifier("?rva00563F34@FXGate@@QAEXXZ"), //  1 0x00563F34
	(const void *)&__identifier("?clone@Rva003AE0AF@@QBEPAV1@XZ"), //  2 0x003AE092
	(const void *)&__identifier("?xfer@Rva003AE0AF@@MAEXPAVXfer@@@Z")  //  3 0x00563F88
};
}
// The compiler table the data ledger binds at this address:
extern "C" char __identifier("??_7Rva003AEDE9@@6BRva003AEEB3Slot18@@@");
// Rva003AE0AF_v10: retail table 0x00C1C9F0 (4 slots). Own the complete initialized table
// instead of its one-byte first-byte stand-in (Rva004DF324Dtor.cpp s_10
// precedent): each slot names a matched row at retail's slot target, taken by
// address and never called through these erased signatures.
extern "C" {
void __identifier("??_ERva003AE358@@WBA@AEPAXI@Z")();
void __identifier("??1Elem4@@QAE@XZ")();
void __identifier("?Rva003ACA7DGet@@YAHXZ")();
void __identifier("?xfer@Rva003AE0AF@@OBA@AEXPAVXfer@@@Z")();
extern const void *const Rva003AE0AF_v10[4] = {
	(const void *)&__identifier("??_ERva003AE358@@WBA@AEPAXI@Z"), //  0 0x003ACA8B
	(const void *)&__identifier("??1Elem4@@QAE@XZ"), //  1 0x000B3FD0
	(const void *)&__identifier("?Rva003ACA7DGet@@YAHXZ"), //  2 0x003ACA7D
	(const void *)&__identifier("?xfer@Rva003AE0AF@@OBA@AEXPAVXfer@@@Z")  //  3 0x003ACA83
};
}

class Rva003AE0AF : public Rva003AE0D5 {
public: __declspec(noinline) Rva003AE0AF(const Rva003AE0AF &that);
};

Rva003AE0AF::Rva003AE0AF(const Rva003AE0AF &that)
	: Rva003AE0D5(that)
{
	*(void **)this = (void *)Rva003AE0AF_v0;
	*(void **)((char *)this + 8) = &__identifier("??_7Rva003AEDE9@@6BRva003AEEB3Slot18@@@");
	*(void **)((char *)this + 0x10) = (void *)Rva003AE0AF_v10;
}
