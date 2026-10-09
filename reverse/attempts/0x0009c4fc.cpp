// ?rva0009C4FC@Rva0008FF3E@@UAEXHHHH@Z
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0009C4FC@Rva0008FF3E@@UAEXHHHH@Z, retail 0x0009C4FC..0x0009C784
// (648 bytes, ret 0x10). Slot 9 (+0x24) of the vtable 0x007C7DC8 that the
// rowed constructor 0x0008FF3E stores (slot 27 is the rowed per-frame update
// 0x0009B0B7 in Rva0009B0B7Update.cpp). It draws the view into a screen
// rectangle. With a scene (+0xC4), a camera (+0xC0) and both flag bytes
// (+0x19, +0x18) set, it:
//  - stores the rectangle at +0x1B0..+0x1BC;
//  - sets the camera viewport to the rectangle over TheDisplay's size,
//    clamped to [0, 1], via the rowed CameraClass::Set_Viewport, and the
//    aspect ratio to width / height via the rowed Set_Aspect_Ratio;
//  - enables ShaderOverbrightEnabled and clears colour and depth through the
//    rowed DX8Wrapper::Clear;
//  - blends two fog values (+0x13C, +0xD8) from the INI-loaded file statics
//    by the +0x198 fade, picked by TheWritableGlobalData's +0xD2E flag; the
//    first is then replaced by TheLivingWorldManager's +0x38;
//  - sets three render objects' opacity (+0x18C and +0x190 to 0, +0x194 to
//    0.8) through 0x0009AACF;
//  - passes +0xE0 to the scene's slot 6, runs 0x0009BAA4 and renders the
//    scene with the camera through the rowed 0x00118660.
// 0x0009AACF is rowed as a free __stdcall function, but retail loads ECX
// with this before each call and the body never reads ECX; it is called here
// through a thiscall pin. The file statics are address-named; class identity
// is address-derived from the constructor.

class Vector2
{
public:
	float X;
	float Y;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class CameraClass
{
public:
	void Set_Viewport(const Vector2 &min, const Vector2 &max);
	void Set_Aspect_Ratio(float ratio);
};

class DX8Wrapper
{
public:
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil,
		const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

class Rva0009C4FCScene
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06(void *arg);
};

class Display
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
};
extern Display *TheDisplay;

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva0009C4FCGlobalData
{
	char m_pad000[0xD2E];
	bool m_D2E; // +0xD2E
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva0009C4FCManager
{
	char m_pad00[0x38];
	float m_38; // +0x38
};

extern bool ShaderOverbrightEnabled;

extern float g_00DE5E2C[2];
extern float g_00DE5E34;
extern float g_00DE5E38[2];
extern float g_00DE5E40;

class Rva0009C134Host
{
public:
	void rva0009BAA4();
};

bool Rva00118660Call(void *scene, void *camera);

class Rva0008FF3E
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void rva0009C4FC(int x, int y, int width, int height);

	void rva0009AACF(int renderObject, float opacity);

private:
	char m_pad004[0x18 - 0x04];
	bool m_active18;                // +0x18
	bool m_visible19;               // +0x19
	char m_pad01A[0xC0 - 0x1A];
	CameraClass *m_camera0C0;       // +0xC0
	Rva0009C4FCScene *m_scene0C4;   // +0xC4
	char m_pad0C8[0xD8 - 0xC8];
	float m_fogD8;                  // +0xD8
	char m_pad0DC[0xE0 - 0xDC];
	char m_sceneArgE0[0x13C - 0xE0]; // +0xE0
	float m_fog13C;                 // +0x13C
	char m_pad140[0x18C - 0x140];
	int m_object18C;                // +0x18C
	int m_object190;                // +0x190
	int m_object194;                // +0x194
	float m_fade198;                // +0x198
	char m_pad19C[0x1B0 - 0x19C];
	int m_x1B0;                     // +0x1B0
	int m_y1B4;                     // +0x1B4
	int m_width1B8;                 // +0x1B8
	int m_height1BC;                // +0x1BC
};

void Rva0008FF3E::rva0009C4FC(int x, int y, int width, int height)
{
	if (!m_scene0C4 || !m_camera0C0 || !m_visible19 || !m_active18)
		return;

	m_x1B0 = x;
	m_y1B4 = y;
	m_width1B8 = width;
	m_height1BC = height;

	float fw = (float)width;
	float fh = (float)height;
	float displayHeight = (float)TheDisplay->getHeight();
	{
		float displayWidth = (float)TheDisplay->getWidth();
		Vector2 vmin;
		Vector2 vmax;
		vmin.X = x / displayWidth;
		vmin.Y = y / displayHeight;
		vmax.X = fw / displayWidth + vmin.X;
		vmax.Y = fh / displayHeight + vmin.Y;
		if (vmin.X < 0.0f)
			vmin.X = 0.0f;
		if (vmin.Y < 0.0f)
			vmin.Y = 0.0f;
		if (vmax.X > 1.0f)
			vmax.X = 1.0f;
		if (vmax.Y > 1.0f)
			vmax.Y = 1.0f;
		m_camera0C0->Set_Viewport(vmin, vmax);
	}
	m_camera0C0->Set_Aspect_Ratio(fw / fh);

	ShaderOverbrightEnabled = true;
	{
		Vector3 color;
		color.X = 0.0f;
		color.Y = 0.0f;
		color.Z = 0.0f;
		DX8Wrapper::Clear(false, true, true, color, 0.0f, 1.0f, 0);
	}

	int index = 0;
	if (TheWritableGlobalData && reinterpret_cast<Rva0009C4FCGlobalData *>(TheWritableGlobalData)->m_D2E)
		index = 1;
	float fog = g_00DE5E38[index];
	m_fog13C = (g_00DE5E40 - fog) * m_fade198 + fog;
	fog = g_00DE5E2C[index];
	m_fogD8 = (g_00DE5E34 - fog) * m_fade198 + fog;
	if (m_visible19)
		m_fog13C = reinterpret_cast<Rva0009C4FCManager *>(TheLivingWorldManager)->m_38;

	if (m_object18C)
		rva0009AACF(m_object18C, 0.0f);
	if (m_object190)
		rva0009AACF(m_object190, 0.0f);
	if (m_object194)
		rva0009AACF(m_object194, 0.8f);

	m_scene0C4->v06(m_sceneArgE0);
	reinterpret_cast<Rva0009C134Host *>(this)->rva0009BAA4();
	Rva00118660Call(m_scene0C4, m_camera0C0);
}
