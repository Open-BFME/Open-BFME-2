// cl: /O1 /DNDEBUG /MD
//
// ?getStatus@Parameter@@QBE?AV?$BitFlags@$0CN@@@XZ
// retail 0x00579696, 18 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os the donor's inline
// `Parameter::getStatus` header accessor is byte-identical to retail once
// relocations are masked (unique hit on unclaimed .text).
//
//   00579696  8b 51 24           mov edx, [ecx+0x24]
//   00579699  8b 44 24 04        mov eax, [esp+4]      ; the hidden return slot
//   0057969D  89 10              mov [eax], edx
//   0057969F  8b 49 28           mov ecx, [ecx+0x28]
//   005796A2  89 48 04           mov [eax+4], ecx
//   005796A5  c2 04 00           ret 4
//
// with 0x00579695 (`ret`) immediately before it, so the boundary is proven.
//
// BFME's Parameter carries its status mask as two dwords at +0x24/+0x28, so the
// decorated return type BitFlags<CN> (CN == OBJECT_STATUS_COUNT) is a
// by-value POD of exactly two dwords, and the whole body is that copy. The
// `QBE?AV...` mangling is the by-value hidden-return convention: [esp+4] is the
// caller's return slot and `ret 4` pops only the single explicit argument, so
// the caller passes no status argument at all.
//
// Declared minimally and instantiated out of class, exactly as the landed
// sibling Code/GameEngine/Source/Common/System/BitFlagsCountIntersection.cpp
// does: the upstream header declares getStatus inline (which is why the sweep
// records it as credited to a header rather than a definition), and an in-class
// body MSVC 7.1 drops when nothing in the TU calls it.

template <int NUMBITS>
class BitFlags
{
	unsigned m_bits[2];
};

// upstream layout: the status mask sits at this+0x24, behind the vptr, the
// parameter-type/initialized pair and the int/real values.
class Parameter
{
public:
	unsigned char m_beforeStatus[0x24];
	BitFlags<0x2D> m_objectStatus;

	BitFlags<0x2D> getStatus() const;
};

// Defined out of line on purpose: an in-class definition is implicitly inline,
// and MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
BitFlags<0x2D> Parameter::getStatus() const
{
	return m_objectStatus;
}