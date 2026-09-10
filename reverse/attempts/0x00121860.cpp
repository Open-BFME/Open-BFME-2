// ?Get_Render_Target_Resolution@DX8Wrapper@@SAXAAH00AA_N@Z
// partial score=0.9 date=2026-09-10
// cl: /O2 /EHa /MD
//
// DX8Wrapper::Get_Render_Target_Resolution, retail 0x00121860, 195 bytes.
// Dedicated TU. Reloc named the WW3D thunk; this is the DX8Wrapper body.
// BFME2 wraps GetDesc in BFMEDX8DeviceLock and inlines Get_Device_Resolution.

struct D3DSURFACE_DESC
{
	unsigned Format;
	unsigned Type;
	unsigned Usage;
	unsigned Pool;
	unsigned MultiSampleType;
	unsigned MultiSampleQuality;
	unsigned Width;
	unsigned Height;
};

struct IDirect3DSurface9;

struct IDirect3DSurface9Vtbl
{
	void *reserved[12];
	long (__stdcall *GetDesc)(IDirect3DSurface9 *self, D3DSURFACE_DESC *desc);
};

struct IDirect3DSurface9
{
	IDirect3DSurface9Vtbl *lpVtbl;
};

void BFME_DX8_Thread_Lock();
void BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock()
	{
		BFME_DX8_Thread_Lock();
	}
	~BFMEDX8DeviceLock()
	{
		BFME_DX8_Thread_Assert();
	}
};

class DX8Wrapper
{
public:
	static void Get_Render_Target_Resolution(int &set_w, int &set_h, int &set_bits, bool &set_windowed);

private:
	static IDirect3DSurface9 *CurrentRenderTarget;
	static int ResolutionWidth;
	static int ResolutionHeight;
	static int BitDepth;
	static bool IsWindowed;
};

void DX8Wrapper::Get_Render_Target_Resolution(int &set_w, int &set_h, int &set_bits, bool &set_windowed)
{
	if (*(unsigned *)&CurrentRenderTarget != 0)
	{
		BFMEDX8DeviceLock lock;
		D3DSURFACE_DESC info;
		CurrentRenderTarget->lpVtbl->GetDesc(CurrentRenderTarget, &info);
		set_w = info.Width;
		set_h = info.Height;
		set_bits = BitDepth;
		set_windowed = IsWindowed;
	}
	else
	{
		set_w = ResolutionWidth;
		set_h = ResolutionHeight;
		set_bits = BitDepth;
		set_windowed = IsWindowed;
	}
}
