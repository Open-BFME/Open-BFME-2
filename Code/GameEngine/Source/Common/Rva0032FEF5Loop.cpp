// cl: /O1 /EHsc /MD
// stlport
// ?rva0032FEF5@Rva0032FEF5@@QAEXXZ, retail 0x0032FEF5, 83 bytes.
// Loop calling pinned 2-arg helper 0x0032FC70 with index and a temp inner
// vector; temp constructed via rowed _Vector_base<BfmeE16> ctor and destroyed
// via rowed ??1Rva0032D279 dtor (same pattern as matched 0x0032FF48 wrapper).
// Evidence: __EH_prolog with mov/or [ebp-4] states, xor edi loop over
// [esi+0x3c], lea/push temp plus index with mov ecx,esi call, tail dtor call.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

struct Rva0019D850Value
{
	int m_words[3];
};

class Rva0032D279 : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
// ??0Rva0032D279@@QAE@XZ present-unmatched
	Rva0032D279() : _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()) {}
	~Rva0032D279();
};

class Rva0032FEF5 : public _STL::vector<_STL::vector<Rva0019D850Value> >
{
	int m_pad[12];
	int m_count;
public:
	void rva0032FEF5();
};

void Rva0032FEF5::rva0032FEF5()
{
	Rva0032D279 tmp;
	for (int i = 0; i < m_count; ++i)
		this->resize(i, reinterpret_cast<const _STL::vector<Rva0019D850Value> &>(tmp));
}
