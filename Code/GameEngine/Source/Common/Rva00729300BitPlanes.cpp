// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
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

// BFME1 donor ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f supplies the
// corner-count and edge-sampling algorithms below. Independent target
// boundaries 112ED3..112FC0 (237B) and 112FC0..1130D1 (273B) prove seven
// stack arguments, the four byte outputs, signed upper clamps and division
// by two truncated toward zero. Native origins are +50/+54 and the pointer
// to the independently matched bit plane is +5C, sixteen bytes later than
// the donor receiver. These are observed borrowed prefixes; original owner,
// method names, geographical edge labels and allocation extent are unproven.
// Keep the bit-test definition visible: separate-TU trials changed one
// load/push scheduling pair in each receiver despite the same extents.
// /O1 with ordinary frame omission matches both new receiver bodies and
// the two pre-existing 79B bit tests; forced /Oy- changes the old tests.
class Rva00112ED3TerrainPrefix
{
public:
	void checkUnsetEdges( int xOffset, int yOffset, int width,
		bool *top, bool *right, bool *bottom, bool *left );

	int countUnsetCorners( int xOffset, int yOffset, int width,
		bool *corner0, bool *corner1, bool *corner2, bool *corner3 );

private:
	Byte m_opaque00[0x50];
	int m_xOrigin;
	int m_yOrigin;
	int m_unmodelled58;
	Rva00729300BitPlane *m_map;
};

void Rva00112ED3TerrainPrefix::checkUnsetEdges( int xOffset, int yOffset, int width,
	bool *top, bool *right, bool *bottom, bool *left )
{
	int xOrigin = m_xOrigin;
	Rva00729300BitPlane *map = m_map;
	int limitX = map->m_width - 1;
	int limitY = map->m_height - 1;
	int minX = xOrigin + xOffset;
	int minY = m_yOrigin + yOffset;
	int maxX = xOffset + width;
	if( m_xOrigin + maxX > limitX )
		maxX = limitX - m_xOrigin;
	register int maxY = yOffset + width;
	if( m_yOrigin + maxY > limitY )
		maxY = limitY - m_yOrigin;

	int halfX = (maxX - xOffset) / 2;
	int halfY = (maxY - yOffset) / 2;
	int centerX = xOffset + halfX;
	int centerY = yOffset + halfY;
	*top = *right = *bottom = *left = false;
	if( !m_map->test( minX, m_yOrigin + centerY ) )
		*top = true;
	if( !m_map->test( m_xOrigin + centerX, maxY + m_yOrigin ) )
		*right = true;
	if( !m_map->test( m_xOrigin + maxX, m_yOrigin + centerY ) )
		*bottom = true;
	if( !m_map->test( m_xOrigin + centerX, minY ) )
		*left = true;
}

int Rva00112ED3TerrainPrefix::countUnsetCorners(int xOffset, int yOffset, int width, bool *corner0, bool *corner1, bool *corner2, bool *corner3)
{
	int xOrigin = m_xOrigin;
	Rva00729300BitPlane *map = m_map;
	int limitX = map->m_width - 1;
	int limitY = map->m_height - 1;
	int minX = xOrigin + xOffset;
	int minY = m_yOrigin + yOffset;
	int maxX = xOffset + width;
	if (m_xOrigin + maxX > limitX)
		maxX = limitX - m_xOrigin;
	register int maxY = yOffset + width;
	if (m_yOrigin + maxY > limitY)
		maxY = limitY - m_yOrigin;
	int count = 0;
	*corner0 = *corner1 = *corner2 = *corner3 = false;
	if (!m_map->test(minX, minY))
	{
		*corner0 = true;
		++count;
	}
	if (!m_map->test(m_xOrigin + maxX, minY))
	{
		*corner1 = true;
		++count;
	}
	if (!m_map->test(minX, m_yOrigin + maxY))
	{
		*corner2 = true;
		++count;
	}
	if (!m_map->test(m_xOrigin + maxX, m_yOrigin + maxY))
	{
		*corner3 = true;
		++count;
	}
	return count;
}


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


