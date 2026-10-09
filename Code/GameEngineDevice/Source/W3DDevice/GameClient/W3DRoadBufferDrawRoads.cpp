// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?drawRoads@W3DRoadBuffer@@QAEXAAVRenderInfoClass@@V?$RefCountPtr@VRenderingMethod@FXShader@@@@HHHHPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z
// retail 0x000D79CB (955B)
//
// BFME 2's W3DRoadBuffer::drawRoads. Zero Hour's camera/cloud/noise/wireframe
// parameters are gone: the caller (the height map render, 0x000E35F1) passes
// the RenderInfoClass and the FX rendering method to push for the roads. The
// Zero Hour skeleton remains -- the visibility-driven buffer reload, the
// stacking loop and the per-type Draw_Triangles -- but each road type now
// either binds no texture under _PresetOpaque2DShader (when the terrain
// render object's slot-18 state reports mode 1) or hands its base texture and
// its _nrm texture (else the 1x1 fallback in the +0x18 holder) to the road
// shader interface g_00DEBC60 (rendering mode 2) and draws through the pushed
// rendering method's passes. The callee shapes follow the matched
// W3DShaderManagerScreenBWFilterSet.cpp (Set_Shader), MeshClassRender.cpp
// (RenderInfoClass rendering-method stack) and Rva000E19A3Dtor.cpp (the
// g_00DEBC60 interface). The Zero Hour-header W3DRoadBuffer.cpp cannot see
// these BFME 2 classes, so the body is compiled here against views of the
// W3DRoadBuffer (+0x00 types, +0x0C initialized, +0x18 fallback texture,
// +0x2C/+0x30 current type, +0x40 type count, +0x4C/+0x4D update flags) and
// RoadType (0x24 bytes: counts +0x10/+0x14, id +0x18, stacking +0x20)
// layouts its matched rows use.
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
	virtual void slot4();
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

// RoadType's texture getters (0x000D6A3F / 0x000D6A57) and its buffer bind
// (0x000D4435) as rowed.
class BfmeRoadTypeTexturesView
{
public:
	RefCountPtr<TextureClass> rva000D6A3F();
	RefCountPtr<TextureClass> rva000D6A57();
};
class Rva000D4435Buffers
{
public:
	void rva000D4435();
};

class RoadType
{
public:
	void applyTexture() { reinterpret_cast<Rva000D4435Buffers *>(this)->rva000D4435(); }
	Int getStacking(void) { return m_stackingOrder; }
	Int getUniqueID(void) { return m_uniqueID; }
	Int getNumVertices(void) { return m_numRoadVertices; }
	Int getNumIndices(void) { return m_numRoadIndices; }
private:
	char m_textures[0x10];
	Int m_numRoadVertices;	// +0x10
	Int m_numRoadIndices;	// +0x14
	Int m_uniqueID;	// +0x18
	Bool m_isAutoLoaded;	// +0x1C
	Int m_stackingOrder;	// +0x20
};

struct IRegion2D
{
	struct { Int x, y; } lo, hi;
};

#define MAP_XY_FACTOR (10.0f)

template <class T> class RefMultiListIterator;
class RenderObjClass;
typedef RefMultiListIterator<RenderObjClass> RefRenderObjListIterator;

class W3DRoadBuffer
{
public:
	void drawRoads(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method,
		Int minX, Int maxX, Int minY, Int maxY, RefRenderObjListIterator *pDynamicLightsIterator);
protected:
	Bool visibilityChanged(const IRegion2D &bounds);
	void loadRoadsInVertexAndIndexBuffers(void);

	RoadType *m_roadTypes;	// +0x00
	char m_pad04[0x0C - 0x04];
	Bool m_initialized;	// +0x0C
	char m_pad0D[0x18 - 0x0D];
	RefCountPtr<TextureClass> m_fallbackTexture;	// +0x18
	char m_pad1C[0x2C - 0x1C];
	Int m_curUniqueID;	// +0x2C
	Int m_curRoadType;	// +0x30
	char m_pad34[0x40 - 0x34];
	Int m_maxRoadTypes;	// +0x40
	char m_pad44[0x4C - 0x44];
	Bool m_updateBuffers;	// +0x4C
	Bool m_bool4D;	// +0x4D
};

void W3DRoadBuffer::drawRoads(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method,
	Int minX, Int maxX, Int minY, Int maxY, RefRenderObjListIterator *pDynamicLightsIterator)
{
	if (!m_initialized)
		return;

	Bool untextured = TheTerrainRenderObject &&
		reinterpret_cast<BfmeTerrainRenderView *>(TheTerrainRenderObject)->getRenderState()->m_mode == 1;

	IRegion2D bounds;
	bounds.lo.x = minX*MAP_XY_FACTOR;
	bounds.hi.x = maxX*MAP_XY_FACTOR;
	bounds.lo.y = minY*MAP_XY_FACTOR;
	bounds.hi.y = maxY*MAP_XY_FACTOR;

	Bool loadBuffers = false;
	if (m_bool4D) {
		if (visibilityChanged(bounds)) {
			loadBuffers = true;
		}
	}
	if (m_updateBuffers)
		loadBuffers = true;
	m_updateBuffers = false;
	m_bool4D = false;

	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);

	Int i;
	Int maxStacking = 0;
	for (i=0; i<m_maxRoadTypes; i++) {
		if (m_roadTypes[i].getStacking() > maxStacking) {
			maxStacking = m_roadTypes[i].getStacking();
		}
	}
	Int stacking;
	for (stacking=0; stacking <= maxStacking; stacking++) {
		for (i=0; i<m_maxRoadTypes; i++) {
			if (stacking != m_roadTypes[i].getStacking()) {
				continue;
			}
			m_curUniqueID = m_roadTypes[i].getUniqueID();
			m_curRoadType = i;
			if (loadBuffers) loadRoadsInVertexAndIndexBuffers();
			if (m_roadTypes[i].getNumIndices() == 0) continue;
			m_roadTypes[i].applyTexture();
			if (untextured) {
				BFME2Set_Texture(0, BFME2TextureRef(0));
				DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
				DX8Wrapper::Draw_Triangles(0, m_roadTypes[i].getNumIndices()/3, 0, m_roadTypes[i].getNumVertices());
				continue;
			}
			g_00DEBC60->setRenderingMode(2);
			g_00DEBC60->setBaseTexture(reinterpret_cast<BfmeRoadTypeTexturesView &>(m_roadTypes[i]).rva000D6A3F());
			Bool hasNrm = reinterpret_cast<BfmeRoadTypeTexturesView &>(m_roadTypes[i]).rva000D6A57().Peek() != 0;
			if (hasNrm)
				g_00DEBC60->setNormalTexture(reinterpret_cast<BfmeRoadTypeTexturesView &>(m_roadTypes[i]).rva000D6A57());
			else
				g_00DEBC60->setNormalTexture(m_fallbackTexture);
			rinfo.Push_Rendering_Method(method);
			Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
			RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
			Int passes;
			if (!current->Begin(&passes, 0xffff))
				return;
			passes = 1;
			for (Int pass = 0; pass < passes; pass++) {
				current->Begin_Pass(pass);
				DX8Wrapper::Draw_Triangles(0, m_roadTypes[i].getNumIndices()/3, 0, m_roadTypes[i].getNumVertices());
				current->End_Pass();
			}
			current->End();
			Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
			rinfo.Pop_Rendering_Method();
		}
	}
	m_curRoadType = 0;
	g_00DEBC60->clearTextures();
	DX8Wrapper::Set_Light_Environment(0);
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
}
