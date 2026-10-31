// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva003F53DAElement { Rva003F53DAElement();Rva003F53DAElement(const Rva003F53DAElement&);~Rva003F53DAElement();Rva003F53DAElement&operator=(const Rva003F53DAElement&);char bytes[104]; bool operator<(const Rva003F53DAElement&)const; bool operator==(const Rva003F53DAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> >::_M_fill_insert(Rva003F53DAElement *, unsigned int, Rva003F53DAElement const &);

// Independent native 0x003F5724..0x003F5729 follows the complete
// RemoveArmy RET4 and precedes another body. It forwards the unchanged
// receiver and three arguments to verified fill-insert 0x003F53DA.
// The containing wrapper and application element identity remain unknown.
class Rva003F5724 : public _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> >
{
public:
    void rva003F5724(Rva003F53DAElement *position, unsigned int count, const Rva003F53DAElement &value);
};
void Rva003F5724::rva003F5724(Rva003F53DAElement *position, unsigned int count, const Rva003F53DAElement &value)
{
    _M_fill_insert(position, count, value);
}

// Native ArmySummary instantiations coexist until callers migrate.
class ArmySummary
{
public:
	ArmySummary(const ArmySummary &);
	virtual ~ArmySummary();
	ArmySummary &operator=(const ArmySummary &);

private:
	char m_fields[0x64];
};

// Native copies use the already-owned placement-copy entry at 0x003B8AD8.
// The imported inline adapter preserves that actual call under /Ob0.
struct BfmePod104;
namespace _STL {
template <> void _Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &);
template <> __declspec(dllimport) __forceinline
void _Construct<ArmySummary, ArmySummary>(ArmySummary *destination, const ArmySummary &value)
{ _Construct(reinterpret_cast<BfmePod104 *>(destination), *reinterpret_cast<const BfmePod104 *>(&value)); }
}

// The overflow copy's storage call binds the proxy allocate that
// StlportVectorInsertOverflowFamily.cpp emits beside the retail overflow, so
// the two units do not keep different copies of that unaddressed helper.
namespace _STL {
template <> ArmySummary *_STLP_alloc_proxy<ArmySummary *, ArmySummary, allocator<ArmySummary> >::allocate(size_t);
}

template void _STL::vector<ArmySummary, _STL::allocator<ArmySummary> >::_M_fill_insert(ArmySummary *, unsigned int, const ArmySummary &);
template void _STL::vector<ArmySummary, _STL::allocator<ArmySummary> >::insert(ArmySummary *, unsigned int, const ArmySummary &);
