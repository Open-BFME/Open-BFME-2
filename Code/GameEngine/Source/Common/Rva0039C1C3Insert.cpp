// cl: /Oy-

// ?rva0039C1C3@Rva0039C1C3@@QAEXPAVRva0039B893@@ABV2@ABU__false_type@_STL@@I_N@Z @0x0039C1C3 186B
// Vector fill-insert realloc path: len = old + max(old,n), allocate, copy [start,pos),
// single copy-ctor or fill_n, maybe copy [pos,finish), tidy old, publish start/finish/end.
// Evidence: chain lane (calls 0x0039B8D8 just landed), callers 0x0039C2AB (pushes 1,1,tag,pos,finish)
// and 0x0039C4EB, callees rowed allocate 0x00395960 uninit-copy 0x0039BA22 fill_n 0x0039B8D8
// copy-ctor 0x0039B893 tidy 0x00565A42, stride 0x14, ret 0x14.

struct BfmeStringRecord002CF4C6;
namespace _STL
{
struct __false_type
{
};
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
}

class Rva0039B893
{
public:
	Rva0039B893(const Rva0039B893 &other);
	virtual ~Rva0039B893();
	int m_field04;
	int m_field08;
	short m_field0C;
	short m_field0E;
	short m_field10;
};

#pragma optimize("y", on)
inline void *__cdecl operator new(unsigned int, void *p) { return p; }
#pragma optimize("", on)

Rva0039B893 *__cdecl Rva0039BA22UninitCopy(Rva0039B893 *first, Rva0039B893 *last, Rva0039B893 *result, const _STL::__false_type &);
Rva0039B893 *__cdecl Rva0039B8D8FillN(Rva0039B893 *first, unsigned int n, const Rva0039B893 &value, const _STL::__false_type &);

class Rva00565A42
{
public:
	void rva00565A42();
	Rva0039B893 *m_00;
	Rva0039B893 *m_04;
};

class Rva0039C1C3
{
public:
	void rva0039C1C3(Rva0039B893 *pos, const Rva0039B893 &x, const _STL::__false_type &, unsigned int n, bool at_end);
	void rva0039C27D(Rva0039B893 *x);
private:
	Rva0039B893 *m_start;
	Rva0039B893 *m_finish;
	union
	{
		_STL::allocator<BfmeStringRecord002CF4C6> m_alloc;
		Rva0039B893 *m_end;
	};
};

void Rva0039C1C3::rva0039C1C3(Rva0039B893 *pos, const Rva0039B893 &x, const _STL::__false_type &, unsigned int n, bool at_end)
{
	unsigned int old_size = (unsigned int)(m_finish - m_start);
	const unsigned int &maxv = old_size < n ? n : old_size;
	unsigned int len = old_size + maxv;
	Rva0039B893 *new_start = (Rva0039B893 *)m_alloc.allocate(len, 0);
	Rva0039B893 *new_finish = Rva0039BA22UninitCopy(m_start, pos, new_start, *(const _STL::__false_type *)((char *)&at_end + 3));
	if (n == 1)
	{
		if (new_finish != 0)
			new (new_finish) Rva0039B893(x);
		++new_finish;
	}
	else
	{
		new_finish = Rva0039B8D8FillN(new_finish, n, x, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	if (!at_end)
	{
		new_finish = Rva0039BA22UninitCopy(pos, m_finish, new_finish, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	((Rva00565A42 *)this)->rva00565A42();
	Rva0039B893 *new_end = new_start + len;
	m_start = new_start;
	m_finish = new_finish;
	m_end = new_end;
}

// ?rva0039C27D@Rva0039C1C3@@QAEXPAVRva0039B893@@@Z @0x0039C27D 56B
// Vector push-back single element: if room copy-construct in place and grow finish,
// else overflow via 0x0039C1C3 with n=1 at_end=1. Evidence: chain lane (calls 0x0039C1C3
// just landed), caller 0x0039C5B8, callees rowed copy-ctor 0x0039B893 overflow 0x0039C1C3,
// stride 0x14, ret 4, null-guarded copy-ctor.

void Rva0039C1C3::rva0039C27D(Rva0039B893 *x)
{
	if (m_finish != m_end)
	{
		if (m_finish != 0)
			new (m_finish) Rva0039B893(*x);
		m_finish++;
	}
	else
	{
		rva0039C1C3(m_finish, *x, *(const _STL::__false_type *)((char *)&x + 3), 1, true);
	}
}
