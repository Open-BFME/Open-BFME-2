// cl: /MD
// ??_GRva004FFE89@@QAEPAXI@Z @0x005000BA 28B: scalar deleting dtor calls rowed ??1Rva004FFE89@@QAE@XZ at 0x004FFE89 plus rowed operator delete 0x0002FD60.
// Chain lane: calls 0x004FFE89 just landed; non-virtual public QAE shape like ??_GRva004FFE81 precedent in LocomotorSetMapThunks.cpp.
// Retail bytes: push esi mov esi ecx call ??1 test [esp+8] 1 je push esi call delete pop ecx mov eax esi pop esi ret 4.

class Rva004FFE89 { public: ~Rva004FFE89(); };
void famgenDelete(Rva004FFE89 *p) { delete p; }
