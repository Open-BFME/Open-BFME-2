// cl: /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5040.md plus retail only.
// ?Rva001C5040PeekBits@@YAIPAUVp6RawBits@@I@Z retail 0x001C5040..0x001C506F
// (47 bytes) the VP6 raw bit reader's non-consuming peek (spec name
// bitreadonly). MSVC gives the static reader its private convention:
// EAX = reader and ESI = bit count with the result in EAX as the spec
// states. The unread bits of the word give the result directly when they
// suffice (unsigned compare); otherwise they are topped up by the next
// buffer byte. Reader state is not modified. Retail holds no direct caller.
// Layout follows the matched readers at 0x001C4FE0 and 0x001C50B0.
struct Vp6RawBits { unsigned bits; unsigned value; const unsigned char *next; };
static unsigned Rva001C5040PeekBits(Vp6RawBits *state, unsigned bits)
{
	unsigned avail = state->bits;
	unsigned word = state->value & ((1 << avail) - 1);
	if (avail >= bits)
		return word >> (avail - bits);
	return (*state->next | (word << 8)) >> (avail - bits + 8);
}
// C++ integration entry absent from retail. Keeping the reader static gives
// MSVC its private EAX/ESI convention; only the 47-byte reader is claimed.
unsigned PeekVp6RawBits(Vp6RawBits *state, unsigned bits) { return Rva001C5040PeekBits(state, bits); }
