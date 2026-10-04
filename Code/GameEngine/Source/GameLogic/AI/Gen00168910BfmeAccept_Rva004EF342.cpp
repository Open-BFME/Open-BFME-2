// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
//
// ?isInList0C@BfmeNode_00161220@@QBE_NPAPAU1@@Z
// retail 0x004EF342, 26 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameLogic/AI/Gen00168910BfmeAccept.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other definition is omitted.
//
//   004EF342  8b 44 24 04        mov eax, [esp+4]      ; head
//   004EF346  39 08              cmp [eax], ecx        ; *head == this?
//   004EF348  74 0c              je  +0x0c
//   004EF34A  33 c0              xor eax, eax
//   004EF34C  39 41 0c           cmp [ecx+0x0c], eax   ; m_next0C
//   004EF34F  75 05              jne +5
//   004EF351  39 41 10           cmp [ecx+0x10], eax   ; m_previous10
//   004EF354  74 03              je  +3
//   004EF356  33 c0              xor eax, eax
//   004EF358  40                 inc eax
//   004EF359  c2 04 00           ret 4
//
// with 0x004EF341 (`ret`) immediately before it, so the boundary is proven.
// The 0x0c/0x10 pair is the second of the node's two intrusive links; the
// sibling isInList04 (0x004F0341) is the same body reading +0x04/+0x08.

typedef bool Bool;

struct BfmeNode_00161220
{
	void *m_vptr;
	BfmeNode_00161220 *m_next04;
	BfmeNode_00161220 *m_previous08;
	BfmeNode_00161220 *m_next0C;
	BfmeNode_00161220 *m_previous10;

	Bool isInList0C(BfmeNode_00161220 **head) const;
};

// Out of line on purpose: an in-class definition is implicitly inline, and
// MSVC 7.1 does not emit an inline member this TU never calls, so the body
// would be missing from the object and the byte gate would have nothing to
// compare. The emitted code is the same either way.
Bool BfmeNode_00161220::isInList0C(BfmeNode_00161220 **head) const
{
	return *head == this || m_next0C != 0 || m_previous10 != 0;
}