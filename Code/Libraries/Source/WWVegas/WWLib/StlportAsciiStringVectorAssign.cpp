// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport vector<AsciiString>::operator= at 0x000BDB46, the copy path
// PeerResponse::operator= (0x0038B383) and ~20 other owners call with a
// pushed source and this in ecx.
//
// Explicit instantiation with the vendored 4.5.3 headers cannot reproduce
// this body: <_vector.c> passes (const_pointer)__x._M_start to __copy_ptrs,
// selecting the const-first overload, while retail calls the non-const
// __copy_ptrs at 0x000B6614 (raw _M_start, whose const-qualified pointer
// decays back to AsciiString*). The member is therefore specialized by hand
// below, following the header line for line with only those two casts
// dropped. Stock headers, not the bfmealloc shim, and a noinline
// __copy_ptrs forwarder (ProductionPrerequisiteCtor precedent) keep the
// dispatch layers out of line as retail has them. The _M_clear call targets
// the Module.cpp 30B instantiation at 0x0002CD53 rather than the 56B one at
// 0x00142EA0, so this row needs gen-alias notes.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	struct AsciiStringData
	{
		virtual void _M_slot_00();
		int m_refCount;
	};

	AsciiStringData *m_data;

public:
	AsciiString();
	AsciiString(const AsciiString &that);
	AsciiString &operator=(const AsciiString &that);
	~AsciiString();
};

namespace _STL
{

// Declared, not defined: the element copy helper lives at 0x00142CC0
// (AsciiStringConstruct.cpp), so the instantiations below call it as retail
// does instead of emitting a local copy.
template <> void _Construct<AsciiString, AsciiString>(AsciiString *, const AsciiString &);

// Retail calls the dispatch layers directly instead of expanding them: the
// non-const __copy_ptrs forwarder takes the const-ref tag (rowed at
// 0x000B6614) and reaches the generic __copy worker. noinline keeps it out
// of line so the callers keep retail's shape; the body is verbatim generic.
template <>
__declspec(noinline) AsciiString *__copy_ptrs<AsciiString *, AsciiString *>(AsciiString *__first, AsciiString *__last, AsciiString *__result, const __false_type &)
{
	return __copy(__first, __last, __result, random_access_iterator_tag(), (ptrdiff_t *)0);
}

template <>
vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &__x)
{
	if (&__x != this) {
		const size_type __xlen = __x.size();
		if (__xlen > capacity()) {
			pointer __tmp = _M_allocate_and_copy(__xlen, (const_pointer)__x._M_start + 0, (const_pointer)__x._M_finish + 0);
			_M_clear();
			_M_start = __tmp;
			_M_end_of_storage._M_data = _M_start + __xlen;
		}
		else if (size() >= __xlen) {
			pointer __i = __copy_ptrs((pointer)__x._M_start + 0, (pointer)__x._M_finish + 0, (pointer)_M_start, _TrivialAss());
			_Destroy(__i, _M_finish);
		}
		else {
			__copy_ptrs((pointer)__x._M_start, (pointer)__x._M_start + size(), (pointer)_M_start, _TrivialAss());
			__uninitialized_copy((const_pointer)__x._M_start + size(), (const_pointer)__x._M_finish + 0, _M_finish, _IsPODType());
		}
		_M_finish = _M_start + __xlen;
	}
	return *this;
}

}
