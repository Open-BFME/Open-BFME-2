// cl: /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHsc
// stlport
// Target Ghidra [3F61C6,3F62C8),258B. Native stride48; temporary
// copy84B3F54DC and destructor60B3F535B independently establish nontrivial
// element lifetime. Both capacity branches and overflow call match STLport
// 4.5.3 _M_fill_insert. Original application record and tag names unproved.
// Scoped opaque48 view and ABI aliases preserve consumed pointer prefixes.
// Inline generic dispatch definitions are retained for caller optimization;
// their retail bodies are already declared in other owning source units.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

typedef unsigned short wchar_t;
#include <vector>
struct Rva003F61C6Record {
 char consumed[48];Rva003F61C6Record();
 Rva003F61C6Record(const Rva003F61C6Record&);
 ~Rva003F61C6Record();
 Rva003F61C6Record &operator=(const Rva003F61C6Record&);
};
namespace _STL {
template <> void _Construct<Rva003F61C6Record, Rva003F61C6Record>(Rva003F61C6Record *, const Rva003F61C6Record &);

// Retail calls the dispatch layers out of line. noinline forwarders keep them
// out of line as retail has them; bodies are verbatim generic.
// LINK-DUP: inline makes these copies select-any so the owners' plain
// definitions link (see packet).
template <>
inline Rva003F61C6Record *__copy_backward_ptrs<Rva003F61C6Record *, Rva003F61C6Record *>(Rva003F61C6Record *__first, Rva003F61C6Record *__last, Rva003F61C6Record *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}

template <>
inline Rva003F61C6Record *uninitialized_fill_n<Rva003F61C6Record *, unsigned int, Rva003F61C6Record>(Rva003F61C6Record *__first, unsigned int __n, const Rva003F61C6Record &__x)
{
	return __uninitialized_fill_n(__first, __n, __x, __false_type());
}

template <>
inline void vector<Rva003F61C6Record, allocator<Rva003F61C6Record> >::_M_fill_insert(
	Rva003F61C6Record *__position, size_type __n, const Rva003F61C6Record &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			Rva003F61C6Record __x_copy = __x;
			const size_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after > __n) {
				__uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __n;
				__copy_backward_ptrs(__position, __old_finish - __n, __old_finish, _TrivialAss());
				_STLP_STD::fill(__position, __position + __n, __x_copy);
			}
			else {
				uninitialized_fill_n(this->_M_finish, __n - __elems_after, __x_copy);
				this->_M_finish += __n - __elems_after;
				__uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __elems_after;
				_STLP_STD::fill(__position, __old_finish, __x_copy);
			}
		}
		else
			_M_insert_overflow(__position, __x, _IsPODType(), __n);
	}
}
}

#pragma inline_depth(0)
// ?Rva003F61C6EmitAnchor absent-from-retail
void Rva003F61C6EmitAnchor(_STL::vector<Rva003F61C6Record> *v,Rva003F61C6Record*p,unsigned n,const Rva003F61C6Record& x){v->_M_fill_insert(p,n,x);}
#pragma inline_depth()

#pragma comment(linker, "/alternatename:??0Rva003F61C6Record@@QAE@ABU0@@Z=??0Rva003F610FElement@@QAE@ABU0@@Z")

#pragma comment(linker, "/alternatename:??1Rva003F61C6Record@@QAE@XZ=??1Rva003F610FElement@@QAE@XZ")

#pragma comment(linker, "/alternatename:??4Rva003F61C6Record@@QAEAAU0@ABU0@@Z=??4Rva003F610FElement@@QAEAAU0@ABU0@@Z")

#pragma comment(linker, "/alternatename:??$__copy_backward_ptrs@PAURva003F61C6Record@@PAU1@@_STL@@YAPAURva003F61C6Record@@PAU1@00ABU__false_type@0@@Z=?backwardDispatchRva003F58A3@@YAPAURva003F5B3ERecord@@PAU1@00ABURva003F5B3EEmpty@@@Z")

#pragma comment(linker, "/alternatename:??$__copy_backward@PAURva003F61C6Record@@PAU1@H@_STL@@YAPAURva003F61C6Record@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z=?Rva003F5584CopyBackward@@YAPADPAD00@Z")

#pragma comment(linker, "/alternatename:??$__uninitialized_copy@PAURva003F61C6Record@@PAU1@@_STL@@YAPAURva003F61C6Record@@PAU1@00ABU__false_type@0@@Z=??$__uninitialized_copy@PBUBfmePod48@@PAU1@@_STL@@YAPAUBfmePod48@@PBU1@0PAU1@ABU__false_type@0@@Z")

#pragma comment(linker, "/alternatename:??$fill@PAURva003F61C6Record@@U1@@_STL@@YAXPAURva003F61C6Record@@0ABU1@@Z=?Rva003F58C0Fill@@YAXPAD00@Z")

#pragma comment(linker, "/alternatename:??$uninitialized_fill_n@PAURva003F61C6Record@@IU1@@_STL@@YAPAURva003F61C6Record@@PAU1@IABU1@@Z=??$uninitialized_fill_n@PAUBfmePod48@@IU1@@_STL@@YAPAUBfmePod48@@PAU1@IABU1@@Z")

#pragma comment(linker, "/alternatename:??$__uninitialized_fill_n@PAURva003F61C6Record@@IU1@@_STL@@YAPAURva003F61C6Record@@PAU1@IABU1@ABU__false_type@0@@Z=??$__uninitialized_fill_n@PAUBfmePod48@@IU1@@_STL@@YAPAUBfmePod48@@PAU1@IABU1@ABU__false_type@0@@Z")

#pragma comment(linker, "/alternatename:??$_Construct@URva003F61C6Record@@U1@@_STL@@YAXPAURva003F61C6Record@@ABU1@@Z=??$_Construct@URva003F610FElement@@U1@@_STL@@YAXPAURva003F610FElement@@ABU1@@Z")

#pragma comment(linker, "/alternatename:?_M_insert_overflow@?$vector@URva003F61C6Record@@V?$allocator@URva003F61C6Record@@@_STL@@@_STL@@IAEXPAURva003F61C6Record@@ABU3@ABU__false_type@2@I_N@Z=?_M_insert_overflow@?$vector@URva003F610FElement@@V?$allocator@URva003F610FElement@@@_STL@@@_STL@@IAEXPAURva003F610FElement@@ABU3@ABU__false_type@2@I_N@Z")
