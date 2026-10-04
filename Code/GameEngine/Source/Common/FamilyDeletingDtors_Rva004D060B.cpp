// cl: /O1 /MD
// ??_GRva004D060B@@QAEPAXI@Z @0x004D064D 28B: scalar deleting dtor calls rowed ??1Rva004D060B@@QAE@XZ at 0x004D060B plus rowed operator delete 0x0002FD60.
class Rva004D060B { public: ~Rva004D060B(); };
void famgenDelete(Rva004D060B *p) { delete p; }
