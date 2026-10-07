// cl: /MD
// ?rva005388F7@QuadStrip2D@@QAEAAV1@ABV1@@Z @0x005388F7 53B
// Holder copy-assign via rowed vector<BfmePod16> assign then flag and conditional region copy.
// Evidence: callee 0x00538782 row vector<BfmePod16> assign; prev 0x005388C2 holder copy same layout region+flag; next 0x00538A0B holder load same layout.
struct BfmePod16 { int a[4]; };
struct BfmeFloat4Record00469C61 { float x; float y; float z; float w; };
struct Region2D
{
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
namespace _STL {
template <class T> class allocator
{
public:
	allocator();
};
template <class T, class Alloc> class vector
{
public:
	vector &operator=(const vector &other);
	void push_back(const T &x);
	T *erase(T *pos);
	T *begin() { return m_start; }
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
class QuadStrip2D
{
public:
	QuadStrip2D &rva005388F7(const QuadStrip2D &other);
	void rva005389D9(const BfmeFloat4Record00469C61 &x);
	void rva00538768(int index);
private:
	_STL::vector<BfmePod16, _STL::allocator<BfmePod16> > m_vec;
	Region2D m_region;
	float m_1c;
	unsigned char m_20;
};
QuadStrip2D &QuadStrip2D::rva005388F7(const QuadStrip2D &other)
{
	m_vec = other.m_vec;
	m_20 = other.m_20;
	if (other.m_20 != 0) {
		m_region = other.m_region;
		m_1c = other.m_1c;
	}
	return *this;
}

void QuadStrip2D::rva005389D9(const BfmeFloat4Record00469C61 &x)
{
	((_STL::vector<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> > *)&m_vec)->push_back(x);
	m_20 = 1;
}

// ?rva00538768@QuadStrip2D@@QAEXH@Z @0x00538768 (26B).
// Gap between rowed vector<BfmePod16> erase 0x00538739 and assign 0x00538782;
// erases m_start+index (16B stride) through the rowed erase then sets m_20=1,
// the same vector-op-plus-flag shape as rva005389D9 above. Caller 0x0030BC53
// passes the QuadStrip2D at +0x68 and refreshes through vtable slot 0x28.
void QuadStrip2D::rva00538768(int index)
{
	m_vec.erase(m_vec.begin() + index);
	m_20 = 1;
}
