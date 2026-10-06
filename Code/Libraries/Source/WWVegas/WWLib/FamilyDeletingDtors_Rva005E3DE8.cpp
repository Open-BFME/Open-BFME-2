// cl: /MD
// ??_GRva005E3DE8@@QAEPAXI@Z @0x005E3EEE 28B.
// Deleting dtor for non-virtual Rva005E3DE8: calls rowed ??1Rva005E3DE8 then sized delete.
// Evidence: chain lane calls rowed 0x005E3DE8 plus rowed delete 0x0002FD60 plus precedent AudioEventRTS family.
class Rva005E3DE8 { public: ~Rva005E3DE8(); };
void famgenDelete(Rva005E3DE8 *p) { delete p; }
