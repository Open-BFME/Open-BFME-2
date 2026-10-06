// cl: /MD
// ??_GRva001EC349@@QAEPAXI@Z @0x001ECB91 28B.
// Deleting dtor via rowed ??1 at 0x001EC349 plus rowed delete 0x0002FD60.
// Evidence: callee rowed 0x001EC349; same 28B shape as FamilyDeletingDtors3 QAEPAXI family.
struct Rva001EC349 { ~Rva001EC349(); };
void famgenDelete(Rva001EC349 *p) { delete p; }
