// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c4fe0.md plus retail only.
// ?Rva001C4FE0ReadBits@@YAIPAUVp6RawBits@@H@Z retail 0x001C4FE0..0x001C503E
// (94 bytes) the VP6 raw bit reader's n-bit read (spec name bitread). MSVC
// gives the static reader its private convention: EAX = reader and ECX = bit
// count with the result in EAX as the spec and the caller 0x001C5310 show.
// Masks the word to its remaining bits; when the count exceeds them the
// masked word shifted by the excess is kept and the next four bytes load
// big-endian (the byte loop is what reproduces retail's register order).
// Table 0x00BD8D40 holds the 33 low-bit masks. Layout follows the matched
// one-bit reader at 0x001C50B0 (Rva009B47B0ReadBit.cpp).
struct Vp6RawBits { unsigned bits; unsigned value; const unsigned char *next; };
extern const unsigned g_00BD8D40[33];
static unsigned Rva001C4FE0ReadBits(Vp6RawBits *state, int bits)
{
	unsigned result = 0;
	state->value &= g_00BD8D40[state->bits];
	bits -= state->bits;
	if (bits > 0) {
		result = state->value << bits;
		unsigned value = 0;
		for (int i = 0; i < 4; i++)
			value = (value << 8) + state->next[i];
		state->value = value;
		state->next += 4;
		bits -= 32;
	}
	state->bits = -bits;
	return result | (state->value >> state->bits);
}
// C++ integration entry absent from retail. Keeping the reader static gives
// MSVC its private EAX/ECX convention; only the 94-byte reader is claimed.
unsigned ReadVp6RawBits(Vp6RawBits *state, int bits) { return Rva001C4FE0ReadBits(state, bits); }
