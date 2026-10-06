// cl: /MD
// Scalar deleting destructors that retail keeps but never references: no
// vtable slot, call or jmp reaches them. Each is the 28B shape that calls
// the rowed complete destructor, tests bit 0 of the flags, frees through
// operator delete 0x0002FD60 and returns this with ret 4. Each class is
// declared locally only so its deleting destructor is emitted; the
// destructor call resolves through that destructor's own row.
// Owner identities and layouts are not recovered.

// ??_GRva003EF14A@@QAEPAXI@Z @0x003EF20F 28B: calls rowed ~Rva003EF14A 0x003EF14A
class Rva003EF14A { public: ~Rva003EF14A(); };
void famgenDelete(Rva003EF14A *p) { delete p; }

// ??_GRva004703E0@@QAEPAXI@Z @0x004704AC 28B: calls rowed ~Rva004703E0 0x004703E0
class Rva004703E0 { public: ~Rva004703E0(); };
void famgenDelete(Rva004703E0 *p) { delete p; }

// ??_GRva004E7DC8@@QAEPAXI@Z @0x004E7E1E 28B: calls rowed ~Rva004E7DC8 0x004E7DC8
class Rva004E7DC8 { public: ~Rva004E7DC8(); };
void famgenDelete(Rva004E7DC8 *p) { delete p; }

// ??_GRva002C589B@@QAEPAXI@Z @0x0050526D 28B: calls rowed ~Rva002C589B 0x002C589B
class Rva002C589B { public: ~Rva002C589B(); };
void famgenDelete(Rva002C589B *p) { delete p; }

// ??_GAIBase@@QAEPAXI@Z @0x00506B58 28B: calls rowed ~AIBase 0x005ADA40
class AIBase
{ public: ~AIBase(); };
void famgenDelete(AIBase *p) { delete p; }

// ??_GRva0052A470@@QAEPAXI@Z @0x0052A5E7 28B: calls rowed ~Rva0052A470 0x0052A470
class Rva0052A470 { public: ~Rva0052A470(); };
void famgenDelete(Rva0052A470 *p) { delete p; }

// ??_GRva0054C941@@QAEPAXI@Z @0x0054CBFF 28B: calls rowed ~Rva0054C941 0x0054C941
class Rva0054C941 { public: ~Rva0054C941(); };
void famgenDelete(Rva0054C941 *p) { delete p; }

// ??_GRva00177860@@QAEPAXI@Z @0x00560191 28B: calls rowed ~Rva00177860 0x00177860
class Rva00177860 { public: ~Rva00177860(); };
void famgenDelete(Rva00177860 *p) { delete p; }

// ??_GRva005DCE08@@QAEPAXI@Z @0x005AD948 28B: calls rowed ~Rva005DCE08 0x005DCE08
class Rva005DCE08 { public: ~Rva005DCE08(); };
void famgenDelete(Rva005DCE08 *p) { delete p; }

// ??_GRva005D309D@@QAEPAXI@Z @0x005D328E 28B: calls rowed ~Rva005D309D 0x005D309D
class Rva005D309D { public: ~Rva005D309D(); };
void famgenDelete(Rva005D309D *p) { delete p; }

// ??_GRva005D4913@@QAEPAXI@Z @0x005D49DD 28B: calls rowed ~Rva005D4913 0x005D4913
class Rva005D4913 { public: ~Rva005D4913(); };
void famgenDelete(Rva005D4913 *p) { delete p; }

// ??_GRva005D4EC6@@QAEPAXI@Z @0x005D4F84 28B: calls rowed ~Rva005D4EC6 0x005D4EC6
class Rva005D4EC6 { public: ~Rva005D4EC6(); };
void famgenDelete(Rva005D4EC6 *p) { delete p; }

// ??_GRva005F18C1@@QAEPAXI@Z @0x005F1B59 28B: calls rowed ~Rva005F18C1 0x005F18C1
class Rva005F18C1 { public: ~Rva005F18C1(); };
void famgenDelete(Rva005F18C1 *p) { delete p; }

// ??_GRva005FEBC8@@QAEPAXI@Z @0x005FA838 28B: calls rowed ~Rva005FEBC8 0x005FEBC8
class Rva005FEBC8 { public: ~Rva005FEBC8(); };
void famgenDelete(Rva005FEBC8 *p) { delete p; }

// ??_GRva005FB615@@QAEPAXI@Z @0x005FB856 28B: calls rowed ~Rva005FB615 0x005FB615
class Rva005FB615 { public: ~Rva005FB615(); };
void famgenDelete(Rva005FB615 *p) { delete p; }
