// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Complete BFME2 [0011204B,00112153),264B, RET12.
// Reference: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DTerrainBackgroundIsEdgeAligned.cpp. Its edge classifier is the
// primary semantic guide. BFME2 shifts the observed terrain prefix by
// 0x10: origins50/54, tile width58, map5C, base divisor88, edge divisors
// A8..C4 and selection modeC8. Map extents remain08/0C.
// Every offset and branch is checked against this complete target body.
// The method name is descriptive; the original spelling is unproved.
// These are borrowed prefix views, not allocation-size assertions.

typedef bool Bool;

class WorldHeightMap
{
public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
};

class W3DTerrainBackground
{
public:
	Bool isEdgeAligned(int x, int y, int requested);

private:
	unsigned char m_pad00[0x50];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0x28];
	int m_baseDivisor;
	unsigned char m_pad8c[0x1c];
	int m_x0Divisor;
	int m_x0Alternate;
	int m_yWidthDivisor;
	int m_yWidthAlternate;
	int m_xWidthDivisor;
	int m_xWidthAlternate;
	int m_y0Divisor;
	int m_y0Alternate;
	int m_mode;
};

// ?isEdgeAligned@W3DTerrainBackground@@QAE_NHHH@Z
Bool W3DTerrainBackground::isEdgeAligned(int x, int y, int requested)
{
	int yValue = y;
	WorldHeightMap *map = m_map;
	int limitY = map->m_height - 1;
	if (yValue != 0)
		goto afterMapRightEdge;
	{
		int limitX = map->m_width - 1;
		if (m_xOrigin + x == limitX)
			goto resultTrue;
	}

afterMapRightEdge:
	if (x != 0)
		goto afterMapBottomEdge;
	if (m_yOrigin + yValue == limitY)
		goto resultTrue;
	if (yValue == 0)
		goto resultTrue;

afterMapBottomEdge:
	{
		int width = m_width;
		if (x == width)
		{
			if (yValue == width)
				goto resultTrue;
		}
		if (x == 0)
		{
			if (yValue == width)
				goto resultTrue;
		}
		if (x == width)
		{
			if (yValue == 0)
				goto resultTrue;
		}
	}

	int divisor;
	if (x == 0) {
		int feature = m_x0Divisor;
		if (!feature)
			divisor = m_baseDivisor;
		else if (m_mode)
			divisor = m_x0Alternate;
		else
			divisor = feature;
		if (requested >= divisor)
			return true;
		if (yValue % divisor == 0)
			goto resultTrue;
		return false;
	}
	if (yValue == 0) {
		int feature = m_y0Divisor;
		if (!feature)
			divisor = m_baseDivisor;
		else if (m_mode)
			divisor = m_y0Alternate;
		else
			divisor = feature;
		if (requested >= divisor)
			return true;
		if (x % divisor == 0)
			goto resultTrue;
		return false;
	}
	if (x == m_width) {
		int feature = m_xWidthDivisor;
		if (!feature)
			divisor = m_baseDivisor;
		else if (m_mode)
			divisor = m_xWidthAlternate;
		else
			divisor = feature;
		if (requested >= divisor)
			return true;
		if (yValue % divisor == 0)
			goto resultTrue;
		return false;
	}
	if (yValue == m_width) {
		int feature = m_yWidthDivisor;
		if (!feature)
			divisor = m_baseDivisor;
		else if (m_mode)
			divisor = m_yWidthAlternate;
		else
			divisor = feature;
		if (requested >= divisor)
			return true;
		if (x % divisor == 0)
			goto resultTrue;
		return false;
	}
resultTrue:
	return true;
}
