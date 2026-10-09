// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// stlport
// ?drawBridges@W3DBridgeBuffer@@QAEXAAVRenderInfoClass@@V?$RefCountPtr@VRenderingMethod@FXShader@@@@@Z
// retail 0x000DF776 (966B)
//
// BFME 2's W3DBridgeBuffer::drawBridges, the bridge counterpart of
// W3DRoadBufferDrawRoads.cpp. The Zero Hour damage-state sync is kept as is
// (TheTerrainLogic's bridge list, BridgeInfo copies, W3DBridge::load with the
// fallback reload, then loadBridgesInVertexAndIndexBuffers when anything
// changed); the camera/wireframe/cloud drawing is replaced by the BFME 2 pair
// of paths: untextured under _PresetOpaque2DShader when the terrain render
// state reports mode 1, else rendering mode 4 on g_00DEBC60 and the pushed FX
// rendering method's passes, each pass rendering every enabled, visible
// bridge with the method. Layout: W3DBridge 0x114 bytes at +0x10 (visible
// +0x104, damage state +0x10C, enabled +0x110), bridge count +0xD7B0, index
// count +0x0C, buffers +0x00/+0x04 (as the matched loaders use them).
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

class IndexBufferClass;
class VertexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
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


// Zero Hour BridgeInfo (rowed as Rva0027C36A: ctor 0x0027C36A, operator=
// 0x00085420): bridge index +0x4C and current damage state +0x50.
class Rva0027C36A
{
public:
	Rva0027C36A();
	Rva0027C36A &operator=(const Rva0027C36A &other);
	char m_pad00[0x4C];
	Int bridgeIndex;	// +0x4C
	Int curDamageState;	// +0x50
	char m_pad54[0xA8 - 0x54];
};
typedef Rva0027C36A BridgeInfo;

class Bridge
{
public:
	Bridge *getNext(void) { return m_next; }
	void getBridgeInfo(BridgeInfo *pInfo) { *pInfo = m_bridgeInfo; }
private:
	char m_pad00[4];
	Bridge *m_next;	// +0x04
	char m_pad08[0x0C - 0x08];
	BridgeInfo m_bridgeInfo;	// +0x0C
};

// TheTerrainLogic's slot 40 is Zero Hour's getFirstBridge.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
class BfmeTerrainLogicBridgeView
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
	virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
	virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
	virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual Bridge *getFirstBridge(void);	// slot 40
};

enum BodyDamageType { BODY_PRISTINE };

class W3DBridge
{
public:
	Bool load(enum BodyDamageType curDamageState);	// 0x000DE648
	void renderBridge(FXShader::RenderingMethod *method);	// 0x000DDAB7
	void setEnabled(Bool enable) { m_enabled = enable; }
	Bool isEnabled(void) { return m_enabled; }
	Bool isVisible(void) { return m_visible; }
	enum BodyDamageType getDamageState(void) { return m_curDamageState; }
	void setDamageState(enum BodyDamageType state) { m_curDamageState = state; }
private:
	char m_pad000[0x104];
	Bool m_visible;	// +0x104
	char m_pad105[0x10C - 0x105];
	enum BodyDamageType m_curDamageState;	// +0x10C
	Bool m_enabled;	// +0x110
	char m_pad111[0x114 - 0x111];
};

#define MAX_BRIDGES 200

class W3DBridgeBuffer
{
public:
	void drawBridges(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method);
	void rva000DF52C(Int pLightsIterator);	// loadBridgesInVertexAndIndexBuffers(NULL)
private:
	VertexBufferClass *m_vertexBridge;	// +0x00
	IndexBufferClass *m_indexBridge;	// +0x04
	Int m_curNumBridgeVertices;	// +0x08
	Int m_curNumBridgeIndices;	// +0x0C
	W3DBridge m_bridges[MAX_BRIDGES];	// +0x10
	Int m_numBridges;	// +0xD7B0
};

void W3DBridgeBuffer::drawBridges(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method)
{
	Int curBridge;
	if (TheTerrainLogic) {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(false);
		}
		/* Check for any changed damage states. */
		Bool changed = false;
		for (Bridge *bridge = reinterpret_cast<BfmeTerrainLogicBridgeView *>(TheTerrainLogic)->getFirstBridge(); bridge; bridge = bridge->getNext()) {
			BridgeInfo info;
			bridge->getBridgeInfo(&info);
			if (info.bridgeIndex<0 || info.bridgeIndex>=m_numBridges) {
				continue;
			}
			m_bridges[info.bridgeIndex].setEnabled(true);
			if (m_bridges[info.bridgeIndex].getDamageState() != info.curDamageState) {
				changed = true;
				enum BodyDamageType curState = m_bridges[info.bridgeIndex].getDamageState();
				m_bridges[info.bridgeIndex].setDamageState((BodyDamageType)info.curDamageState);
				if (!m_bridges[info.bridgeIndex].load((BodyDamageType)info.curDamageState)) {
					m_bridges[info.bridgeIndex].load(curState);
					m_bridges[info.bridgeIndex].setDamageState((BodyDamageType)info.curDamageState);
				}
			}
		}
		if (changed) {
			rva000DF52C(0);
		}
	}	else {
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			m_bridges[curBridge].setEnabled(true);
		}
	}
	if (m_curNumBridgeIndices == 0) {
		return;
	}
	DX8Wrapper::Set_Index_Buffer(m_indexBridge,0);
	DX8Wrapper::Set_Vertex_Buffer(m_vertexBridge,0);
	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);

	if (TheTerrainRenderObject &&
		reinterpret_cast<BfmeTerrainRenderView *>(TheTerrainRenderObject)->getRenderState()->m_mode == 1) {
		BFME2Set_Texture(0, BFME2TextureRef(0));
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
		for (curBridge=0; curBridge<m_numBridges; curBridge++) {
			if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
				m_bridges[curBridge].renderBridge(0);
			}
		}
	} else {
		g_00DEBC60->setRenderingMode(4);
		rinfo.Push_Rendering_Method(method);
		Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
		Int passes;
		if (!current->Begin(&passes, 0xffff))
			return;
		passes = 1;
		for (Int pass = 0; pass < passes; pass++) {
			current->Begin_Pass(pass);
			for (curBridge=0; curBridge<m_numBridges; curBridge++) {
				if (m_bridges[curBridge].isEnabled() && m_bridges[curBridge].isVisible()) {
					m_bridges[curBridge].renderBridge(current.Peek());
				}
			}
			current->End_Pass();
		}
		current->End();
		Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		rinfo.Pop_Rendering_Method();
	}
	g_00DEBC60->clearTextures();
	DX8Wrapper::Set_Light_Environment(0);
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
}
