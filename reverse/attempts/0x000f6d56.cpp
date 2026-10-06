// ?preRender@Rva000F6D56Filter@@UAE_NAA_NAAH@Z
// partial score=0.9774 date=2026-10-06
// ?preRender@Rva000F6D56Filter@@UAE_NAA_NAAH@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /G7 /arch:SSE
// ?preRender@Rva000F6D56Filter@@UAE_NAA_NAAH@Z @0x000F6D56 90B.
// Filter-style preRender(bool &skip, int &mode): clear skip, bind this+0x1C
// surface as render target, clear color to black, set mode 6, return true.
// Straight-line 90B thiscall ret 8. Closest donor shape is the
// Set_Render_Target(true) + Clear(true,false,false,black,0,1,0) sequence in
// ScreenHilightFilter::preRender's else branch and Rva007DCA80::preRender's
// mode=6; class/layout unproven, hence the address-derived name (virtual per
// filter convention; virtual-ness is not in the mangled name).
struct IDirect3DSurface8;
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *surface, bool flag);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};
class Rva000F6D56Filter
{
public:
	virtual bool preRender(bool &skip, int &mode);

private:
	char m_pad00[0x18];
	IDirect3DSurface8 *m_surface; // +0x1C
};

#ifndef NULL
#define NULL 0
#endif

bool Rva000F6D56Filter::preRender(bool &skip, int &mode)
{
	skip = false;
	DX8Wrapper::Set_Render_Target(m_surface, true);
	float one = 1.0f;
	Vector3 black;
	black.Z = 0.0f;
	black.Y = 0.0f;
	black.X = 0.0f;
	DX8Wrapper::Clear(true, false, false, black, 0.0f, one, 0);
	mode = 6;
	return true;
}
