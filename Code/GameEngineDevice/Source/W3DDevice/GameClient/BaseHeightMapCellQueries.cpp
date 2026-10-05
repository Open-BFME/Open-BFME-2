// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// BaseHeightMapRenderObjClass per-cell terrain queries.
//
// isCliffCell is ZH BaseHeightMap.cpp's body: null-check m_map, turn the world
// position into a border-adjusted cell, clamp it to the map and ask the
// WorldHeightMap. Target evidence for the name: W3DTerrainLogic::isCliffCell
// (0x00062D94, vftable slot after isUnderwater) forwards to 0x000671B2 with
// ECX=TheTerrainRenderObject. The other bodies are the same code asking
// different per-cell questions; W3DTerrainLogic's next four vftable slots
// (0x00062DB3..0x00062E10) and 0x000802C3 call them. Their names are unknown,
// so they are address-derived.
//
// Retail layout read from the bodies: m_map at +0x37C0; WorldHeightMap
// width +0x08, height +0x0C, border size +0x10. The scale is -0.1f
// (0x00BC5CD0), subtracted from the border.

// Callees retail calls on m_map are rowed under other spellings at the same
// addresses (same ABI); reverse/symbols.csv pins the WorldHeightMap spellings.

class WorldHeightMap
{
public:
	bool getCliffState(int xIndex, int yIndex) const;
	unsigned char rva000AE18D(int xIndex, int yIndex);
	unsigned char rva000AE234(int xIndex, int yIndex);
	bool rva0006AB49(int xIndex, int yIndex) const;
	unsigned char rva0006AB98(int xIndex, int yIndex);
	int getXExtent() const { return m_width; }
	int getYExtent() const { return m_height; }
	int getBorderSizeInline() const { return m_borderSize; }
private:
	char m_unknown00[8];
	int m_width;
	int m_height;
	int m_borderSize;
};

class BaseHeightMapRenderObjClass
{
public:
	bool isCliffCell(float x, float y);
	unsigned char rva00067225(float x, float y);
	unsigned char rva0006730B(float x, float y);
	bool rva0006B114(float x, float y);
	unsigned char rva0006B187(float x, float y);
private:
	char m_unknown0000[0x37C0];
	WorldHeightMap *m_map;
};

bool BaseHeightMapRenderObjClass::isCliffCell(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->getCliffState(iX, iY);
}

unsigned char BaseHeightMapRenderObjClass::rva00067225(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->rva000AE18D(iX, iY);
}

unsigned char BaseHeightMapRenderObjClass::rva0006730B(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->rva000AE234(iX, iY);
}

bool BaseHeightMapRenderObjClass::rva0006B114(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->rva0006AB49(iX, iY);
}

unsigned char BaseHeightMapRenderObjClass::rva0006B187(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->rva0006AB98(iX, iY);
}
