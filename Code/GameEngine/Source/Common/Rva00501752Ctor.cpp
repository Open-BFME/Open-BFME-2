// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00501776@@QAE@XZ @0x00501752 36B: ctor constructing vectors at +0x14/+0x20 via rowed Vector_base 0x00211E58; evidence same offsets as dtor 0x00501776 and caller 0x00503A28
#include <vector>

struct BfmeE16 { float x; float y; float z; float w; };

struct Rva005011DA
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva005011DA();
};

struct Rva00501776
{
	char m_pad[0x14];
	_STL::vector<BfmeE16> m_a;
	_STL::vector<BfmeE16> m_b;
	Rva00501776();
};

Rva00501776::Rva00501776()
{
}
