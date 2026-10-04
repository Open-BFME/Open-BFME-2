// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw
// stlport
//
// ?clamp779@@YAHHHH@Z
// retail 0x000B23BE, 26 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// TextureSelection007781C0.cpp (reference/open-bfme-1 @ 6d943426), trimmed to
// this one body; the donor's other definition is omitted.
//
//   000B23BE  55                 push ebp
//   000B23BF  8b ec              mov ebp, esp
//   000B23C1  8b 45 08           mov eax, [ebp+8]      ; v
//   000B23C4  3b 45 0c           cmp eax, [ebp+0xc]     ; lo
//   000B23C7  7d 05              jge +5
//   000B23C9  8b 45 0c           mov eax, [ebp+0xc]     ; below range: lo
//   000B23CC  5d                 pop ebp
//   000B23CD  c3                 ret
//   000B23CE  3b 45 10           cmp eax, [ebp+0x10]   ; hi
//   000B23D1  7e 03              jle +3
//   000B23D3  8b 45 10           mov eax, [ebp+0x10]   ; above range: hi
//   000B23D6  5d                 pop ebp
//   000B23D7  c3                 ret
//
// with 0x000B23BD (`ret`) immediately before it, so the boundary is proven.
//
// The `YAHHHH@Z` is a __cdecl free function: the donor's `inline` would be
// dropped by MSVC 7.1 in a TU that never calls it, so it is defined out of line
// with external linkage -- which is what makes it a real symbol at all. The frame
// is push ebp/mov ebp,esp because the donor declares it without __forceinline;
// /Os alone does not drop it.

int clamp779(int v, int lo, int hi)
{
	if (v < lo)
		return lo;
	if (v > hi)
		return hi;
	return v;
}