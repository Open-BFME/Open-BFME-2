// cl: /DNDEBUG /MD
// ?Rva003F1F06Copy@@YAPADPAD00@Z @0x003F1F06 50B:
// counted copy stride 12 via rowed vector uint assign 0x0026F4F4;
// (last-first)/12 with idiv then counted loop calling assign per element.
// Callers 0x003F2460. Dedicated TU so the call stays external.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A = allocator<T> > class vector
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
	vector &operator=(const vector &that);
};
}
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > Rva003F1F06Vec;
char *__cdecl Rva003F1F06Copy(char *first, char *last, char *result)
{
	int n = (last - first) / 12;
	if (n <= 0)
		return result;
	for (; n != 0; --n, first += 12, result += 12)
		*reinterpret_cast<Rva003F1F06Vec *>(result) = *reinterpret_cast<Rva003F1F06Vec *>(first);
	return result;
}
