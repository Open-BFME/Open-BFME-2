// cl: /O1 /Oy- /G7
//
// ?rva004EE6D0@Rva004EE6D0@@QAEXPAUElem003AF8C0@@ABU2@ABU__false_type@_STL@@I_N@Z
// retail 0x004EE6D0, 186 bytes.
// Masked-identical to the landed 0x0039C1C3 insert path except stride 0x0C
// (three sites). Helpers already rowed: allocate 0x00395928, uninit-copy
// 0x004EE1E2, copy-ctor 0x004EE1A9, fill_n 0x004EE20B, tidy 0x004EE540.

struct BfmeE12;
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

struct Elem003AF8C0
{
	Elem003AF8C0(const Elem003AF8C0 &other);
	char m_pad[0xC];
};

typedef char Elem003AF8C0SizeCheck[sizeof(Elem003AF8C0) == 0xC ? 1 : -1];

#pragma optimize("y", on)
inline void *__cdecl operator new(unsigned int, void *p) { return p; }
#pragma optimize("", on)

Elem003AF8C0 *__cdecl Rva004EE1E2UninitCopy(Elem003AF8C0 *first, Elem003AF8C0 *last, Elem003AF8C0 *result, const _STL::__false_type &);
Elem003AF8C0 *__cdecl Rva004EE20BFillN(Elem003AF8C0 *first, unsigned int n, const Elem003AF8C0 &value, const _STL::__false_type &);

class Rva004EE540
{
public:
	void rva004EE540();
	Elem003AF8C0 *m_00;
	Elem003AF8C0 *m_04;
};

class Rva004EE6D0
{
public:
	void rva004EE6D0(Elem003AF8C0 *pos, const Elem003AF8C0 &x, const _STL::__false_type &, unsigned int n, bool at_end);

private:
	Elem003AF8C0 *m_start;
	Elem003AF8C0 *m_finish;
	union
	{
		_STL::allocator<BfmeE12> m_alloc;
		Elem003AF8C0 *m_end;
	};
};

void Rva004EE6D0::rva004EE6D0(Elem003AF8C0 *pos, const Elem003AF8C0 &x, const _STL::__false_type &, unsigned int n, bool at_end)
{
	unsigned int old_size = (unsigned int)(m_finish - m_start);
	const unsigned int &maxv = old_size < n ? n : old_size;
	unsigned int len = old_size + maxv;
	Elem003AF8C0 *new_start = (Elem003AF8C0 *)m_alloc.allocate(len, 0);
	Elem003AF8C0 *new_finish = Rva004EE1E2UninitCopy(m_start, pos, new_start, *(const _STL::__false_type *)((char *)&at_end + 3));
	if (n == 1)
	{
		if (new_finish != 0)
			new (new_finish) Elem003AF8C0(x);
		++new_finish;
	}
	else
	{
		new_finish = Rva004EE20BFillN(new_finish, n, x, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	if (!at_end)
	{
		new_finish = Rva004EE1E2UninitCopy(pos, m_finish, new_finish, *(const _STL::__false_type *)((char *)&at_end + 3));
	}
	((Rva004EE540 *)this)->rva004EE540();
	Elem003AF8C0 *new_end = new_start + len;
	m_start = new_start;
	m_finish = new_finish;
	m_end = new_end;
}
