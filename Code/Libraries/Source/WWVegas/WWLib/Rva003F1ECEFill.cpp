// cl: /DNDEBUG /MD
// ?Rva003F1ECEFill@@YAXPAD00@Z @0x003F1ECE 29B:
// range fill stride 12 via rowed vector uint assign 0x0026F4F4 (pinned true
// name); while (first != last) assign *value into *first and advance by 12.
// Callers 0x003F366A 0x003F36AA in 0x003F35E3. Sibling of Rva003F1F06Copy
// 0x003F1F06 (counted copy) and Rva003F1F38CopyBackward. Dedicated TU so the
// call stays external.
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
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > Rva003F1ECEVec;
void __cdecl Rva003F1ECEFill(char *first, char *last, char *value)
{
	for (; first != last; first += 12)
		*reinterpret_cast<Rva003F1ECEVec *>(first) = *reinterpret_cast<Rva003F1ECEVec *>(value);
}
