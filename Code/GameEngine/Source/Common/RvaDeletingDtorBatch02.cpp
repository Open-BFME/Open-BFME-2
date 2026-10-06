// cl: /MD
// Five more scalar deleting destructors sharing the 28B shape (dtor call,
// flags byte test, conditional scalar delete through pinned ??3@YAXPAX@Z
// 0x0002FD60, return this), same recipe as batch 01. Each dtor is declared
// but not defined here and reached through an address-honest pin (all five
// retail sites call directly, so the dtors are non-virtual). Emitted via
// delete anchors; anchors never called. Honest address names; owners unproven.
//  0x001FC036 via dtor 0x001FBF4D
//  0x00204D6B via dtor 0x00204C16 (address also carries a HolderBase dtor row)
//  0x002109F8 via dtor 0x00210830
//  0x00210CF1 via dtor 0x003FA14B
//  0x002146F7 via dtor 0x004043FF

class Rva001FC036 { public: ~Rva001FC036(); };
class Rva00204D6B { public: ~Rva00204D6B(); };
class Rva002109F8 { public: ~Rva002109F8(); };
class Rva00210CF1 { public: ~Rva00210CF1(); };
class Rva002146F7 { public: ~Rva002146F7(); };

void operator delete(void *p);

void Rva001FC036_DeleteAnchor(Rva001FC036 *p) { delete p; }
void Rva00204D6B_DeleteAnchor(Rva00204D6B *p) { delete p; }
void Rva002109F8_DeleteAnchor(Rva002109F8 *p) { delete p; }
void Rva00210CF1_DeleteAnchor(Rva00210CF1 *p) { delete p; }
void Rva002146F7_DeleteAnchor(Rva002146F7 *p) { delete p; }
