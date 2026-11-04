// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva005965A5@@QAE@XZ, retail 0x005965A5, 33 bytes.
// Calls base ctor 0x0025BFC7 and ScienceType vector-base ctor 0x00211E58.
// Register at 0x00596635 pushes the object's ScienceType at +0x74 into
// this +0x10 vector; destructor 0x005965C6 uses the same typed range erase.
// The folded empty-storage initializer alone does not identify the element.
enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
	template <class T> class allocator
	{
	public:
		allocator() {}
	};

	// Storage-only view. The rowed STLport base constructor initializes the
	// three pointers without allocating; Rva005965A5 owns erase and free.
	template <class T, class A> class _Vector_base
	{
	public:
		_Vector_base(const A &allocator) throw();
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};

	template <class T, class A = allocator<T> > class vector : public _Vector_base<T, A>
	{
	public:
		vector(const A &allocator = A()) : _Vector_base<T, A>(allocator) {}
		T *erase(T *first, T *last);
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }
		void clear() { erase(begin(), end()); }
	};
}

class Rva0025BFE3
{
public:
	Rva0025BFE3();
	virtual ~Rva0025BFE3();
private:
	char m_pad04[0x10 - 4];
};

class Rva005965A5 : public Rva0025BFE3
{
public:
	Rva005965A5();
	virtual ~Rva005965A5();

private:
	_STL::vector<ScienceType> m_sciences; // +0x10
};

Rva005965A5::Rva005965A5() : Rva0025BFE3(), m_sciences()
{
}
