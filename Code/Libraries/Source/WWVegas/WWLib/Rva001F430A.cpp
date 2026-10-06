// cl: /Ob1
// Whole U1SmallStateProbes.cpp @5cc75ddda6455c338a5068307e587a793f96d6b3.
// Target raw CDECL pointer-word zero test; original names and entry unresolved.
struct Rva001F430APointerCell {void *word;};
bool rva001F430A(const Rva001F430APointerCell *p) {return !p->word;}