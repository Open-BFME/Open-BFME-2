// ?rva003F2106@Rva003F2106@@QAEXXZ
// partial score=0.82 date=2026-10-05
// ?rva003F2106@Rva003F2106@@QAEXXZ
// cl: /O1 /DNDEBUG /MD /GX-
// ?rva003F2106@Rva003F2106@@QAEXXZ @0x003F2106 74B:
// __thiscall clearer over the void* vector at +0x170: for each element,
// virtual slot-0 call with 0 then operator delete on the result, then
// rowed voidptr erase 0x0031BD55 over the range. Callers 0x003F276F
// 0x003F2AD3 0x003F2B01 0x003F3375 0x003F3D23 0x003F3F43.
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
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *begin() { return m_start; }
	T *end() { return m_finish; }
	unsigned int size() { return ((char *)m_finish - (char *)m_start) >> 2; }
	T **erase(T *first, T *last);
};
}
struct Rva003F2106Elem
{
	virtual void *rva003F2106Elem(int flag);
};
void __cdecl operator delete(void *block);
class Rva003F2106
{
public:
	void rva003F2106();
private:
	char m_pad[0x170];
	_STL::vector<void *, _STL::allocator<void *> > m_vec170;
};
// ?rva003F2106@Rva003F2106@@QAEXXZ present-unmatched
void Rva003F2106::rva003F2106()
{
	_STL::vector<void *, _STL::allocator<void *> > *vec = &m_vec170;
	for (unsigned int i = 0; i < vec->size(); ++i)
	{
		void *p = vec->begin()[i];
		void *q = 0;
		if (p != 0)
			q = ((Rva003F2106Elem *)p)->rva003F2106Elem(0);
		operator delete(q);
	}
	vec->erase(vec->begin(), vec->end());
}
