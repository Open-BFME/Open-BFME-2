// cl: /MD
// ??_GRva0042FCE6@@QAEPAXI@Z, RVA 0x0042FE1F, 28B. Chain lane: deleting dtor
// calling rowed ??1Rva0042FCE6@@QAE@XZ at 0x0042FCE6 then rowed operator
// delete 0x0002FD60; test flags, ret 4. Evidence: vtable slot 1 of 0x0083C960.
class Rva0042FCE6 { public: ~Rva0042FCE6(); };
void famgenDelete(Rva0042FCE6 *p) { delete p; }
