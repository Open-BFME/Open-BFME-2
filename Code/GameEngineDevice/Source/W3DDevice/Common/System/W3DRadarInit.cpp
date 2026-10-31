// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// Native [0004E3F1,0004E490),159B, RET0 and [0004E7D2,0004EB00),814B, RET0.
// BFME 2 W3DRadar::init with its terrain-image helper; the ZH W3DRadar::init
// (W3DRadar.cpp: texture formats, terrain texture, terrain Image with
// raw-texture status, flipped UV, texture and image sizes) is the semantic
// guide. BFME 2 builds four textures (formats +0x1468/+0x1478/+0x1484/+0x1490
// into the holders +0x1470/+0x1480/+0x148C/+0x1498 through 0x00131DFC, the
// last two with clamped filters) and four Images (+0x146C/+0x147C/+0x1488/
// +0x1494); the first Image is configured by the helper, which picks the
// holder at +0x1474 instead of +0x1470 when +0x14D5 is set. Texture size is
// +0x149C/+0x14A0. init overrides the SubsystemInterface slot of the second
// base (+0x04), so it runs on the adjusted this. Every offset is target
// evidence; the helper name is address-derived.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "GameClient/Image.h"
#include "W3DDevice/Common/W3DRadar.h"

class BfmeMapPictureTexture
{
	void *m_ptr;
};

// The texture filter block, reached through the ledger's name for the
// folded holder accessor 0x00132856.
class ShroudFilter
{
public:
	Int m_minFilter;
	Int m_magFilter;
	Int m_mipFilter;
	Int m_uAddressMode;
	Int m_vAddressMode;
};

class ShroudTexture
{
public:
	ShroudFilter *getFilter(void);
};

class Rva00131DFC
{
public:
	void rva00131DFC(void *width, void *height, void *format, void *levels, Int a, Int b);
};

void W3DRadar::rva0004E3F1(void)
{
	Region2D uv;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	const CursorTextureSlot &texture = m_useAltTerrainTexture ? m_terrainTextureAlt : m_terrainTexture;
	m_terrainImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	m_terrainImage->bfmeSetTexture(reinterpret_cast<const BfmeMapPictureTexture &>(texture));
	m_terrainImage->setUV(&uv);
	m_terrainImage->setTextureWidth(m_textureWidth);
	m_terrainImage->setTextureHeight(m_textureHeight);
	ICoord2D size;
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_terrainImage->setImageSize(&size);
}

void W3DRadar::init(void)
{
	initializeTextureFormats();

	((Rva00131DFC *)&m_terrainTexture)->rva00131DFC((void *)m_textureWidth, (void *)m_textureHeight,
		(void *)m_terrainTextureFormat, (void *)1, 1, 0);
	((Rva00131DFC *)&m_overlayTexture)->rva00131DFC((void *)m_textureWidth, (void *)m_textureHeight,
		(void *)m_overlayTextureFormat, (void *)1, 1, 0);
	((Rva00131DFC *)&m_shroudTexture)->rva00131DFC((void *)m_textureWidth, (void *)m_textureHeight,
		(void *)m_shroudTextureFormat, (void *)1, 1, 0);
	((ShroudTexture *)&m_shroudTexture)->getFilter()->m_minFilter = 4;
	((ShroudTexture *)&m_shroudTexture)->getFilter()->m_magFilter = 4;
	((ShroudTexture *)&m_shroudTexture)->getFilter()->m_uAddressMode = 1;
	((ShroudTexture *)&m_shroudTexture)->getFilter()->m_vAddressMode = 1;
	((Rva00131DFC *)&m_fogTexture)->rva00131DFC((void *)m_textureWidth, (void *)m_textureHeight,
		(void *)m_fogTextureFormat, (void *)1, 1, 0);
	((ShroudTexture *)&m_fogTexture)->getFilter()->m_minFilter = 4;
	((ShroudTexture *)&m_fogTexture)->getFilter()->m_magFilter = 4;

	m_terrainImage = new Image;
	rva0004E3F1();

	Region2D uv;
	ICoord2D size;

	m_overlayImage = new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_overlayImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	m_overlayImage->bfmeSetTexture(reinterpret_cast<const BfmeMapPictureTexture &>(m_overlayTexture));
	m_overlayImage->setUV(&uv);
	m_overlayImage->setTextureWidth(m_textureWidth);
	m_overlayImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_overlayImage->setImageSize(&size);

	m_shroudImage = new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_shroudImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	m_shroudImage->bfmeSetTexture(reinterpret_cast<const BfmeMapPictureTexture &>(m_shroudTexture));
	m_shroudImage->setUV(&uv);
	m_shroudImage->setTextureWidth(m_textureWidth);
	m_shroudImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_shroudImage->setImageSize(&size);

	m_fogImage = new Image;
	uv.lo.x = 0.0f;
	uv.lo.y = 1.0f;
	uv.hi.x = 1.0f;
	uv.hi.y = 0.0f;
	m_fogImage->setStatus(IMAGE_STATUS_RAW_TEXTURE);
	m_fogImage->bfmeSetTexture(reinterpret_cast<const BfmeMapPictureTexture &>(m_fogTexture));
	m_fogImage->setUV(&uv);
	m_fogImage->setTextureWidth(m_textureWidth);
	m_fogImage->setTextureHeight(m_textureHeight);
	size.x = m_textureWidth;
	size.y = m_textureHeight;
	m_fogImage->setImageSize(&size);
}
