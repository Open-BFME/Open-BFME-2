// ?swap@Rva003B56A5@@QAEXPAV1@@Z
// partial score=0.97 date=2026-09-26
// Banked near-miss for ?swap@Rva003B56A5@@QAEXPAV1@@Z at 0x003B56A5
// (55B): two 12B vectors swapped through rowed vector<UBfmeE12>::swap
// (0x00567ECD) plus two int swaps. Best shape (GenV2 two-temp) is 55/55B
// with identical head and registers; sole diff is scheduler order in the
// int tail: retail completes the first int (store other.first) before
// loading other.second, ours hoists the second load above that store.
// Refuted: single-temp this/other-first, mixed temp forms, struct-pair
// swap, hoisted temps, volatile members, /Os /O2 /Ob1 /G6 /G7, temp reuse.
// Real-vector .swap() proven out-of-line (no pin needed for the callees).
// Next ideas: force S2-before-L3 via a dependency the scheduler honors,
// or find the true member class (its ctor 0x3B761E / dtors 0x3B7167 and
// 0x3B766B may reveal a different member model).

// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct BfmeE12 { float x, y, z; };

class Rva003B56A5
{
public:
	void swap(Rva003B56A5 *other);

private:
	_STL::vector<BfmeE12> m_a;			// +0x00
	_STL::vector<BfmeE12> m_b;			// +0x0C
	int m_first;						// +0x18
	int m_second;						// +0x1C
};

void Rva003B56A5::swap(Rva003B56A5 *other)
{
	m_a.swap(other->m_a);
	m_b.swap(other->m_b);
	int first = other->m_first;
	int mine = m_first;
	m_first = first;
	other->m_first = mine;
	int second = other->m_second;
	int mine2 = m_second;
	m_second = second;
	other->m_second = mine2;
}
