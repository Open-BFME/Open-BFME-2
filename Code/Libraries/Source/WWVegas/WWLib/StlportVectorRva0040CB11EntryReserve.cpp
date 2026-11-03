// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva0040CB11Entry>::reserve, retail 0x0040E135 (104 bytes). STLport
// 4.5.3 reserve body over the rowed Rva0040CB11Entry allocate_and_copy and
// allocate; its _M_clear resolves to the Rva004F69C3 _M_clear body ICF
// folded at 0x004F89F9 (pinned as an alias). Built from the banked attempt
// reverse/attempts/0x0040e135.cpp.
#include "../../../../GameEngine/Include/Common/Rva004F6093Holder.h"
class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry();
	Rva0040CB11Entry(const Rva0040CB11Entry &other);
	~Rva0040CB11Entry();
private:
	int m_first;
	Rva004F6093Holder m_second;
};
#include <memory>
namespace _STL {
template<> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, const Rva0040CB11Entry &);
template<> void _Destroy<Rva0040CB11Entry *>(Rva0040CB11Entry *, Rva0040CB11Entry *);
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, Rva0040CB11Entry const &); }
// bfme link decl-only end
template <>
void _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::reserve(size_type __n)
{
  if (capacity() < __n) {
    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, (const_pointer)this->_M_start, (const_pointer)this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}
