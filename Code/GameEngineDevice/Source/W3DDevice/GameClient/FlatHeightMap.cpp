// cl: /O1 /arch:SSE /G7 /MD /EHsc
// stlport
// BFME1 f98983a7 FlatHeightMap.cpp / ZH Render tile loop supplies the
// semantic tile traversal and output-bounds guide. BFME2 adds the FX pass
// sequence independently verified in the955B road renderer. Target facts:
// WB names renderTerrain; native E1D6E..E1F42 proves the complete468B driver;
// E1C1A..E1D51 proves the311B tile loop and its four output int pointers.
// Camera list38B4; D4-byte tile stride3888; dimensions3890/3894; distance
// at tile64 and optional limiting fields38A8/38AC/38B0 are native accesses.
// The tile helper and limiting field names remain address-derived views.
// The rendering method's stack/refcounts and seven slots come from the
// matched road renderer; no donor-only layout is asserted as target fact.
#include <vector>

typedef int Int;
typedef bool Bool;
typedef float Real;

class TextureClass
{
public:
	void Release_Ref();	// 0x0061ED10
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}
	T *Peek(void) const { return Referent; }
 bool isValid()const{return Referent!=0;}
	T *operator->(void) const { return Referent; }

private:
	T *Referent;
};
// The texture handle's copy constructor is the out-of-line 0x000424BB.
template <> RefCountPtr<TextureClass>::RefCountPtr(const RefCountPtr<TextureClass> &rhs);

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
public:
	virtual void slot1();
	virtual bool Begin(Int *passCount, Int flags);	// slot 2
	virtual void Begin_Pass(Int pass);	// slot 3
	virtual void rvaSlot4(int);
	virtual void End_Pass(void);	// slot 5
	virtual void End(void);	// slot 6
};
}

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

class LightEnvironmentClass;

class RenderInfoClass
{
public:
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);
	const RenderingMethodStackType &Get_Rendering_Method_Stack(void) const;

	char _bfme_unk_00[0x28];
	LightEnvironmentClass *light_environment;	// +0x28
};

// Callees taking the rendering-method stack as (first element, count) around
// the passes; their identities are not established.
void Rva001688FF(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);
void Rva00168952(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	__forceinline ~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};

class ShaderClass
{
public:
	static ShaderClass _PresetOpaque2DShader;
	unsigned int ShaderBits;
	static bool ShaderDirty;
};

class TextureBaseClass
{
public:
	void Release_Ref();
};

struct BFME2TextureResource;
struct BFME2TextureRef
{
	BFME2TextureRef(BFME2TextureResource *texture) : Ptr(texture) {}
	~BFME2TextureRef()
	{
		if (Ptr)
			((TextureBaseClass *)Ptr)->Release_Ref();
	}
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

#define PAD_STDCALL10(p) \
	virtual void __stdcall p##0() = 0; virtual void __stdcall p##1() = 0; virtual void __stdcall p##2() = 0; \
	virtual void __stdcall p##3() = 0; virtual void __stdcall p##4() = 0; virtual void __stdcall p##5() = 0; \
	virtual void __stdcall p##6() = 0; virtual void __stdcall p##7() = 0; virtual void __stdcall p##8() = 0; \
	virtual void __stdcall p##9() = 0;

struct IDirect3DDevice8
{
	PAD_STDCALL10(d0) PAD_STDCALL10(d1) PAD_STDCALL10(d2) PAD_STDCALL10(d3) PAD_STDCALL10(d4)
	PAD_STDCALL10(d5) PAD_STDCALL10(d6) PAD_STDCALL10(d7) PAD_STDCALL10(d8)
	virtual void __stdcall d90() = 0; virtual void __stdcall d91() = 0;
	virtual long __stdcall SetVertexShader(void *shader) = 0;	// slot 92
	PAD_STDCALL10(e0)
	virtual void __stdcall f103() = 0; virtual void __stdcall f104() = 0;
	virtual void __stdcall f105() = 0; virtual void __stdcall f106() = 0;
	virtual long __stdcall SetPixelShader(void *shader) = 0;	// slot 107
};

extern unsigned number_of_DX8_calls;

struct RenderStateStruct
{
	ShaderClass shader;
};

class DX8Wrapper
{
public:
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader.ShaderBits = shader.ShaderBits;
		render_state_changed |= 0x8000;
		StringClass str;
	}
	static __forceinline void Set_Vertex_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetVertexShader(shader);
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Pixel_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetPixelShader(shader);
		number_of_DX8_calls++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned int render_state_changed;
	static RenderStateStruct render_state;
};

// g_00DEBC60, the road/terrain shader interface (Rva000E19A3Dtor.cpp).
class Rva000E19A3Interface
{
public:
	virtual void setRenderingMode(int mode) = 0;
	virtual void setBaseTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void setNormalTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void clearTextures() = 0;
};
extern Rva000E19A3Interface *g_00DEBC60;

// TheTerrainRenderObject's slot 18 returns a state whose +0x14 mode 1 makes
// the roads draw untextured.
struct BfmeTerrainRenderState { char m_pad[0x14]; Int m_mode; };
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class BfmeTerrainRenderView
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual BfmeTerrainRenderState *getRenderState();	// slot 18
};


class Rva000E0EDD { public:bool rva000E0EDD(int cameraIndex); };
class W3DTerrainBackground { public:void rva0011580A(RenderInfoClass&,bool,FXShader::RenderingMethod*); };
struct TerrainTileView { char unknown00[0x64];float distance;char unknown68[0xD4-0x68]; };
class FlatHeightMapRenderObjClass : public BfmeTerrainRenderView {
public:
 void renderTerrain(RenderInfoClass&rinfo,int *minX,int *maxX,int *minY,int *maxY);
 void rva000E1C1A(RenderInfoClass&rinfo,bool untextured,int *minX,int *maxX,int *minY,int *maxY,FXShader::RenderingMethod*method);
private:
 char unknown04[0x3888-4];
 struct TerrainTileView *m_tiles; int m_numTiles,m_tilesWidth,m_tilesHeight;
 char unknown3898[16];bool m_partial;char unknown38A9[3];int m_currentTile;float m_distanceLimit;
 _STL::vector<void*> m_cameras;
 char unknown38C0[0x3938-0x38C0]; RefCountPtr<FXShader::RenderingMethod> m_method;
};
void FlatHeightMapRenderObjClass::renderTerrain(RenderInfoClass&rinfo,int *minX,int *maxX,int *minY,int *maxY) {
 if(!m_method.isValid())return;
 DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
 if(getRenderState() && getRenderState()->m_mode==1) {
  DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
  BFME2Set_Texture(0,BFME2TextureRef(0));
  rva000E1C1A(rinfo,1,minX,maxX,minY,maxY,0);
 } else {
  g_00DEBC60->setRenderingMode(0);
  rinfo.Push_Rendering_Method(m_method);
  Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(),rinfo.Get_Rendering_Method_Stack().size());
  RefCountPtr<FXShader::RenderingMethod> current=rinfo.Get_Rendering_Method_Stack()[0];
  int passes;
  if(!current->Begin(&passes,0xffff))return;
  for(int pass=0;pass<passes;++pass) {
   current->Begin_Pass(pass);
   rva000E1C1A(rinfo,0,minX,maxX,minY,maxY,current.Peek());
   current->End_Pass();
  }
  current->End();
  Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(),rinfo.Get_Rendering_Method_Stack().size());
  rinfo.Pop_Rendering_Method();
 }
 DX8Wrapper::Set_Light_Environment(0);
}

void FlatHeightMapRenderObjClass::rva000E1C1A(RenderInfoClass &rinfo,bool untextured,int *minX,int *maxX,int *minY,int *maxY,FXShader::RenderingMethod*method) {
 int cameraIndex=-1;
 for(int k=0;k<(int)m_cameras.size();++k) {
  if(m_cameras[k]==*(void**)&rinfo){cameraIndex=k;break;}
 }
 for(int i=0;i<m_tilesWidth;++i) {
  for(int j=0;j<m_tilesHeight;++j) {
   TerrainTileView *tile=m_tiles+j*m_tilesWidth+i;
   if(((Rva000E0EDD*)tile)->rva000E0EDD(cameraIndex))continue;
   if(m_partial && m_currentTile<m_numTiles && tile->distance>m_distanceLimit)continue;
   ((W3DTerrainBackground*)tile)->rva0011580A(rinfo,untextured,method);
   if(i*16<*minX)*minX=i*16;
   if(j*16<*minY)*minY=j*16;
   if((i+1)*16>*maxX)*maxX=(i+1)*16;
   if((j+1)*16>*maxY)*maxY=(j+1)*16;
  }
 }
}
