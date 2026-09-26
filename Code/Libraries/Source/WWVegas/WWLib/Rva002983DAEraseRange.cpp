// cl: /O1 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Range-erase over the stride-0x10 Rva00297360Element vector at retail
// 0x002983DA (51B): copy [last, finish) down to first through the rowed
// Rva002915EBCopyRange, destroy the vacated tail [newFinish, finish) through
// the rowed range _Destroy, store the new finish and return first. /Oy-
// keeps the ebp frame retail uses to address its params; the copy-range
// dummy arrives as pop-slot address [ebp+0xb].
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

Rva00297360Element *Rva002915EBCopyRange(Rva00297360Element *first, Rva00297360Element *last, Rva00297360Element *result, int dummy);

class Rva002983DAVector {
public:
  Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);
private:
  int m_00;
  Rva00297360Element *m_finish;
  int m_08;
};

Rva00297360Element *Rva002983DAVector::EraseRange(Rva00297360Element *first, Rva00297360Element *last)
{
  Rva00297360Element *newFinish = Rva002915EBCopyRange(last, m_finish, first, (int)((char*)&first + 3));
  _STL::_Destroy(newFinish, m_finish);
  m_finish = newFinish;
  return first;
}
