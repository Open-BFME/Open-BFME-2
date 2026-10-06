// cl: /DNDEBUG /MD
// ?rva00319F5A@Rva00319F5A@@QAEXPAVRva00318B5C@@ABV2@HI_N@Z @0x00319F5A 180B via vector reallocate with Rva copy fill
// Evidence: unlock lane caller 0x0031A156; sibling copy fill at 0x00318D75 0x00318D9B share Rva00318B5C 0x10 stride and __false_type tag; rowed allocate and pin _M_clear; three pointers at +0/+4/+8

class Rva00319F5A;
struct BfmeE16
{
	char _m[16];
};
struct BfmeVectorRecord00319C84
{
	char _m[16];
};
class Rva00318B5C
{
	char _m[16];
public:
	Rva00318B5C(const Rva00318B5C &that);
};
namespace _STL
{
	struct __false_type
	{
	};
	template <class T> class allocator
	{
	public:
		T *allocate(unsigned n, const void *hint) const;
	};
	template <class T, class A> class vector
	{
	protected:
		void _M_clear();
		friend class ::Rva00319F5A;
	};
}
void Rva00318D63Copy(Rva00318B5C *dest, const Rva00318B5C &src);
Rva00318B5C *Rva00318D75Copy(Rva00318B5C *first, Rva00318B5C *last, Rva00318B5C *result, const _STL::__false_type &tag);
Rva00318B5C *Rva00318D9BFill(Rva00318B5C *first, unsigned n, const Rva00318B5C &x, const _STL::__false_type &tag);
class Rva00319F5A
{
public:
	void rva00319F5A(Rva00318B5C *pos, const Rva00318B5C &x, int dummy, unsigned n, bool flag);
	void rva0031A129(const Rva00318B5C &x);
private:
	Rva00318B5C *m_begin;
	Rva00318B5C *m_end;
	union
	{
		_STL::allocator<BfmeE16> m_alloc;
		Rva00318B5C *m_endStorage;
	};
};

void Rva00319F5A::rva00319F5A(Rva00318B5C *pos, const Rva00318B5C &x, int dummy, unsigned n, bool flag)
{
	int sz = (int)(((char *)m_end - (char *)m_begin) >> 4);
	int szCopy = sz;
	int *p = (int *)&n;
	if ((unsigned)sz >= n)
		p = &szCopy;
	int max = *p;
	int newCap = max + sz;
	BfmeE16 *newBuf = m_alloc.allocate((unsigned)newCap, 0);
	const _STL::__false_type &tag = *(const _STL::__false_type *)((char *)&flag + 3);
	Rva00318B5C *cur = Rva00318D75Copy(m_begin, pos, (Rva00318B5C *)newBuf, tag);
	(void)dummy;
	if (n == 1) {
		Rva00318D63Copy(cur, x);
		++cur;
	} else {
		cur = Rva00318D9BFill(cur, n, x, tag);
	}
	if (!flag) {
		cur = Rva00318D75Copy(pos, m_end, cur, tag);
	}
	((_STL::vector<BfmeVectorRecord00319C84, _STL::allocator<BfmeVectorRecord00319C84> > *)this)->_M_clear();
	m_begin = (Rva00318B5C *)newBuf;
	m_end = cur;
	m_endStorage = (Rva00318B5C *)((char *)newBuf + (newCap << 4));
}
void Rva00319F5A::rva0031A129(const Rva00318B5C &x)
{
	if (m_end != m_endStorage) {
		Rva00318D63Copy(m_end, x);
		m_end = (Rva00318B5C *)((char *)m_end + 16);
	}
	else {
		_STL::__false_type tag;
		rva00319F5A(m_end, x, (int)&tag, 1, true);
	}
}
