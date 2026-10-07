// cl: /MD /EHsc /DNDEBUG
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
// getMaxCellHeight (0x000670B8) is virtual: vftables 0x007C5FF8 and 0x007CE9D0
// hold it. Its body is the BFME 1 donor's (Open-BFME-1 BaseHeightMap.cpp):
// the local logicHeightMap behind compiler barriers, which keeps the map in
// edi while border size and xExtent are reread from m_map, and the four
// heights sampled at 0.0390625f (0x00BC596C) and folded through __max.
//
// Retail layout read from the bodies: m_map at +0x37C0; WorldHeightMap
// width +0x08, height +0x0C, border size +0x10, height data +0x24. The scale
// is -0.1f (0x00BC5CD0), subtracted from the border.

#include <stdlib.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	bool rva000AE1DC(int xIndex, int yIndex) const;
	int getXExtent() const { return m_width; }
	int getYExtent() const { return m_height; }
	int getBorderSizeInline() const { return m_borderSize; }
	unsigned short *getDataPtr() const { return m_data; }
private:
	char m_unknown00[8];
	int m_width;
	int m_height;
	int m_borderSize;
	char m_unknown14[0x10];
	unsigned short *m_data;
};

class BaseHeightMapRenderObjClass
{
public:
	bool isCliffCell(float x, float y);
	bool rva00067298(float x, float y);
	unsigned char rva00067225(float x, float y);
	unsigned char rva0006730B(float x, float y);
	bool rva0006B114(float x, float y);
	unsigned char rva0006B187(float x, float y);
	virtual float getMaxCellHeight(float x, float y) const;
private:
	char m_unknown0004[0x37C0 - 4];
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

bool BaseHeightMapRenderObjClass::rva00067298(float x, float y)
{
	if (m_map == 0)
		return false;
	int iX = m_map->getBorderSizeInline() - (int)(x * -0.1f);
	int iY = m_map->getBorderSizeInline() - (int)(y * -0.1f);
	if (iX < 0) iX = 0;
	if (iY < 0) iY = 0;
	if (iX >= m_map->getXExtent() - 1) iX = m_map->getXExtent() - 2;
	if (iY >= m_map->getYExtent() - 1) iY = m_map->getYExtent() - 2;
	return m_map->rva000AE1DC(iX, iY);
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

float BaseHeightMapRenderObjClass::getMaxCellHeight(float x, float y) const
{
	float p0,p1,p2,p3;
	float height;
	WorldHeightMap *logicHeightMap = m_map;
	_ReadWriteBarrier();

	if (logicHeightMap == 0)
		return 0.0f;

	int offset = 1;
	int borderSize = m_map->getBorderSizeInline();
	int iX = borderSize - (int)(x * -0.1f);
	int iY = borderSize - (int)(y * -0.1f);
	if (iX<0) iX = 0;
	if (iY<0) iY = 0;
	if (iX >= (logicHeightMap->getXExtent()-1)) {
		iX = logicHeightMap->getXExtent()-2;
	}
	if (iY >= (logicHeightMap->getYExtent()-1)) {
		iY = logicHeightMap->getYExtent()-2;
	}
	register unsigned short *data;
	_ReadWriteBarrier();
	data = logicHeightMap->getDataPtr();
	int xExtent = m_map->getXExtent();
	p0=data[iX+iY*xExtent]*0.0390625f;
	p1=data[(iX+offset)+iY*xExtent]*0.0390625f;
	p2=data[(iX+offset)+(iY+offset)*xExtent]*0.0390625f;
	p3=data[iX+(iY+offset)*xExtent]*0.0390625f;

	height=p0;
	height=__max(height,p1);
	height=__max(height,p2);
	height=__max(height,p3);

	return height;
}
