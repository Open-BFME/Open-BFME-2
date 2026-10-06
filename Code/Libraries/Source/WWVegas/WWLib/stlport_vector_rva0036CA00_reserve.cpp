// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?reserve@?$vector@VRva0036CA00Str@@V?$allocator@VRva0036CA00Str@@@_STL@@@_STL@@QAEXI@Z @0x00239ED8 104B
// vector<Rva0036CA00Str>::reserve. Same 104B shape as Ascii reserve 0x00057E02 and
// Unicode reserve 0x0005A27E. Calls allocate_and_copy 0x00239408 and _M_clear via
// 0x00057DE4 plus folded allocator 0x00068E15. Caller 0x0023B990. Chain from 0x00239408.
#include <vector>

class Rva0036CA00Str
{
public:
    Rva0036CA00Str();
    Rva0036CA00Str(const Rva0036CA00Str &);
    ~Rva0036CA00Str();
    Rva0036CA00Str &operator=(const Rva0036CA00Str &);
private:
    void *m_data;
};

namespace _STL {
template <> void _Construct<Rva0036CA00Str, Rva0036CA00Str>(Rva0036CA00Str *, const Rva0036CA00Str &);
template <> void _Destroy<Rva0036CA00Str *>(Rva0036CA00Str *, Rva0036CA00Str *);
}

template <>
void _STL::vector<Rva0036CA00Str, _STL::allocator<Rva0036CA00Str> >::reserve(size_type __n)
{
  if (capacity() < __n) {
    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, (pointer)this->_M_start, (pointer)this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}
