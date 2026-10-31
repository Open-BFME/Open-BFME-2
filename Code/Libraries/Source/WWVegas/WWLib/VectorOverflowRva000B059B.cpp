// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x000B059B, 183B; Ghidra boundary, ret14 ABI and 28-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// Native placement-copy and range-destruction calls identify these existing
// helper owners. The opaque element spelling stays local; no new identity
// or layout is claimed for the record. Bind its helper calls to those owners.
struct BfmeStringRecord00111ACF;
struct EvaMessageInfo;
class Rva000B0298
{
public:
	void rva000B0298();
private:
	EvaMessageInfo *m_00; // +0x00
	EvaMessageInfo *m_04; // +0x04
};
namespace _STL { template<> void _Construct<BfmeStringRecord00111ACF,BfmeStringRecord00111ACF>(BfmeStringRecord00111ACF*,const BfmeStringRecord00111ACF&); }

struct Rva000B059BRecord {
 Rva000B059BRecord(); Rva000B059BRecord(const Rva000B059BRecord&); ~Rva000B059BRecord(); Rva000B059BRecord&operator=(const Rva000B059BRecord&);
private: char bytes[28];
};
// Keep the native B0298 clear as an external owner; re-emitting it after
// inlining the element destructor would produce a different destroy loop.
namespace _STL {
template<> __declspec(dllimport) __forceinline void vector<Rva000B059BRecord>::_M_clear()
{ reinterpret_cast<Rva000B0298*>(this)->rva000B0298(); }
template<> __declspec(dllimport) __forceinline void _Construct<Rva000B059BRecord,Rva000B059BRecord>(Rva000B059BRecord*p,const Rva000B059BRecord&v)
{ _Construct(reinterpret_cast<BfmeStringRecord00111ACF*>(p),reinterpret_cast<const BfmeStringRecord00111ACF&>(v)); }
}
template void _STL::vector<Rva000B059BRecord>::_M_insert_overflow(Rva000B059BRecord*,const Rva000B059BRecord&,const _STL::__false_type&,unsigned int,bool);
