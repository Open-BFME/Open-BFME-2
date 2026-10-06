// cl: /MD
// ??_GRva00204686@@QAEPAXI@Z @0x00204AF6 28B
// Scalar deleting dtor: calls rowed ??1Rva00204686@@QAE@XZ at 0x00204686 then
// rowed operator delete at 0x0002FD60. Non-virtual public dtor (no vtable).
class Rva00204686 { public: ~Rva00204686(); };
void famgenDelete(Rva00204686 *p) { delete p; }
