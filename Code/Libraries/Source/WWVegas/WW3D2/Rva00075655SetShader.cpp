// cl: /DNDEBUG /MD /EHsc
//
// ?setShader@Rva00075655@@SAHHH@Z @0x00075655 64B.
// Static shader-cache check: when both args match the cached pair return 1,
// otherwise refresh the cache, fetch the slot object from the table at
// 0x009E1F24, return 0 for an empty slot, else return its slot-0 virtual
// called with the second arg. Called from W3DShroudMaterialPass install.

enum ChipsetType { DC_UNKNOWN = 0 };
enum CpuType { XX, P3, P4, K7 };
struct IDirect3DTexture8;
struct IDirect3DSurface8;
class Vector2;
struct GlowSampleVector;
struct BfmeGaussianParams;
class W3DShaderManager
{
private:
	friend class Rva00075655;
	friend void Rva00075695Notify(int index);
	friend bool __cdecl Rva000756BFSelect(int index, int a1, int a2);
	friend bool __cdecl Rva000756F1Dispatch(int index, int a1, int a2, int a3, int a4);
public:
	enum ShaderTypes { ST_INVALID };
protected:
	static int m_currentShader;
	static int m_currentFilter;
	static bool m_renderingToTexture;
	static unsigned long m_dwGlowPixelShader;
	static unsigned long m_dwGlowVertexShader;
public:
	static IDirect3DSurface8 *m_oldRenderSurface;
	static IDirect3DTexture8 *m_renderTexture;
	W3DShaderManager();
	static int getShaderPasses(ShaderTypes shader);
	static void startRenderToTexture();
	static IDirect3DTexture8 *endRenderToTexture();
	static IDirect3DTexture8 *getRenderTexture();
	static void drawViewport(int color, bool useExplicitDimensions, const Vector2 *dimensions);
	static bool testMinimumRequirements(ChipsetType *, CpuType *, int *, unsigned __int64 *, float *, float *, float *);
	static int setShroudTex(int);
	static void performGlow(float weightScale, const GlowSampleVector *samples, int textureSize, IDirect3DTexture8 *sourceTexture, IDirect3DSurface8 *tempSurface, IDirect3DTexture8 *tempTexture, IDirect3DSurface8 *destSurface);
	static void createGaussianVector(void *,BfmeGaussianParams *);
};
extern int g_00DE1F18;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DE1F18).
int g_00DE1F18 = 0;

struct ShaderSlotObj
{
	virtual int slot00(int b);
};

extern ShaderSlotObj * volatile g_00DE1F24[];
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DE1F24).
ShaderSlotObj * volatile g_00DE1F24[1] = { 0 };

class Rva00075655
{
public:
	static int setShader(int a, int b);
};

int Rva00075655::setShader(int a, int b)
{
	if (a == W3DShaderManager::m_currentShader && b == g_00DE1F18)
		return 1;
	W3DShaderManager::m_currentShader = a;
	g_00DE1F18 = b;
	if (g_00DE1F24[a] != 0)
		return g_00DE1F24[a]->slot00(b);
	return 0;
}
