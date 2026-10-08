// cl: /MD
// ?rva00423D0DCreate@@YGHPAXH@Z @0x00423D0D 34B (name TBD, free stdcall)
// The callees are the rowed STLport allocator<char>::allocate and
// _Construct<Rva00423648Element>.
struct Rva00423648Element;
namespace _STL
{
template <class T> class allocator
{
public:
	static T *allocate(unsigned int n, const void *hint);
};
template <class T1, class T2> void _Construct(T1 *p, const T2 &value);
}
void *__stdcall rva00423D0DCreate(int a)
{
	void *blk = _STL::allocator<char>::allocate(0x14, 0);
	_STL::_Construct<Rva00423648Element, Rva00423648Element>((Rva00423648Element *)((char *)blk + 8), *(const Rva00423648Element *)a);
	return blk;
}
