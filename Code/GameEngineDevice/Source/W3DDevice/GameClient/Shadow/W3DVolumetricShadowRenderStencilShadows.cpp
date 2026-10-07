// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?renderStencilShadows@W3DVolumetricShadowManager@@IAEXXZ @0x000F0842 208B.
//
// W3DVolumetricShadowManager::renderStencilShadows: blends the shadow colour
// over every stencil-marked pixel. Target evidence: retail 0x000F0842..
// 0x000F0912 (plain frame, two float slots, ret), called from renderShadows
// (0x000F4AB7) through this; every state goes through the out-of-line
// DX8Wrapper::Set_DX8_Render_State (0x0006615F) and the fill is
// W3DShaderManager::drawViewport (0x00075746) with the shadow colour read at
// TheW3DShadowManager+4, gated on the triangle-draw flag at 0x00DB5FCD.
// Donor: Open-BFME-1 W3DVolumetricShadow.cpp renderStencilShadows
// (0x007B9280), itself the ZH body; BFME 2 drops the device-null guard and
// routes the raw device SetRenderState calls through DX8Wrapper.

typedef float Real;
typedef unsigned long DWORD;
typedef DWORD D3DRENDERSTATETYPE;

#define TRUE	1
#define FALSE	0

#define D3DRS_ZENABLE			7
#define D3DRS_SHADEMODE			9
#define D3DRS_SRCBLEND			19
#define D3DRS_DESTBLEND			20
#define D3DRS_ZFUNC				23
#define D3DRS_ALPHABLENDENABLE	27
#define D3DRS_STENCILENABLE		52
#define D3DRS_STENCILPASS		55
#define D3DRS_STENCILFUNC		56
#define D3DRS_STENCILREF		57
#define D3DRS_STENCILMASK		58

#define D3DSHADE_FLAT			1
#define D3DSHADE_GOURAUD		2
#define D3DBLEND_ZERO			1
#define D3DBLEND_DESTCOLOR		9
#define D3DCMP_LESSEQUAL		4
#define D3DCMP_ALWAYS			8
#define D3DSTENCILOP_KEEP		1

struct Vector2
{
	Real X, Y;
};

class DX8Wrapper
{
public:
	static void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value);
	static bool _Is_Triangle_Draw_Enabled(void) { return _EnableTriangleDraw; }
private:
	static bool _EnableTriangleDraw;
};

class W3DShaderManager
{
public:
	static void drawViewport(int color, bool flip, const Vector2 *uv);
};

class W3DShadowManager
{
public:
	unsigned getShadowColor(void) { return m_shadowColor; }
	unsigned getStencilShadowMask(void) { return m_stencilShadowMask; }
private:
	void *m_vtable;
	unsigned m_shadowColor;
	unsigned m_stencilShadowMask;
};
extern W3DShadowManager *TheW3DShadowManager;

class W3DVolumetricShadowManager
{
protected:
	void renderStencilShadows(void);
};

void W3DVolumetricShadowManager::renderStencilShadows( void )
{
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	if (TheW3DShadowManager->getStencilShadowMask() == 0x80808080)
		DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILMASK, 0x7f7f7f0f);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILREF, 1);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SHADEMODE, D3DSHADE_FLAT);

	if (DX8Wrapper::_Is_Triangle_Draw_Enabled())
	{
		Vector2 uv;
		uv.X = 1.0f;
		uv.Y = 1.0f;
		W3DShaderManager::drawViewport(TheW3DShadowManager->getShadowColor(), false, &uv);
	}

	DX8Wrapper::Set_DX8_Render_State(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, FALSE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_STENCILENABLE, FALSE);

}  // end renderStencilShadows
