// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ?swap@Rva003B56A5@@QAEXPAV1@@Z @0x003B56A5 (55B).
// Swaps two 12B vectors through rowed vector<UBfmeE12>::swap 0x00567ECD
// plus two int members. The _ReadWriteBarrier between the int swaps stops
// the scheduler hoisting the second load above the first store; it emits
// no code. Callers: ScriptList::swap plus two INI list bodies.
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
	_ReadWriteBarrier();
	int second = other->m_second;
	int mine2 = m_second;
	m_second = second;
	other->m_second = mine2;
}
