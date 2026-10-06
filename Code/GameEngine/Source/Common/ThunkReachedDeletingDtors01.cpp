// cl: /MD
// Scalar deleting destructors with no direct data or call reference in
// retail, so neither caller- nor vtable-based discovery served them. Four
// are reached only through an adjustor thunk (sub ecx,N; jmp) that sits in
// a secondary vftable; 0x005F5087 has no reference at all. All five share
// the 28B shape (dtor call, flags byte test, conditional scalar delete
// through pinned ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// VslotSmallBodiesAR.cpp. Each dtor is declared but not defined here and
// resolves through a pin in reverse/symbols.csv read from the wrapper's own
// REL32 at +4, so the dtors are non-virtual here; the thunks themselves are
// not modelled. Owner identities and layouts are not recovered; class names
// are the dtor addresses. 0x005E7ED7 is already rowed as a virtual MI dtor
// (Rva005E7ED7Dtor.cpp), so its owner here takes a distinct view name;
// 0x005F501E carries an existing pin.
//  0x00254008 via dtor 0x00254024, thunk 0x00253328 sub ecx,4
//  0x002F312E via dtor 0x002F213F, thunk 0x002F21F1 sub ecx,4
//  0x005E7EBB via dtor 0x005E7ED7, thunk 0x005E7EB3 sub ecx,0x24
//  0x005F06D3 via dtor 0x005F0584, thunk 0x005F05CF sub ecx,4
//  0x005F5087 via dtor 0x005F501E, unreferenced

class Rva00254024 { public: ~Rva00254024(); };
class Rva002F213F { public: ~Rva002F213F(); };
class Rva005E7ED7View { public: ~Rva005E7ED7View(); };
class Rva005F0584 { public: ~Rva005F0584(); };
class Rva005F501E { public: ~Rva005F501E(); };

void operator delete(void *p);

void Rva00254024_DeleteAnchor(Rva00254024 *p) { delete p; }
void Rva002F213F_DeleteAnchor(Rva002F213F *p) { delete p; }
void Rva005E7ED7View_DeleteAnchor(Rva005E7ED7View *p) { delete p; }
void Rva005F0584_DeleteAnchor(Rva005F0584 *p) { delete p; }
void Rva005F501E_DeleteAnchor(Rva005F501E *p) { delete p; }
