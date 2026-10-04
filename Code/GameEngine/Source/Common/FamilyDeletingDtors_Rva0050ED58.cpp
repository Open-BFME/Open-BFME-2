// cl: /O1 /MD
// ??_GRva0050ED58@@QAEPAXI@Z @0x0050F182 28B: scalar deleting dtor calls rowed ??1Rva0050ED58@@QAE@XZ at 0x0050ED58 plus rowed operator delete 0x0002FD60.
class Rva0050ED58 { public: ~Rva0050ED58(); };
void famgenDelete(Rva0050ED58 *p) { delete p; }
