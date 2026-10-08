// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ScreenBWFilter::init, retail 0x000FB9D4..0x000FBA0F (59 bytes): Zero
// Hour's W3DShaderManager.cpp body without the chipset gate. The pixel
// shader handle (+0x04) and the shared fade frame are cleared; when render
// to texture is available and "shaders\monochrome.pso" loads, the filter
// registers itself as the black & white view filter and returns TRUE.
//
// Callees: W3DShaderManager::canRenderToTexture is the two-global test
// rowed at 0x000F630C under an int-returning address-derived name, but all
// five of its callers test AL, so it is called here by its Zero Hour name
// as the bool static it is (pinned); LoadAndCreateD3DShader's two-argument
// BFME 2 form is rowed at 0x00077D0F. Data is resolved from retail:
// m_curFadeFrame 0x00DEC1AC, W3DFilters[FT_VIEW_BW_FILTER] 0x00DE1F30 and
// screenBWFilter 0x00DB5B54.

typedef int Int;
typedef bool Bool;

enum FilterTypes
{
	FT_NULL_FILTER = 0,
	FT_VIEW_BW_FILTER,
	FT_MAX = 5
};

class W3DShaderManager
{
public:
	static Bool canRenderToTexture(void);
};

long __cdecl Rva00077D0FLoad(const char *strFilePath, unsigned long *pHandle);

class W3DFilterInterface
{
public:
	virtual Int init(void) = 0;
};

class ScreenBWFilter : public W3DFilterInterface
{
public:
	virtual Int init(void);

	static Int m_curFadeFrame;

protected:
	unsigned long m_dwBWPixelShader;	// +0x04
};

extern W3DFilterInterface *W3DFilters[FT_MAX];
extern ScreenBWFilter screenBWFilter;

Int ScreenBWFilter::init(void)
{
	m_dwBWPixelShader = 0;
	m_curFadeFrame = 0;

	if (!W3DShaderManager::canRenderToTexture()) {
		// Have to be able to render to texture.
		return false;
	}

	//Monochrome pixel shader.
	if (Rva00077D0FLoad("shaders\\monochrome.pso", &m_dwBWPixelShader) < 0)
		return false;

	W3DFilters[FT_VIEW_BW_FILTER]=&screenBWFilter;

	return true;
}
