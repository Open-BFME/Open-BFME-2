// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// Notifies the indexed shader through virtual slot 1 and clears the current-shader latch.
class Rva00075695Item
{
public:
	virtual void f0();
	virtual void f1();
};

class ShaderInterface;
extern ShaderInterface *W3DShaders[];
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

void __cdecl Rva00075695Notify(int index)
{
	if (W3DShaderManager::m_currentShader != 0) {
		Rva00075695Item * volatile *slot = (Rva00075695Item * volatile *)&W3DShaders[index];
		if (*slot != 0)
			(*slot)->f1();
		W3DShaderManager::m_currentShader = 0;
	}
}
