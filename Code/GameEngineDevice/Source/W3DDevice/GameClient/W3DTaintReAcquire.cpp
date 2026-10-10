// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?ReAcquireResources@W3DTaint@@QAE_NXZ retail 0x00073816..0x000738C4 (174B).
// Identity: WB W3DTaint.cpp:217 ("Failed ReAcquire of taint texture") names the
// owner; ZH W3DShroud::ReAcquireResources is the semantic donor (width gate,
// create, null check with width/height reset, clamp both axes, no mip
// mapping, force first clear). BFME 2 target evidence: the device lock is a
// scope object, creation is gated on GlobalData+0xC6A (the taint enable byte)
// and goes through the rowed 0x00131DFC holder helper with format 0x15.
typedef unsigned char UnsignedByte;

class GlobalData
{
	unsigned char m_pad00[0xc6a];
public:
	UnsignedByte m_taintOn;
};
extern GlobalData *TheWritableGlobalData;

class TextureClass { public: void Release_Ref(); };
class ShroudFilter {
public:
	int unused[2], mip, u, v;
	void SetMip(int);
};
class ShroudTexture { public: ShroudFilter *getFilter(); };
struct IDirect3DBaseTexture8;
class TextureBaseClass { public: IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const; };
class BfmeResetTextureRef { public: void clear(); };
class Rva00131DFC { public: void rva00131DFC(void *, void *, void *, void *, int, int); };

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock {
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class W3DTaint
{
public:
	bool ReAcquireResources();
private:
	unsigned char m_pad00[0x1c];
	void *m_dstTexture;
	int m_dstTextureWidth, m_dstTextureHeight;
	unsigned char m_pad28[0x35 - 0x28];
	unsigned char m_clearDstTexture;
};

// ?ReAcquireResources@W3DTaint@@QAE_NXZ
bool W3DTaint::ReAcquireResources()
{
	if (!m_dstTextureWidth)
		return true;

	BFMEDX8DeviceLock lock;
	if (TheWritableGlobalData && TheWritableGlobalData->m_taintOn)
		reinterpret_cast<Rva00131DFC *>(&m_dstTexture)->rva00131DFC(
			(void *)m_dstTextureWidth, (void *)m_dstTextureHeight,
			(void *)0x15, (void *)1, 1, 0);

	if (!reinterpret_cast<TextureBaseClass *>(&m_dstTexture)->Peek_D3D_Base_Texture())
	{
		reinterpret_cast<BfmeResetTextureRef *>(&m_dstTexture)->clear();
		m_dstTextureWidth = 0;
		m_dstTextureHeight = 0;
		return false;
	}
	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->u = 1;
	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->v = 1;
	reinterpret_cast<ShroudTexture *>(&m_dstTexture)->getFilter()->SetMip(0);
	m_clearDstTexture = 1;
	return true;
}
