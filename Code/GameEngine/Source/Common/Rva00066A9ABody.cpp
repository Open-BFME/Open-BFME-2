// cl: /DNDEBUG /MD
// dxsdk
// platformsdk
//
// Dump range 1 (0x00066A9A 55B): head calls plus dual guarded tail.
// Head calls W3DShaderManager::init (0x00077F80), then the pinned 0x0007E89C
// through the retail global at 0x00DE2000 when non-null. Tail reuses the
// proven 0x680B3 pattern: +0x3850 call plus +0x3854 tail jmp into pinned
// 0x000EA1F3/0x000E6FC8. Honest address-derived names.

extern void *W3DGCData00DE2000;

class Rva00066A9ASub
{
public:
	void headB();
};

// The two tail callees are rowed as Rva000E6FC8's rva000EA1F3 (0x000EA1F3)
// and rva000E6FC8 (0x000E6FC8).
class Rva000E6FC8
{
public:
	void rva000EA1F3();
	void rva000E6FC8();
};

// GeneralsMD's W3DShaderManager (W3DShaderManager.h); retail 0x00077F80 is
// its static init (the W3DDisplay::init callee pinned at 0x00046F3B), which
// this host calls first.
// The glow shader handles are W3DShaderManager.cpp's m_dwGlowPixelShader
// (0x009E1F74) and m_dwGlowVertexShader (0x009E1F78).
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

// 0x00066A9A is slot 130 of BaseHeightMapRenderObjClass, in BaseHeightMap.cpp.

// W3DShaderManager::init in GeneralsMD walks the master shader and filter
// lists. Retail's 0x77F80 does the same, then creates the Glow declaration and
// loads its vertex and pixel shaders. The two list roots and shader handles
// below are target addresses.
class Rva00077F80Shader
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual int init();
};

class Rva00077F80Filter
{
public:
	virtual int init();
};

// Retail's master lists (VA 0x00DB43A4 and 0x00DB43AC), each entry a null-terminated list of alternatives.
extern void *g_shaderList0[], *g_filterList0[], *g_filterList1[], *g_filterList2[], *g_filterList3[], *g_filterList4[],
	*g_filterList5[], *g_filterList6[], *g_filterList7[], *g_filterList8[];
Rva00077F80Shader **g_Va00DB43A4[2] = { (Rva00077F80Shader **)g_shaderList0, 0 };
Rva00077F80Filter **g_Va00DB43AC[10] = {
	(Rva00077F80Filter **)g_filterList0, (Rva00077F80Filter **)g_filterList1, (Rva00077F80Filter **)g_filterList2,
	(Rva00077F80Filter **)g_filterList3, (Rva00077F80Filter **)g_filterList4, (Rva00077F80Filter **)g_filterList5,
	(Rva00077F80Filter **)g_filterList6, (Rva00077F80Filter **)g_filterList7, (Rva00077F80Filter **)g_filterList8, 0
};

#include <d3d9.h>

struct IDirect3DDevice8;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

extern unsigned g_fvfShader;
extern void __cdecl rva00075E42();
extern void __cdecl Rva000754DEInit();
extern long __cdecl Rva00077C19Load(const char *path, unsigned *shader);
extern long __cdecl Rva00077D0FLoad(const char *path, unsigned long *shader);

void W3DShaderManager::init(void)
{
	rva00075E42();
	Rva000754DEInit();

	int i, j;
	Rva00077F80Shader **shaders;
	for (i = 0; g_Va00DB43A4[i] != 0; ++i) {
		shaders = g_Va00DB43A4[i];
		for (j = 0; shaders[j] != 0; ++j) {
			if (shaders[j]->init())
				break;
		}
	}

	Rva00077F80Filter **filters;
	for (i = 0; g_Va00DB43AC[i] != 0; ++i) {
		filters = g_Va00DB43AC[i];
		for (j = 0; filters[j] != 0; ++j) {
			if (filters[j]->init())
				break;
		}
	}

	D3DVERTEXELEMENT9 declaration[4] = {
		{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
		{ 0, 20, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	if (g_fvfShader == 0) {
		IDirect3DDevice9 *device =
			reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
		HRESULT hr = device->CreateVertexDeclaration(
			declaration, reinterpret_cast<IDirect3DVertexDeclaration9 **>(&g_fvfShader));
		if (hr < 0)
			g_fvfShader = 0;
	}

	if (Rva00077C19Load("shaders\\Glow.vso",
		(unsigned *)&W3DShaderManager::m_dwGlowVertexShader) < 0)
		W3DShaderManager::m_dwGlowVertexShader = 0;

	if (Rva00077D0FLoad("shaders\\Glow.pso",
		&W3DShaderManager::m_dwGlowPixelShader) < 0)
		W3DShaderManager::m_dwGlowPixelShader = 0;
}
