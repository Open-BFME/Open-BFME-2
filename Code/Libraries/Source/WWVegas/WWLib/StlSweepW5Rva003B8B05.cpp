// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<ArmySummary>'s fill helpers: __uninitialized_fill_n (0x003B8B05),
// reached from the overflow 0x003B9184, and the uninitialized_fill_n wrapper
// (0x003F4163), reached from vector<ArmySummary>::_M_fill_insert 0x003F53DA.
// Retail's loop places each element through _Construct 0x003B8AD8, the
// placement copy that calls the ArmySummary copy constructor 0x0040E96D; that
// _Construct is rowed under the BfmePod104 spelling (StlportConstructFamily.cpp),
// so the forwarder below binds it by that name.
#include <algorithm>
#include <memory>

class ArmySummary
{
public:
	ArmySummary(const ArmySummary &);
	virtual ~ArmySummary();

private:
	char m_fields[0x64];
};

struct BfmePod104 { char m_pad[104]; BfmePod104(const BfmePod104 &); ~BfmePod104(); };
namespace _STL {
template <> void _Construct<BfmePod104, BfmePod104>(BfmePod104 *, const BfmePod104 &);
template <> __declspec(dllimport) __forceinline void _Construct<ArmySummary, ArmySummary>(ArmySummary *__p, const ArmySummary &__val)
{ _Construct(reinterpret_cast<BfmePod104 *>(__p), *reinterpret_cast<const BfmePod104 *>(&__val)); }
}

template ArmySummary *_STL::__uninitialized_fill_n<ArmySummary *, unsigned int, ArmySummary>(ArmySummary *, unsigned int, const ArmySummary &, const _STL::__false_type &);

// 0x003F4163 calls this fill through the out-of-line uninitialized_fill_n wrapper
// (three arguments plus the __false_type tag at [ebp-1]).
template ArmySummary *_STL::uninitialized_fill_n<ArmySummary *, unsigned int, ArmySummary>(ArmySummary *, unsigned int, const ArmySummary &);

template BfmePod104 * _STL::__uninitialized_fill_n<BfmePod104 *, unsigned int, BfmePod104>(BfmePod104 *, unsigned int, BfmePod104 const &, _STL::__false_type const &);
template BfmePod104 * _STL::uninitialized_fill_n<BfmePod104 *, unsigned int, BfmePod104>(BfmePod104 *, unsigned int, BfmePod104 const &);
