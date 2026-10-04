// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?setValues@Offset140IntegerPairSetterThunk@@QAEXHH@Z
// retail 0x0008BBA1, 23 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/VirtualSlot5CallThunk.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other 384 definitions are omitted.
//
//   0008BBA1  8b 44 24 04        mov eax, [esp+4]      ; firstValue
//   0008BBA5  89 81 8c 00 00 00  mov [ecx+0x8c], eax
//   0008BBAB  8b 44 24 08        mov eax, [esp+8]      ; secondValue
//   0008BBAF  89 81 90 00 00 00  mov [ecx+0x90], eax
//   0008BBB5  c2 08 00           ret 8
//
// with 0x0008BBA0 (`ret`) immediately before it, so the boundary is proven.
// The same 0x8c pair offset the sibling copyTo reads as its triple, so this is
// the setter for the first two ints of that same record.

struct Offset140IntegerPairSetterThunk
{
	unsigned char padding[0x8c];
	int first;
	int second;

	void setValues(int firstValue, int secondValue);
};

void Offset140IntegerPairSetterThunk::setValues(int firstValue, int secondValue)
{
	first = firstValue;
	second = secondValue;
}