// Target 0x0008E7A4, 1779 bytes, through RET 4 at 0x0008EE94.
// Source lead: BF1 f98983a7d W3DStatusCircleRenderBFME.cpp; ZH W3DStatusCircle.cpp.
// Target calls both buffer updates; +C8/+CC/+D0 are the fade mode/previous/current
// values, and ScriptEngine uses +1A138/+1A13C/+1A148. These are target accesses.
// The init provider still has the provisional TerrainTracksRenderObjClass owner;
// use that verified provider without asserting or renaming its identity.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc

typedef int Int;
typedef float Real;
typedef bool Bool;

class RenderInfoClass;
class IndexBufferClass;
class VertexBufferClass;
class TextureBaseClass;

class StringClass {
 char *m_Buffer; static char *m_EmptyString; static char m_NullChar;
 void Free_String();
public:
 StringClass(int n=0,bool temporary=false);
 __forceinline ~StringClass() { Free_String(); }
};
class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	void Release_Ref()
	{
		if (!--refs)
			Delete_This();
	}
};

class TextureClass
{
public:
	void Release_Ref();
};

class TextureHandle
{
public:
	TextureClass *p;
	TextureHandle() : p(0) {}
	~TextureHandle()
	{
		if (p)
			p->Release_Ref();
	}
};

void BoxSetTexture(unsigned int, TextureBaseClass *&);

struct IDirect3DDevice8;
struct DeviceVtable
{
	char pad[0xe4];
	int (__stdcall *SetRenderState)(IDirect3DDevice8 *, unsigned long, unsigned);
};
struct IDirect3DDevice8
{
	DeviceVtable *v;
};

extern VertexMaterialClass *ScreenMaterial;
extern unsigned number_of_DX8_calls;
class ShaderClass { unsigned bits; protected: static bool ShaderDirty; public:
 unsigned Get_Bits() const {return bits;}
 static __forceinline bool IsDirty(){return ShaderDirty;}
 static __forceinline void Invalidate(){ShaderDirty=true;}
};
class Matrix4 { public: float Row[16]; };
// DX8Wrapper::render_state (VA 0x00DEE5D8, defined in dx8wrapper.cpp): the
// shader word, then Zero Hour's material, Textures[16], Lights[4] and
// LightEnable[4] (0x1E8 bytes, bfmestages/dx8wrapper.h), then world at +0x1EC
// (0x00DEE7C4) and view at +0x22C (0x00DEE804).
struct RenderStateStruct { unsigned shader; char m_pad04[0x1E8]; Matrix4 world; };
class WW3D { friend class W3DStatusCircle; static bool SnapshotActivated; };
struct Rva00726290Matrix3D;
__forceinline void Rva00726290SetWorld(const Rva00726290Matrix3D &);
__forceinline void SetShader(const ShaderClass &);

class DX8Wrapper
{
 friend class W3DStatusCircle;
 friend void SetShader(const ShaderClass &);
 friend void Rva00726290SetWorld(const Rva00726290Matrix3D &);
protected:
 static unsigned render_state_changed, RenderStates[256],render_state_changes;
 static RenderStateStruct render_state;
 static IDirect3DDevice8 *D3DDevice;
public:
	static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
	static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned);
	static void Draw_Triangles(unsigned, unsigned, unsigned, unsigned);
	static void Apply_Render_State_Changes();
	static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
};

#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
class ScriptEngine;
extern GameLogic *TheGameLogic;
class GlobalData;
extern GlobalData *TheWritableGlobalData;
class W3DStatusCircle;
class GameEngine { friend class W3DStatusCircle; private: bool rva00225D38(); };
extern GameEngine *TheGameEngine;

// Retail's singleton (0x012F076C), defined in ScriptEngine.cpp. Spelled with
// the real pointee type so the mangled name matches the definition.
extern ScriptEngine *TheScriptEngine;
extern unsigned char g_trackDirty;







struct Rva00726290Vector3
{
	Real x;
	Real y;
	Real z;
	Rva00726290Vector3(Real x_, Real y_, Real z_)
		: x(x_), y(y_), z(z_) {}
};

struct Rva00726290Matrix3D
{
	Real row[12];

	__forceinline Rva00726290Matrix3D(Bool init)
	{
		if (init)
			Make_Identity();
	}
	__forceinline void Make_Identity()
	{
		row[0] = 1.0f; row[1] = 0.0f; row[2] = 0.0f; row[3] = 0.0f;
		row[4] = 0.0f; row[5] = 1.0f; row[6] = 0.0f; row[7] = 0.0f;
		row[8] = 0.0f; row[9] = 0.0f; row[10] = 1.0f; row[11] = 0.0f;
	}
	__forceinline void Set_Translation(const Rva00726290Vector3 &t)
	{
		row[3] = t.x;
		row[7] = t.y;
		row[11] = t.z;
	}
};

__forceinline void Rva00726290SetWorld(const Rva00726290Matrix3D &m)
{
	DX8Wrapper::render_state.world.Row[0] = m.row[0];
	DX8Wrapper::render_state.world.Row[1] = m.row[4];
	DX8Wrapper::render_state.world.Row[2] = m.row[8];
	DX8Wrapper::render_state.world.Row[3] = 0.0f;
	DX8Wrapper::render_state.world.Row[4] = m.row[1];
	DX8Wrapper::render_state.world.Row[5] = m.row[5];
	DX8Wrapper::render_state.world.Row[6] = m.row[9];
	DX8Wrapper::render_state.world.Row[7] = 0.0f;
	DX8Wrapper::render_state.world.Row[8] = m.row[2];
	DX8Wrapper::render_state.world.Row[9] = m.row[6];
	DX8Wrapper::render_state.world.Row[10] = m.row[10];
	DX8Wrapper::render_state.world.Row[11] = 0.0f;
	DX8Wrapper::render_state.world.Row[12] = m.row[3];
	DX8Wrapper::render_state.world.Row[13] = m.row[7];
	DX8Wrapper::render_state.world.Row[14] = m.row[11];
	DX8Wrapper::render_state.world.Row[15] = 1.0f;
	DX8Wrapper::render_state_changed = (DX8Wrapper::render_state_changed & 0xfffbffff) | 1;
}


__forceinline void SetShader(const ShaderClass &shader) {
 if (ShaderClass::IsDirty() || shader.Get_Bits()!=DX8Wrapper::render_state.shader) {
  DX8Wrapper::render_state.shader=shader.Get_Bits();
  DX8Wrapper::render_state_changed|=0x8000;
  StringClass shaderDescription;
 }
}
class TerrainTracksRenderObjClass { public: int rva0008E1F2(); };
class W3DStatusCircle { public:
 virtual void Render(RenderInfoClass &);
 int updateCircleVB(); int updateScreenVB(int);
};
#define BFME_SET_RS(state_, value_) do { \
	if (DX8Wrapper::RenderStates[(state_)] != (unsigned)(value_)) { \
		if (WW3D::SnapshotActivated) { \
			StringClass valueName(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(valueName, (state_), (value_)); \
		} \
		DX8Wrapper::RenderStates[(state_)] = (value_); \
		DX8Wrapper::D3DDevice->v->SetRenderState(DX8Wrapper::D3DDevice, (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8Wrapper::render_state_changes; \
	} \
} while (0)

// ?Render@W3DStatusCircle@@UAEXAAVRenderInfoClass@@@Z
void W3DStatusCircle::Render(RenderInfoClass &)
{
	if (*(Int *)((char *)TheGameLogic + 0x110) == 9)
		return;

	IndexBufferClass *&indexBuffer = *(IndexBufferClass **)((char *)this + 0xd4);
	if (indexBuffer == 0) {
		((TerrainTracksRenderObjClass *)this)->rva0008E1F2();
	}
	if (indexBuffer == 0)
		return;

	Bool setIndex = false;
	Rva00726290Matrix3D tm(true);
	if (*(Bool *)((char *)TheWritableGlobalData + 0x9d0) &&
		!TheGameLogic->rva00085124()) {
		if (g_trackDirty)
			((W3DStatusCircle *)this)->updateCircleVB();

		VertexMaterialClass *vmat = *(VertexMaterialClass **)((char *)this + 0xdc);
		if (vmat)
			++vmat->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		DX8Wrapper::render_state_changed |= 0x4000;
		SetShader(*(ShaderClass*)((char*)this+0xd8));
		{
			TextureHandle texture;
			BoxSetTexture(0, (TextureBaseClass *&)texture.p);
		}
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(
			*(VertexBufferClass **)((char *)this + 0xe0), 0);

		Rva00726290Vector3 vec(0.95f, 0.67f, 0.0f);
		tm.Set_Translation(vec);
		Rva00726290SetWorld(tm);
		setIndex = true;
		DX8Wrapper::Draw_Triangles(
			0, 20, 0,
			(*(unsigned *)((char *)this + 0xc4) * 3));
	}

	Int &fade = *(Int *)((char *)this + 0xc8);
	Real &previousIntensity = *(Real *)((char *)this + 0xcc);
	Real &currentIntensity = *(Real *)((char *)this + 0xd0);
	if (TheGameEngine->rva00225D38()) {
		previousIntensity = currentIntensity;
		fade = *(Int *)((char *)TheScriptEngine + 0x1a138);
		if (fade == 0) {
			currentIntensity = 0.0f;
			return;
		}
		currentIntensity = *(Real *)((char *)TheScriptEngine + 0x1a148);
		if (*(Bool *)((char *)TheScriptEngine + 0x1a13c))
			previousIntensity = currentIntensity;
	}
	if (fade == 0)
		return;

	if (!setIndex) {
		VertexMaterialClass *vmat = *(VertexMaterialClass **)((char *)this + 0xdc);
		if (vmat)
			++vmat->refs;
		if (ScreenMaterial)
			ScreenMaterial->Release_Ref();
		ScreenMaterial = vmat;
		DX8Wrapper::render_state_changed |= 0x4000;
		DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
		{
			TextureHandle texture;
			BoxSetTexture(0, (TextureBaseClass *&)texture.p);
		}
	}

	Real intensity = currentIntensity;
	Real frameFraction = *(Real *)((*reinterpret_cast<char **>(&TheGameEngine)) + 0x3c);
	if (previousIntensity < 0.0f) {
		previousIntensity = intensity;
	} else if (currentIntensity != previousIntensity) {
        Real old = previousIntensity;
        intensity = old;
        Real inv = 1.0f - frameFraction;
        intensity *= inv;
        intensity += currentIntensity * frameFraction;
    } else { intensity = previousIntensity; }
	intensity *= 255.0f;
	Int clr = (Int)intensity;
	Int diffuse = (0xff << 24) | (clr << 16) | (clr << 8) | clr;
	((W3DStatusCircle *)this)->updateScreenVB(diffuse);

	tm.Make_Identity();
	Rva00726290SetWorld(tm);
	unsigned shaderBits = 0x00114037;
	if (ShaderClass::IsDirty() || shaderBits != DX8Wrapper::render_state.shader) {
		DX8Wrapper::render_state.shader = shaderBits;
		DX8Wrapper::render_state_changed |= 0x8000;
		StringClass shaderDescription(0, false);
	}
	DX8Wrapper::Set_Vertex_Buffer(
		*(VertexBufferClass **)((char *)this + 0xe4), 0);
	DX8Wrapper::Apply_Render_State_Changes();

	switch (fade) {
		default:
		case 2:
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case 1:
			BFME_SET_RS(0xab, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			BFME_SET_RS(0xab, 1);
			break;
		case 3:
			BFME_SET_RS(0x13, 9);
			BFME_SET_RS(0x14, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
		case 4:
			BFME_SET_RS(0x13, 1);
			BFME_SET_RS(0x14, 3);
			DX8Wrapper::Draw_Triangles(0, 2, 0, 6);
			break;
	}
	ShaderClass::Invalidate();
}
