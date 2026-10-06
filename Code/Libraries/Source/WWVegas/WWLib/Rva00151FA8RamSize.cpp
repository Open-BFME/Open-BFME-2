// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00151FA8@Rva00151FA8@@QBEHXZ @ 0x00151FA8 (34B).
// Honest address-named const RAM-size getter called once from MeshMatDescClass::Compute_Ram_Size
// at 0x0015CC4D for ShaderArray elements (sibling call at 0x0015CB9A/0x0015CBEC is VertexMaterial
// 0x0013D250 for MaterialArray). Layout is two _STL::vectors: 0x24-byte elements at +0x0C and
// 8-byte elements at +0x28, base 0x2834. Proven by byte-exact schedule: /G7 gives the retail
// imul tail, and the accumulating source shape keeps the second load late in edx.
#include <vector>

struct Rva00151FA8Elem36
{
	char m_bytes[0x24];
};

struct Rva00151FA8Elem8
{
	char m_bytes[8];
};

class Rva00151FA8
{
public:
	int rva00151FA8() const;

private:
	char m_pad00[0x0C];
	_STL::vector<Rva00151FA8Elem36> m_vec0C;
	char m_pad18[0x28 - 0x18];
	_STL::vector<Rva00151FA8Elem8> m_vec28;
};

int Rva00151FA8::rva00151FA8() const
{
	int a = m_vec0C.size() * sizeof(Rva00151FA8Elem36);
	a += 0x2834;
	return a + m_vec28.size() * sizeof(Rva00151FA8Elem8);
}
