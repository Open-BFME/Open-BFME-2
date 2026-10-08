// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /Oy- /DNDEBUG /MD /GX- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022CA45@@QAE@XZ @0x0022CA45 (47B): frameless ctor running
// baseConstruct() over this, then the own vtable, then two outlined
// _Vector_base<BfmeE16> member inits at +0xC/+0x18; returns this.
// Follows precedent Rva00221088Ctor: a __declspec(novtable) head lets the
// inlined base ctor's call precede the derived vtable store. Members use a
// TU-local minimal _Vector_base view so the member inits emit the outlined
// 0x00211E58 ctor (the header-inline body folds to zero stores); /GX- keeps
// the TU frameless. Evidence: vtable VA 0x00BE25B4; address-derived.
struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

namespace _STL
{
	template <class T>
	class allocator
	{
	public:
		allocator() {}
	};

	// TU-local minimal view of the rowed _Vector_base<BfmeE16> instantiation:
	// start/finish/end-of-storage plus the outlined ctor at 0x00211E58.
	// Declared, never defined here, so the member inits below emit the
	// outlined call (the header-inline body would fold to zero stores).
	template <class T, class A>
	struct _Vector_base
	{
		void *m_start;
		void *m_finish;
		void *m_endOfStorage;
		_Vector_base(const A &alloc);
	};
}

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

// Precedent Rva00221088Ctor: novtable head whose inlined ctor runs
// baseConstruct() over this, so the call precedes the own vtable store.
class __declspec(novtable) Rva0022CA45Base
{
public:
	__forceinline Rva0022CA45Base() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~Rva0022CA45Base() {}
private:
	char m_flag;
	int m_value;
};

class Rva0022CA45 : public Rva0022CA45Base
{
public:
	virtual void rva_vtable_anchor() {}
	Rva0022CA45();
private:
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vecA;
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_vecB;
};

Rva0022CA45::Rva0022CA45() : m_vecA(_STL::allocator<BfmeE16>()), m_vecB(_STL::allocator<BfmeE16>()) {}
