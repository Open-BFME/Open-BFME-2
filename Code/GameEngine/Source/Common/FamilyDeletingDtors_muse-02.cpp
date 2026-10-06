// cl: /MD
// ??_GRva004F6986@@QAEPAXI@Z @0x004F6E2B 28B: scalar deleting dtor calls rowed ??1 at 0x004F6986 plus rowed operator delete 0x0002FD60.
// Non-virtual public QAE shape like ??_GRva0021A0C2 precedent; chain from just-landed 0x004F6986.

class Rva004F6986 { public: ~Rva004F6986(); };
void famgenDelete(Rva004F6986 *p) { delete p; }
