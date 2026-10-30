// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /I. /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x003F318C is vector<Rva003F318CRecord>::operator= (STLport 4.5.3 _vector.c:90) over the
// 24-byte LivingWorldRegionConnection elements (Rva003F3F27 assigns +0x1A8 from +0x60). Its
// five callees are rowed under other spellings: 0x003F2CD6
// vector<BfmeStringRecord000B9534>::_M_allocate_and_copy<LivingWorldRegionConnection*>
// (Rva003F2CD6.cpp), 0x00565A24 ConnectionVec::Rva00565A24_ScrapStorage (_M_clear),
// 0x003F325A Rva003F325ACopy (__copy_ptrs), 0x003F0CA1 Rva003F0CA1_DestroyRange (_Destroy) and
// 0x003F29D2 Rva003F29D2_CopyRange (__uninitialized_copy); the last three live in
// LivingWorldRegionConnectionHelpers.cpp / Rva003F325ACopy.cpp. Instantiating operator= from
// <vector> emitted those helpers again over the record and left its dtor, operator= and
// _Construct unresolved, so this unit spells only the vector shape it needs (as
// Rva00569F0CAssign.cpp does) and calls the rows by their own types. Retail passes the two
// copy helpers their __false_type tag as a fourth argument, so those are called through
// tag-taking casts (Rva003F325ACopy.cpp's pattern). Calling a declared-only specialization
// of the real <vector> member template ICEs cl 7.1 (C1001 in P2), hence the stub.
struct Rva003F318CRecord { char bytes[24]; };
struct BfmeStringRecord000B9534 { char m_body[24]; };
class LivingWorldRegionConnection;
class Rva003F2A11;

namespace _STL {
struct __false_type { __false_type() {} };
template <class T> class allocator {};
template <class T, class A> class vector
{
public:
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef unsigned int size_type;
	size_type size() const { return size_type(_M_finish - _M_start); }
	size_type capacity() const { return size_type(_M_end_of_storage - _M_start); }
	vector &operator=(const vector &x);
protected:
	template <class I> T *_M_allocate_and_copy(size_type n, I first, I last);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

struct ConnectionVec { void Rva00565A24_ScrapStorage(); };
Rva003F2A11 *Rva003F325ACopy(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *);
LivingWorldRegionConnection *Rva003F29D2_CopyRange(LivingWorldRegionConnection *, LivingWorldRegionConnection *, LivingWorldRegionConnection *);
void Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *, LivingWorldRegionConnection *);
typedef Rva003F2A11 *(__cdecl *Rva003F325ACopyTagFn)(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *, const _STL::__false_type &);
typedef LivingWorldRegionConnection *(__cdecl *Rva003F29D2CopyTagFn)(LivingWorldRegionConnection *, LivingWorldRegionConnection *, LivingWorldRegionConnection *, const _STL::__false_type &);

// _M_allocate_and_copy is protected; reach the rowed 0x003F2CD6 member through a derived view.
struct Rva003F318CAllocate : _STL::vector<BfmeStringRecord000B9534, _STL::allocator<BfmeStringRecord000B9534> >
{
	BfmeStringRecord000B9534 *call(unsigned int count, LivingWorldRegionConnection *first, LivingWorldRegionConnection *last)
	{
		return _M_allocate_and_copy(count, first, last);
	}
};

namespace _STL {
template <>
vector<Rva003F318CRecord, allocator<Rva003F318CRecord> > &
vector<Rva003F318CRecord, allocator<Rva003F318CRecord> >::operator=(const vector<Rva003F318CRecord, allocator<Rva003F318CRecord> > &__x)
{
	if (&__x != this) {
		const size_type __xlen = __x.size();
		if (__xlen > capacity()) {
			pointer __tmp = (pointer)((Rva003F318CAllocate *)this)->call(__xlen,
				(LivingWorldRegionConnection *)__x._M_start, (LivingWorldRegionConnection *)__x._M_finish);
			((ConnectionVec *)this)->Rva00565A24_ScrapStorage();
			_M_start = __tmp;
			_M_end_of_storage = _M_start + __xlen;
		}
		else if (size() >= __xlen) {
			pointer __i = (pointer)((Rva003F325ACopyTagFn)&Rva003F325ACopy)((Rva003F2A11 *)__x._M_start,
				(Rva003F2A11 *)__x._M_finish, (Rva003F2A11 *)_M_start, __false_type());
			Rva003F0CA1_DestroyRange((LivingWorldRegionConnection *)__i, (LivingWorldRegionConnection *)_M_finish);
		}
		else {
			((Rva003F325ACopyTagFn)&Rva003F325ACopy)((Rva003F2A11 *)__x._M_start,
				(Rva003F2A11 *)(__x._M_start + size()), (Rva003F2A11 *)_M_start, __false_type());
			((Rva003F29D2CopyTagFn)&Rva003F29D2_CopyRange)((LivingWorldRegionConnection *)(__x._M_start + size()),
				(LivingWorldRegionConnection *)__x._M_finish, (LivingWorldRegionConnection *)_M_finish, __false_type());
		}
		_M_finish = _M_start + __xlen;
	}
	return *this;
}
}
