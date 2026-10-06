// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004EB583@@QAE@H@Z @0x004EB583 102B
// Evidence: unlock ctor stores vtable 0x00862928 at +0; 3x BfmeE16 Vector_base via rowed 0x00211E58 at +8 +0x1C +0x28; ints +4 +0x14 +0x18 +0x34 +0x3C zeroed +0x38 +0x40 -1; id from g_00E044A0 at +0x44 with inc; arg at +0x48; callers 0x004E9AFD 0x004E9CBC.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
extern int g_00E044A0;
// g_00E044A0: matched references place it at VA 0xe044a0 (zero-filled .bss).
int g_00E044A0;
class Rva004EB583
{
public:
	Rva004EB583(int v);
protected:
	virtual ~Rva004EB583();
private:
	int m_04;
	_STL::vector<BfmeE16> m_vec08;
	int m_14;
	int m_18;
	_STL::vector<BfmeE16> m_vec1C;
	_STL::vector<BfmeE16> m_vec28;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
};

Rva004EB583::Rva004EB583(int v)
	: m_04(0), m_vec08(_STL::allocator<BfmeE16>()), m_14(0), m_18(0), m_vec1C(_STL::allocator<BfmeE16>()), m_vec28(_STL::allocator<BfmeE16>()), m_34(0), m_38(-1), m_3C(0), m_40(-1), m_44(g_00E044A0++), m_48(v)
{
}
