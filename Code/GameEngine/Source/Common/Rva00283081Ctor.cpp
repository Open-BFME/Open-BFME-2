// cl: /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??0Rva00283081@@QAE@MH@Z, RVA 0x004DFC59, 59 bytes.
// Ctor twin of dtor 0x00283081/0x004DFED8: vstore vtable RVA 0x008615D4,
// constructs two vectors at +0x4 and +0x10 via rowed Vector_base<BfmeE16>
// 0x00211E58, stores float arg at +0x1c and dword arg at +0x20.
// Evidence: same vtable and vector layout as Rva00283081Dtor/Rva004DFED8Dtor;
// callees all rowed; callers 0x0028415C 0x004E0407.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva00283081
{
public:
	Rva00283081(float f, int i);
	virtual ~Rva00283081();
private:
	_STL::vector<BfmeE16> m_vec4;
	_STL::vector<BfmeE16> m_vec10;
	float m_f1c;
	int m_i20;
};

Rva00283081::Rva00283081(float f, int i) : m_f1c(f), m_i20(i)
{
}
