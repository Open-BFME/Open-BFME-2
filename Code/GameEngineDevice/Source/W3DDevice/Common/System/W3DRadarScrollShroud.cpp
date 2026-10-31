// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// ?rva0004F580@W3DRadar@@UAEXXZ, retail 0x0004F580..0x0004F7D8 (600 bytes, EH).
// W3DRadar primary vftable 0x00BC4E34 slot 8 (the step W3DRadar::reset calls
// first): clears the texture held at +0x148C, then copies the "ScrollShroud"
// mapped image into it. The image's texture holder (+0x2C) is used when present,
// else the image file is loaded (0x00132D89, cached handle) and flagged
// (0x00132FE9). Under the DX8 device lock both top surfaces are locked
// (source read-only), equal-sized A8R8G8B8/A4R4G4B4 rows are copied (a size
// mismatch clears the destination), both are unlocked and +0x14D6 is set.
// Purpose and every offset/slot are read from the retail bytes; names of the
// method and of the +0x148C/+0x14D6 members are not recovered.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "GameClient/Image.h"
#include "W3DDevice/Common/W3DRadar.h"
#include "WW3D2/Texture.h"
#include "WW3D2/dx8wrapper.h"
#include "ascii_string.h"

extern void BFME_DX8_Thread_Lock(void);
extern bool BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// Retail's surface slots, reached through W3DRadarResetSurface::m_surface.
struct BfmeD3DSurface
{
	virtual long __stdcall QueryInterface(void);
	virtual unsigned long __stdcall AddRef(void);
	virtual unsigned long __stdcall Release(void);
	virtual long __stdcall GetDevice(void);
	virtual long __stdcall SetPrivateData(void);
	virtual long __stdcall GetPrivateData(void);
	virtual long __stdcall FreePrivateData(void);
	virtual long __stdcall GetContainer(void);
	virtual long __stdcall GetDesc(void);
	virtual long __stdcall unused09(void);
	virtual long __stdcall unused10(void);
	virtual long __stdcall unused11(void);
	virtual long __stdcall unused12(void);
	virtual long __stdcall LockRect(D3DLOCKED_RECT *locked, const RECT *rect, unsigned long flags);	// +0x34
	virtual long __stdcall UnlockRect(void);								// +0x38
};

enum
{
	BFME_D3DFMT_A8R8G8B8 = 21,
	BFME_D3DFMT_A4R4G4B4 = 26,
	BFME_D3DLOCK_READONLY = 0x10
};

class BFME2ParticleTextureHandle
{
public:
	~BFME2ParticleTextureHandle() { if (m_ptr) m_ptr->Release_Ref(); }
	TextureClass *m_ptr;
};


class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *filename, int a, int b);
	void rva00132FE9(bool flag);
};

void W3DRadar::rva0004F580()
{
	m_scrollShroudLoaded = false;
	m_shroudTexture.Get_Surface_Level().clear(false);

	const Image *image = TheMappedImageCollection->findImageByName(AsciiString("ScrollShroud"));
	if (!image)
		return;

	BFME2ParticleTextureHandle texture = TextureAsset::Get(image->getFilename().str(), 1, 0);
	((TextureAsset *)&texture)->rva00132FE9(true);

	CursorTextureSlot *slot = image->getRawTextureData() ? (CursorTextureSlot *)image->getRawTextureData() : (CursorTextureSlot *)&texture;
	if (slot)
	{
		W3DRadarResetSurface srcSurface = slot->Get_Surface_Level();
		W3DRadarResetSurface dstSurface = m_shroudTexture.Get_Surface_Level();
		SurfaceClass::SurfaceDescription srcDesc;
		SurfaceClass::SurfaceDescription dstDesc;
		((SurfaceClass *)&srcSurface)->Get_Description(srcDesc);
		((SurfaceClass *)&dstSurface)->Get_Description(dstDesc);
		if (srcDesc.Format == dstDesc.Format)
		{
			BFMEDX8DeviceLock lock;
			BfmeD3DSurface *src = (BfmeD3DSurface *)srcSurface.m_surface;
			BfmeD3DSurface *dst = (BfmeD3DSurface *)dstSurface.m_surface;
			if (src && dst)
			{
				D3DLOCKED_RECT srcRect;
				D3DLOCKED_RECT dstRect;
				memset(&srcRect, 0, sizeof(srcRect));
				memset(&dstRect, 0, sizeof(dstRect));
				DX8_ErrorCode(src->LockRect(&srcRect, 0, BFME_D3DLOCK_READONLY));
				DX8_ErrorCode(dst->LockRect(&dstRect, 0, 0));
				if (srcDesc.Width == dstDesc.Width && srcDesc.Height == dstDesc.Height)
				{
					int bytesPerPixel;
					if (srcDesc.Format == BFME_D3DFMT_A8R8G8B8)
						bytesPerPixel = 4;
					else if (srcDesc.Format == BFME_D3DFMT_A4R4G4B4)
						bytesPerPixel = 2;
					else
						goto unlock;
					unsigned char *srcBits = (unsigned char *)srcRect.pBits;
					unsigned char *dstBits = (unsigned char *)dstRect.pBits;
					for (int y = dstDesc.Height - 1; y >= 0; --y)
					{
						memcpy(dstBits, srcBits, bytesPerPixel * dstDesc.Width);
						srcBits += srcRect.Pitch;
						dstBits += dstRect.Pitch;
					}
				}
				else if (dstDesc.Format == BFME_D3DFMT_A8R8G8B8 || dstDesc.Format == BFME_D3DFMT_A4R4G4B4)
				{
					memset(dstRect.pBits, 0, dstRect.Pitch * dstDesc.Height);
				}
unlock:
				DX8_ErrorCode(dst->UnlockRect());
				DX8_ErrorCode(src->UnlockRect());
				m_scrollShroudLoaded = true;
			}
		}
	}
}
