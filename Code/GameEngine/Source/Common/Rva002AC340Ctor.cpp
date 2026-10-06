// cl: /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002AC340@@QAE@XZ @0x002AC340 (32B): opaque ctor with int at +4 and BfmeE16 vector at +8.
// Evidence: stores vtable 0x007FDD6C at +0 via gate DIR32; zeroes +4 via AND; calls rowed Vector_base BfmeE16 0x00211E58 for +8; caller at 0x002B1093; pattern matches Rva0022DE6B ctor.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva002AC340
{
public:
	Rva002AC340();
protected:
	virtual ~Rva002AC340();
private:
	int m_int;
	_STL::vector<BfmeE16> m_vec;
};

Rva002AC340::Rva002AC340() : m_int(0), m_vec()
{
}
