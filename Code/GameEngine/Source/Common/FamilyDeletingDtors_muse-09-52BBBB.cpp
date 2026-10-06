// cl: /MD
// ??_GRva004E1A04@@QAEPAXI@Z @0x0052BBBB 28B
// Scalar deleting dtor: calls rowed ??1Rva004E1A04@@QAE@XZ at 0x004E1A04 then
// rowed operator delete at 0x0002FD60. Non-virtual public dtor (no vtable).
class Rva004E1A04 { public: ~Rva004E1A04(); };
void famgenDelete(Rva004E1A04 *p) { delete p; }
