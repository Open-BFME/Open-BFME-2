// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ??4?$vector@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@QAEAAV01@ABV01@@Z @0x00317EBB 180B: vector NoCase pair assign via allocate_and_copy 0x00317D5C plus clear 0x004C3D8B plus copy 0x00255CFA plus destroy 0x0032C0CA plus uninitialized_copy 0x00317CF2. Evidence: retail calls rowed allocate_and_copy plus rowed clear plus pinned copy plus rowed destroy plus pinned uninitialized_copy; sar 3 stride 8 throughout; same 3-path shape as Science assign 0x0021C21B.
// stlport
#include "ascii_string.h"
#include <vector>
#include <utility>
#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"
struct BfmeStringRecord00426A5B
{
	AsciiString text;
	unsigned char flag0, flag1, flag2;
};
struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;
};
struct RvaPair0032C0CA
{
	AsciiString m_key;
	int m_value;
};
void Rva0032C0CADestroyPairs(RvaPair0032C0CA *first, RvaPair0032C0CA *last);
// Retail's worker at 0x00317CF2 is rowed under its 8-byte element view
// (StlSweepW5Rva00317CF2.cpp); its placement copy is 0x00317CA0, not the
// _Construct<pair<..., NoCaseTreeValue4>> row 0x000A7849, so call that row.
struct Rva00317CF2Element { char bytes[8]; bool operator<(const Rva00317CF2Element&)const; bool operator==(const Rva00317CF2Element&)const; };
void __cdecl Rva00317CA0Construct(void *, const void *);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva00317CF2Element, Rva00317CF2Element>(Rva00317CF2Element *__p, const Rva00317CF2Element &__val)
{ Rva00317CA0Construct(__p, &__val); }
}
namespace _STL
{
typedef pair<const AsciiString, NoCaseTreeValue4> CopyNoCasePair;

template <> CopyNoCasePair *allocator<CopyNoCasePair>::allocate(unsigned int, const void *) const;

// Keep the separately rowed allocation worker out of this assignment body.
// A declaration-only member-template specialization triggers VC7.1 C1001.
template <> template <> inline __declspec(noinline) CopyNoCasePair *
vector<CopyNoCasePair, allocator<CopyNoCasePair> >::_M_allocate_and_copy<const CopyNoCasePair *>(
    size_type n, const CopyNoCasePair *first, const CopyNoCasePair *last)
{
    pointer result = _M_end_of_storage.allocate(n);
    __false_type tag; // Empty dispatch tag; retail does not value-initialize storage.
    __uninitialized_copy(reinterpret_cast<const Rva00317CF2Element *>(first),
                         reinterpret_cast<const Rva00317CF2Element *>(last),
                         reinterpret_cast<Rva00317CF2Element *>(result), tag);
    return result;
}

template <> void vector<BfmeStringRecord00426A5B, allocator<BfmeStringRecord00426A5B> >::_M_clear();
// The allocator shim also declares a by-value dispatch overload; this row's
// existing worker takes the empty tag by const reference.
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <> FXBoneInfo *__copy_ptrs<FXBoneInfo *, FXBoneInfo *>(FXBoneInfo *, FXBoneInfo *, FXBoneInfo *, const __false_type &);
}

typedef FXBoneInfo *(__cdecl *NoCasePairCopy)(FXBoneInfo *, FXBoneInfo *, FXBoneInfo *, const _STL::__false_type &);

// Expose the existing protected worker without adding a wrapper function.
struct NoCaseAssignClear : _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >
{
    using _STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> >::_M_clear;
};

template <>
_STL::vector<_STL::CopyNoCasePair, _STL::allocator<_STL::CopyNoCasePair> > &_STL::vector<_STL::CopyNoCasePair, _STL::allocator<_STL::CopyNoCasePair> >::operator=(const vector &x)
{
	_STL::__false_type tag;
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			reinterpret_cast<NoCaseAssignClear *>(this)->_M_clear();
			_M_start = tmp;
			_M_end_of_storage._M_data = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			FXBoneInfo *new_finish = static_cast<NoCasePairCopy>(&_STL::__copy_ptrs<FXBoneInfo *, FXBoneInfo *>)(const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin())), const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.end())), reinterpret_cast<FXBoneInfo *>(_M_start), tag);
			Rva0032C0CADestroyPairs(reinterpret_cast<RvaPair0032C0CA *>(new_finish), reinterpret_cast<RvaPair0032C0CA *>(_M_finish));
		}
		else
		{
			static_cast<NoCasePairCopy>(&_STL::__copy_ptrs<FXBoneInfo *, FXBoneInfo *>)(const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin())), const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin() + size())), reinterpret_cast<FXBoneInfo *>(_M_start), tag);
			_STL::__uninitialized_copy(reinterpret_cast<const Rva00317CF2Element *>(x.begin() + size()), reinterpret_cast<const Rva00317CF2Element *>(x.end()), reinterpret_cast<Rva00317CF2Element *>(_M_finish), tag);
		}
		_M_finish = _M_start + xsize;
	}
	return *this;
}
