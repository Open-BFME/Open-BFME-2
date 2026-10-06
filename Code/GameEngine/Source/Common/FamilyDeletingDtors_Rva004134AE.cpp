// cl: /MD
// ??_GRva004134AE@@QAEPAXI@Z @0x00413492 28B: scalar deleting dtor calling rowed ??1Rva004134AE at 0x004134AE plus rowed operator delete 0x0002FD60.
// Evidence: chain lane, 28B push esi/call ??1/test [esp+8]/call delete/ret 4; same QAE shape as ??_GRva00402F28Item precedent.
class Rva004134AE { public: ~Rva004134AE(); };
void famgenDelete(Rva004134AE *p) { delete p; }
