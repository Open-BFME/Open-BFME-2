// cl: /MD
// Rva003F1A44Delete @0x003F1A44 27B: null-checked delete of an Rva003F0C6C.
// Evidence: retail reads its pointer from [esp+8] not ecx, calls the rowed
// ??1Rva003F0C6C@@QAE@XZ @0x003F0C6C then operator delete 0x0002FD60, and
// returns with ret 4, so it is a one-argument __stdcall free function. The
// name is generated; its callers are not yet identified.
class Rva003F0C6C { public: ~Rva003F0C6C(); };

void __stdcall Rva003F1A44Delete(Rva003F0C6C *p) { delete p; }
