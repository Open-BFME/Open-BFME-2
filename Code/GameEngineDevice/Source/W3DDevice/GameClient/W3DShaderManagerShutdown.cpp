// cl: /DNDEBUG /MD /EHsc
//
// W3DShaderManager's two-phase shutdown, retail 0x00076790 (186 bytes) and
// 0x0007684A (171 bytes), back to back. Ported from the Open-BFME-1 donors
// game/GameEngineDevice/Source/W3DDevice/GameClient/
// W3DShaderManagerReleaseResources.cpp and W3DShaderManagerShutdown.cpp
// (1281192f68; donor flags /DNDEBUG /MD [/EHsc] plus BFME 2's /O1). Compiled
// that way both bodies place uniquely on unclaimed .text by masked whole-.text
// search (tools/donor_sweep.py); shutdown's first call lands on the release
// body. The names and the address-qualified globals are the donor's (BFME 1
// addresses); BFME 2's globals are the 0x00DE1Fxx slots the bodies touch.
// The texture-handle reset calls the rowed RefCountPtr<TextureClass>
// assignment at 0x000424D0, which the handle view's operator= is pinned to.
//
// The donors' own notes below cite BFME 1 addresses.

// Retail RVA 0x00717C90; shutdown at 0x00717DA2 calls ILT RVA 0x1BB30.
// Global 0x012F9D1C is a vertex buffer: allocation path 0x00716770 calls
// DX8VertexBuffer ctor 0x0091F2F0. Other addresses remain explicit.
// The eight texture-handle resets retain a temporary lifetime around release.
static inline int decrement(int *p) { return --*p; }
class ShaderVertexBufferRef { public: virtual void Delete_This(); int NumRefs; void Release_Ref() { decrement(&NumRefs); if(NumRefs==0) Delete_This(); } };
struct ShaderComResourceRef { void **VTable; };
typedef unsigned long (__stdcall *ReleaseResource)(ShaderComResourceRef*);
// The texture-slot handles are RefCountPtr<TextureClass>; their assignment is
// the rowed 0x000424D0, spelled as its owning unit (TextureStatisticsVector.cpp)
// spells it so this unit's COMDAT copy is the same body.
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};
inline void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}
class TextureClass : public TextureBaseClass
{
};
template<class T>
class RefCountPtr
{
public:
	__declspec(dllimport) __forceinline RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
		}
	}
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	T *Referent;
};
struct IDirect3DSurface8;
struct IDirect3DTexture8;
// W3DShaderManager's statics under their owners' names (W3DShaderManager.cpp,
// Rva00075A23Draw.cpp); this unit reads them through its own view types.
#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"
// rva012F9D1C is only an alias of the owned global g_vb (ledger names column); this unit reads the owner through its own view type.
extern class VertexBufferClass *g_vb;
#define rva012F9D1C (*(ShaderVertexBufferRef * *)&g_vb)
// rva012F9D20 is only an alias of the owned global g_quadIndex (ledger names column); this unit reads the owner through its own view type.
extern int g_quadIndex;
#define rva012F9D20 (*(unsigned *)&g_quadIndex)
// 0x009E1F64..0x009E1F70: the render-to-texture surfaces, under their owners' names.
extern unsigned int g_Va009E1F6C;
#define rva012F9D0C (*(ShaderComResourceRef **)&g_Va009E1F6C)
#define rva012F9D04 (*(ShaderComResourceRef **)&W3DShaderManager::m_oldRenderSurface)
#define rva012F9D08 (*(ShaderComResourceRef **)&W3DShaderManager::m_renderTexture)
extern ShaderComResourceRef *rva012F9D10;
// The native eight-slot table is owned by W3DShroudMaterialPass.cpp.
extern RefCountPtr<TextureClass> g_shaderTextureSlots[8];
class BfmeShaderShutdown { public: static void releaseDependentResources(); };
void BfmeShaderShutdown::releaseDependentResources() {
 if(rva012F9D1C) { rva012F9D1C->Release_Ref(); rva012F9D1C=0; }
 rva012F9D20=0;
 if(rva012F9D0C) { ((ReleaseResource)rva012F9D0C->VTable[2])(rva012F9D0C); rva012F9D0C=0; }
 if(rva012F9D04) { ((ReleaseResource)rva012F9D04->VTable[2])(rva012F9D04); rva012F9D04=0; }
 if(rva012F9D08) { ((ReleaseResource)rva012F9D08->VTable[2])(rva012F9D08); rva012F9D08=0; }
 if(rva012F9D10) { ((ReleaseResource)rva012F9D10->VTable[2])(rva012F9D10); rva012F9D10=0; }
 for(unsigned i=0;i<8;++i) ((RefCountPtr<TextureClass> *)g_shaderTextureSlots)[i]=RefCountPtr<TextureClass>();
}

// ?shutdown@W3DShaderManager@@SAXXZ
// Retail 0x00717DA0, 187 bytes: two-phase shader-manager shutdown.
// The buffer at VA 0x012F9D1C is created at 0x00716770 by the matched
// DX8VertexBufferClass constructor at 0x0091F2F0; it is not a texture.
// Extra BFME COM-resource member names are unknown and remain address-qualified.

// Retain the inline call boundary and the separate zero test: MSVC 7.1
// otherwise folds the decrement into a different instruction sequence.
static inline int decrementRef(int *p) { return --*p; }
class ShaderVertexBuffer
{
public:
	virtual void Delete_This();
	int NumRefs;

	void Release_Ref()
	{
		decrementRef(&NumRefs);
		if (NumRefs == 0) Delete_This();
	}
};

class ShaderInterface
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual int shutdown();
};

class W3DFilterInterface
{
public:
	virtual void unused0();
	virtual int shutdown();
};

// Target operands at 0x768BD and 0x768D1 span VA 0xDE1F24..0xDE1F2C,
// proving two shader pointers. The BFME 1 donor has seventeen. Both tables
// are defined by W3DShaderManager.cpp.
extern ShaderInterface *W3DShaders[2];
extern W3DFilterInterface *W3DFilters[10];

// The quad vertex buffer (0x009E1F7C), the glow shader handles
// (0x009E1F74/0x009E1F78) and the vertex shader (0x009E1F84), released as
// COM resources here, under their owners' names.
extern unsigned g_fvfShader;
#define m_vertexBuffer012F9D1C (*(ShaderVertexBuffer **)&g_vb)
#define m_resource012F9D14 (*(ShaderComResourceRef **)&m_dwGlowPixelShader)
#define m_resource012F9D18 (*(ShaderComResourceRef **)&m_dwGlowVertexShader)
#define m_resource012F9D24 (*(ShaderComResourceRef **)&g_fvfShader)

void W3DShaderManager::shutdown()
{
	BfmeShaderShutdown::releaseDependentResources();
	
	m_currentShader = 0;
	m_currentFilter = 0;

	if (m_vertexBuffer012F9D1C) {
		m_vertexBuffer012F9D1C->Release_Ref();
		m_vertexBuffer012F9D1C = 0;
	}

	if (m_resource012F9D14)
		((ReleaseResource)m_resource012F9D14->VTable[2])(m_resource012F9D14);
	if (m_resource012F9D18)
		((ReleaseResource)m_resource012F9D18->VTable[2])(m_resource012F9D18);
	if (m_resource012F9D24)
		((ReleaseResource)m_resource012F9D24->VTable[2])(m_resource012F9D24);

	m_resource012F9D24 = 0;
	m_resource012F9D14 = 0;
	m_resource012F9D18 = 0;

	for (int i = 0; i < 2; ++i) {
		if (W3DShaders[i])
			W3DShaders[i]->shutdown();
	}

	for (int i = 0; i < 10; ++i) {
		if (W3DFilters[i])
			W3DFilters[i]->shutdown();
	}
}
