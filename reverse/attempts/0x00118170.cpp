// ?Begin_Render@WW3D@@SA?AW4WW3DErrorType@@_N0ABVVector3@@MP6AXXZ@Z
// partial score=0.98 date=2026-10-05
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc

// Clean BFME body for WW3D::Begin_Render at BFME1 donor RVA 0x008FE280; BFME2 native118170..118296.
// Semantic donor BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Target flags, removed counters/statistics, pool reset callees, viewport
// direct DX8 call and bool result are proved by native294, not donor labels.
// All instructions match except REL32+5B to empty folded69E440: the stack
// carries value1 but original identity/member-vs-static ABI is unknown.
// The opaque cdecl-member hook below preserves the donor call shape only;
// do not pin its invented name or infer unique identity from the empty RET.
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
class DX8Wrapper
{
 friend class WW3D;
 protected:
 static void Get_Render_Target_Resolution(int &,int &,int &,bool &);
public:
	static bool Reset_Device(bool force);
	static void Set_Viewport(const _D3DVIEWPORT8 *viewport);
	static void Clear(bool clear_color, bool clear_z_stencil,
		bool clear_stencil, const Vector3 &color, float dest_alpha,
		float z, UnsignedInt stencil);
	static void Begin_Scene_Inner(void);

	static void *D3DDevice;
};

class BfmeDynamicVBAccess
{
public:
	static void _Reset(bool);
};

class DynamicIBAccessClass
{
public:
	static void _Reset(bool);
};

class Rva0069E440BeginResetHook
{
public:
	void __cdecl m(void);
};


class WW3D
{
public:
	static void Get_Render_Target_Resolution(int &, int &, int &, bool &);
	static void Update_Movie_Capture(void);
	static bool Begin_Render(bool, bool, const Vector3 &, float, void (*)(void));

	static bool IsInitted;
	static bool IsRendering;
	static bool IsCapturing;

private:
	static bool PauseRecord;
	static bool RecordNextFrame;
};


bool WW3D::Begin_Render(bool clear, bool clearz, const Vector3 &color,
	float dest_alpha, void (*network_callback)(void))
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

	BfmeDynamicVBAccess::_Reset(true);
	DynamicIBAccessClass::_Reset(true);
	((Rva0069E440BeginResetHook *)1)->m();

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
