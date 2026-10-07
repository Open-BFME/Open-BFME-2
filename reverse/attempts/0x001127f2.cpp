// ?rva001127F2@Rva001127F2@@QAE_NAAUICoord2D@@HHHH@Z
// partial score=0.9 date=2026-10-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /O1 /arch:SSE /G7
// FUN_005127f2 at 0x001127F2, 166 bytes. The packet shows the rowed
// Rva00729300BitPlane::test calls and target accesses at +0x50/+0x54/+0x5c;
// class identity and full layout remain address-derived.

typedef unsigned char Byte;
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

class Rva00729300BitPlane
{
public:
	bool test(Int x, Int y) const;
	Byte m_opaque00[8];
	Int m_width;
	Int m_height;
};

class Rva001127F2
{
public:
	bool rva001127F2(ICoord2D &right, Int xOffset, Int yOffset, Int width, Int height);

private:
	Byte m_lead[0x50];
	Int m_xOrigin;
	Int m_yOrigin;
	Int m_opaque58;
	Rva00729300BitPlane *m_map;
};

bool Rva001127F2::rva001127F2(ICoord2D &right, Int xOffset, Int yOffset, Int width, Int height)
{
	register ICoord2D *point = &right;
	register Int maxY = m_map->m_height - m_yOrigin;
	register Int maxX = m_map->m_width - m_xOrigin;
	Int endX = xOffset + width;
	--maxX;
	--maxY;
	if (point->x < endX)
	{
	xloop:
		if (point->x >= maxX)
			goto yscan;
		++point->x;
		if (m_map->test(m_xOrigin + point->x, m_yOrigin + point->y))
			return true;
		if (point->x < endX)
			goto xloop;
	}

	yscan:
	Int endY = yOffset + height - 1;
	if (point->y >= endY)
		return false;
	--maxY;
	yloop:
	if (point->y >= maxY)
		return false;
	++point->y;
	if (m_map->test(m_xOrigin + point->x, m_yOrigin + point->y))
		return true;
	if (point->y < endY)
		goto yloop;
	return false;
}
