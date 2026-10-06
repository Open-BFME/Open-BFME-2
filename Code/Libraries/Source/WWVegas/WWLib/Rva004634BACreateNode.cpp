// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva004634BACreate@@YGPAURva004634BANode@@ABVRva0046267A@@@Z 0x004634BA 34B
// _Rb_tree<Rva0046267A> create_node: alloc 0x60 via rowed byte allocator 0x307F0
// then rowed _Construct<Rva0046267A> 0x462D83 at +0x10; returns node.
// Evidence: sole callees 0x307F0 plus 0x462D83 both rowed; callers at 0x4637DF
// plus 0x4637F8 in 0x4637B7; size 0x60 equals base 0x10 plus 0x50 Rva0046267A.
class Rva0046267A
{
public:
	Rva0046267A(const Rva0046267A &other);
};

struct Rva004634BANode
{
	char _head[0x10];
	Rva0046267A _val;
};

namespace _STL
{
template <class _Tp>
class allocator;
template <>
class allocator<char>
{
public:
	static char *allocate(unsigned int n, const void *hint);
};
template <class _T1, class _T2>
void _Construct(_T1 *p, const _T2 &value);
}

struct Rva004634BANode *__stdcall Rva004634BACreate(const class Rva0046267A &x)
{
	char *mem = _STL::allocator<char>::allocate(0x60, 0);
	_STL::_Construct((class Rva0046267A *)(mem + 0x10), x);
	return (struct Rva004634BANode *)mem;
}
