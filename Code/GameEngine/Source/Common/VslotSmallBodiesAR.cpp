// cl: /MD
// Scalar deleting destructors that retail reaches only through vtable slots,
// so caller-based discovery never served them. All seventeen share the 28B
// shape (dtor call, flags byte test, conditional scalar delete through pinned
// ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// FamilyDeletingDtors11.cpp and RvaDeletingDtorBatch04.cpp. Each dtor is
// declared but not defined here and resolves through an address-derived pin
// in reverse/symbols.csv read from the wrapper's own REL32 at +4; every
// retail site calls it directly, so the dtors are non-virtual here. Emitted
// via delete anchors that are never called. Owner identities and layouts are
// not recovered; class names are the dtor addresses.
//  0x005CBAEE via dtor 0x002BEDA4   0x00419B71 via dtor 0x00419B8D
//  0x00431A64 via dtor 0x004318D8   0x00575700 via dtor 0x0057571C
//  0x005CFCD1 via dtor 0x005CF86B   0x005E57AD via dtor 0x005E57C9
//  0x005EA28F via dtor 0x005EA2AB   0x00604A6F via dtor 0x00604A68
//  0x00740E85 via dtor 0x004102A4   0x005FAA31 via dtor 0x004E84A4
//  0x0040C5DE via dtor 0x0040C39E   0x0040FD1C via dtor 0x0040FB4A
//  0x00445211 via dtor 0x0044455C   0x004AF161 via dtor 0x004AF17D
//  0x004BAF11 via dtor 0x004BAEC8   0x00558F6E via dtor 0x00557CCC
//  0x006022AE via dtor 0x006022CA

class Rva002BEDA4 { public: ~Rva002BEDA4(); };
class Rva00419B8D { public: ~Rva00419B8D(); };
class Rva004318D8 { public: ~Rva004318D8(); };
class Rva0057571C { public: ~Rva0057571C(); };
class Rva005CF86B { public: ~Rva005CF86B(); };
class Rva005E57C9 { public: ~Rva005E57C9(); };
class Rva005EA2AB { public: ~Rva005EA2AB(); };
class Rva00604A68 { public: ~Rva00604A68(); };
class Rva004102A4 { public: ~Rva004102A4(); };
class Rva004E84A4 { public: ~Rva004E84A4(); };
class Rva0040C39E { public: ~Rva0040C39E(); };
class Rva0040FB4A { public: ~Rva0040FB4A(); };
class Rva0044455C { public: ~Rva0044455C(); };
class Rva004AF17D { public: ~Rva004AF17D(); };
class Rva004BAEC8 { public: ~Rva004BAEC8(); };
class Rva00557CCC { public: ~Rva00557CCC(); };
class Rva006022CA { public: ~Rva006022CA(); };

void operator delete(void *p);

void Rva002BEDA4_DeleteAnchor(Rva002BEDA4 *p) { delete p; }
void Rva00419B8D_DeleteAnchor(Rva00419B8D *p) { delete p; }
void Rva004318D8_DeleteAnchor(Rva004318D8 *p) { delete p; }
void Rva0057571C_DeleteAnchor(Rva0057571C *p) { delete p; }
void Rva005CF86B_DeleteAnchor(Rva005CF86B *p) { delete p; }
void Rva005E57C9_DeleteAnchor(Rva005E57C9 *p) { delete p; }
void Rva005EA2AB_DeleteAnchor(Rva005EA2AB *p) { delete p; }
void Rva00604A68_DeleteAnchor(Rva00604A68 *p) { delete p; }
void Rva004102A4_DeleteAnchor(Rva004102A4 *p) { delete p; }
void Rva004E84A4_DeleteAnchor(Rva004E84A4 *p) { delete p; }
void Rva0040C39E_DeleteAnchor(Rva0040C39E *p) { delete p; }
void Rva0040FB4A_DeleteAnchor(Rva0040FB4A *p) { delete p; }
void Rva0044455C_DeleteAnchor(Rva0044455C *p) { delete p; }
void Rva004AF17D_DeleteAnchor(Rva004AF17D *p) { delete p; }
void Rva004BAEC8_DeleteAnchor(Rva004BAEC8 *p) { delete p; }
void Rva00557CCC_DeleteAnchor(Rva00557CCC *p) { delete p; }
void Rva006022CA_DeleteAnchor(Rva006022CA *p) { delete p; }
