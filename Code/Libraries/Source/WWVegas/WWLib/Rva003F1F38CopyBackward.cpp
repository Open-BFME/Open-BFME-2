// cl: /DNDEBUG /MD
// ?Rva003F1F38CopyBackward@@YAPADPAD00@Z @0x003F1F38 50B:
// counted copy-backward stride 12 via rowed vector uint assign 0x0026F4F4;
// (last-first)/12 with idiv then counted loop decrementing last/result
// before each assign. Callers 0x003F24D6. Dedicated TU so the call stays
// external. Sibling of Rva003F1F06Copy 0x003F1F06 (forward direction).
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
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > Rva003F1F38Vec;
char *__cdecl Rva003F1F38CopyBackward(char *first, char *last, char *result)
{
	int n = (last - first) / 12;
	if (n <= 0)
		return result;
	for (; n != 0; --n)
	{
		last -= 12;
		result -= 12;
		*reinterpret_cast<Rva003F1F38Vec *>(result) = *reinterpret_cast<Rva003F1F38Vec *>(last);
	}
	return result;
}
