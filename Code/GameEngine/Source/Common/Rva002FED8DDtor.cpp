// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva002FED8D@@UAE@XZ @0x002FEDEC 64B virtual dtor via vptr plus List_base AsciiString plus releaseBuffer
// Evidence: vtable 0x00807408; List_base dtor 0x002FECBC; releaseBuffer 0x00036410; caller deleting dtor 0x002FFCEA; ctor sibling Rva002FED8DCtor same flags.
#include <list>
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};
#include "ascii_string.h"
class Rva002FED8D
{
public:
	virtual ~Rva002FED8D();
private:
	AsciiString m_name;
	int m_val8;
	_STL::list<AsciiString> m_list;
	int m_val10;
};
Rva002FED8D::~Rva002FED8D()
{
	m_val10 = 0;
}
