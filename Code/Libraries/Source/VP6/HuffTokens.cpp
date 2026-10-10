// cl: /O2 /G6 /Ob1 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c5310.md plus retail only.
// No decoder source was consulted.
// _VP6_ReadHuffTokens retail 0x001C5310..0x001C598D (1661 bytes) cdecl
// (decoder instance / 64 coefficients / plane) returning the end-of-block
// offset byte (field 0x5FC) at one below the scan position reached. It
// calls the raw bit reader statics ?Rva001C4FE0ReadBits (0x001C4FE0: EAX
// reader / ECX count) and ?Rva009B47B0ReadBit (0x001C50B0: EAX reader) with
// MSVC's private register conventions so both statics live in this unit
// (their bodies are the matched ones and still compile exact here; their
// rows move to this file). The lookup-table token extraction (the matched
// 0x001C5200 body) is inlined three times: DC (lookup 0x30FC / tree 0xA20
// by plane) AC (lookup 0x31FC / tree 0x1A70 by precedence plane and band
// from the band map 0x00BD8B78) and zero run (lookup 0x43FC / tree 0x2FAC
// by scan position at or above 6). Token minimums come from 0x00BD8B48.
// DC and AC run counters sit at 0x4524 / 0x452C; coefficients other than
// DC land at the merged scan order byte (0x57C). /Ob1 keeps the two statics
// out of line while the small-token sign read stays inline as retail has
// it; each branch advances the scan position itself (retail's per-branch
// reload into ECX before the shared increment).

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

struct Vp6HuffTokenInstance
{
	unsigned char m_pad000[0x190];
	Vp6RawBits m_bits;
	unsigned char m_pad19c[0x57c - 0x19c];
	unsigned char m_scanOrder[64];
	unsigned char m_pad5bc[0x5fc - 0x5bc];
	unsigned char m_eobOffsets[64];
	unsigned char m_pad63c[0xa20 - 0x63c];
	Vp6TreeNode m_dcTree[2][12];
	unsigned char m_padb40[0x1a70 - 0xb40];
	Vp6TreeNode m_acTree[3][2][6][12];
	unsigned char m_pad2eb0[0x2fac - 0x2eb0];
	Vp6TreeNode m_zeroTree[2][14];
	Vp6TokenEntry m_dcLookup[2][64];
	Vp6TokenEntry m_acLookup[3][2][6][64];
	Vp6TokenEntry m_zeroLookup[2][64];
	unsigned char m_pad44fc[0x4524 - 0x44fc];
	int m_dcRun[2];
	int m_acRun[2];
};

// The three .rdata constant tables the token readers index. Retail bakes their
// addresses into the reading bodies, so each one is defined here from retail's
// bytes: the bit mask read by Rva001C4FE0ReadBits at VA 0x00BD8D40, the token
// minimums at VA 0x00BD8B48 and the AC band map at VA 0x00BD8B78.
extern const unsigned g_00BD8D40[33] = {
	0, 1, 3, 7, 15, 31, 63, 127,
	255, 511, 1023, 2047, 4095, 8191, 16383, 32767,
	65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607,
	16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647,
	-1,
};
extern const int g_00BD8B48[12] = {
	0, 1, 2, 3, 4, 5, 7, 11,
	19, 35, 67, 0,
};
extern const int g_00BD8B78[65] = {
	-1, 0, 1, 1, 1, 2, 2, 2,
	2, 2, 2, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3,
};

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

static int Rva009B47B0ReadBit(Vp6RawBits *state)
{
	if (state->bits) { --state->bits; return (state->value >> state->bits) & 1; }
	const unsigned char *next = state->next;
	unsigned value = next[0];
	value = (value << 8) + next[1];
	value = (value << 8) + next[2];
	value = (value << 8) + next[3];
	state->value = value;
	state->next = next + 4;
	state->bits = 31;
	return state->value >> 31;
}

static __forceinline unsigned Vp6ExtractToken(const Vp6TokenEntry *table, Vp6RawBits *reader, const Vp6TreeNode *nodes)
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

extern "C" unsigned char __cdecl VP6_ReadHuffTokens(Vp6HuffTokenInstance *pbi, short *coeffs, int plane)
{
	Vp6RawBits *br = &pbi->m_bits;
	int pos = 1;
	int prec;
	int token;
	unsigned zero;
	int value, sign, run, band, table, extra;

	if (pbi->m_dcRun[plane] > 0) {
		pbi->m_dcRun[plane]--;
		prec = 0;
	} else {
		token = Vp6ExtractToken(pbi->m_dcLookup[plane], br, pbi->m_dcTree[plane]);
		value = g_00BD8B48[token];
		if (token == 11)
			goto done;
		if (token == 0) {
			run = Rva001C4FE0ReadBits(br, 2) + 1;
			if (run == 3)
				run = Rva001C4FE0ReadBits(br, 2) + 3;
			else if (run == 4) {
				if (Rva009B47B0ReadBit(br))
					run = Rva001C4FE0ReadBits(br, 6) + 11;
				else
					run = Rva001C4FE0ReadBits(br, 2) + 7;
			}
			pbi->m_dcRun[plane] = run - 1;
			prec = 0;
		} else {
			if (token > 4) {
				extra = token - 4;
				if (token > 9)
					extra = 11;
				value += Rva001C4FE0ReadBits(br, extra);
			}
			sign = Rva009B47B0ReadBit(br);
			coeffs[0] = (short)((value ^ -sign) + sign);
			prec = (value > 1) + 1;
		}
	}

	if (pbi->m_acRun[plane] > 0) {
		pbi->m_acRun[plane]--;
		goto done;
	}

	do {
		band = g_00BD8B78[pos];
		token = Vp6ExtractToken(pbi->m_acLookup[prec][plane][band], br, pbi->m_acTree[prec][plane][band]);
		value = g_00BD8B48[token];
		if (token == 0) {
			table = pos >= 6;
			zero = Vp6ExtractToken(pbi->m_zeroLookup[table], br, pbi->m_zeroTree[table]);
			if (zero < 8)
				pos += zero;
			else
				pos += Rva001C4FE0ReadBits(br, 6) + 8;
			prec = 0;
			pos++;
		} else if (token == 11) {
			if (pos == 1) {
				run = Rva001C4FE0ReadBits(br, 2) + 1;
				if (run == 3)
					run = Rva001C4FE0ReadBits(br, 2) + 3;
				else if (run == 4) {
					if (Rva009B47B0ReadBit(br))
						run = Rva001C4FE0ReadBits(br, 6) + 11;
					else
						run = Rva001C4FE0ReadBits(br, 2) + 7;
				}
				pbi->m_acRun[plane] = run - 1;
			}
			goto done;
		} else {
			if (token <= 4)
				sign = br->bit();
			else {
				extra = token - 4;
				if (token > 9)
					extra = 11;
				value += Rva001C4FE0ReadBits(br, extra);
				sign = Rva009B47B0ReadBit(br);
			}
			coeffs[pbi->m_scanOrder[pos]] = (short)((value ^ -sign) + sign);
			prec = (value > 1) + 1;
			pos++;
		}
	} while (pos < 64);
done:
	return pbi->m_eobOffsets[pos - 1];
}
