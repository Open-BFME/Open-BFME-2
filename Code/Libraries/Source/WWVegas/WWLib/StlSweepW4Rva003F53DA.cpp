// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<ArmySummary>::_M_fill_insert (0x003F53DA) and the insert(pos, n, x)
// forwarder that tail-jumps to it (0x003F5724). The element is ArmySummary:
// the body copies its value through the ArmySummary copy constructor
// (0x0040E96D) and destroys the copy through ~ArmySummary (0x0040E499); its
// fill (0x003F4146) assigns through ArmySummary::operator= (0x0040EAED); the
// resize at 0x003F5A06 and swap<ArmySummary> (0x003F40EF) reach the same
// members. The overflow path is vector<ArmySummary>::_M_insert_overflow
// (0x003B9184), rowed in StlportVectorInsertOverflowFamily.cpp. This unit
// uses /Ob1 so the placement-copy helper retains its complete native EH body.
// The two small wrappers below stay out of line, preserving the 258-byte
// fill-insert schedule. The overflow definition remains visible because its
// empty-tag analysis affects the caller's native stack slots.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// Only the members the vector operations reach are declared; the 0x64 bytes
// after the vptr give the retail 0x68 stride.
class ArmySummary
{
public:
	ArmySummary(const ArmySummary &);
	virtual ~ArmySummary();
	ArmySummary &operator=(const ArmySummary &);

private:
	char m_fields[0x64];
};

// Native placement copy retains its complete EH cleanup frame.
namespace _STL {
template <> inline __declspec(noinline)
void _Construct<ArmySummary, ArmySummary>(ArmySummary *destination, const ArmySummary &value)
{ ::new ((void *)destination) ArmySummary(value); }
template <> inline __declspec(noinline)
ArmySummary *__copy_backward_ptrs<ArmySummary *, ArmySummary *>(ArmySummary *first, ArmySummary *last, ArmySummary *result, const __false_type &)
{ return __copy_backward(first, last, result, random_access_iterator_tag(), (int *)0); }
template <> inline __declspec(noinline)
ArmySummary *uninitialized_fill_n<ArmySummary *, unsigned int, ArmySummary>(ArmySummary *first, unsigned int count, const ArmySummary &value)
{ return __uninitialized_fill_n(first, count, value, __false_type()); }
}

// The overflow copy's storage call binds the proxy allocate that
// StlportVectorInsertOverflowFamily.cpp emits beside the retail overflow, so
// the two units do not keep different copies of that unaddressed helper.
namespace _STL {
template <> ArmySummary *_STLP_alloc_proxy<ArmySummary *, ArmySummary, allocator<ArmySummary> >::allocate(size_t);
}

template void _STL::vector<ArmySummary, _STL::allocator<ArmySummary> >::_M_fill_insert(ArmySummary *, unsigned int, const ArmySummary &);
template void _STL::vector<ArmySummary, _STL::allocator<ArmySummary> >::insert(ArmySummary *, unsigned int, const ArmySummary &);
