// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
//
// ?isInList04@BfmeNode_00161220@@QBE_NPAPAU1@@Z
// retail 0x004F0341, 26 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/AI/Gen00168910BfmeAccept.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other definition is omitted.
//
//   004F0341  8b 44 24 04        mov eax, [esp+4]      ; head
//   004F0345  39 08              cmp [eax], ecx        ; *head == this?
//   004F0347  74 0c              je  +0x0c
//   004F0349  33 c0              xor eax, eax
//   004F034B  39 41 04           cmp [ecx+0x04], eax   ; m_next04
//   004F034E  75 05              jne +5
//   004F0350  39 41 08           cmp [ecx+0x08], eax   ; m_previous08
//   004F0353  74 03              je  +3
//   004F0355  33 c0              xor eax, eax
//   004F0357  40                 inc eax
//   004F0358  c2 04 00           ret 4
//
// with 0x004F0340 (`ret`) immediately before it, so the boundary is proven.
// Byte-identical to the sibling isInList0C (0x004EF342) apart from the +0x04 /
// +0x08 link pair this one tests instead of +0x0c / +0x10.

typedef bool Bool;

struct BfmeNode_00161220
{
	void *m_vptr;
	BfmeNode_00161220 *m_next04;
	BfmeNode_00161220 *m_previous08;
	BfmeNode_00161220 *m_next0C;
	BfmeNode_00161220 *m_previous10;

	Bool isInList04(BfmeNode_00161220 **head) const;
};

// Out of line on purpose: an in-class definition is implicitly inline, and
// MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
Bool BfmeNode_00161220::isInList04(BfmeNode_00161220 **head) const
{
	return *head == this || m_next04 != 0 || m_previous08 != 0;
}