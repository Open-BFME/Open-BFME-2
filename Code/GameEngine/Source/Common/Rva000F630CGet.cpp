// cl: /MD
// ?canRenderToTexture@W3DShaderManager@@SA_NXZ @0x000F630C 20B.
// Retail: xor eax,eax / cmp [0x009E1F64],eax / je ret / cmp [0x009E1F6C],eax / je ret / inc eax / ret.
// Identity: Zero Hour's W3DShaderManager::canRenderToTexture (W3DShaderManager.h:
// return (m_oldRenderSurface && m_newRenderSurface)), out of line in BFME 2. The
// name was pinned here from the REL32 in the matched ScreenBWFilter::init
// 0x000FB9D4, which tests it before creating its render target as Zero Hour
// does; all nine callers (0x000F64B5 0x000F9DA4 0x000FA93E 0x000FB9E2 0x000FBA27
// 0x000FC5D4 0x000FC923 0x000FD4B6 0x000FDCD7) test al, the bool return.
// 0x009E1F64 is the data ledger's ?m_oldRenderSurface@W3DShaderManager@@ (the
// pointer W3DShaderManager.cpp's matched render-target restore passes to
// DX8Wrapper::Set_Render_Target); this unit defines it. The second global keeps
// its address name until its data row is named.
struct IDirect3DSurface8;
extern unsigned int g_Va009E1F6C;
// g_Va009E1F6C: matched references place it at VA 0xde1f6c (zero-filled .bss).
unsigned int g_Va009E1F6C;

class W3DShaderManager
{
public:
	static bool canRenderToTexture(void);
	static IDirect3DSurface8 *m_oldRenderSurface;
};

IDirect3DSurface8 *W3DShaderManager::m_oldRenderSurface;

bool W3DShaderManager::canRenderToTexture(void)
{
	return (m_oldRenderSurface && g_Va009E1F6C);
}
