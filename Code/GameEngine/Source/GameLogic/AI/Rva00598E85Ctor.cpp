// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00598B2A@@QAE@PAX@Z, retail 0x00598E85..0x00598F08 (131 bytes, EH,
// ret 4): the constructor AIBuilder's constructor (??0AIBuilder@@QAE@PAVPlayer@@@Z)
// calls with its argument. The destructor owner at 0x00598CFD uses this
// same class: both install vtable VA 0x00C70D2C, and the native AIBuilder
// unwind map destroys the +0x38 member through that destructor. Over the rowed
// Rva00506B1B base (ctor 0x00506B1B) it installs table 0x00C70D2C and builds
// the members through the rowed STLport instantiations each call names: the
// int-keyed map at +0x08 (0x0033C432), the observer list at +0x14 (list base
// 0x004EC36C), the int-keyed hash_map at +0x18 (0x00598E66) and two vectors
// at +0x3C/+0x4C (folded vector base 0x00211E58), each after a -1 word; the
// argument at +0x30 and two flags at +0x2C/+0x34. Element identities are the
// existing address-derived spellings.
#include <map>
#include <list>
#include <hash_map>
#include <vector>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
namespace _STL { template <> inline allocator<void *>::~allocator() _STLP_NOTHROW {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL {
// end() and the fill insert(pos, n, x) are taken inline, as retail's
// hashtable::_M_initialize_buckets does (59 bytes: it reads _M_finish and
// calls the rowed _M_fill_insert); dllimport + forceinline emits no copy.
template <> __declspec(dllimport) __forceinline void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline void vector<void*>::insert(void **pos, size_t n, void *const &x)
{ _M_fill_insert(pos, n, x); }
}
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

struct Rva00501875Count
{
	int m_count;
};

// Bind EH cleanup to the byte-verified count-tree destructor in
// Rva00501875KeyPresence.cpp instead of emitting this TU's competing copy.
namespace _STL {
template <> _Rb_tree<int, pair<const int, Rva00501875Count>,
    _Select1st<pair<const int, Rva00501875Count> >, less<int>,
    allocator<pair<const int, Rva00501875Count> > >::~_Rb_tree();
}

struct Rva004FA1FObserver;

struct Rva00598E66Element
{
	char bytes[1];
	bool operator<(const Rva00598E66Element &) const;
	bool operator==(const Rva00598E66Element &) const;
};

class Rva00506B1B
{
public:
	Rva00506B1B();										// 0x00506B1B
	virtual ~Rva00506B1B() {}
	// Retail vftable 0x00C63F9C: dtor, then two __purecall slots.
	virtual void v1() = 0;
	virtual void v2() = 0;
	bool m_04;
};

class Rva00598B2A : public Rva00506B1B
{
public:
	Rva00598B2A(void *owner);
	virtual ~Rva00598B2A();	// virtual list as Rva00598CFDDtor.cpp declares it

private:
	_STL::map<int, Rva00501875Count> m_counts;			// +0x08
	_STL::list<Rva004FA1FObserver *> m_observers;		// +0x14
	_STL::hash_map<int, Rva00598E66Element> m_table;	// +0x18
	bool m_2C;											// +0x2C
	void *m_owner;										// +0x30
	bool m_34;											// +0x34
	int m_38;											// +0x38
	_STL::vector<int> m_3C;								// +0x3C
	int m_48;											// +0x48
	_STL::vector<int> m_4C;								// +0x4C
};

Rva00598B2A::Rva00598B2A(void *owner)
	: m_2C(true), m_owner(owner), m_34(false), m_38(-1), m_48(-1)
{
}
