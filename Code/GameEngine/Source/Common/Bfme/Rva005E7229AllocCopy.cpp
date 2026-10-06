// cl: /DNDEBUG /MD /EHsc
// ?rva005E7229@Rva005E7229@@QAEPAURva005E71C6Ref@@IPAU2@0@Z @0x005E7229 45B
// Vector _M_allocate_and_copy: allocate n via rowed allocator<BfmeE12*> at
// +8 (same 4B POD stride) then rowed __uninitialized_copy<Rva005E71C6Ref>
// 0x005E71DE then return new storage. Caller 0x005E80C7 passes count plus
// start/finish. Same /O1 flags as prev/next Fill/CopyBackward. Evidence:
// chain via 0x005E71DE plus unlock lane plus callers 0x005E80C7.
struct Rva005E71C6Ref { void *m_object; };
struct BfmeE12 { float x, y, z; };
namespace _STL {
template <typename T> class allocator {
public:
  T *allocate(unsigned n, const void *hint) const;
};
struct __false_type {};
template <typename _InputIter, typename _ForwardIter>
_ForwardIter __uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __result, const __false_type &);
template <>
Rva005E71C6Ref *__uninitialized_copy<Rva005E71C6Ref *, Rva005E71C6Ref *>(Rva005E71C6Ref *, Rva005E71C6Ref *, Rva005E71C6Ref *, const __false_type &);
}
class Rva005E7229 {
public:
  Rva005E71C6Ref *rva005E7229(unsigned n, Rva005E71C6Ref *first, Rva005E71C6Ref *last);
private:
  char m_pad[8];
  _STL::allocator<BfmeE12 *> m_alloc;
};
Rva005E71C6Ref *Rva005E7229::rva005E7229(unsigned n, Rva005E71C6Ref *first, Rva005E71C6Ref *last)
{
  BfmeE12 **mem = m_alloc.allocate(n, 0);
  _STL::__false_type f;
  _STL::__uninitialized_copy(first, last, (Rva005E71C6Ref *)mem, f);
  return (Rva005E71C6Ref *)mem;
}
