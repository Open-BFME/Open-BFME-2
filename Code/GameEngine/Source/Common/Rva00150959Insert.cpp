// cl: /Oy- /EHsc /MD
// stlport
// ?rva00150959@Rva00150959@@QAEXPAURva001504A1Record@@IABVRva0014F699@@@Z @0x00150959 258B
// vector fill-insert 76B elements with EH and x_copy dtor via rowed callees.
// Evidence: unlock lane idiv strides tag at ebp+0xb callers 0x00150BD7/0x00150A86.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAURva001504A1Record@@PAU1@@_STL@@YAPAURva001504A1Record@@PAU1@00A:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001504A1Record;
namespace _STL { template <> Rva001504A1Record * __uninitialized_copy<Rva001504A1Record *,Rva001504A1Record *>(Rva001504A1Record *,Rva001504A1Record *,Rva001504A1Record *,__false_type const &); }
// Retail range cleanup is the rowed virtual-destruction dispatcher.
struct Rva001504A1Record;
class Rva0014F3E7;
void __cdecl Rva0014F8AEDestroy(Rva0014F3E7*,Rva0014F3E7*);
namespace _STL {
template <> __declspec(dllimport) __forceinline void _Destroy<Rva001504A1Record *>(Rva001504A1Record *first,Rva001504A1Record *last)
{ Rva0014F8AEDestroy((Rva0014F3E7*)first,(Rva0014F3E7*)last); }
}
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@URva001504A1Record@@@_STL@@QBEXPAURva001504A1Record@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001504A1Record;
namespace _STL { template <> void allocator<Rva001504A1Record>::deallocate(Rva001504A1Record *,unsigned int) const; }

struct Rva001504A1Record
{
	char bytes[76];
};
// Retail 00150990 calls the established Shadow copy owner at 0014F4E3.
// The temporary remains an opaque 76-byte view with its rowed destructor.
namespace FXShaderParameterSourceNamespaceSAS {
struct SourceNamespace_Shadow { SourceNamespace_Shadow(const SourceNamespace_Shadow&); };
}
class __declspec(novtable) Rva0014F699
{
public:
    __declspec(dllimport) __forceinline Rva0014F699(const Rva0014F699 &other)
    {
        typedef FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow T;
        ((T*)this)->T::SourceNamespace_Shadow(*(const T*)&other);
    }
    virtual ~Rva0014F699();
    Rva0014F699 &operator=(const Rva0014F699 &other);
private:
    char bytes[72];
};
// Bind shared vector operations to their native rowed providers.
struct Rva0014F647Element;
class Rva0014F8C6 { public: void rva0014F8C6(); };
namespace _STL {
template<> void _Construct<Rva0014F647Element,Rva0014F647Element>(Rva0014F647Element*,const Rva0014F647Element&);
template<> __declspec(dllimport) __forceinline void _Construct<Rva001504A1Record,Rva001504A1Record>(Rva001504A1Record*p,const Rva001504A1Record&v)
{ _Construct(reinterpret_cast<Rva0014F647Element*>(p),reinterpret_cast<const Rva0014F647Element&>(v)); }
template<> __declspec(dllimport) __forceinline void vector<Rva001504A1Record>::_M_clear()
{ ((Rva0014F8C6*)this)->rva0014F8C6(); }
template<> void vector<Rva001504A1Record>::_M_insert_overflow(Rva001504A1Record*,const Rva001504A1Record&,const __false_type&,unsigned int,bool);
}
void __cdecl Rva0014FA0DCopyBackward(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result);
typedef void (__cdecl *CopyBackward4Fn)(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result, const _STL::__false_type &tag);
void __cdecl Rva0014FA2AFill(Rva0014F699 *first, Rva0014F699 *last, const Rva0014F699 &value);
void *__cdecl rva0014FA47(void *first, unsigned int n, void *value);

class Rva00150959 : public _STL::vector<Rva001504A1Record>
{
public:
	void rva00150959(Rva001504A1Record*,unsigned,const Rva0014F699&);
};

void Rva00150959::rva00150959(Rva001504A1Record *pos, unsigned int count, const Rva0014F699 &fillValue)
{
	if (count == 0)
		return;
	if ((unsigned int)(_M_end_of_storage._M_data - _M_finish) >= count) {
		Rva0014F699 x_copy(fillValue);
		unsigned int elems_after = (unsigned int)(_M_finish - pos);
		Rva001504A1Record *old_finish = _M_finish;
		if (elems_after > count) {
			_STL::__uninitialized_copy(old_finish - count, old_finish, old_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			_M_finish += count;
			Rva001504A1Record *p = pos;
			((CopyBackward4Fn)Rva0014FA0DCopyBackward)((Rva0014F699 *)p, (Rva0014F699 *)(old_finish - count), (Rva0014F699 *)old_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			Rva0014FA2AFill((Rva0014F699 *)p, (Rva0014F699 *)(p + count), x_copy);
		} else {
			rva0014FA47(old_finish, count - elems_after, (void *)&x_copy);
			_M_finish += count - elems_after;
			_STL::__uninitialized_copy(pos, old_finish, _M_finish, *(const _STL::__false_type *)((char *)&pos + 3));
			_M_finish += elems_after;
			Rva0014FA2AFill((Rva0014F699 *)pos, (Rva0014F699 *)old_finish, x_copy);
		}
	} else {
		_M_insert_overflow(pos, (const Rva001504A1Record &)fillValue, *(const _STL::__false_type *)((char *)&pos + 3), count, false);
	}
}
