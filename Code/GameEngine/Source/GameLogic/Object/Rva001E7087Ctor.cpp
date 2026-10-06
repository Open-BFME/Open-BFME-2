// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001E7087@@QAE@XZ retail 0x001E7087 53B: ctor stores vtable 0x007DE950 plus vector BfmeE16 at +4 via 0x00211E58 plus zero members plus float 0.
// Evidence: push ecx push esi mov esi ecx lea esp+7 push allocator call 0x00211E58 Vector_base BfmeE16 then xorps xor eax movs plus movss float 0 at +0x20; vtable g_00BDE950 at +0; callers 0x002642EE 0x0026EA4F 0x0033A5C5 0x00377164 0x004DA3FA.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva001E7087
{
public:
	Rva001E7087();
protected:
	virtual ~Rva001E7087();
private:
	_STL::vector<BfmeE16> m_vec04;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
	int m_18;
	int m_1c;
	float m_20;
};
Rva001E7087::Rva001E7087()
	: m_vec04(_STL::allocator<BfmeE16>()), m_10(0), m_14(0), m_15(0), m_18(0), m_1c(0), m_20(0.0f)
{
}
