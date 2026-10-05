// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00317F6F@@QAE@XZ @0x00317F6F 129B: ctor storing vtable 0x0080C66C, clearing two AsciiString members, defaulting two vector<ScienceType> members, pushing SCIENCE_NONE into the first, zeroing flag bytes plus0C plus1C and dword plus20. Evidence: rowed Vector_base plus releaseBuffer plus push_back callees plus vtable store; class identity unproven so honest-address name.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

#include "ascii_string.h"
class Rva00317F6F {
public:
  virtual ~Rva00317F6F();
  Rva00317F6F();
private:
  AsciiString m_a;
  AsciiString m_b;
  unsigned char m_f0c;
  _STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v1;
  unsigned char m_f1c;
  int m_i20;
  _STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v2;
};
Rva00317F6F::Rva00317F6F()
{
  m_a.clear();
  m_b.clear();
  ScienceType st = SCIENCE_NONE;
  m_f0c = 0;
  m_v1.push_back(st);
  m_i20 = 0;
  m_f1c = 0;
}
