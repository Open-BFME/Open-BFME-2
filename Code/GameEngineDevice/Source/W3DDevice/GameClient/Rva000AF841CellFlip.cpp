// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva000AF841@Rva000ABD19@@QAE_NHH@Z
// Retail 0x000AF841 214 bytes RET8. Height-map cell diagonal choice on the
// class of the rowed Rva000ABD19 (cell index y*width(+8)+x checked against
// +0x20 with the 16-bit height array at +0x24). When the rowed presence
// test 0x000ABD19 and the unrowed 0x000AE37E both hold it returns its flip
// flag without writing it (retail reads the never-stored byte from the dead
// y slot; WorldBuilder's twin 0x0076CA30 still fills it through an out
// argument). Otherwise for a cell inside the grid whose corner height span
// times the 1/256 scale (global 0x00DB4D40) exceeds the 0.5 global
// (0x00DB4D3C) it reports abs(p0-p2) > abs(p1-p3) (the dz1 > dz2 flip test
// of WorldHeightMap::getAlphaUVData). abs is the CRT import (0x00629952).

extern "C" int __cdecl abs(int value);

extern float g_00DB4D40;
extern float g_00DB4D3C;

class Rva000ABD19
{
public:
	bool rva000ABD19(int x, int y);
	bool rva000AE37E(int x, int y);
	bool rva000AF841(int x, int y);

	unsigned char m_pad00[8];
	int m_width;                    // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	int m_dataSize;                 // +0x20
	unsigned short *m_data;         // +0x24
};

bool Rva000ABD19::rva000AF841(int x, int y)
{
	bool flip;
	if (rva000ABD19(x, y) && rva000AE37E(x, y))
		return flip;

	int ndx = y * m_width + x;
	if (ndx < 0 || ndx >= m_dataSize || m_data == 0 || ndx >= m_dataSize - m_width - 1)
		return false;

	int p0 = m_data[ndx];
	int p1 = m_data[ndx + 1];
	int p2 = m_data[ndx + m_width + 1];
	int p3 = m_data[ndx + m_width];
	int minH, maxH;
	minH = maxH = p0;
	if (minH > p1)
		minH = p1;
	if (maxH < p1)
		maxH = p1;
	if (minH > p2)
		minH = p2;
	if (maxH < p2)
		maxH = p2;
	if (minH > p3)
		minH = p3;
	if (maxH < p3)
		maxH = p3;
	if ((float)(maxH - minH) * g_00DB4D40 > g_00DB4D3C) {
		int dz1 = abs(p0 - p2);
		int dz2 = abs(p1 - p3);
		return dz1 > dz2;
	}
	return false;
}
