// cl: /DNDEBUG /MD /EHsc /O1
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
class TextureBaseClass { public: void Release_Ref(); void Add_Ref(); };
class ShaderTextureHandle { public:
 TextureBaseClass *ptr;
 ShaderTextureHandle(TextureBaseClass *p):ptr(p) { if(ptr) ptr->Add_Ref(); }
 ~ShaderTextureHandle() { if(ptr) ptr->Release_Ref(); }
 ShaderTextureHandle &operator=(const ShaderTextureHandle &o) { if(o.ptr) o.ptr->Add_Ref(); if(ptr) ptr->Release_Ref(); ptr=o.ptr; return *this; }
};
extern ShaderVertexBufferRef *rva012F9D1C;
extern unsigned rva012F9D20;
extern ShaderComResourceRef *rva012F9D0C, *rva012F9D04, *rva012F9D08, *rva012F9D10;
// 0x012F9D28 is the shader texture-handle table (BfmeHandleCX *[8]), defined by
// Rva00C6C520StaticInit.cpp. Declared by its defining name; the table's 4-byte
// slots are cleared through the ShaderTextureHandle view this TU models.
class BfmeHandleCX;
extern BfmeHandleCX *g_bfmeTableDU;
class BfmeShaderShutdown { public: static void releaseDependentResources(); };
void BfmeShaderShutdown::releaseDependentResources() {
 if(rva012F9D1C) { rva012F9D1C->Release_Ref(); rva012F9D1C=0; }
 rva012F9D20=0;
 if(rva012F9D0C) { ((ReleaseResource)rva012F9D0C->VTable[2])(rva012F9D0C); rva012F9D0C=0; }
 if(rva012F9D04) { ((ReleaseResource)rva012F9D04->VTable[2])(rva012F9D04); rva012F9D04=0; }
 if(rva012F9D08) { ((ReleaseResource)rva012F9D08->VTable[2])(rva012F9D08); rva012F9D08=0; }
 if(rva012F9D10) { ((ReleaseResource)rva012F9D10->VTable[2])(rva012F9D10); rva012F9D10=0; }
 for(unsigned i=0;i<8;++i) ((ShaderTextureHandle *)&g_bfmeTableDU)[i]=0;
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

class FilterInterface
{
public:
	virtual void unused0();
	virtual int shutdown();
};

static ShaderInterface *W3DShaders[17];
static FilterInterface *W3DFilters[10];

class W3DShaderManager
{
public:
	static void shutdown();

protected:
	static int m_currentShader;
	static int m_currentFilter;
	static ShaderVertexBuffer *m_vertexBuffer012F9D1C;
	static ShaderComResourceRef *m_resource012F9D14;
	static ShaderComResourceRef *m_resource012F9D18;
	static ShaderComResourceRef *m_resource012F9D24;
};

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

	for (int i = 0; i < 17; ++i) {
		if (W3DShaders[i])
			W3DShaders[i]->shutdown();
	}

	for (int i = 0; i < 10; ++i) {
		if (W3DFilters[i])
			W3DFilters[i]->shutdown();
	}
}
