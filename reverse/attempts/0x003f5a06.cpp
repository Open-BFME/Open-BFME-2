// ?rva003F5A06@Rva003F5A06@@QAEXIVRva0040E3EE@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F5A06@Rva003F5A06@@QAEXIVRva0040E3EE@@@Z @0x003F5A06 108B
// Evidence: caller 0x003F5C4F builds Rva0040E3EE temp and int; callees erase 0x003B908A and _M_fill_insert 0x003F53DA; dtor 0x0040E499; resize shape (erase vs fill_insert).

struct BfmeAssignRecord104
{
	int a[26];
};

struct Rva003F53DAElement
{
	char bytes[104];
};

class Rva0040E3EE
{
public:
	Rva0040E3EE();
	virtual ~Rva0040E3EE();
	char _pad[100];
};

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc>
class vector
{
};

template <>
class vector<BfmeAssignRecord104, allocator<BfmeAssignRecord104> >
{
public:
	BfmeAssignRecord104 *_M_start;
	BfmeAssignRecord104 *_M_finish;
	BfmeAssignRecord104 *_M_end_of_storage;
	BfmeAssignRecord104 *erase(BfmeAssignRecord104 *first, BfmeAssignRecord104 *last);
};

template <>
class vector<Rva003F53DAElement, allocator<Rva003F53DAElement> >
{
public:
	Rva003F53DAElement *_M_start;
	Rva003F53DAElement *_M_finish;
	Rva003F53DAElement *_M_end_of_storage;
	void _M_fill_insert(Rva003F53DAElement *pos, unsigned int n, const Rva003F53DAElement &x);
};
}

class Rva003F5A06
{
public:
	Rva0040E3EE *_M_start;
	Rva0040E3EE *_M_finish;
	Rva0040E3EE *_M_end_of_storage;
	Rva0040E3EE *begin() { return _M_start; }
	Rva0040E3EE *end() { return _M_finish; }
	unsigned int size() { return (unsigned int)(_M_finish - _M_start); }
	void rva003F5A06(unsigned int n, Rva0040E3EE val);
};

void Rva003F5A06::rva003F5A06(unsigned int n, Rva0040E3EE val)
{
	Rva0040E3EE *begin = _M_start;
	Rva0040E3EE *end = _M_finish;
	unsigned int sz = (unsigned int)(end - begin);
	if (n < sz)
	{
		typedef _STL::vector<BfmeAssignRecord104, _STL::allocator<BfmeAssignRecord104> > VecA;
		VecA *self = (VecA *)this;
		self->erase((BfmeAssignRecord104 *)(begin + n), (BfmeAssignRecord104 *)end);
	}
	else
	{
		typedef _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> > VecB;
		VecB *self = (VecB *)this;
		Rva003F53DAElement *fresh = self->_M_finish;
		unsigned int cur = (unsigned int)((Rva0040E3EE *)fresh - begin);
		unsigned int count = n - cur;
		self->_M_fill_insert(fresh, count, (const Rva003F53DAElement &)val);
	}
}
