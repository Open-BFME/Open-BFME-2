// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FAC21 ctor @0x004FAC21 46B: derived of Rva004FA830 plus vector
// at +8 plus int 10 at +0x14. Retail forwards its single StringBase arg to
// the rowed base ctor 0x004FA815 then constructs the vector via rowed
// _Vector_base 0x00211E58 then stores 10. Vtable 0x008633B0. Layout read
// from retail lea ecx,[esi+8] and store [esi+0x14].
#include <vector>

template <typename T> class StringBase
{
	friend class Rva004FA830;
	StringBase(const StringBase<T> &other);
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
};

class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &s);

private:
	StringBase<char> m_s;
};

struct BfmeE16
{
	float x, y, z, w;
};

class Rva004FAC21 : public Rva004FA830
{
public:
	Rva004FAC21(const StringBase<char> &s);

private:
	_STL::vector<BfmeE16> m_v;
	int m_x;
};

Rva004FAC21::Rva004FAC21(const StringBase<char> &s) : Rva004FA830(s), m_v(), m_x(10)
{
}
