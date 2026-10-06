// cl: /MD
// ??_GRva005C4758@@UAEPAXI@Z, RVA 0x005C473C, 28B. Chain lane: deleting dtor
// calling rowed ??1Rva005C4758@@UAE@XZ at 0x005C4758 then rowed operator
// delete 0x0002FD60; test flags, ret 4. Virtual public dtor (UAE).
// Follows FamilyDeletingDtors_Rva005F6AB0.cpp pattern.
class Rva005C4758 { public: __declspec(noinline) virtual ~Rva005C4758(); private: int m_famgen;
  friend void famgenDelete(Rva005C4758 *p); };
Rva005C4758::~Rva005C4758() { m_famgen = 0; }
void famgenDelete(Rva005C4758 *p) { delete p; }
