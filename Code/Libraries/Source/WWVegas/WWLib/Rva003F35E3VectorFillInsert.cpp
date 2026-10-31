// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail 0x003F35E3, Ghidra boundary 265B. The three-pointer element width and
// calls to vector<unsigned int> copy, assignment, and destruction routines
// support this address-derived 12-byte ABI view; the application type remains
// unknown. STLport 4.5.3 supplies the fill-insert control flow. Target calls
// identify the local workers at 0x003F24D6, 0x003F1ECE, 0x003F1EEB, and the
// already matched overflow body at 0x003F3277.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}
}

#pragma optimize("", on)

#include <vector>

typedef _STL::vector<unsigned int> Rva003F3277VectorValue;
// STLport supplies an empty __false_type dispatch tag as the fourth cdecl
// argument at the rowed copy-backward wrapper. Retail's caller uses the
// transient frame slot [ebp+0x0b]. In this build value_copy starts at
// [ebp-0x18], so this typed view places tag at that same slot and lets cl emit
// the target's single frame-relative LEA. The wrapper ignores the extra tag;
// the view records compiler/frame evidence, not an element layout.
struct Rva003F35E3DispatchFrameSlot { char padding[35]; _STL::__false_type tag; };
void __cdecl Rva00030830FreeAllocation(void *);
struct Rva003F3277Record { Rva003F3277Record(); Rva003F3277Record(const Rva003F3277Record &); __declspec(noinline) ~Rva003F3277Record() { ((Rva003F3277VectorValue *)this)->~Rva003F3277VectorValue(); } Rva003F3277Record &operator=(const Rva003F3277Record &); private: char bytes[12]; };

void __cdecl Rva003F24D6CopyBackward(char *, char *, char *);
void __cdecl Rva003F1ECEFill(char *, char *, char *);

namespace _STL {
template <> void _Construct<Rva003F3277Record, Rva003F3277Record>(Rva003F3277Record *, const Rva003F3277Record &);

extern template vector<unsigned int> *uninitialized_fill_n<vector<unsigned int> *, unsigned int, vector<unsigned int> >(
	vector<unsigned int> *, unsigned int, const vector<unsigned int> &);

template <> __forceinline void allocator<unsigned int>::deallocate(unsigned int *p, allocator<unsigned int>::size_type) const
{
	if (p != 0)
		Rva00030830FreeAllocation(p);
}

template <>
inline void fill<Rva003F3277Record *, Rva003F3277Record>(
	Rva003F3277Record *first, Rva003F3277Record *last, const Rva003F3277Record &value)
{
	Rva003F1ECEFill(reinterpret_cast<char *>(first), reinterpret_cast<char *>(last), const_cast<char *>(reinterpret_cast<const char *>(&value)));
}

template <>
inline void vector<Rva003F3277Record, allocator<Rva003F3277Record> >::_M_fill_insert(
	Rva003F3277Record *position, size_type n, const Rva003F3277Record &value)
{
	if (n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= n) {
			Rva003F3277VectorValue value_copy = reinterpret_cast<const Rva003F3277VectorValue &>(value);
			const size_type elems_after = this->_M_finish - position;
			pointer old_finish = this->_M_finish;
			if (elems_after > n) {
				__uninitialized_copy(this->_M_finish - n, this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += n;
				typedef void (__cdecl *CopyBackwardDispatchFn)(char *, char *, char *, const _STL::__false_type &);
				((CopyBackwardDispatchFn)&Rva003F24D6CopyBackward)(reinterpret_cast<char *>(position), reinterpret_cast<char *>(old_finish - n), reinterpret_cast<char *>(old_finish), reinterpret_cast<const Rva003F35E3DispatchFrameSlot &>(value_copy).tag);
				_STLP_STD::fill(position, position + n, reinterpret_cast<const Rva003F3277Record &>(value_copy));
			}
			else {
				uninitialized_fill_n<vector<unsigned int> *, unsigned int, vector<unsigned int> >(
					reinterpret_cast<vector<unsigned int> *>(this->_M_finish), n - elems_after, value_copy);
				this->_M_finish += n - elems_after;
				__uninitialized_copy(position, old_finish, this->_M_finish, _IsPODType());
				this->_M_finish += elems_after;
				_STLP_STD::fill(position, old_finish, reinterpret_cast<const Rva003F3277Record &>(value_copy));
			}
		}
		else
			_M_insert_overflow(position, value, _IsPODType(), n);
	}
}
}

#pragma inline_depth(0)
// ?_bfmeStlportVectorRva003F35E3FillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeStlportVectorRva003F35E3FillInsertAnchor()
{
	typedef _STL::vector<Rva003F3277Record, _STL::allocator<Rva003F3277Record> > RecordVector;
	RecordVector *vector = 0;
	Rva003F3277Record *position = 0;
	const Rva003F3277Record *value = 0;
	vector->_M_fill_insert(position, 0, *value);
}
#pragma inline_depth()

// The 12-byte element is retail's vector<unsigned int> element under an
// address-derived label: its placement copy is the rowed _Construct 0x003F1A5F
// (dup_003F1A5F, the alias of _Construct<vector<unsigned int>> rowed at
// 0x000796E8), whose vector copy ctor is rowed at 0x002CFAB9, and whose
// destructor is the rowed vector<unsigned int> destructor at 0x0007FAB3 (free
// the start pointer). Reproduce the placement copy here and forward the
// element's destructor to that rowed owner, so the vector helpers' calls
// resolve instead of the undefined ??$_Construct@URva003F3277Record /
// ??1Rva003F3277Record. The destructor stays noinline so the emitted _Destroy
// helpers (shared, first-copy-in-link-order) keep calling it rather than
// inlining an extra body.
namespace _STL {
template <> void _Construct<Rva003F3277Record, Rva003F3277Record>(
	Rva003F3277Record *p, const Rva003F3277Record &value)
{
	_STLP_PLACEMENT_NEW ((void *)p) Rva003F3277VectorValue(*(const Rva003F3277VectorValue *)&value);
}
}

// Complete native forwarder 0x003F3744..0x003F3749: the verified
// fill-insert at 0x003F35E3 receives the same ECX and three stack arguments.
// Retain an address-derived wrapper instead of asserting an original
// application class or a particular STL public-overload identity.
class Rva003F3744 : public _STL::vector<Rva003F3277Record, _STL::allocator<Rva003F3277Record> >
{
public:
	void fillInsert(Rva003F3277Record *position, unsigned int count, const Rva003F3277Record &value);
};

void Rva003F3744::fillInsert(Rva003F3277Record *position, unsigned int count, const Rva003F3277Record &value)
{
	_M_fill_insert(position, count, value);
}
