// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva002F3738@Rva002F3738@@QAEXPAPAX@Z @0x002F3738 33B
// Thiscall, one pointer-to-pointer argument, ret 4: push_back of the 4-byte
// record at the argument into the vector at +0, then std::make_heap over
// [begin, end) with the one-byte empty comparator stored at +0xC. Follows
// 0x002F370D (43B) in PathfinderRva002F36E5.cpp; the heap instance is the
// rowed StlSweep make_heap at 0x002F0D35 with the same opaque record.
#include <algorithm>
#include <functional>
#include <vector>

struct Rva002F0D35Record
{
	void *m_value;
	bool operator<(const Rva002F0D35Record &) const;
};

class Rva002F3738
{
public:
	void rva002F3738(void **value);
private:
	_STL::vector<Rva002F0D35Record> m_vec;
	_STL::less<Rva002F0D35Record> m_less;
};

void Rva002F3738::rva002F3738(void **value)
{
	m_vec.push_back(*reinterpret_cast<Rva002F0D35Record *>(value));
	_STL::make_heap(m_vec.begin(), m_vec.end(), m_less);
}
