// cl: /MD
// ??_GRva002105A6@@QAEPAXI@Z @0x00210604 28B
// Scalar deleting dtor; calls rowed ??1Rva002105A6@@QAE@XZ at 0x002105A6
// then rowed operator delete at 0x0002FD60. Evidence: retail push esi call
// ??1 test flag delete ret 4. No vftable or call site references 0x00210604
// and every retail delete of this record calls the dtor directly, so the dtor
// is non-virtual; it is declared, not defined, here and the body is emitted
// through a delete anchor that is never called (recipe of
// RvaDeletingDtorBatch02.cpp).
class Rva002105A6 { public: ~Rva002105A6(); };

void famgenDelete(Rva002105A6 *p) { delete p; }
