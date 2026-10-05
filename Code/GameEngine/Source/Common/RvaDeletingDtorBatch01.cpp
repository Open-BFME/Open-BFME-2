// cl: /O1 /MD
// Five scalar deleting destructors sharing one 28B shape (dtor call, flags
// byte test, conditional scalar delete through pinned ??3@YAXPAX@Z
// 0x0002FD60, return this), same recipe as the landed 0x005E948B/0x005E3051/
// 0x005EB35D rows: each dtor is declared but not defined here and reached
// through an address-honest pin (all five retail sites call directly, so the
// dtors are non-virtual). Emitted via delete anchors; anchors never called.
// Honest address names; owners unproven.
//  0x0009A200 via dtor 0x001076E9
//  0x000FE9C7 via dtor 0x000FE290
//  0x001732C6 via dtor 0x0018C57C
//  0x001F097A via dtor 0x001F077D

class Rva0009A200 { public: ~Rva0009A200(); };
class Rva000FE9C7 { public: ~Rva000FE9C7(); };
class Rva001732C6 { public: ~Rva001732C6(); };
class Rva001F097A { public: ~Rva001F097A(); };

void operator delete(void *p);

void Rva0009A200_DeleteAnchor(Rva0009A200 *p) { delete p; }
void Rva000FE9C7_DeleteAnchor(Rva000FE9C7 *p) { delete p; }
void Rva001732C6_DeleteAnchor(Rva001732C6 *p) { delete p; }
void Rva001F097A_DeleteAnchor(Rva001F097A *p) { delete p; }
