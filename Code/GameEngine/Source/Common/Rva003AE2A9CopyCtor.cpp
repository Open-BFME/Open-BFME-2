// cl: /DNDEBUG /MD /GX- /O1 /Ob2
// ??0Rva003AE2A9@@QAE@ABV0@@Z @0x003AE2A9 38B
// Copy ctor: base Rva003AE2CF at +0 via rowed copy 0x003AE2CF then own
// three vptrs. Evidence: retail base call plus stores at +0/+8/+0x10
// plus ret 4, chain after landing 0x003AE2CF. Sibling of 0x003AE0AF.
class Rva003AE2CF {
public: Rva003AE2CF(const Rva003AE2CF &that);
private: char m_pad[0x24]; // the clone at 0x003AE28C allocates 0x24
};

// Rva003AE2A9_v0: matched references place it at VA 0xc1caa4 (retail .rdata value 60).
extern "C" char Rva003AE2A9_v0 = 60;
// Rva003AE2A9_v8: matched references place it at VA 0xc1caa0 (retail .rdata value 103).
extern "C" char Rva003AE2A9_v8 = 103;
// Rva003AE2A9_v10: matched references place it at VA 0xc1ca90 (retail .rdata value -117).
extern "C" char Rva003AE2A9_v10 = -117;

class Rva003AE2A9 : public Rva003AE2CF {
public: __declspec(noinline) Rva003AE2A9(const Rva003AE2A9 &that);
	Rva003AE2A9 *rva003AE28C() const;
};

Rva003AE2A9::Rva003AE2A9(const Rva003AE2A9 &that)
	: Rva003AE2CF(that)
{
	*(void **)this = &Rva003AE2A9_v0;
	*(void **)((char *)this + 8) = &Rva003AE2A9_v8;
	*(void **)((char *)this + 0x10) = &Rva003AE2A9_v10;
}

// ?rva003AE28C@Rva003AE2A9@@QBEPAV1@XZ @0x003AE28C 29B: vtable slot before
// the rowed ?xfer@Rva003AE2A9; allocates 0x24 bytes and copy-constructs this.
Rva003AE2A9 *Rva003AE2A9::rva003AE28C() const
{
	return new Rva003AE2A9(*this);
}
