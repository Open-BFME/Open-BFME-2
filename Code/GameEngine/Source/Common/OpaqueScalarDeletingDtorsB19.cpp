// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Target74104C is the79B destructor called by the existing28B deleting
// wrapper7410D0. Native stores primaryCF1648 and secondaryCF1644 vptrs;
// destroys StringBase<char> at64 through full133B36410 and its secondary
// base at8 through full111B5248D0; finally restores primary C3962C.
// The secondary provider consumes58 bytes; the primary consumed prefix is8.
// Model only this68B consumed prefix; factory74109B allocates80 bytes, so
// neither full size nor the original owner/payload identity is asserted.
// Primary base table C3962C has an existing verified provider; it is not
// the canonical Snapshot table. Its force-inline restoration adds no row.
struct EmitVtableTag;
extern "C" const void *const __identifier("??_7Rva0045EF90Base@@6B@")[];
class __declspec(novtable) Rva0074104CBase {
public:
 // ?Rva0074104CBase::~Rva0074104CBase present-unmatched
 // LINK: the implicit default ctor's COMDAT loses to the first-in-order copy; the vtable
 // emitter ctor below calls a TU-unique no-init ctor instead. No flags touched.
 struct BfmeNoInitB19 {};
 Rva0074104CBase(BfmeNoInitB19) {}
 Rva0074104CBase() {}
 virtual __forceinline ~Rva0074104CBase() {*(const void**)this=__identifier("??_7Rva0045EF90Base@@6B@");}
private: unsigned int unknown04;
};
class __declspec(novtable) Rva005248D0 {
public: Rva005248D0(); virtual ~Rva005248D0();
private: unsigned char opaque[0x54];
};
// The canonical frozen StringBase replaces the private copy; the switches make
// its default ctor and dtor reachable and declare the narrow dtor out of line.
#define BFME_STRINGBASE_PUBLIC_DEFAULT_CTOR
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"
class Rva0074104C : public Rva0074104CBase, public Rva005248D0 {
public: Rva0074104C(); Rva0074104C(EmitVtableTag*); virtual ~Rva0074104C();
private:
 unsigned int unknown60;
 StringBase<char> str64;
 unsigned char unmodelled68[0x18]; // retail factory allocates 0x80 bytes; fields beyond the consumed prefix are unknown.
};
Rva0074104C::~Rva0074104C() {}

// Target name is address-derived. The /O1 BFME 1 Q4 niladic factory is a
// unique 53-byte placement here; target relocations call operator new(0x80)
// and the constructor at 0x00740FD9. The constructor's vtable references and
// the adjacent destructor rows tie that call to this target class. The donor
// class name and source-side identity are not carried over.
Rva0074104C *makeRva0074104C()
{
	return new Rva0074104C;
}

// ?<Rva0074104C::Rva0074104C> absent-from-retail
Rva0074104C::Rva0074104C(EmitVtableTag *) : Rva0074104CBase((Rva0074104CBase::BfmeNoInitB19()))
{
}
