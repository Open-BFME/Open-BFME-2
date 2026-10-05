// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva00729300BitPlanes.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva00729300BitPlane::test 0x001126FD (79B), Rva00729370BitPlane::test
// 0x0006AB49 (79B). Callee addresses are read off retail's call sites
// (reverse/symbols.csv). Only the placed bodies are carried; the donor's other
// definitions are omitted.

typedef unsigned char Byte;

struct Rva00729300Bytes
{
	Byte *m_begin;
	Byte *m_end;

	unsigned size() const { return (unsigned)(m_end - m_begin); }
	Byte operator[]( int index ) const { return m_begin[index]; }
};

class Rva00729300BitPlane
{
public:
	bool test( int x, int y ) const;

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x0c];
	Rva00729300Bytes m_bits;
};

class Rva00729370BitPlane
{
public:
	bool test( int x, int y ) const;

public:
	Byte m_opaque00[0x08];
	int m_width;
	int m_height;
	Byte m_opaque10[0x24];
	int m_stride;
	Byte m_opaque38[0x18];
	Rva00729300Bytes m_bits;
};

bool Rva00729300BitPlane::test( int x, int y ) const
{
	register const Rva00729300BitPlane *self = this;
	if( x < 0 || y < 0 || y >= self->m_height || x >= self->m_width )
	{
		return false;
	}

	const int index = self->m_stride * y + (x >> 3);
	if( (unsigned)index >= self->m_bits.size() )
	{
		return false;
	}

	int mask = 1;
	mask <<= x & 7;
	Byte value = self->m_bits[index];
	bool result = (value & mask) != 0;
	return result;
}

// The complete five-body clean BFME1 donor at revision
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 also supplies the
// Rva00729370BitPlane::test source lead. Target Ghidra6AB49/79 and
// complete RET8 independently prove signed bounds against +8/+C,
// stride +34 and byte-range pointers +50/+54. The native final byte
// mask test establishes the return's zero/nonzero meaning. This is a
// separate observed prefix; original owners, full layouts and any
// relationship to the existing +44/+48 bit plane remain unknown.
class Rva0006AB49BitPlane
{
public:
    bool test(int x, int y) const;
private:
    Byte reserved00[8];
    int width;
    int height;
    Byte reserved10[0x24];
    int stride;
    Byte reserved38[0x18];
    Rva00729300Bytes bits;
};

bool Rva0006AB49BitPlane::test(int x, int y) const
{
    register const Rva0006AB49BitPlane *self = this;
    if (x < 0 || y < 0 || y >= self->height || x >= self->width)
        return false;

    const int index = self->stride * y + (x >> 3);
    if ((unsigned)index >= self->bits.size())
        return false;

    int mask = 1;
    mask <<= x & 7;
    Byte value = self->bits[index];
    bool result = (value & mask) != 0;
    return result;
}

class Rva00729D30Terrain
{
public:
	void checkEdges( int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left );

	int rva00729BF0( int xOffset, int yOffset, int width,
		bool *corner0, bool *corner1, bool *corner2, bool *corner3 );

private:
	Byte m_opaque00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};


struct ICoord2D
{
	int x;
	int y;
};

class Rva00729570Terrain
{
public:
	bool advanceRight( ICoord2D &right, int xOffset, int yOffset,
		int width, int height );

private:
	Byte m_pad00[0x40];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	Rva00729300BitPlane *m_map;
};


