// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?addShadow@W3DShadowManager@@QAEPAVShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@2@PAVDrawable@@@Z
// Retail 0x0009A8D3..0x0009AA01 (302 bytes).
// BFME 2 shape of Zero Hour's W3DShadowManager::addShadow (W3DShadow.cpp):
// the shadow type defaults to 2 (volume) or comes from shadowInfo +8; types
// 0x4000 and 0x8000 are first resolved through TheGlobalData's byte at +0x60
// (set: 0x4000 -> 2 and 0x8000 -> 4; clear: 1) on a local copy of the info.
// Then types 2/0x80/0x100/0x200 go to the volumetric manager (0x00DEBCD8)
// types 1/0x20/0x40/0x400/0x800/0x1000 to the projected manager
// (0x00DEC2D8) and type 4 to the V2 manager (0x00DEC2CC); a missing manager
// gives NULL and any other type returns NULL.
// Evidence: WorldBuilder 0x00778800 has the same flow constants and calls.
// Rowed callees W3DVolumetricShadowManager::addShadow 0x000F2BB9
// W3DProjectedShadowManager::addShadow 0x0010C578 and
// W3DVolumetricShadowManagerV2::rva0010837F 0x0010837F fix which manager
// each global holds; data rows TheW3DVolumetricShadowManager (0x009EBCD8)
// Rva00DEC2D8Manager (0x009EC2D8; it holds the projected manager here) and
// the 0x009EC2CC alias TheW3DShadowHelperManager (V2 manager).
// The local info copy is constructed assigned and destroyed by the rows
// 0x00079514 / 0x0009A41B / 0x000793FA that the ledger names
// AudioEventRTS (their two-string / int type at +8 / five-Real layout is the
// shadow type info's); the view below derives ShadowTypeInfo from that name
// so the copy calls exactly those rows.
#include "ascii_string.h"

class RenderObjClass;
class Drawable;
class W3DVolumetricShadow;
class W3DProjectedShadow;
class W3DVolumetricShadowV2;

class AudioEventRTS
{
public:
	AudioEventRTS();
	AudioEventRTS &operator=(const AudioEventRTS &that);
	~AudioEventRTS();
	AsciiString m_name0;  // +0x00
	AsciiString m_name4;  // +0x04
	int m_type;           // +0x08
	float m_reals[6];     // +0x0C
	unsigned char m_flags[4]; // +0x24
};

class Shadow
{
public:
	struct ShadowTypeInfo : public AudioEventRTS
	{
	};
};

class W3DVolumetricShadowManager
{
public:
	W3DVolumetricShadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

class W3DProjectedShadowManager
{
public:
	W3DProjectedShadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

class W3DVolumetricShadowManagerV2
{
public:
	W3DVolumetricShadowV2 *rva0010837F(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

class Rva00108660ResourceManager;

extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;
extern Rva00108660ResourceManager *Rva00DEC2D8Manager;
extern W3DVolumetricShadowManagerV2 *TheW3DShadowHelperManager;

class GlobalData
{
public:
	unsigned char m_pad00[0x60];
	bool m_60; // +0x60
};
extern GlobalData *TheWritableGlobalData;

class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

Shadow *W3DShadowManager::addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
	int type = 2;
	if (shadowInfo)
		type = shadowInfo->m_type;

	Shadow::ShadowTypeInfo localInfo;
	if (shadowInfo && (type == 0x4000 || type == 0x8000))
	{
		if (TheWritableGlobalData->m_60)
		{
			if (type == 0x4000)
				type = 2;
			else if (type == 0x8000)
				type = 4;
		}
		else
		{
			type = 1;
		}
		localInfo = *shadowInfo;
		shadowInfo = &localInfo;
		shadowInfo->m_type = type;
	}

	switch (type)
	{
	case 2:
	case 0x80:
	case 0x100:
	case 0x200:
		if (TheW3DVolumetricShadowManager)
			return (Shadow *)TheW3DVolumetricShadowManager->addShadow(robj, shadowInfo, draw);
		break;
	case 1:
	case 0x20:
	case 0x40:
	case 0x400:
	case 0x800:
	case 0x1000:
		if (Rva00DEC2D8Manager)
			return (Shadow *)((W3DProjectedShadowManager *)Rva00DEC2D8Manager)->addShadow(robj, shadowInfo, draw);
		break;
	case 4:
		if (TheW3DShadowHelperManager)
			return (Shadow *)TheW3DShadowHelperManager->rva0010837F(robj, shadowInfo, draw);
		break;
	default:
		return 0;
	}
	return 0;
}
