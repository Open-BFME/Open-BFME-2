// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva001DC0EC@@QAE@XZ @0x001DC0C7 37B. Ctor adjacent to dtor 0x001DC0EC
// for the same class: list<int> at +0 via rowed _List_base ctor 0x004EC36C
// then int at +4 =1 int at +8 =0 AsciiString data at +0xC =0 bool at +0x10 =0.
// Evidence: contiguous bytes 0x001DC0C7+37=0x001DC0EC and dtor TU layout
// list at +0 string at +0xC. Honest class reuse.
#include <list>

class Rva001DC0EC
{
public:
	Rva001DC0EC();
private:
	_STL::list<int, _STL::allocator<int> > m_list;
	int m_04;
	int m_08;
	int m_0C;
	bool m_10;
};

Rva001DC0EC::Rva001DC0EC()
{
	m_0C = 0;
	m_08 = 0;
	m_10 = false;
	m_04 = 1;
}
