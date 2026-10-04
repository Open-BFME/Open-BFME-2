// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00153A7BFill@@YAXPAVRva001539BC@@0ABV1@@Z retail 0x00153A7B 29 bytes.
// Fill range with value via rowed 0x001539BC rva assign.
// Callers 0x00153DE5 0x00153E25 in 0x00153D5E.
// Identity honest address free function.
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
void __cdecl Rva00153A7BFill(class Rva001539BC *first, class Rva001539BC *last, const class Rva001539BC &value)
{
	for (; first != last; ++first)
		first->rva001539BC(value);
}
