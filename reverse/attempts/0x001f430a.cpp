// ?rva001F430A@@YA_NPBURva001F430APointerCell@@@Z
// partial score=1.0 date=2026-10-05
// cl: /O1 /Ob1 /Fabuild/seat3/PointerZero12.asm /Fdbuild/seat3/PointerZero12.pdb
// Whole U1SmallStateProbes.cpp @5cc75ddda6455c338a5068307e587a793f96d6b3.
// Target raw CDECL pointer-word zero test; original names and entry unresolved.
struct Rva001F430APointerCell {void *word;};
bool rva001F430A(const Rva001F430APointerCell *p) {return !p->word;}