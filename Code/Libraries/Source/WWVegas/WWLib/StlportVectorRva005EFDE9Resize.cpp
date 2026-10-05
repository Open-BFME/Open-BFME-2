// cl: /G7 /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail evidence: this is the 105-byte Ghidra body at 0x005EFDE9. It calls
// the rowed range erase at 0x005EF8FA and the fill-insert candidate at
// 0x005EFC30; the rowed one-argument resize at 0x005EFE6E forwards to it.
// The Q3SortElem4 donor name is only a lead. The element remains an
// address-derived four-byte pointer-backed codegen view; its retail C++ name
// and full layout are unresolved. Copy/release operations below model only
// the target call shape established by the helper family and release at
// 0x0007DEEF.
struct TargetRef00217D4C { void *m_vtbl; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005EFDE9Target { int m_00; TargetRef00217D4C m_04; };
struct Rva005EFDE9Element {
	Rva005EFDE9Target *m_ptr;
	// ?Rva005EFDE9Element copy ctor present-unmatched
	Rva005EFDE9Element(const Rva005EFDE9Element &other) : m_ptr(other.m_ptr) {
		if (m_ptr != 0) ++m_ptr->m_04.references;
	}
	// ?Rva005EFDE9Element dtor present-unmatched
	~Rva005EFDE9Element() {
		if (m_ptr != 0) ReleaseTreeHintRef00217D4C(&m_ptr->m_04);
	}
};
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector {
public:
	typedef unsigned int size_type;
	void _M_fill_insert(T *position, size_type count, const T &value);
	T *erase(T *first, T *last);
	void resize(size_type newSize, T value) {
		if (newSize < (_M_finish - _M_start))
			erase(_M_start + newSize, _M_finish);
		else {
			T *finish = _M_finish;
			const size_type count = newSize - (_M_finish - _M_start);
			_M_fill_insert(finish, count, value);
		}
	}
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template void vector<Rva005EFDE9Element, allocator<Rva005EFDE9Element> >::resize(
	unsigned int, Rva005EFDE9Element);
}
