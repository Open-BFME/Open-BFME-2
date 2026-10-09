// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5200.md plus retail only.
// ?Rva001C5200ExtractTokenN@@YAIPBUVp6TokenEntry@@PAUVp6RawBits@@PBUVp6TreeNode@@@Z
// retail 0x001C5200..0x001C530D (269 bytes) (spec name VP6_ExtractTokenN).
// MSVC gives the static decoder its private convention: EAX = 64-entry
// lookup table of 16-bit entries / EDX = raw bit reader / EBX = Huffman node
// array with the token in EAX as the spec states. Peeks 6 bits (the
// bitreadonly step inlined) and consumes the entry's length from bits 12..15
// (bitShift inlined). A leaf entry (bit 0) returns its bits 1..5; otherwise
// those bits name the first node and the tree is walked one bit at a time
// (bitread1 inlined): a set bit takes the right edge and a clear bit the left
// until a leaf edge (bit 0) whose bits 1..7 are returned. The walk edge is a
// stack bitfield whose leaf bit starts undefined as retail shows. Retail
// holds no direct caller. Reader layout follows the matched readers at
// 0x001C4FE0 0x001C5040 0x001C5070 and 0x001C50B0.
struct Vp6RawBits {
	int bits; unsigned value; const unsigned char *next;
	__forceinline unsigned peek(unsigned count)
	{
		unsigned avail = bits;
		unsigned word = value & ((1 << avail) - 1);
		if (avail >= count)
			return word >> (avail - count);
		return (*next | (word << 8)) >> (avail - count + 8);
	}
	__forceinline void skip(int count)
	{
		if ((bits -= count) < 0) {
			unsigned v = 0;
			for (int i = 0; i < 4; i++)
				v = (v << 8) + next[i];
			value = v;
			next += 4;
			bits += 32;
		}
	}
	__forceinline int bit()
	{
		if (bits) { --bits; return (value >> bits) & 1; }
		unsigned v = 0;
		v = (v << 8) + next[0];
		v = (v << 8) + next[1];
		v = (v << 8) + next[2];
		v = (v << 8) + next[3];
		value = v;
		next += 4;
		bits = 31;
		return value >> 31;
	}
};
struct Vp6TokenEntry { unsigned short leaf : 1; unsigned short value : 5; unsigned short unused : 6; unsigned short length : 4; };
struct Vp6TreeEdge { unsigned leaf : 1; unsigned value : 7; unsigned unused : 24; };
struct Vp6TreeNode { Vp6TreeEdge left; Vp6TreeEdge right; unsigned probability; };
static unsigned Rva001C5200ExtractTokenN(const Vp6TokenEntry *table, Vp6RawBits *reader, const Vp6TreeNode *nodes)
{
	unsigned index = reader->peek(6);
	reader->skip(table[index].length);
	if (table[index].leaf)
		return table[index].value;
	Vp6TreeEdge edge;
	edge.value = table[index].value;
	do {
		if (reader->bit())
			edge = nodes[edge.value].right;
		else
			edge = nodes[edge.value].left;
	} while (!edge.leaf);
	return edge.value;
}
// C++ integration entry absent from retail. Keeping the decoder static gives
// MSVC its private EAX/EDX/EBX convention; only the 269-byte body is claimed.
unsigned ExtractVp6TokenN(const Vp6TokenEntry *table, Vp6RawBits *reader, const Vp6TreeNode *nodes) { return Rva001C5200ExtractTokenN(table, reader, nodes); }
