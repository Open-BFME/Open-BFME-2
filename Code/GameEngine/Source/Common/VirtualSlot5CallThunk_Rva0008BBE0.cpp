// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?copyTo@Offset140IntegerTripleCopyThunk@@QAEPAHPAH@Z
// retail 0x0008BBE0, 22 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/VirtualSlot5CallThunk.cpp
// (reference/open-bfme-1 @ 6d943426). Recompiled /Os it is byte-identical to
// retail once relocations are masked (unique hit on unclaimed .text). Only the
// placed body is defined here; the donor's other 384 definitions are omitted.
//
//   0008BBE0  8b 44 24 04        mov eax, [esp+4]      ; the destination pointer
//   0008BBE4  56                 push esi
//   0008BBE5  57                 push edi
//   0008BBE6  8d b1 8c 00 00 00  lea esi, [ecx+0x8c]   ; the source triple
//   0008BBEC  8b f8              mov edi, eax
//   0008BBEE  a5                 rep movsd             ; x3 = 12 bytes
//   0008BBEF  a5
//   0008BBF0  a5
//   0008BBF1  5f                 pop edi
//   0008BBF2  5e                 pop esi
//   0008BBF3  c2 04 00           ret 4
//
// with 0x0008BBDF (`ret`) immediately before it, so the boundary is proven.
// Three `rep movsd` is the shape MSVC 7.1 gives a 12-byte POD assignment, so
// the value is a plain three-int struct: anything with a constructor or a
// non-trivial member would break it into loads and stores instead.

struct IntegerTripleCopyValue
{
	int first;
	int second;
	int third;
};

struct Offset140IntegerTripleCopyThunk
{
	unsigned char padding[0x8c];
	IntegerTripleCopyValue value;

	int *copyTo(int *destination);
};

int *Offset140IntegerTripleCopyThunk::copyTo(int *destination)
{
	*reinterpret_cast<IntegerTripleCopyValue *>(destination) = value;
	return destination;
}