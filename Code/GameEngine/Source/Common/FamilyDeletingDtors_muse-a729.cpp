// cl: /MD
// ??_GBfmeRecordOwner900@@QAEPAXI@Z @0x004CB730 28B: scalar deleting dtor calls rowed ??1 at 0x004CB6C9 plus rowed delete at 0x0002FD60.
class BfmeRecordOwner900 { public: ~BfmeRecordOwner900(); };
void famgenDelete(BfmeRecordOwner900 *p) { delete p; }
