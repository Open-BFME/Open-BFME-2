// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// preRender (vftable 0x007CF338) of the screen filter the ledger calls
// Rva007D85C0 (its shutdown 0x000FB964 sits one slot earlier). Zero Hour's
// preRender contract: clear skipRender, redirect rendering to the filter's
// render target and clear it. BFME 2 first rebuilds the filter's gaussian
// kernel at +0x10 from the settings block returned by Rva00309E4BGet whenever
// g_bfmeDirtyCU is set (WorldBuilder names the builder
// W3DShaderManager::createGaussianVector).

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct IDirect3DSurface8;

class DX8Wrapper
{
public:
	static void Set_Render_Target(IDirect3DSurface8 *render_target, bool use_default_depth_buffer);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned int stencil);
};

// The settings block behind Rva00309E4BGet.
struct BfmeGaussianSettings
{
	char m_pad00[4];
	int m_taps; // +0x04
	char m_pad08[0x10 - 0x08];
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};
int Rva00309E4BGet();

struct BfmeGaussianParams
{
	int m_mode;
	int m_taps;
	float m_10;
	float m_14;
	float m_18;
	float m_1C;
};

class W3DShaderManager
{
public:
	static void createGaussianVector(void *kernel, BfmeGaussianParams *params);
};

extern bool g_bfmeDirtyCU;

enum CustomScenePassModes
{
	SCENE_PASS_DEFAULT
};

class Rva007D85C0
{
public:
	virtual bool preRender(bool &skipRender, CustomScenePassModes &scenePassMode);
private:
	char m_pad04[0x0C - 0x04];
	bool m_0C; // +0x0C
	int m_kernel[(0x28 - 0x10) / 4]; // +0x10
	IDirect3DSurface8 *m_renderTarget; // +0x28
};

// ?preRender@Rva007D85C0@@UAE_NAA_NAAW4CustomScenePassModes@@@Z @0x000FAFF8
bool Rva007D85C0::preRender(bool &skipRender, CustomScenePassModes &scenePassMode)
{
	skipRender = false;
	if (g_bfmeDirtyCU) {
		BfmeGaussianParams params;
		params.m_mode = 2;
		params.m_taps = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_taps;
		params.m_14 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_14;
		params.m_1C = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_1C;
		params.m_10 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_10;
		params.m_18 = ((BfmeGaussianSettings *)Rva00309E4BGet())->m_18;
		W3DShaderManager::createGaussianVector(m_kernel, &params);
		g_bfmeDirtyCU = false;
	}
	DX8Wrapper::Set_Render_Target(m_renderTarget, true);
	{
		Vector3 color(0.0f, 0.0f, 0.0f);
		DX8Wrapper::Clear(true, false, false, color, 0.0f, 1.0f, 0);
	}
	m_0C = true;
	return true;
}
