// cl: /MD
// ??_GRva00585B16@@QAEPAXI@Z @0x00585D21 28B
// Scalar deleting dtor: calls rowed ??1Rva00585B16@@QAE@XZ at 0x00585B16 then
// rowed operator delete at 0x0002FD60. Non-virtual public dtor (no vtable).
class Rva00585B16 { public: ~Rva00585B16(); };
void famgenDelete(Rva00585B16 *p) { delete p; }
