// cl: /O1 /G7 /arch:SSE

// Target evidence at 0x000AE490: signed cell bound check, four UV locals,
// helper call at 0x000AC2F6, target global byte +0x4B, cliff-info copy (0x24B),
// texture-class scan (0x28B stride), and terrain height at this+0x120D4.
// The BFME 1 donor WorldHeightMapGetUVForTileIndex.cpp (revision
// 6583b3c1ff21db4a561285717028fdafc780b7db) supplies the same UV and
// cliff-remap behavior. This address-named class view records target offsets;
// it does not assert that the target owner is WorldHeightMap.

struct Rva000AE490CliffInfo
{
	float u0;
	float v0;
	float u1;
	float v1;
	float u2;
	float v2;
	float u3;
	float v3;
	bool flip;
	bool mutant;
	short tileIndex;
};

struct Rva000AE490CliffInfoVector
{
	Rva000AE490CliffInfo *first;
	Rva000AE490CliffInfo *last;
	Rva000AE490CliffInfo *reserved;
};

struct Rva000AE490TextureClass
{
	int firstTile;
	int numTiles;
	int width;
	int flags;
	int blend;
	int positionX;
	int positionY;
	int name;
	int extra;
	int spare;
};

struct Rva000AE6ADBlendTileInfo
{
	short blendNdx;
	unsigned char padding02[2];
	unsigned char horiz;
	unsigned char vert;
	unsigned char rightDiagonal;
	unsigned char leftDiagonal;
	unsigned char inverted;
	unsigned char longDiagonal;
	unsigned char padding0A[2];
	int customBlendEdgeClass;
};

class Rva000AC2F6
{
public:
	void rva000AC2F6(int ndx, float *minU, float *minV, float *maxU,
		float *maxV, bool fullTile);
};

extern void *g_00DFE758;

class Rva000AE490
{
public:
	bool rva000AE490(int ndx, short tileNdx, float U[4], float V[4],
		bool fullTile);
	bool rva000AE6AD(int xIndex, int yIndex, float U[4], float V[4],
		unsigned char alpha[4], bool *needFlip, bool *cliff);

private:
	char m_pad00[8];
	int m_width;
	char m_pad0C[0x20 - 0x0C];
	int m_dataSize;
	char m_pad24[0x98 - 0x24];
	void *m_tileNdxes;
	int m_unknown9C;
	int *m_cliffInfoNdxes;
	int *m_extraBlendTileNdxes;
	char m_padA8[0x80B0 - 0xA8];
	Rva000AE6ADBlendTileInfo *m_blendedTiles;
	char m_pad80B4[0x80BC - 0x80B4];
	Rva000AE490CliffInfoVector m_cliffInfo;
	int m_numTextureClasses;
	char m_padCC[4];
	Rva000AE490TextureClass m_textureClasses[0x200];
	char m_padD0D0[0x5004];
	int m_terrainTexHeight;
};

bool Rva000AE490::rva000AE490(int ndx, short tileNdx, float U[4],
	float V[4], bool fullTile)
{
	float nU, nV, xU, xV;
	nU = nV = xU = xV = 0.0f;
	int tilesPerRow = 2048 / (2 * 64);
	tilesPerRow *= 4;

	if ((ndx < m_dataSize) && m_tileNdxes)
	{
		((Rva000AC2F6 *)this)->rva000AC2F6(tileNdx, &nU, &nV, &xU, &xV,
			fullTile);
		U[0] = nU;
		U[1] = xU;
		U[2] = xU;
		U[3] = nU;
		V[0] = xV;
		V[1] = xV;
		V[2] = nV;
		V[3] = nV;
		if (g_00DFE758 && !((unsigned char *)g_00DFE758)[0x4B])
			return false;
		if (nU == 0.0)
			return false;
		if (fullTile)
			return false;
		if (m_cliffInfoNdxes[ndx])
		{
			Rva000AE490CliffInfo *cliffInfo = m_cliffInfo.first;
			Rva000AE490CliffInfo info = cliffInfo[m_cliffInfoNdxes[ndx]];
			bool tilesMatch = false;
			register int ndx1 = tileNdx >> 2;
			register int ndx2 = info.tileIndex >> 2;
			register int i;
			for (i = 0; i < m_numTextureClasses; i++)
			{
				if (ndx1 >= m_textureClasses[i].firstTile &&
					ndx1 < m_textureClasses[i].firstTile + m_textureClasses[i].numTiles)
				{
					tilesMatch = ndx2 >= m_textureClasses[i].firstTile &&
						ndx2 < m_textureClasses[i].firstTile + m_textureClasses[i].numTiles;
					break;
				}
			}
			if (tilesMatch)
			{
				float minU = (float)m_textureClasses[i].positionX;
				float maxV = (float)(m_textureClasses[i].positionY +
					m_textureClasses[i].width * 64);
				minU *= 0.00048828125f;
				maxV /= m_terrainTexHeight;
				float vFactor = 2048 / m_terrainTexHeight;
				U[0] = info.u0 + minU;
				U[1] = info.u1 + minU;
				U[2] = info.u2 + minU;
				U[3] = info.u3 + minU;
				V[0] = info.v0 * vFactor + maxV;
				V[1] = info.v1 * vFactor + maxV;
				V[2] = info.v2 * vFactor + maxV;
				V[3] = info.v3 * vFactor + maxV;
				return info.flip;
			}
		}
	}
	return false;
}

// Target evidence at 0x000AE6AD: width +0x08, data size +0x20, tile map
// +0x98, blend map +0xA4, blend records +0x80B0, and a direct call to
// 0x000AE490. The BFME 1 donor WorldHeightMapGetExtraAlphaUVData.cpp (revision
// 6583b3c1ff21db4a561285717028fdafc780b7db) supplies the same tile lookup, UV
// call, and blend-flag behavior; owner and field names remain address-derived
// where target evidence does not establish them.
bool Rva000AE490::rva000AE6AD(int xIndex, int yIndex, float U[4],
	float V[4], unsigned char alpha[4], bool *needFlip, bool *cliff)
{
	int ndx = (yIndex * m_width) + xIndex;
	register int zero = 0;
#define RVA000AE6AD_NEED_FLIP \
	(*needFlip)
	RVA000AE6AD_NEED_FLIP = zero;
	*cliff = zero;

	if ((ndx >= 0) && (ndx < m_dataSize) && m_tileNdxes)
	{
		int blendNdx = m_extraBlendTileNdxes[ndx];
		if (blendNdx == zero)
		{
			return 0;
		}
		else
		{
			const unsigned int blendBaseForCall =
				(unsigned int)m_blendedTiles;
			*cliff = rva000AE490(ndx,
				*(short *)((blendNdx << 4) + blendBaseForCall),
				U, V, zero);
			alpha[0] = alpha[1] = alpha[2] = alpha[3] = zero;
			const unsigned int blendBaseForHoriz =
				(unsigned int)m_blendedTiles;
			if (*(const unsigned char *)((blendNdx << 4) +
				blendBaseForHoriz + 4))
			{
				RVA000AE6AD_NEED_FLIP = m_blendedTiles[blendNdx].inverted & 0x2;
				if (m_blendedTiles[blendNdx].inverted & 0x1)
				{
					alpha[0] = alpha[3] = 255;
				}
				else
				{
					alpha[1] = alpha[2] = 255;
				}
			}
			if (m_blendedTiles[blendNdx].vert)
			{
				RVA000AE6AD_NEED_FLIP = m_blendedTiles[blendNdx].inverted & 0x2;
				if (m_blendedTiles[blendNdx].inverted & 0x1)
				{
					alpha[0] = alpha[1] = 255;
				}
				else
				{
					alpha[2] = alpha[3] = 255;
				}
			}
			if (m_blendedTiles[blendNdx].rightDiagonal)
			{
				if (m_blendedTiles[blendNdx].inverted & 0x1)
				{
					alpha[1] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal)
					{
						alpha[0] = 255;
						alpha[2] = 255;
					}
				}
				else
				{
					RVA000AE6AD_NEED_FLIP = 1;
					alpha[2] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal)
					{
						alpha[1] = 255;
						alpha[3] = 255;
					}
				}
			}
			if (m_blendedTiles[blendNdx].leftDiagonal)
			{
				if (m_blendedTiles[blendNdx].inverted & 0x1)
				{
					RVA000AE6AD_NEED_FLIP = 1;
					alpha[0] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal)
					{
						alpha[1] = 255;
						alpha[3] = 255;
					}
				}
				else
				{
					alpha[3] = 255;
					if (m_blendedTiles[blendNdx].longDiagonal)
					{
						alpha[0] = 255;
						alpha[2] = 255;
					}
				}
			}
			if (m_blendedTiles[blendNdx].customBlendEdgeClass >= zero)
			{
				alpha[0] = alpha[1] = alpha[2] = alpha[3] = zero;
				RVA000AE6AD_NEED_FLIP = zero;
			}
		}
	}

	return 1;
}

#undef RVA000AE6AD_NEED_FLIP
