// cl: /MD
// Five more scalar deleting destructors sharing the 28B shape (dtor call,
// flags byte test, conditional scalar delete through pinned ??3@YAXPAX@Z
// 0x0002FD60, return this), same recipe as batches 01-03. Each dtor is
// declared but not defined here and reached through an address-honest pin
// (all five retail sites call directly, so the dtors are non-virtual).
// Emitted via delete anchors; anchors never called. Honest address names;
// owners unproven.
//  0x002BF17C via dtor 0x002BF0D6
//  0x002C5F72 via dtor 0x00505BBA
//  0x002C5F8E via dtor 0x0050549A
//  0x002D28FF via dtor 0x002D284F
//  0x002D339F via dtor 0x0052710C

class Rva002BF17C { public: ~Rva002BF17C(); };
class Rva002C5F72 { public: ~Rva002C5F72(); };
class Rva002C5F8E { public: ~Rva002C5F8E(); };
class Rva002D28FF { public: ~Rva002D28FF(); };
class Rva002D339F { public: ~Rva002D339F(); };

void operator delete(void *p);

void Rva002BF17C_DeleteAnchor(Rva002BF17C *p) { delete p; }
void Rva002C5F72_DeleteAnchor(Rva002C5F72 *p) { delete p; }
void Rva002C5F8E_DeleteAnchor(Rva002C5F8E *p) { delete p; }
void Rva002D28FF_DeleteAnchor(Rva002D28FF *p) { delete p; }
void Rva002D339F_DeleteAnchor(Rva002D339F *p) { delete p; }
