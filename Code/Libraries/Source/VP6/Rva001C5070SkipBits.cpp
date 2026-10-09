// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5070.md plus retail only.
// ?Rva001C5070SkipBits@@YAXPAUVp6RawBits@@H@Z retail 0x001C5070..0x001C50AC
// (60 bytes) the VP6 raw bit reader's consume step (spec name bitShift).
// MSVC gives the static reader its private convention: EAX = reader and
// ECX = bit count as the spec states. Subtracts the count from the unread
// bits; when that goes negative the next four bytes load big-endian as the
// new word (pointer advanced by 4) and 32 is added back. Retail holds no
// direct caller. Layout follows the matched readers at 0x001C4FE0 and
// 0x001C50B0.
struct Vp6RawBits { int bits; unsigned value; const unsigned char *next; };
static void Rva001C5070SkipBits(Vp6RawBits *state, int bits)
{
	if ((state->bits -= bits) < 0) {
		const unsigned char *next = state->next;
		unsigned value = next[0];
		value = (value << 8) + next[1];
		value = (value << 8) + next[2];
		value = (value << 8) + next[3];
		state->value = value;
		state->next = next + 4;
		state->bits += 32;
	}
}
// C++ integration entry absent from retail. Keeping the reader static gives
// MSVC its private EAX/ECX convention; only the 60-byte reader is claimed.
void SkipVp6RawBits(Vp6RawBits *state, int bits) { Rva001C5070SkipBits(state, bits); }
