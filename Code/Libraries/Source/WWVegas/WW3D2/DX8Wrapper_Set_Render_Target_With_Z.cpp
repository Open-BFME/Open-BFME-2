// cl: /arch:SSE /G7 /DNDEBUG /MD /EHsc
// DX8Wrapper::Set_Render_Target_With_Z retail 0x00120850 (228 B).
// Donor: reference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2/
// DX8Wrapper_Set_Render_Target_With_Z.cpp (BFME 1 0x00906F10). BFME 2 keeps
// both surfaces in W3DRadarResetSurface holders for the whole call: the colour
// surface lives until the epilogue, and the z holder starts empty and is
// assigned (AddRef new, Release old, copy) from the z texture's level-0 temp
// only when that texture holds a D3D texture. Both holders are destroyed by
// the out-of-line release at 0x00176CB0; the level-0 fetch is the forwarder
// at 0x00132D70, rowed under its CursorTextureSlot role name. Built with
// dx8wrapper.cpp's /arch:SSE /G7: under the default /G6 the colour-surface
// test loads into eax instead of retail's cmp [esp],0. The early return keeps
// both holders in one scope; nesting the z holder swaps their frame slots.

struct IDirect3DSurface8;

class SurfaceResource
{
public:
	virtual void slot00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface() : m_surface(0) {}
	~W3DRadarResetSurface();
	W3DRadarResetSurface &operator=(const W3DRadarResetSurface &other)
	{
		if (other.m_surface)
			other.m_surface->addRef();
		if (m_surface)
			m_surface->release();
		m_surface = other.m_surface;
		return *this;
	}
	IDirect3DSurface8 *getSurface() const { return reinterpret_cast<IDirect3DSurface8 *>(m_surface); }

	SurfaceResource *m_surface;
};

// The texture's D3D texture pointer and its level-0 surface fetch.
struct CursorTextureSlot
{
	void *Ptr;

	W3DRadarResetSurface Get_Surface_Level(void);
};

class TextureClass : public CursorTextureSlot
{
};

class ZTextureClass : public CursorTextureSlot
{
};

class DX8Wrapper
{
public:
	static void Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture);
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, IDirect3DSurface8 *depthBuffer);
	static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);

private:
	static bool IsRenderToTexture;
};

// ?Set_Render_Target_With_Z@DX8Wrapper@@SAXPAVTextureClass@@PAVZTextureClass@@@Z
void DX8Wrapper::Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture)
{
	W3DRadarResetSurface d3d_surf = texture->Get_Surface_Level();
	if (d3d_surf.getSurface() == 0)
		return;
	W3DRadarResetSurface d3d_zbuf;
	if (ztexture->Ptr != 0)
		d3d_zbuf = ztexture->Get_Surface_Level();
	if (d3d_zbuf.getSurface() != 0)
		Set_Render_Target(d3d_surf.getSurface(), d3d_zbuf.getSurface());
	else
		Set_Render_Target(d3d_surf.getSurface(), true);
	IsRenderToTexture = true;
}
