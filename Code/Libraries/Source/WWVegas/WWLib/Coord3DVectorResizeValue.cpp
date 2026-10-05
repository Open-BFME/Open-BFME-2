// cl: /O1 /G7 /MD
// stlport
// Retail evidence: 0x000CA2F3 is the 73-byte vector<Coord3D> two-argument
// resize body. Its identity is supported by the rowed one-argument forwarder
// at 0x000CA33C and the direct DockUpdate call. The body calls rowed 12-byte
// range erase 0x002A133B and a helper at 0x000CA1EE decoded from its REL32.
// That helper's full name is unknown, so it is called by an address-derived
// alias. Coord3D uses the existing three-float codegen view; the body proves
// stride and calls, not the target's complete source layout.
struct Coord3D { Coord3D() {} Coord3D(const Coord3D &) {} ~Coord3D() {} float x; float y; float z; };
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector {
public:
	typedef unsigned int size_type;
	typedef T *iterator;
	iterator erase(iterator first, iterator last);
	void rva00ca1ee(iterator position, size_type count, const T &value);
	void resize(size_type n, T value) {
		T *start = _M_start;
		T *finish = _M_finish;
		const size_type size = (size_type)(finish - start);
		if (n < size) {
			erase(start + n, finish);
		} else {
			rva00ca1ee(_M_finish, n - (size_type)(_M_finish - start), value);
		}
	}
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end;
};
template void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int, Coord3D);
}
