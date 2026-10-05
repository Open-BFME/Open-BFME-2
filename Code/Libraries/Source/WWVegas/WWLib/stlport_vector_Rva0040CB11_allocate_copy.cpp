// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_M_allocate_and_copy@PBVRva0040CB11Entry@@@?$vector@VRva0040CB11Entry@@V?$allocator@VRva0040CB11Entry@@@_STL@@@_STL@@IAEPAVRva0040CB11Entry@@IPBV2@0@Z, retail 0x0040D077, 45 bytes.
// Vector<Rva0040CB11Entry> allocate-and-copy: allocate N via 0x00523D6C then
// uninitialized_copy range via rowed 0x004F6AD3. Entry is int key plus
// Rva004F6093Holder value matching rowed entry ctor 0x0040CB11 and copy
// 0x004F6335. Same 45B ebp-tag shape as 0x00426B46. Caller at 0x0040E167.
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other);
private:
	void *m_ptr;
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry();
	Rva0040CB11Entry(const Rva0040CB11Entry &other);
private:
	int m_first;
	Rva004F6093Holder m_second;
};

#include <memory>
namespace _STL {
template<> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, const Rva0040CB11Entry &);
}
#include <vector>
template<> void _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::_M_clear();
// STLport 4.5.3 _vector.h at BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db.
// Retail 0x004F8EAF..0x004F8F61: five arguments / ret 0x14; eight-byte
// records copied by 0x004F6AD3, constructed by 0x004F6A64, filled by
// 0x004F6AF9, cleared by 0x004F89F9. Existing entry constructor/copy rows
// establish the int/Holder view; the original application type remains unknown.
// Const source ranges select the already verified copy helper's ABI without
// changing the reference algorithm. The served SubsystemInterface pointer pair
// cannot account for these nontrivial construction and destruction calls.
namespace _STL {
template<> void vector<Rva0040CB11Entry, allocator<Rva0040CB11Entry> >::_M_insert_overflow(
    pointer __position, const Rva0040CB11Entry &__x, const __false_type &,
    size_type __fill_len, bool __atend) {
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    _STLP_TRY {
      __new_finish = __uninitialized_copy((const_pointer)this->_M_start, (const_pointer)__position, __new_start, __false_type());
      // handle insertion
      if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
      } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
      if (!__atend)
        // copy remainder
        __new_finish = __uninitialized_copy((const_pointer)__position, (const_pointer)this->_M_finish, __new_finish, __false_type());
    }
    _STLP_UNWIND((_Destroy(__new_start,__new_finish), 
                  this->_M_end_of_storage.deallocate(__new_start,__len)));
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
  }
}
template Rva0040CB11Entry * _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::_M_allocate_and_copy<const Rva0040CB11Entry *>(size_type, const Rva0040CB11Entry *, const Rva0040CB11Entry *);
template void _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::push_back(const Rva0040CB11Entry &);
