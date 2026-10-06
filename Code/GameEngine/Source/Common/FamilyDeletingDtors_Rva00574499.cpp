// cl: /MD
// ??_GRva00574499@@QAEPAXI@Z @0x00574B4C 28B.
// Deleting dtor via rowed ??1 at 0x00574499 plus rowed delete 0x0002FD60.
// Evidence: chain lane from 0x00574499; same 28B shape as FamilyDeletingDtors3 QAEPAXI family.
struct Rva00574499 { ~Rva00574499(); };
void famgenDelete(Rva00574499 *p) { delete p; }
