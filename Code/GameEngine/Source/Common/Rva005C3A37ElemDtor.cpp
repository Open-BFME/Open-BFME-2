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
struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 TreeHintRef00217D4C(const TreeHintRef00217D4C &);
 TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
 ~TreeHintRef00217D4C() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
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
 void clear();
};
class Rva005C39DEMember {
public:
 ~Rva005C39DEMember();
public:
 Rva005C39DERef first;
 Rva000AD6F4 middle;
 Rva005C39DERef last;
};
Rva005C39DEMember::~Rva005C39DEMember() {}
class AptCommandMapAdder {
public:
 char unknown00[0xC];
public:
 ~AptCommandMapAdder();
};
class Rva005C3DE1Owner { public: virtual void unknown0(); virtual void unknown1(); virtual void finish(); };
class Rva005C3A37Elem {
 Rva005C3DE1Owner *owner;
 void *unknown04;
 AsciiString name;
 AptCommandMapAdder commands;
 bool active;
 char unknown19[3];
 int count;
 Rva005C39DEMember members[3];
 bool pending;
 bool reload;
 char unknown46[2];
public:
 ~Rva005C3A37Elem();
 void rva005C3DE1(int);
 void Add(TreeHintRef00217D4C);
 void rva005C3B3E();
};
Rva005C3A37Elem::~Rva005C3A37Elem() {}

// Native005C3DE1..005C3E31 RET4. Guard44 is cleared before checking18;
// count1C is decremented at least once then the selected12B element's
// holders are cleared in reverse order. Positive remaining count repeats;
// the owner0 virtual slot8 is called after disabling18. Argument is unread.
struct Rva002BED91 { void clear(); };
void Rva005C3A37Elem::rva005C3DE1(int)
{
 if(pending) {
  pending=false;
  if(active) {
   do {
    --count;
    Rva005C39DEMember *member=&members[count];
    reinterpret_cast<Rva002BED91 *>(&member->last)->clear();
    member->middle.clear();
    reinterpret_cast<Rva002BED91 *>(&member->first)->clear();
   } while(count>0);
   active=false;
   owner->finish();
  }
 }
}

