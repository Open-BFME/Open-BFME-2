// ??$__uninitialized_copy@PBVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PBV1@0PAV1@ABU__false_type@0@@Z
// partial score=0.85 date=2026-09-12
// cl: /O1 /DNDEBUG /MD
//
// _STL::__uninitialized_copy<AsciiString const*, AsciiString*>, retail
// 0x0002C4B2, 38 bytes. Named by two call sites in
// Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp (vector<AsciiString>
// growth). Same loop shape as WeaponTemplateSetUninitializedCopy.cpp's
// sibling. STLport does not fold _Construct<AsciiString,AsciiString> across
// translation units: retail calls a second, TU-local instance of that exact
// body at 0x0002C485 rather than the already-matched one at 0x00142CC0
// (AsciiStringConstruct.cpp) -- pinned in reverse/symbols.csv as a second
// candidate address under the same mangled name.

class AsciiString
{
	void *m_data;

public:
	AsciiString(const AsciiString &that);
};

namespace _STL
{

struct __false_type {};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last,
	ForwardIter result, const __false_type &)
{
	ForwardIter cur = result;
	for (; first != last; ++first, ++cur)
		_Construct(cur, *first);
	return cur;
}

}

template AsciiString *_STL::__uninitialized_copy(const AsciiString *,
	const AsciiString *, AsciiString *, const _STL::__false_type &);

// STUCK ON: everything but the callee address matches (34/38 positional,
// exact prefix 15B). This loop calls _Construct<AsciiString,AsciiString>,
// which IS already matched at 0x00142CC0 (AsciiStringConstruct.cpp) -- but
// retail's REL32 here targets 0x0002C485, a DIFFERENT address, not the
// matched one. Manually disassembling 0x0002C485 shows a full-frame body
// with an SEH prolog (mov eax,<cookie>; call 0x629188; ...; mov fs:0,ecx;
// leave; ret), ~44 bytes ending in a ret at 0x0002C4B1 -- structurally
// consistent with an unshared, debug-shaped duplicate of the same
// _Construct instantiation (STLport does not get COMDAT-folded across
// every retail TU). But `python3 tools/pin_consistency.py --symbol
// '??$_Construct@VAsciiString@@V1@@_STL@@YAXPAVAsciiString@@ABV1@@Z'`
// reports a size-disagreement once a second candidate address is pinned:
// ghidra's own inventory extent for 0x0002C485 is only 10 bytes, not ~44 --
// so either ghidra's boundary there is wrong, or 0x0002C485 is not really
// a second _Construct body and this call target needs a different
// explanation entirely. Do not add the pin without resolving that
// disagreement (attempted here, reverted after pin_consistency flagged it).
// Next step: read the full 0x0002C485 body (and whatever owns the 10-byte
// ghidra chunk) before pinning anything.
