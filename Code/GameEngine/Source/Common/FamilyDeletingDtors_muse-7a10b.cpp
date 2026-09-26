// cl: /O2 /MD
// ??_GRva00801FB0Elem@@QAEPAXI@Z @0x0066E2E0 30B
// Deleting dtor slot 0 of vtable 0x008E3C20; calls pinned ??1Rva00801FB0Elem@@QAE@XZ at 0x0066DF10 then rowed operator delete at 0x0002FD60; ctor rowed at 0x0066E270 installs same vtable; ICF-folded with bfmeClearVHW.
class Rva00801FB0Elem { public: ~Rva00801FB0Elem(); };
void famgenDelete(Rva00801FB0Elem *p) { delete p; }
