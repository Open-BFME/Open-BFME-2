// cl: /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
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

// The m_map cell queries are rowed under the addresses' owner spellings
// (reverse/functions.csv); call them through their owner views.
class Rva0006AB49BitPlane { public: bool test(int xIndex, int yIndex) const; };
class Rva0006AB98 { public: unsigned char rva0006AB98(int xIndex, int yIndex); };
class BfmeGridWM { public: unsigned char rva000AE18D(int xIndex, int yIndex); };
class Gen_0074BB30 { public: bool bfmeBitA(int xIndex, int yIndex) const; };
class Rva000AE234 { public: char rva000AE234(int xIndex, int yIndex); };
class Gen_0074BA50 { public: bool bfmeBitA(int xIndex, int yIndex) const; };

#include "../../../Include/W3DDevice/GameClient/WorldHeightMap.h"

// Use the canonical RefCountClass above instead of the donor refcount.h.
#define REFCOUNT_H

#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"

// Select the const accessors to preserve this object's existing COMDAT providers.
// The border is read directly so no additional accessor body is emitted.

bool BaseHeightMapRenderObjClass::isCliffCell(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return ((Gen_0074BA50 *)m_map)->bfmeBitA(cellX, cellY);
}

bool BaseHeightMapRenderObjClass::rva00067298(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return ((Gen_0074BB30 *)m_map)->bfmeBitA(cellX, cellY);
}

unsigned char BaseHeightMapRenderObjClass::rva00067225(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return ((BfmeGridWM *)m_map)->rva000AE18D(cellX, cellY);
}

unsigned char BaseHeightMapRenderObjClass::rva0006730B(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return (unsigned char)((Rva000AE234 *)m_map)->rva000AE234(cellX, cellY);
}

bool BaseHeightMapRenderObjClass::rva0006B114(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return ((Rva0006AB49BitPlane *)m_map)->test(cellX, cellY);
}

unsigned char BaseHeightMapRenderObjClass::rva0006B187(float x, float y)
{
	if (m_map == 0)
		return false;
	int cellX = m_map->m_borderSize - (int)(x * -0.1f);
	int cellY = m_map->m_borderSize - (int)(y * -0.1f);
	if (cellX < 0) cellX = 0;
	if (cellY < 0) cellY = 0;
	if (cellX >= static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 1) cellX = static_cast<const WorldHeightMap *>(m_map)->getXExtent() - 2;
	if (cellY >= static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 1) cellY = static_cast<const WorldHeightMap *>(m_map)->getYExtent() - 2;
	return ((Rva0006AB98 *)m_map)->rva0006AB98(cellX, cellY);
}

float BaseHeightMapRenderObjClass::getMaxCellHeight(float x, float y) const
{
	float baseCornerHeight,adjacentXHeight,diagonalHeight,adjacentYHeight;
	float height;
	const WorldHeightMap *logicHeightMap = m_map;
	_ReadWriteBarrier();

	if (logicHeightMap == 0)
		return 0.0f;

	int offset = 1;
	int borderSize = m_map->m_borderSize;
	int cellX = borderSize - (int)(x * -0.1f);
	int cellY = borderSize - (int)(y * -0.1f);
	if (cellX<0) cellX = 0;
	if (cellY<0) cellY = 0;
	if (cellX >= (logicHeightMap->getXExtent()-1)) {
		cellX = logicHeightMap->getXExtent()-2;
	}
	if (cellY >= (logicHeightMap->getYExtent()-1)) {
		cellY = logicHeightMap->getYExtent()-2;
	}
	register unsigned short *data;
	_ReadWriteBarrier();
	data = logicHeightMap->getDataPtr();
	int xExtent = static_cast<const WorldHeightMap *>(m_map)->getXExtent();
	baseCornerHeight=data[cellX+cellY*xExtent]*0.0390625f;
	adjacentXHeight=data[(cellX+offset)+cellY*xExtent]*0.0390625f;
	diagonalHeight=data[(cellX+offset)+(cellY+offset)*xExtent]*0.0390625f;
	adjacentYHeight=data[cellX+(cellY+offset)*xExtent]*0.0390625f;

	height=baseCornerHeight;
	height=__max(height,adjacentXHeight);
	height=__max(height,diagonalHeight);
	height=__max(height,adjacentYHeight);

	return height;
}
