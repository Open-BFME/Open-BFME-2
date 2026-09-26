// cl: /O1
// stlport
//
// vector<FXBoneInfo>::erase(first, last), retail 0x00207F0D, 51 bytes,
// plus the __copy_ptrs wrapper it calls, retail 0x00255CFA, 29 bytes.
// Range erase over 8-byte pairs (AsciiString key plus a 4-byte payload):
// shift the tail down with the 8-byte __copy_ptrs wrapper, destroy the
// vacated tail with the rowed pair-destroy range at 0x0032C0CA, store the
// new finish, return first.
//
// Identity evidence. The copy worker under the wrapper (0x00254D65) drives
// per-element `*dest = *first` whose sole byte-true target is
// FXBoneInfo::operator= at 0x001D9990 (rowed, ZH donor layout boneName
// plus template), so the erased element type is FXBoneInfo; the wrapper
// body is shape-identical to the landed AsciiString __copy_ptrs at
// 0x000B6614, and this TU's own emission of the wrapper is byte-identical
// to the 29 bytes at 0x00255CFA, which the ledger also rows under the
// sibling's forwarder spelling (kept as the ICF owner: same machine code,
// two instantiation names). The destroy range releases each element's key
// through the rowed AsciiString scalar dtor at 0x0048BA39.
//
// Shared-body caveat. Seven retail callers erase heterogeneous 8-byte-pair
// vectors through the one erase address (ProductionUpdate 0x0049F7DB,
// StructureCollapse 0x00257A5E, CastleBehavior 0x0039A027 among them), so
// the linker folded them; the FXBoneInfo spelling claims the bytes, which
// are literally parameterized by FXBoneInfo's assignment.
//
// Shape levers (VectorAsciiStringErase precedent, same 51 bytes at
// 0x002CCFC): the tag is a `__false_type()` prvalue bound to the wrapper's
// const reference, which is what forces the EBP frame and homes the tag at
// [ebp+0xb] -- a declared-only wrapper compiles the same call frameless
// with a zeroed [ebp-1] temp instead (six probed spellings). The destroy
// call takes reinterpreted pair pointers (free casts) so it resolves to
// the rowed range destroy with no new pins.
class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
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

FXBoneInfo *copyEightByteRange(FXBoneInfo *first, FXBoneInfo *last,
	FXBoneInfo *dest, void *tag, int extra);

void Rva0032C0CADestroyPairs(RvaPair0032C0CA *first, RvaPair0032C0CA *last);

namespace _STL
{

struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *iterator;

	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

// ??$__copy_ptrs@PAUFXBoneInfo@@PAU1@@_STL@@YAPAUFXBoneInfo@@PAU1@00ABU__false_type@0@@Z present-unmatched
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result,
	const __false_type &tag){
	__false_type local;
	return copyEightByteRange(first, last, result,
		reinterpret_cast<void *>(&local), 0);
}

}

_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> >::iterator
_STL::vector<FXBoneInfo, _STL::allocator<FXBoneInfo> >::erase(
	iterator first, iterator last){
	iterator result = _STL::__copy_ptrs(last, m_finish, first, _STL::__false_type());
	Rva0032C0CADestroyPairs((RvaPair0032C0CA *)result, (RvaPair0032C0CA *)m_finish);
	m_finish = result;
	return first;
}
