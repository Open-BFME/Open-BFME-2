// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD
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
extern "C" const void *const vtbl_00C3962C[];
#pragma comment(linker, "/alternatename:_vtbl_00C3962C=??_7Rva0045EF90Base@@6B@")
class __declspec(novtable) Rva0074104CBase {
public:
 // ?Rva0074104CBase::~Rva0074104CBase present-unmatched
 virtual __forceinline ~Rva0074104CBase() {*(const void**)this=vtbl_00C3962C;}
private: unsigned int unknown04;
};
class __declspec(novtable) Rva005248D0 {
public: Rva005248D0(); virtual ~Rva005248D0();
private: unsigned char opaque[0x54];
};
template<class T> class StringBase {public: ~StringBase();private: void* data;};
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
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
Rva0074104C::Rva0074104C(EmitVtableTag *)
{
}
