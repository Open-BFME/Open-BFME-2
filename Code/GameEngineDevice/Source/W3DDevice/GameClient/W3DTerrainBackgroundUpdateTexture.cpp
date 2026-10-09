// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [001125BE,001126FD),319B, RET0. BFME 2 W3DTerrainBackground::
// updateTexture (WorldBuilder places it in W3DTerrainBackground.cpp; the ZH
// updateTexture is the semantic guide). BFME 2 returns whether it built a
// texture, culls on three camera statuses (+0x00..+0x08, 1 = visible) and
// keeps the 1x/flat texture at +0x38 and the second texture at +0x40.
// Target facts: multiplier +0x44, origin +0x50/+0x54, width +0x58, map
// +0x5C, surface flag +0x84, TheGlobalData +0xEA0 and +0x49 gates, the
// 0x000AE989 map texture builder taking (x, y, width, 0x20, 0x19, second).
// Holder methods are reached through the ledger's names for their folded
// bodies (0x0004D75B clear, 0x000424D0 assign, 0x00132856 filter,
// 0x00132989 surface fill); the views are borrowed, not asserted types.

class TextureClass
{
public:
	void Release_Ref();
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr()
	{
		if (m_referent)
			m_referent->Release_Ref();
	}
	const RefCountPtr<T> &operator=(const RefCountPtr<T> &rhs);
	bool isNull() const { return m_referent == 0; }

private:
	T *m_referent;
};

struct BfmeResetTextureRef
{
	void clear();
};

class ShroudFilter
{
public:
	int m_pad00[3];
	int m_uAddressMode;
	int m_vAddressMode;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class CursorTextureSlot
{
public:
	void FillLevelSurfaces();
};

class WorldHeightMap
{
public:
	RefCountPtr<TextureClass> rva000AE989(int xCell, int yCell, int cellWidth,
		int pixelsPerCell, int format, bool second);
};

class GlobalData
{
public:
	unsigned char m_pad00[0x49];
	bool m_secondTerrainTexture;
	unsigned char m_pad4a[0xEA0 - 0x4A];
	int m_stretchTerrain;
};

extern GlobalData *TheGlobalData;

class W3DTerrainBackground
{
public:
	bool updateTexture(void);

private:
	__forceinline bool isCulled()
	{
		for (int i = 0; i < 3; i++) {
			if (m_cullStatus[i] == 1)
				return false;
		}
		return true;
	}

	__forceinline void clearTextures()
	{
		((BfmeResetTextureRef *)&m_terrainTexture)->clear();
		((BfmeResetTextureRef *)&m_terrainTexture2)->clear();
	}

	int m_cullStatus[3];
	unsigned char m_pad0c[0x38 - 0x0C];
	RefCountPtr<TextureClass> m_terrainTexture;
	unsigned char m_pad3c[0x40 - 0x3C];
	RefCountPtr<TextureClass> m_terrainTexture2;
	int m_texMultiplier;
	unsigned char m_pad48[0x50 - 0x48];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0x84 - 0x60];
	bool m_fillSurfaces;
};

bool W3DTerrainBackground::updateTexture(void)
{
	if (isCulled()) {
		clearTextures();
		return false;
	}

	if (m_texMultiplier == 2 || TheGlobalData->m_stretchTerrain) {
		if (m_terrainTexture.isNull()) {
			m_terrainTexture = m_map->rva000AE989(m_xOrigin, m_yOrigin, m_width, 0x20, 0x19, false);
			((ShroudTexture *)&m_terrainTexture)->getFilter()->m_uAddressMode = 1;
			((ShroudTexture *)&m_terrainTexture)->getFilter()->m_vAddressMode = 1;
			if (m_fillSurfaces)
				((CursorTextureSlot *)&m_terrainTexture)->FillLevelSurfaces();

			if (TheGlobalData->m_secondTerrainTexture && m_terrainTexture2.isNull()) {
				m_terrainTexture2 = m_map->rva000AE989(m_xOrigin, m_yOrigin, m_width, 0x20, 0x19, true);
				((ShroudTexture *)&m_terrainTexture2)->getFilter()->m_uAddressMode = 1;
				((ShroudTexture *)&m_terrainTexture2)->getFilter()->m_vAddressMode = 1;
				if (m_fillSurfaces)
					((CursorTextureSlot *)&m_terrainTexture2)->FillLevelSurfaces();
			}
			return true;
		}
	} else {
		clearTextures();
	}
	return false;
}
