// ??0Rva0060D06AMember@@QAE@XZ
// partial score=0.925926 date=2026-10-04
// cl: /O1
// BFME1 donor1281192f68 BfmeConv881.cpp exposes this hash-map default
// constructor through its two opaque20B members. Target0060D06A/31B is
// called at offsets18 and2C by the independently identified0060D1F7 ctor.
// It passes100 and three empty policy/allocator objects by reference to
// the already byte-verified64B table initializer0060CF76. Empty object
// meanings come from STLport/donor source; target does not establish key
// or value types, so no FXList/ArmorTemplate identity is introduced here.
struct Rva0060D06AHash { Rva0060D06AHash() {} };
struct Rva0060D06AEqual { Rva0060D06AEqual() {} };
struct Rva0060D06AAllocator { Rva0060D06AAllocator() {} };



class Rva0060D06AMember
{
public:
	Rva0060D06AMember();
	void initialize(unsigned int count, const Rva0060D06AHash &,
		const Rva0060D06AEqual &, const Rva0060D06AAllocator &);
private:
	unsigned int opaque[5];
};

#pragma comment(linker, "/alternatename:?initialize@Rva0060D06AMember@@QAEXIABURva0060D06AHash@@ABURva0060D06AEqual@@ABURva0060D06AAllocator@@@Z=?dup_0060cf76@@YAXXZ")

Rva0060D06AMember::Rva0060D06AMember()
{
	initialize(100, Rva0060D06AHash(), Rva0060D06AEqual(), Rva0060D06AAllocator());
}
