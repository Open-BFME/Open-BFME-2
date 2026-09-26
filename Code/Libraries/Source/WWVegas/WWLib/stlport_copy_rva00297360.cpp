// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Assign-copy chain for Rva00297360Element (stride-0x10 element with an
// AsciiString at +4): the random-access __copy loop at retail 0x0028F869
// (47B, count via sar 4, per-element copy through the rowed operator=) and
// the Rva-named range-forwarding wrapper at retail 0x002915EB (29B, tag temp
// plus null distance). The wrapper spells the __copy_aux<false> forwarding
// explicitly because MSVC 7.1 drops the unreferenced inline template even
// under explicit instantiation; the body is byte-identical either way.
#include <algorithm>

class AsciiString {
public:
  AsciiString() {}
  AsciiString &operator=(const AsciiString &other);
private:
  void *m_data;
};

class Rva00297360Element {
public:
  ~Rva00297360Element();
  Rva00297360Element &operator=(const Rva00297360Element &other);
private:
  int m_00;
  AsciiString m_04;
  int m_08;
  int m_0C;
};

template Rva00297360Element *_STL::__copy<Rva00297360Element*, Rva00297360Element*, int>(Rva00297360Element*, Rva00297360Element*, Rva00297360Element*, const _STL::random_access_iterator_tag&, int*);

Rva00297360Element *Rva002915EBCopyRange(Rva00297360Element *first, Rva00297360Element *last, Rva00297360Element *result, int dummy)
{
  _STL::random_access_iterator_tag tag;
  (void)dummy;
  return _STL::__copy(first, last, result, tag, (int*)0);
}
