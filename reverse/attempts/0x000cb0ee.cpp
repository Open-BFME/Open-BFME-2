// ?rva000CB0EE@Rva000CB0EEPointerView@@QBEPAEXZ
// partial score=1.0 date=2026-10-05
// Boundary-review draft only: inferred completeCB0EE/17 between priorRET8
// atCB0EB and next rowed FILD methodCB0FF/4. Internal JECB0F6 reachesCB0FC.
// No independently witnessed parent-entry reference; cannot assert recovery.
// Target raw ABI: receiver word+13C; return its raw byte address+3C if nonzero.
// No original class identity, pointee owner, full extent or lifetime asserted.
// cl: /O1 /Ob1
class Rva000CB0EEPointerView {public:unsigned char *rva000CB0EE() const;private:unsigned char head[0x13C];unsigned char *word;};
unsigned char *Rva000CB0EEPointerView::rva000CB0EE() const {return word ? word+0x3C : 0;}
