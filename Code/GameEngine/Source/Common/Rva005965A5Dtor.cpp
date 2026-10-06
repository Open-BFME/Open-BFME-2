// cl: /O1 /MD /EHs
// ??1Rva005965A5@@UAE@XZ retail 0x005965C6 83B
// Own vptr C70A54; under EH state 0 the 4-byte-element vector at +0x10 is
// emptied through the rowed range erase 0x00532803 (folded STLport
// vector<ScienceType>::erase) and its block freed with the CRT free; then the
// rowed base dtor ??1Rva0025BFE3@@UAE@XZ 0x0025BFE3 runs. The element size
// follows from the folded erase (4-byte enum stride), not the ctor's view in
// Rva005965A5Ctor.cpp. Names address-derived.

extern "C" void __cdecl free(void *block);

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
	template <class T> class allocator
	{
	};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *erase(T *first, T *last);
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }
		void clear() { erase(begin(), end()); }

		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};
}

class Rva0025BFE3
{
public:
	virtual ~Rva0025BFE3();
private:
	char m_pad04[0x10 - 4];
};

class Rva005965A5 : public Rva0025BFE3
{
public:
	virtual ~Rva005965A5();

private:
	_STL::vector<ScienceType> m_sciences; // +0x10
};

Rva005965A5::~Rva005965A5()
{
	m_sciences.clear();
	if (m_sciences._M_start)
		free(m_sciences._M_start);
}
