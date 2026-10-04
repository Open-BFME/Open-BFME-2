// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva006BE630BitQuery.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva006BE630::bfmeBitA 0x00062EA9 (79B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Near-twin of Gen_0074B410::bfmeBitA (twin 0x0074B410,
// BfmeBitPlaneQueries.cpp): identical bounds-checked bit-test shape (same
// family as the already-landed Gen_0074BA50/BAC0/BB30 siblings in that file),
// but the byte-mask begin/end pair sits at +0x5c/+0x60 here -- 0x24 more
// padding after the stride than Gen_0074BA50 has.  Address-derived identity.

struct Rva006BE630Bytes
{
	unsigned char *m_begin;
	unsigned char *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	unsigned char operator[](int index) const { return m_begin[index]; }
};

class Rva006BE630
{
public:
	bool bfmeBitA(int x, int y) const;

private:
	unsigned char m_opaque00[0x08];
	int m_width;
	int m_height;
	unsigned char m_opaque10[0x24];
	int m_stride;
	unsigned char m_opaque38[0x24];
	Rva006BE630Bytes m_bits;
};

// @?bfmeBitA@Rva006BE630@@QBE_NHH@Z 0x006BE630
bool Rva006BE630::bfmeBitA(int x, int y) const
{
	register const Rva006BE630 *self = this;
	if (x < 0 || y < 0 || y >= self->m_height || x >= self->m_width)
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if ((unsigned)index >= self->m_bits.size())
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	unsigned char value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}
