// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva001539ECCopyBackward@@YAPAVRva001539BC@@PAV1@00@Z retail 0x001539EC 50 bytes.
// Backward copy of Rva001539BC array via rowed 0x001539BC rva assign.
// Caller 0x00153A71 in 0x00153A5E; prev 0x001539BC assign next 0x00153A7B fill.
// Identity honest address free function __cdecl 3-pointer copy_backward shape.
struct Rva005F8F96;
namespace _STL
{
template <class T> class allocator;
template <class T, class Alloc> class vector
{
public:
	vector &operator=(const vector &x);
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}
class Rva001539BC
{
public:
	class Rva001539BC &rva001539BC(const class Rva001539BC &other);
private:
	int m_00;
	_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > m_vec[6];
};
class Rva001539BC *__cdecl Rva001539ECCopyBackward(class Rva001539BC *first, class Rva001539BC *last, class Rva001539BC *result)
{
	int n = last - first;
	if (n <= 0)
		return result;
	for (int i = n; i != 0; --i)
	{
		--last;
		--result;
		result->rva001539BC(*last);
	}
	return result;
}
