// cl: /MD
// ??_GRva003FE792@@QAEPAXI@Z, RVA 0x003FE7CA, 28B. Chain lane: deleting dtor
// calling rowed ??1Rva003FE792@@QAE@XZ at 0x003FE6D5 then rowed operator
// delete 0x0002FD60; test flags, ret 4. Evidence: vtable slot 0 of 0x00837E88.
class Rva003FE792 { public: ~Rva003FE792(); };
void famgenDelete(Rva003FE792 *p) { delete p; }
