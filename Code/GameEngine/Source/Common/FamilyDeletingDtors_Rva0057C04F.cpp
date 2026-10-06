// cl: /MD
// ??_GRva0057C04F@@QAEPAXI@Z @0x0042D55B 28B.
// Deleting dtor via rowed ??1 at 0x0057C04F plus rowed delete 0x0002FD60.
// Evidence: chain lane calls 0x0057C04F now resolved; same 28B shape as FamilyDeletingDtors_Rva00574499 QAEPAXI family.
struct Rva0057C04F { ~Rva0057C04F(); };
void famgenDelete(Rva0057C04F *p) { delete p; }
