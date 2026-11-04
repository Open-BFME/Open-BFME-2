// cl: /MD /D_STLP_USE_STATIC_LIB /EHs
// stlport
// ??0Rva005386F5@@QAE@ABV0@@Z @0x005386F5 68B
// Vector copy ctor via rowed Vector_base E16 size get_allocator AsciiString then Float4Record uninit-copy.
// Evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x005385F3 row Float4Record; caller 0x005388C2 holder copy; prev Rva005386B7Swap same layout.
#include "../../../Libraries/Include/Lib/BfmeE16.h"
struct BfmeFloat4Record00469C61 { float x, y, z, w; };
class AsciiString;
#include <vector>
namespace _STL {
template <> _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(unsigned int, const allocator<BfmeE16> &);
template <> vector<AsciiString, allocator<AsciiString> >::allocator_type vector<AsciiString, allocator<AsciiString> >::get_allocator() const;
// Retail 0x005385F3 only loops through _Construct (0x00469C61) and the
// four-dword copy at 0x0004254E; none can throw. Keep that contract visible
// so this constructor needs no base-destructor unwind when /EHs is enabled.
template <> BfmeFloat4Record00469C61 *__uninitialized_copy(BfmeFloat4Record00469C61 *, BfmeFloat4Record00469C61 *, BfmeFloat4Record00469C61 *, const __false_type &) throw();
}
// A user-constructed empty tag avoids value-initializing a separate byte;
// retail reuses the allocator temporary's stack slot for this argument.
struct VectorCopyTag : _STL::__false_type { VectorCopyTag() {} };

class Rva005386F5 : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva005386F5(const Rva005386F5 &x);
};
Rva005386F5::Rva005386F5(const Rva005386F5 &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x._M_finish - x._M_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	_M_finish = (BfmeE16 *)_STL::__uninitialized_copy((BfmeFloat4Record00469C61 *)x._M_start, (BfmeFloat4Record00469C61 *)x._M_finish, (BfmeFloat4Record00469C61 *)_M_start, VectorCopyTag());
}
