// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc

// Clean BFME body for WW3D::Begin_Render at BFME1 donor RVA 0x008FE280; BFME2 native118170..118296.
// Semantic donor BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Target flags, removed counters/statistics, pool reset callees, viewport
// direct DX8 call and bool result are proved by native294, not donor labels.
// Target returns AL; keep an address-derived API name because the return
// ABI and return values differ from the donor enum. The frame-start purpose
// is established by the reset/capture/
// clear/scene sequence and matched WW3D companions; original enum identity
// is not asserted. The reset-phase empty call uses an existing provider ABI
// view; it does not name the original folded function.
// Reset_Device122600, target resolution121860 and Clear11D330 are unrowed.

typedef unsigned int UnsignedInt;

class Vector3
{
	float X;
	float Y;
	float Z;
};

struct _D3DVIEWPORT8
{
	UnsignedInt X;
	UnsignedInt Y;
	UnsignedInt Width;
	UnsignedInt Height;
	float MinZ;
	float MaxZ;
};


class BfmeD3DDevice
{
public:
	virtual long __stdcall slot00(void);
	virtual long __stdcall slot04(void);
	virtual long __stdcall slot08(void);
	virtual long __stdcall TestCooperativeLevel(void);
};

class WW3D;
struct IDirect3DDevice8;
class DX8Wrapper
{
 friend class WW3D;
 // BFME 2's body is the private ?Get_Render_Target_Resolution@DX8Wrapper@@CAXAAH00AA_N@Z
 // (0x00121860, WW3D_Get_Render_Target_Resolution.cpp); dx8wrapper.cpp's protected copy is Zero Hour's.
 private:
 static void Get_Render_Target_Resolution(int &,int &,int &,bool &);
public:
	static bool Reset_Device(bool force);
	static void Set_Viewport(const _D3DVIEWPORT8 *viewport);
	static void Clear(bool clear_color, bool clear_z_stencil,
		bool clear_stencil, const Vector3 &color, float dest_alpha,
		float z, UnsignedInt stencil);
	static void Begin_Scene_Inner(void);

protected:
	// dx8wrapper.cpp: ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A.
	static IDirect3DDevice8 *D3DDevice;
};

class DynamicVBAccessClass
{
public:
	static void _Reset(bool);
};

class DynamicIBAccessClass
{
public:
	static void _Reset(bool);
};

// Native pushes an unused value1 before calling the shared empty RET.
// Reuse its already rowed provider without adding a second pin/name.
// The bool cdecl call view describes the caller stack, not DX8_Assert identity.
void DX8_Assert(void);


class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
	static void Update_Movie_Capture(void);
	static bool rva00118170(bool, bool, const Vector3 &, float);

private:
	// ww3d.cpp defines these private (?IsInitted@WW3D@@0_NA, ...).
	static bool IsInitted;
	static bool IsRendering;
	static bool IsCapturing;
	static bool PauseRecord;
	static bool RecordNextFrame;
};


bool WW3D::rva00118170(bool clear, bool clearz, const Vector3 &color,
	float dest_alpha)
{
	if (!IsInitted)
		return true;
	if (IsRendering)
		return false;
	{
		BfmeD3DDevice *device = (BfmeD3DDevice *)DX8Wrapper::D3DDevice;
		if (device)
		{
			long hr = device->TestCooperativeLevel();
			if (hr != 0)
			{
				if (hr == 0x88760868)
					return false;
				if (hr != 0x88760869)
					return false;
				DX8Wrapper::Reset_Device(true);
				return false;
			}
		}
	}
	DynamicVBAccessClass::_Reset(true);
	DynamicIBAccessClass::_Reset(true);
	reinterpret_cast<void(__cdecl *)(bool)>(&DX8_Assert)(true);
	if (IsCapturing && (!PauseRecord || RecordNextFrame))
	{
		WW3D::Update_Movie_Capture();
		RecordNextFrame = false;
	}
	if (clear)
	{
		IsRendering = true;
		goto clear_viewport;
	}
	IsRendering = true;
	if (clearz)
		goto clear_viewport;
	goto begin_scene;
clear_viewport:
	{
		_D3DVIEWPORT8 vp;
		int width, height, bits;
		bool windowed;
		DX8Wrapper::Get_Render_Target_Resolution(width, height, bits, windowed);
		vp.X = 0;
		vp.Y = 0;
		vp.Width = width;
		vp.Height = height;
		vp.MinZ = 0.0f;
		vp.MaxZ = 1.0f;
		DX8Wrapper::Set_Viewport(&vp);
		DX8Wrapper::Clear(clear, clearz, clearz, color, dest_alpha, 1.0f, 0);
	}
begin_scene:
	DX8Wrapper::Begin_Scene_Inner();
	return true;
}
