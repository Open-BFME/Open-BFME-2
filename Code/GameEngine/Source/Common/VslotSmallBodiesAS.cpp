// cl: /MD
// Scalar deleting destructors that retail reaches only through vtable slots,
// so caller-based discovery never served them. All six share the 28B shape
// (dtor call, flags byte test, conditional scalar delete through pinned
// ??3@YAXPAX@Z 0x0002FD60, return this), same recipe as
// VslotSmallBodiesAR.cpp. Each dtor is declared but not defined here and
// resolves through an address-derived pin in reverse/symbols.csv read from the
// wrapper's own REL32 at +4; every retail site calls it directly, so the dtors
// are non-virtual here. Emitted via delete anchors that are never called.
// Owner identities and layouts are not recovered; class names are the dtor
// addresses. 0x003B241A is already rowed under its own forwarder view
// (Rva003B241AForwarder.cpp), so its owner here takes a distinct name.
//  0x0044BE69 via dtor 0x0044BE85   0x005D6C78 via dtor 0x005D63CB
//  0x005EB079 via dtor 0x005EB095   0x0041E6F3 via dtor 0x003B241A
//  0x004E186D via dtor 0x004E1416
//  0x005D10BA via dtor 0x005D10D6
// The recovered virtual 0x005B4A46 destructor and its 0x005B4C7B wrapper
// now live together in Rva005B4A46Dtor.cpp.

class Rva0044BE85 { public: ~Rva0044BE85(); };
class Rva005D63CB { public: ~Rva005D63CB(); };
class Rva005EB095 { public: ~Rva005EB095(); };
class Rva003B241AOwner { public: ~Rva003B241AOwner(); };
class Rva004E1416 { public: ~Rva004E1416(); };
class Rva005D10D6 { public: ~Rva005D10D6(); };

void operator delete(void *p);

void Rva0044BE85_DeleteAnchor(Rva0044BE85 *p) { delete p; }
void Rva005D63CB_DeleteAnchor(Rva005D63CB *p) { delete p; }
void Rva005EB095_DeleteAnchor(Rva005EB095 *p) { delete p; }
void Rva003B241AOwner_DeleteAnchor(Rva003B241AOwner *p) { delete p; }
void Rva004E1416_DeleteAnchor(Rva004E1416 *p) { delete p; }
void Rva005D10D6_DeleteAnchor(Rva005D10D6 *p) { delete p; }
