// cl: /MD
// ??_GRva005D3731@@QAEPAXI@Z @0x0057856A 28B.
// Deleting dtor via rowed ??1 at 0x005D3731 plus rowed delete 0x0002FD60.
// Evidence: callee rowed 0x005D3731; same 28B shape as FamilyDeletingDtors3 QAEPAXI family.
struct Rva005D3731 { ~Rva005D3731(); };
void famgenDelete(Rva005D3731 *p) { delete p; }
