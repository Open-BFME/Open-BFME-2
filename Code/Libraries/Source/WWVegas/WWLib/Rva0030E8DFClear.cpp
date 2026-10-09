// cl: /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
namespace _STL {
template<> void vector<float>::_M_fill_insert(float *, size_t, const float &);
template<> vector<void *>::iterator vector<void *>::erase(iterator, iterator);
}

// ?rva0030E8DF@Rva0030E8DF@@QAEXXZ, retail 0x0030E8DF, 44 bytes.
// Clear helper: vector erase via rowed voidptr erase plus zeroing and 1.0f default.
// Evidence: callers at 0x00085947/0x0008D807 operate on subobject at +0x2458;
//   vector at +0x00 clears through rowed erase 0x0031BD55 (ICF pin for RvaVector erase);
//   float at +0x14 defaults to shared 1.0f at 0x00BBB8D8; ints at +0x0C/+0x10/+0x18 and byte at +0x1C zeroed.
struct RvaVector {
	void **m_begin;
	void **m_end;
	void **m_cap;
	void **erase(void **first, void **last);
	void rva0030E910(unsigned n, float value);
};
class Rva0030E8DF {
public:
	void rva0030E8DF();
private:
	RvaVector m_vec; // +0x00
	int m_0c; // +0x0C
	int m_10; // +0x10
	float m_14; // +0x14
	int m_18; // +0x18
	unsigned char m_1c; // +0x1C
};
void Rva0030E8DF::rva0030E8DF()
{
	m_0c = 0;
	m_10 = 0;
	m_18 = 0;
	m_14 = 1.0f;
	m_vec.erase(m_vec.m_begin, m_vec.m_end);
	m_1c = 0;
}

// The native resize uses two independent size reads. The scalar is a 4-byte
// storage view; float selects the observed MOVSS copy, without naming the
// unresolved application element type. BFME1 IntVectorResizeThunk is the
// semantic donor lead; target calls are erase31BD55 and fill30E7FE.
void RvaVector::rva0030E910(unsigned n, float value)
{
	if (n < (unsigned)(m_end - m_begin))
		((_STL::vector<void *> *)this)->erase(m_begin + n, m_end);
	else
		((_STL::vector<float> *)this)->_M_fill_insert(
			(float *)m_end, n - (m_end - m_begin), value);
}
