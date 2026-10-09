// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DBFME_ASCII_DTOR_DECL /EHsc /MD
// Native005C39DE..005C39EB is a 13B three-word zero constructor.
// Native005C39EB..005C3A37 is a complete 76B EH destructor: counted
// words0/8 use the rowed7DEEF release; owning word4 uses rowed AD6F4.
// Native005C3A37..005C3A86 is a complete79B parent destructor, using
// vector-dtor iterator629110 with stride12/count3 at+20 then the rowed
// command-map-adder52413E at+C and AsciiString36410 at+8.
// Original identities remain neutral. These layout/lifetime facts come
// from target bytes and callback references, independent of donor names.
#include "ascii_string.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005C39DERef {
 TargetRef00217D4C *ptr;
 Rva005C39DERef():ptr(0) {}
 ~Rva005C39DERef() { if(ptr) ReleaseTreeHintRef00217D4C(ptr); }
};
class Rva000AD6F4 {
public:
 void *ptr;
 Rva000AD6F4():ptr(0) {}
 ~Rva000AD6F4();
};
class Rva005C39DEMember {
public:
 ~Rva005C39DEMember();
private:
 Rva005C39DERef first;
 Rva000AD6F4 middle;
 Rva005C39DERef last;
};
Rva005C39DEMember::~Rva005C39DEMember() {}
class AptCommandMapAdder {
 char unknown00[0x14];
public:
 ~AptCommandMapAdder();
};
class Rva005C3A37Elem {
 char unknown00[8];
 AsciiString name;
 AptCommandMapAdder commands;
 Rva005C39DEMember members[3];
 char unknown44[4];
public:
 ~Rva005C3A37Elem();
};
Rva005C3A37Elem::~Rva005C3A37Elem() {}
