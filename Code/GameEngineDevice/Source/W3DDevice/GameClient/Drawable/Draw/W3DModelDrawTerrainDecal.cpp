// cl: /MD /DNDEBUG
//
// W3DModelDraw::setTerrainDecalSize (retail 0x000B314B, 32 bytes) and
// W3DModelDraw::setTerrainDecalOpacity (0x000B316B, 34 bytes), ported from
// Zero Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DModelDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slots 21 and 22 of the W3DModelDraw-family vtable 0x00BCBFC0
// (installed at 0x000CACA8 and by the destructor 0x000CAEC6; slot-2 name
// getter returns "W3DSupplyDraw"; slot 35 is the rowed W3DModelDraw::setFullyObscuredByShroud).
// Zero Hour's DrawModule declares setTerrainDecal, setTerrainDecalSize and
// setTerrainDecalOpacity in that order, and both bodies are Zero Hour's
// shape: a null test of the terrain decal and setSize(x, y), resp. the rowed
// Shadow::setOpacity with (Int)(255 * o).
// BFME 2 differences (target evidence): Shadow::setSize only stores the two
// sizes (Shadow +0x58/+0x5C; Zero Hour also caches their reciprocals), and
// the decal sits at W3DModelDraw +0x5C. Retail is size-optimised here: the
// opacity setter pushes its argument and calls instead of reusing the
// argument slot for a tail call, which /O2 (W3DModelDraw.cpp's flags) does.

typedef float Real;
typedef int Int;

class Shadow
{
public:
	void setOpacity(Int value);
	void setSize(Real sizeX, Real sizeY)
	{
		m_decalSizeX = sizeX;
		m_decalSizeY = sizeY;
	}
private:
	unsigned char m_pad00[0x58];
	Real m_decalSizeX; // +0x58
	Real m_decalSizeY; // +0x5C
};

class W3DModelDraw
{
public:
	virtual void setTerrainDecalSize(Real x, Real y);
	virtual void setTerrainDecalOpacity(Real o);
private:
	unsigned char m_pad04[0x5C - 0x04];
	Shadow *m_terrainDecal; // +0x5C
};

//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setTerrainDecalSize(Real x, Real y)
{
	if (m_terrainDecal)
	{
		m_terrainDecal->setSize(x,y);
	}
}
//-------------------------------------------------------------------------------------------------
void W3DModelDraw::setTerrainDecalOpacity(Real o)
{
	if (m_terrainDecal)
	{
		m_terrainDecal->setOpacity((Int)(255.0f * o));
	}
}
