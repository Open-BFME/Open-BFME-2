// ??_GRva004E16D9Record@@UAEPAXI@Z
// partial score=0.95 date=2026-09-28
// cl: /MD
// ??_GRva004E16D9Record@@UAEPAXI@Z @0x004E1BE0 (28B).
// Scalar deleting dtor slot 0 of vtable 0x00861A70; calls rowed
// ??1Rva004E16D9Record@@QAE@XZ at 0x004E1682 plus delete at 0x0002FD60.
// Evidence: vtable slot plus ??1 row plus retail call bytes; BFME1 donor none;
// pattern follows FamilyDeletingDtors_0021C7e.cpp siblings.

class Rva004E16D9Record { public: __declspec(noinline) virtual ~Rva004E16D9Record(); private: int m_famgen;
  friend void famgenDelete(Rva004E16D9Record *p); };
Rva004E16D9Record::~Rva004E16D9Record() { m_famgen = 0; }
void famgenDelete(Rva004E16D9Record *p) { delete p; }
