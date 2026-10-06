// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00317F6F@@UAE@XZ, retail 0x00317FF0, 93 bytes.
// Dtor storing vtable 0x0080C66C, destroying vector of pairs at +0x24 via
// rowed 0x00317E7C, freeing vector storage at +0x10 via game _free,
// releasing two AsciiString members at +4/+8 via releaseBuffer.
// Evidence: vtable store plus rowed vector dtor plus _free plus releaseBuffer
// callees; class from rowed ctor 0x00317F6F in Rva00317F6FCtor.cpp.
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

#include "ascii_string.h"
struct Rva00317E7C
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva00317E7C();
};
class Rva00317F6F {
public:
  virtual ~Rva00317F6F();
private:
  AsciiString m_a;
  AsciiString m_b;
  unsigned char m_f0c;
  _STL::vector<ScienceType, _STL::allocator<ScienceType> > m_v1;
  unsigned char m_f1c;
  int m_i20;
  Rva00317E7C m_v2;
};

Rva00317F6F::~Rva00317F6F()
{
}
