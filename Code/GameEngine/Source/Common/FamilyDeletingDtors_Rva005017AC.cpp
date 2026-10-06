// cl: /MD
// ??_GRva005017AC@@QAEPAXI@Z @0x00501D96 28B: scalar deleting dtor calls rowed ??1Rva005017AC@@QAE@XZ at 0x005017AC plus rowed operator delete 0x0002FD60.
// Chain lane: calls 0x005017AC just landed; non-virtual public QAE shape like ??_GRva004FFE89 precedent.
// Retail bytes: push esi mov esi ecx call ??1 test [esp+8] 1 je push esi call delete pop ecx mov eax esi pop esi ret 4.

class Rva005017AC { public: ~Rva005017AC(); };
void famgenDelete(Rva005017AC *p) { delete p; }
