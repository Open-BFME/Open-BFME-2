// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /arch:SSE
// stlport
// ?rva005386B7@Rva005386B7@@QAEXPAU1@@Z, retail 0x005386B7, 62 bytes.
// Swap holder via rowed vector swap 0x00567ECD plus rowed Region swap 0x0030B31A plus float and byte swaps.
// Evidence: chain from 0x0030B31A; caller 0x0030C164; prev fill_n float4 next erase pod16 both vector /O1.
struct BfmeE12 { float x, y, z; };
namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void *m_start;
	void *m_finish;
	void *m_end;
	void swap(vector &);
};
}
struct Region2D
{
	Region2D(const Region2D &that);
	~Region2D() {}
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
void __cdecl Rva0030B31ASwap(Region2D *a, Region2D *b);

struct Rva005386B7
{
	void rva005386B7(Rva005386B7 *other);
	_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec;
	Region2D m_region;
	float m_1c;
	unsigned char m_20;
};

void Rva005386B7::rva005386B7(Rva005386B7 *other)
{
	m_vec.swap(other->m_vec);
	Rva0030B31ASwap(&m_region, &other->m_region);
	{
		float &a = m_1c;
		float &b = other->m_1c;
		float t = a;
		a = b;
		b = t;
	}
	{
		unsigned char &a = m_20;
		unsigned char &b = other->m_20;
		unsigned char t = a;
		a = b;
		b = t;
	}
}
