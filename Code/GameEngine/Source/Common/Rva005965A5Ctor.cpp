// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005965A5@@QAE@XZ, retail 0x005965A5, 33 bytes.
// Derived ctor calling base Rva0025BFE3 ctor at 0x0025BFC7, then vector<BfmeE16>
// at +0x10 via rowed vector_base at 0x00211E58 with stack allocator temp.
// Stores derived vtable 0x00870A54. Layout: base 0x10 bytes, vector 12 bytes.
// Caller at 0x004E03AC constructs this.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();
private:
	_STL::vector<BfmeE16> m_vec04;
};
class Rva005965A5 : public Rva0025BFE3
{
public:
	Rva005965A5();
private:
	_STL::vector<BfmeE16> m_vec10;
};
Rva005965A5::Rva005965A5() : Rva0025BFE3(), m_vec10()
{
}
