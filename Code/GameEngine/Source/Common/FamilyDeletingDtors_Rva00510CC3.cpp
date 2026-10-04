// cl: /O1 /MD
// ??_GRva00510CC3@@QAEPAXI@Z @0x00510CA7 28B: scalar deleting dtor calls rowed ??1Rva00510CC3@@QAE@XZ at 0x00510CC3 plus rowed operator delete 0x0002FD60.
class Rva00510CC3 { public: ~Rva00510CC3(); };
void famgenDelete(Rva00510CC3 *p) { delete p; }
