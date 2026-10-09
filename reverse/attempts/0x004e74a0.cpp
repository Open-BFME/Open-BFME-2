// ?rva004E74A0@Rva004E7392@@QAE?AURva004E7392Ref@@XZ
// partial score=0.82 date=2026-10-09
// cl: /O1 /EHsc /DNDEBUG /MD
//
// Native factory4E74A0..4E74E0 returns pointer ownership by value: hidden
// sret/frame+8 stores and returns output storage; FuncInfo94490C cleanup
// 7922C7 tests return bit and destroys it through null-guarded virtual slot0
// with delete flag1 at helper2E3A80. This proves the return-storage ABI and
// destructor role; original return class and method names are unknown.
// Ordinary new below emits71B vs native64B because of allocation unwind
// state stores; retail allocation/exception policy is still unresolved.
// Bank only, never a claimed match.
//
// ??0Rva004E7392@@QAE@ABV0@@Z @0x004E7392 39B: copy constructor (caller
// 0x004E74C1). It copies the state-free polymorphic base through its
// out-of-line copy 0x004E72C0 (Rva004E72C0Copy.cpp), installs vtable
// 0x00BFD010 and copies the two plain fields at +4 and +8. Identities are
// address-derived.

struct Rva004E72C0
{
	Rva004E72C0(const Rva004E72C0 &other);
	virtual ~Rva004E72C0();
};

struct Rva004E7392;
struct Rva004E7392Ref
{
    Rva004E7392 *ptr;
    Rva004E7392Ref(Rva004E7392 *p) : ptr(p) {}
    ~Rva004E7392Ref();
};
struct Rva004E7392 : Rva004E72C0
{
	Rva004E7392(const Rva004E7392 &other);
	Rva004E7392Ref rva004E74A0();
	virtual ~Rva004E7392();

	int m_04;
	int m_08;
};


Rva004E7392Ref Rva004E7392::rva004E74A0()
{
    return Rva004E7392Ref(new Rva004E7392(*this));
}

inline Rva004E7392Ref::~Rva004E7392Ref()
{
    if (ptr)
        delete ptr;
}
