// ?Rva0033DBE5Parse@@YAXPAVINI@@PAX1PBD@Z
// partial score=0.8914459278095642 date=2026-10-10
// ?Rva0033DBE5Parse@@YAXPAVINI@@PAX1PBD@Z
// partial score=0.75 date=2026-10-09
// cl:   /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE
// stlport
#include "ascii_string.h"
#include <set>
class INI { public: const char *getNextToken(const char * = 0); };
class OpaqueRefCounted { public: void Release_Ref(); };
class Rva002390CB {
public:
 Rva002390CB();
 ~Rva002390CB() { if (ref) ref->Release_Ref(); }
 int id; OpaqueRefCounted *ref;
};
struct BfmeStringRecord002CF550 {
 AsciiString text; Rva002390CB sound;
 BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &);
 ~BfmeStringRecord002CF550();
};
struct BfmeStringRecord0033B1DE { AsciiString text; Rva002390CB sound; ~BfmeStringRecord0033B1DE(); };
struct Rva0033B830 : BfmeStringRecord0033B1DE {
 operator const BfmeStringRecord002CF550 &() const { return *(const BfmeStringRecord002CF550 *)this; }
};
Rva0033B830 Rva0033BEF5Make(const StringBase<char> &, const Rva002390CB &);
void Rva00339235(const char *, void *);
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > TreeR;
template <> _STL::pair<TreeR::iterator, bool> TreeR::insert_unique(const TreeR::value_type &);
// ?Rva0033DBE5Parse@@YAXPAVINI@@PAX1PBD@Z
void Rva0033DBE5Parse(INI *ini, void *instance, void *, const char *name) {
 const char *token = ini->getNextToken();
 Rva002390CB sound;
 Rva00339235(token, &sound);
 ((TreeR *)instance)->insert_unique(BfmeStringRecord002CF550(Rva0033BEF5Make(*(const StringBase<char> *)&AsciiString(name), sound)));
}
