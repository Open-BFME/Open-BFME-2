// cl: /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0050492F@Rva0050492F@@QAEXPAU1@@Z 0x0050492F 117B evidence: unlock swap via rowed vector BfmeE12 swap 0x00567ECD; caller 0x00504E52 unblocks 0x00504E38; siblings Rva005386B7Swap Rva0030B76FSwap same flags
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
struct Rva0050492F
{
	void rva0050492F(Rva0050492F *other);
	int m_0;
	int m_4;
	_STL::vector<BfmeE12, _STL::allocator<BfmeE12> > m_vec;
	int m_14;
	int m_18;
	float m_1c;
	float m_20;
	float m_24;
	float m_28;
};
void Rva0050492F::rva0050492F(Rva0050492F *other)
{
	{
		int &lhs = m_0;
		int &rhs = other->m_0;
		int t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		int &lhs = m_4;
		int &rhs = other->m_4;
		int t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		int &lhs = m_18;
		int &rhs = other->m_18;
		int t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		float &lhs = m_1c;
		float &rhs = other->m_1c;
		float t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		float &lhs = m_20;
		float &rhs = other->m_20;
		float t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		float &lhs = m_24;
		float &rhs = other->m_24;
		float t = lhs;
		lhs = rhs;
		rhs = t;
	}
	{
		float &lhs = m_28;
		float &rhs = other->m_28;
		float t = lhs;
		lhs = rhs;
		rhs = t;
	}
	m_vec.swap(other->m_vec);
}
