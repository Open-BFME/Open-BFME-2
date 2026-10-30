// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0030B76F@Rva0030B76F@@QAEXPAU1@@Z, retail 0x0030B76F, 78 bytes.
// Swap holder via rowed vector swap 0x00567ECD plus rowed Region2D swap 0x0030B31A plus float and byte swaps.
// Evidence: chain from 0x0030B31A; caller 0x0030B81B; prev copy-backward next reserve both vector e8 /O1 /EHsc.
#include <vector>
#include "../../../Libraries/Include/Lib/Region2D.h"
struct BfmeE12 { float x, y, z; };
// Bind the holder swap to the rowed vector<BfmeE12>::swap 0x00567ECD instead
// of emitting this unit's own copy of the header's inline definition.
namespace _STL
{
template <class T, class A> class vector;
template <> void vector<BfmeE12, allocator<BfmeE12> >::swap(vector<BfmeE12, allocator<BfmeE12> > &);
}
void __cdecl Rva0030B31ASwap(Region2D *a, Region2D *b);

struct Rva0030B76F
{
public:
	void rva0030B76F(Rva0030B76F *other);
	_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec; // +0x00
	Region2D m_region; // +0x0C
	float m_1c; // +0x1C
	float m_20; // +0x20
	unsigned char m_24; // +0x24
	char m_pad25[0x3];
};

void Rva0030B76F::rva0030B76F(Rva0030B76F *other)
{
	m_vec.swap(other->m_vec);
	Rva0030B31ASwap(&m_region, &other->m_region);
	float t1 = m_1c;
	m_1c = other->m_1c;
	other->m_1c = t1;
	{
		float &a = m_20;
		float &b = other->m_20;
		float t = a;
		a = b;
		b = t;
	}
	{
		unsigned char &a = m_24;
		unsigned char &b = other->m_24;
		unsigned char t = a;
		a = b;
		b = t;
	}
}
