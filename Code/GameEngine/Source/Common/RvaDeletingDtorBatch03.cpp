// cl: /O1 /MD
// Five more scalar deleting destructors sharing the 28B shape (dtor call,
// flags byte test, conditional scalar delete through pinned ??3@YAXPAX@Z
// 0x0002FD60, return this), same recipe as batches 01-02. Each dtor is
// declared but not defined here and reached through an address-honest pin
// (all five retail sites call directly, so the dtors are non-virtual).
// Emitted via delete anchors; anchors never called. Honest address names;
// owners unproven.
//  0x002189C5 via dtor 0x00218803
//  0x00225B63 via dtor 0x001B5207
//  0x00229487 via dtor 0x0022630F
//  0x0023903B via dtor 0x0042C1B7
//  0x00239E64 via dtor 0x00239D7A

class Rva002189C5 { public: ~Rva002189C5(); };
class Rva00225B63 { public: ~Rva00225B63(); };
class Rva00229487 { public: ~Rva00229487(); };
class Rva0023903B { public: ~Rva0023903B(); };
class Rva00239E64 { public: ~Rva00239E64(); };

void operator delete(void *p);

void Rva002189C5_DeleteAnchor(Rva002189C5 *p) { delete p; }
void Rva00225B63_DeleteAnchor(Rva00225B63 *p) { delete p; }
void Rva00229487_DeleteAnchor(Rva00229487 *p) { delete p; }
void Rva0023903B_DeleteAnchor(Rva0023903B *p) { delete p; }
void Rva00239E64_DeleteAnchor(Rva00239E64 *p) { delete p; }
