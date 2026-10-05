// ?ReAcquireResources@W3DSmudgeManager@@UAEXXZ
// RVA 0x000A6176, size 250. Virtual slot 4 (offset 0x10) of vtable 0x007C92D8
// (class of ??0W3DSmudgeManager@@QAE@XZ). Evidence: BFME1 donor
// W3DSmudgeManager_ReAcquireResources.cpp (ReleaseResources call via slot 3,
// getBackBufferSurface006e, Get_Description, DX8IndexBuffer 0x1770, 500-quad
// WriteLock fill), BFME2 thread guard BFMEDX8DeviceLock (Lock/Assert) per
// W3DSmudgeManagerReleaseResources.cpp sibling, m_indexBuffer +0x34,
// width +0x38 height +0x3C.
//
// cl: /O1 /DNDEBUG /MD /EHsc

#define SMUDGE_DRAW_SIZE 500

extern void BFME_DX8_Thread_Lock();
extern bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// Retail reads Width at desc+4 ([ebp-0x1c]) and Height at desc+8 ([ebp-0x18]),
// so this TU declares a 16-byte description, not the upstream 32-byte one.
// Retail's constructor (0x0011E050) and destructor (0x00176CB0) treat the
// first word as a reference-counted handle -- the destructor loads it and
// enters its table to release -- and Get_Description (0x00116620) is a member
// reached with `this` = the object at [ebp-0x10]. The base is non-empty, so
// the object is larger than the four-byte pointer its destructor touches.
class SurfaceClass
{
public:
	void *m_surface;

	struct SurfaceDescription
	{
		unsigned Format;
		unsigned Width;
		unsigned Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface();
};

W3DRadarResetSurface getBackBufferSurface006e(int index);

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		IndexBufferClass *index_buffer;
		unsigned short *indices;
		BFMEDX8DeviceLock device_lock;

	public:
		WriteLockClass(IndexBufferClass *index_buffer, int flags = 0);
		~WriteLockClass();

		unsigned short *Get_Index_Array() { return indices; }
	};
};

class DX8IndexBufferClass
{
	unsigned char m_bfmeBody[0x18];

public:
	enum UsageType
	{
		USAGE_DEFAULT = 0
	};

	DX8IndexBufferClass(unsigned index_count, UsageType usage = USAGE_DEFAULT);
};

class SmudgeManager
{
public:
	virtual ~SmudgeManager();
	virtual void init(void);
	virtual void reset(void);
	virtual void ReleaseResources(void);
	virtual void ReAcquireResources(void);

private:
	char m_smudgeManagerPad[0x20];
};

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual void ReAcquireResources(void);

	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	DX8IndexBufferClass *m_indexBuffer;
	int m_backBufferWidth;
	int m_backBufferHeight;
	unsigned int m_probeColor;
};

void W3DSmudgeManager::ReAcquireResources(void)
{
	ReleaseResources();

	BFMEDX8DeviceLock lock;

	W3DRadarResetSurface surface = getBackBufferSurface006e(0);
	SurfaceClass::SurfaceDescription surface_desc;
	surface.Get_Description(surface_desc);

	m_backBufferWidth = (int)surface_desc.Width;
	m_backBufferHeight = (int)surface_desc.Height;

	DX8IndexBufferClass *index_buffer =
		new DX8IndexBufferClass((unsigned)(SMUDGE_DRAW_SIZE * 4 * 3));
	m_indexBuffer = index_buffer;

	{
		IndexBufferClass::WriteLockClass lockIdxBuffer((IndexBufferClass *)index_buffer);
		unsigned short *ib = lockIdxBuffer.Get_Index_Array();
		int vbCount = 0;
		for (int i = 0; i < SMUDGE_DRAW_SIZE; i++)
		{
			ib[0] = (unsigned short)vbCount;
			ib[1] = (unsigned short)(vbCount + 4);
			ib[2] = (unsigned short)(vbCount + 3);
			ib[3] = (unsigned short)(vbCount + 3);
			ib[4] = (unsigned short)(vbCount + 4);
			ib[5] = (unsigned short)(vbCount + 2);
			ib[6] = (unsigned short)(vbCount + 2);
			ib[7] = (unsigned short)(vbCount + 4);
			ib[8] = (unsigned short)(vbCount + 1);
			ib[9] = (unsigned short)(vbCount + 1);
			ib[10] = (unsigned short)(vbCount + 4);
			ib[11] = (unsigned short)(vbCount + 0);

			vbCount += 5;
			ib += 12;
		}
	}
}