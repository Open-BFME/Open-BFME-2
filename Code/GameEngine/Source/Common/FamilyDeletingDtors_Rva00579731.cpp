// cl: /MD
// ??_GRva00579731@@QAEPAXI@Z @0x00579CB8 28B.
// Evidence: chain lane calls just-landed ??1Rva00579731 at 0x00579731 plus operator delete 0x0002FD60; shape push esi call ??1 test flag call delete ret 4.
class Rva00579731 { public: ~Rva00579731(); };
void famgenDelete(Rva00579731 *p) { delete p; }
