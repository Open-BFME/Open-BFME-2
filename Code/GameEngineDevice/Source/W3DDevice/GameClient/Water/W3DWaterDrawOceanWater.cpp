// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?drawOceanWater@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@PAVRenderableStandingWaterArea@@_N@Z
// retail 0x001011CA..0x001014A9 (735 bytes) EH thiscall ret 0xC.
// WorldBuilder twin 0x00768E50 names WaterRenderObjClass::drawOceanWater
// (W3DWaterDraw.cpp assert line 1422 "shader.IsBound()"); it opens with the
// same statements: the area's +0x40 standing water area is read and the
// shader is either the depth-only shader (rowed 0x00100981 on this) or a
// counted copy (rowed 0x001007D5) of the standing water area's FX shader
// setup (rowed 0x00308DF0) chosen by a conditional expression whose two
// temporaries are destroyed under a flag word. Retail follows the
// neighbouring drawRiverWater (0x00100A0B) and the road pass draw: the
// identity world transform (DX8Wrapper::Set_Transform WORLD with a Matrix4
// identity local) the render info's light environment (rowed
// Set_Light_Environment) the area remembered at this+0x260 the shader
// pushed as a rendering method and the method stack handed to the pinned
// 0x001688FF; the stack's first method runs Begin(&passes 0xFFFF) and per
// pass draws the area through the rowed 0x000834CE (the area's own vertex
// and index buffers; its 0x0008304A callee is WorldBuilder's
// RenderableStandingWaterArea::AllocateAndFillBuffers); then End the pinned
// 0x00168952 Pop_Rendering_Method the remembered area and light
// environment cleared and the vertex and pixel shaders reset.
// Codegen notes: the two shader temporaries bind as const references of
// the counted-pointer type (the rowed holder spelling of 0x001007D5 is a
// derived view of it) so neither is copied before the shader local is;
// the donor Set_Transform switch is kept whole because its default arm
// hands m2 to the device's SetTransform and that keeps retail's sixteen
// dead m2 stores (bfme2_mesh_material_pass.cpp keeps the same switch).
#include <vector>
#include <set>
// Keep typed iterator comparisons local; do not emit the incompatible
// out-of-line base-iterator comparison used by other STLport units.
namespace _STL {
 template<class T, class L, class R>
 static inline bool operator!=(const _Rb_tree_iterator<T, L>& a,
                               const _Rb_tree_iterator<T, R>& b)
 { return a._M_node != b._M_node; }
}

typedef int Int;
typedef bool Bool;
typedef float Real;

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(void) : Referent(0) {}
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	template <class U>
	RefCountPtr(const RefCountPtr<U> &rhs) : Referent(rhs.Peek())
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

class FXShaderSetup : public FXShader::RenderingMethod
{
};

class LightEnvironmentClass;
class CameraClass;

#include "../../../../../Libraries/Source/WWVegas/WW3D2/RenderInfoClass.h"

// Rendering-method stack walkers (element array, count): rows Rva001688FFShift
// 0x001688FF and Rva00168952Clear 0x00168952 (RenderingMethodLinkArray.cpp).
class Rva001688FFElement;
void Rva001688FFShift(Rva001688FFElement **items, int count);
void Rva00168952Clear(Rva001688FFElement **items, int count);

#define PAD_STDCALL10(p) \
	virtual void __stdcall p##0() = 0; virtual void __stdcall p##1() = 0; virtual void __stdcall p##2() = 0; \
	virtual void __stdcall p##3() = 0; virtual void __stdcall p##4() = 0; virtual void __stdcall p##5() = 0; \
	virtual void __stdcall p##6() = 0; virtual void __stdcall p##7() = 0; virtual void __stdcall p##8() = 0; \
	virtual void __stdcall p##9() = 0;

struct IDirect3DDevice8
{
	PAD_STDCALL10(d0) PAD_STDCALL10(d1) PAD_STDCALL10(d2) PAD_STDCALL10(d3)
	virtual void __stdcall d40() = 0; virtual void __stdcall d41() = 0;
	virtual void __stdcall d42() = 0; virtual void __stdcall d43() = 0;
	virtual long __stdcall SetTransform(int state, const void *matrix) = 0;	// slot 44
	virtual void __stdcall d45() = 0; virtual void __stdcall d46() = 0; virtual void __stdcall d47() = 0;
	virtual void __stdcall d48() = 0; virtual void __stdcall d49() = 0;
	PAD_STDCALL10(d5) PAD_STDCALL10(d6) PAD_STDCALL10(d7) PAD_STDCALL10(d8)
	virtual void __stdcall d90() = 0; virtual void __stdcall d91() = 0;
	virtual long __stdcall SetVertexShader(void *shader) = 0;	// slot 92
	PAD_STDCALL10(e0)
	virtual void __stdcall f103() = 0; virtual void __stdcall f104() = 0;
	virtual void __stdcall f105() = 0; virtual void __stdcall f106() = 0;
	virtual long __stdcall SetPixelShader(void *shader) = 0;	// slot 107
};

extern unsigned number_of_DX8_calls;

#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"

#include "../../../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
// WWMath matrix3d.h's inline Set(x, y, z, pos), which the canonical header leaves to units.
static __forceinline void matrixSet(Matrix3D &m, const Vector3 &x, const Vector3 &y, const Vector3 &z, const Vector3 &pos)
{
	m.Row[0].Set(x.X, y.X, z.X, pos.X);
	m.Row[1].Set(x.Y, y.Y, z.Y, pos.Y);
	m.Row[2].Set(x.Z, y.Z, z.Z, pos.Z);
}

class Matrix4
{
public:
	Matrix4() {}
	__forceinline explicit Matrix4(const Matrix3D &matrix3D) { Init(matrix3D); }
	__forceinline Matrix4(const Matrix4 &matrix4)
	{
		Row[0] = matrix4.Row[0];
		Row[1] = matrix4.Row[1];
		Row[2] = matrix4.Row[2];
		Row[3] = matrix4.Row[3];
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		Row[3] = m.Row[3];
		return *this;
	}
	__forceinline Matrix4(const Vector4 &vector4, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = vector4;
		Row[1] = r1;
		Row[2] = r2;
		Row[3] = r3;
	}
	__forceinline void Init(const Matrix3D &matrix3D)
	{
		Row[0] = matrix3D.Row[0];
		Row[1] = matrix3D.Row[1];
		Row[2] = matrix3D.Row[2];
		Row[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4 Transpose() const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}

	Vector4 Row[4];
};
// DX8Wrapper::render_state (dx8wrapper.cpp, protected static, 656 bytes at 0x00DEE5D8): this view names only the transforms; world is +0x1EC, view +0x22C.
struct RenderStateStruct
{
	char m_shaderToLights[0x1EC];
	Matrix4 world;
	Matrix4 view;
	char m_buffers[0x290 - 0x26C];
};

enum _D3DTRANSFORMSTATETYPE
{
	D3DTS_VIEW = 2,
	D3DTS_PROJECTION = 3,
	D3DTS_WORLD = 256
};

class DX8Wrapper
{
protected:
	static RenderStateStruct render_state;
private:

public:
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __declspec(dllimport) __forceinline void Set_Transform(_D3DTRANSFORMSTATETYPE transform, const Matrix3D &matrix3D)
	{
		Matrix4 m2(matrix3D);
		switch ((int)transform)
		{
		case D3DTS_WORLD:
			DX8Wrapper::render_state.world = m2.Transpose();
			render_state_changed |= 0x1;
			render_state_changed &= ~0x40000;
			break;
		case D3DTS_VIEW:
			DX8Wrapper::render_state.view = m2.Transpose();
			render_state_changed |= 0x2;
			render_state_changed &= ~0x80000;
			break;
		default:
			number_of_DX8_calls++;
			m2 = m2.Transpose();
			_Get_D3D_Device8()->SetTransform(transform, &m2);
			break;
		}
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

private:
	template<class T> friend struct DataRowPrivateProbe;
};

// The rowed 0x00308DF0: the standing water area's (lazily reloaded) FX
// shader setup.
class Rva00308DF0Ref;
#include "../../../../Include/W3DDevice/GameClient/Rva00308DF0.h"

// The rowed 0x001007D5: a counted copy of a raw shader pointer.
class Rva001007D5Model;
struct Rva001007D5Holder : public RefCountPtr<FXShaderSetup>
{
};
Rva001007D5Holder Rva001007D5Hold(Rva001007D5Model *p);

// The rowed 0x00100981: the lazily created depth-only water shader.
class Rva00100981
{
public:
	RefCountPtr<FXShaderSetup> rva00100981();
};

// The rowed 0x000834CE: the area's vertex and index buffer draw.
class Rva000834CE
{
public:
	void rva000834CE();
};

#define PAD_VIRTUAL10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

// One object attached to a standing water area (the area's +0x58 set): slot
// 49 answers the object that draws itself with the render info (slot 12).
class Rva001014A9Drawer
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void Render(RenderInfoClass &rinfo);	// slot 12
};

class Rva001014A9Item
{
public:
	PAD_VIRTUAL10(a0) PAD_VIRTUAL10(a1) PAD_VIRTUAL10(a2) PAD_VIRTUAL10(a3)
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44();
	virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48();
	virtual Rva001014A9Drawer *Get_Drawer();	// slot 49
};

class RenderableStandingWaterArea
{
public:
	Rva00308DF0 *getStandingWaterArea() const { return m_standingWaterArea; }
	const _STL::set<Rva001014A9Item *> &getItems() const { return m_items; }

private:
	unsigned char m_pad00[0x40];
	Rva00308DF0 *m_standingWaterArea;	// +0x40
	unsigned char m_pad44[0x58 - 0x44];
	_STL::set<Rva001014A9Item *> m_items;	// +0x58 (header), +0x5C (count)
};

// The rowed per-entry visibility test (Rva0007FD89EntryVisible.cpp).
class Rva0007FD89Entry
{
public:
	bool rva0007FB85(void *camera);
};

struct WaterRenderBox;
class Rva0007E6F6
{
public:
	const WaterRenderBox &rva0007E6F6();
};

class CameraClass
{
public:
	PAD_VIRTUAL10(c0) PAD_VIRTUAL10(c1) PAD_VIRTUAL10(c2) PAD_VIRTUAL10(c3) PAD_VIRTUAL10(c4)
	PAD_VIRTUAL10(c5) PAD_VIRTUAL10(c6) PAD_VIRTUAL10(c7) PAD_VIRTUAL10(c8) PAD_VIRTUAL10(c9)
	PAD_VIRTUAL10(d0) PAD_VIRTUAL10(d1) PAD_VIRTUAL10(d2)
	virtual bool Cull_Box(const WaterRenderBox &box);	// slot 130
};

class RenderableRiverArea;

class LightClass : public RefCountClass
{
public:
	enum LightType { POINT = 0, DIRECTIONAL, SPOT };
	LightClass(LightType type = POINT);
	virtual void l01(); virtual void l02(); virtual void l03(); virtual void l04();
	virtual void l05(); virtual void l06(); virtual void l07(); virtual void l08(); virtual void l09();
	virtual void l10(); virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
	virtual void l15(); virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
	virtual void l20();
	virtual void Set_Transform(const Matrix3D &m);	// slot 21
	void Set_Ambient(const Vector3 &color) { Ambient.Set(color); }
	void Set_Diffuse(const Vector3 &color) { Diffuse.Set(color); }

private:
	unsigned char m_pad08[0xD4 - 0x08];
	Vector3 Ambient;	// +0xD4
	Vector3 Diffuse;	// +0xE0
	unsigned char m_padEC[0x120 - 0xEC];
};

class LightEnvironmentClass
{
public:
	LightEnvironmentClass();
	~LightEnvironmentClass();
	void Add_Light(const LightClass &light);

private:
	unsigned char m_data[0x228];
};

void rva001173f0(unsigned int renderInfo);

// The counted shader holder of the water draw: retail assigns it through the
// rowed 0x001007B0, the one add-ref/release/store body ICF keeps under
// HAnimComboDataClass::Set_HAnim. Its body is visible (noinline, as in
// W3DMeshHolderHold.cpp): cl then proves the holder's address does not
// escape and keeps the held pointer in EDI across the draw loop as retail
// does; with only a declaration it reloads the holder after every call.
// The holder itself is a RefCountPtr<RenderingMethod>: its release is the
// rowed fold 0x0007B724 the unwind funclet 0x007641F4 jumps to.
class HAnimClass : public RefCountClass
{
};
class HAnimComboDataClass
{
public:
	__declspec(noinline) void Set_HAnim(HAnimClass *motion)
	{
		if (motion != 0)
			motion->Add_Ref();
		if (HAnim != 0)
			HAnim->Release_Ref();
		HAnim = motion;
	}

private:
	HAnimClass *HAnim;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct WaterGlobalLightView
{
	unsigned char m_pad000[0x8FC];
	Vector3 m_diffuse[3];	// +0x8FC
	Vector3 m_lightPos[3];	// +0x920
	unsigned char m_pad944[0x988 - 0x944];
	Int m_numGlobalLights;	// +0x988
};

class WaterRenderObjClass
{
protected:
	void drawRiverWater(RenderInfoClass &rinfo, RenderableRiverArea *area);
	void drawOceanWater(RenderInfoClass &rinfo, RenderableStandingWaterArea *area, Bool depthOnly);
	void rva001014A9(RenderInfoClass &rinfo, bool depthOnly);

private:
	unsigned char m_pad000[0x108];
	_STL::vector<RenderableStandingWaterArea *> m_standingWaterAreas;	// +0x108
	unsigned char m_pad114[0x118 - 0x114];
	_STL::vector<RenderableRiverArea *> m_riverAreas;	// +0x118
	unsigned char m_pad124[0x25C - 0x124];
	Bool m_doWaterRender;	// +0x25C
	Rva00308DF0 *m_currentStandingWaterArea;	// +0x260
};

void WaterRenderObjClass::drawOceanWater(RenderInfoClass &rinfo, RenderableStandingWaterArea *area, Bool depthOnly)
{
	Rva00308DF0 *standingWaterArea = area->getStandingWaterArea();
	RefCountPtr<FXShaderSetup> shader = depthOnly
		? static_cast<const RefCountPtr<FXShaderSetup> &>(reinterpret_cast<Rva00100981 *>(this)->rva00100981())
		: static_cast<const RefCountPtr<FXShaderSetup> &>(Rva001007D5Hold(reinterpret_cast<Rva001007D5Model *>(standingWaterArea->rva00308DF0())));
	if (!shader.Peek())
		return;

	Matrix3D tm(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, tm);
	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
	m_currentStandingWaterArea = area->getStandingWaterArea();

	rinfo.Push_Rendering_Method(shader);
	Rva001688FFShift((Rva001688FFElement **)rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
	RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
	Int passes;
	if (current->Begin(&passes, 0xffff))
	{
		for (Int pass = 0; pass < passes; pass++)
		{
			current->Begin_Pass(pass);
			reinterpret_cast<Rva000834CE *>(area)->rva000834CE();
			current->End_Pass();
		}
		current->End();
	}
	Rva00168952Clear((Rva001688FFElement **)rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
	rinfo.Pop_Rendering_Method();
	m_currentStandingWaterArea = 0;
	DX8Wrapper::Set_Light_Environment(0);
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
}

// retail 0x001014A9..0x001017E7 (830 bytes) EH thiscall ret 8; the water
// object's draw (pinned callee of WaterRenderObjClass::Render 0x001017E7,
// which passes false). WorldBuilder twin 0x007684C0 (W3DWaterDraw.cpp; its
// name is lost): a light environment from the global lights, the objects
// attached to each visible standing water area drawn under that area's
// shader, then the ocean pass over the visible standing water areas and the
// river pass over the rivers the camera does not cull.
void WaterRenderObjClass::rva001014A9(RenderInfoClass &rinfo, bool depthOnly)
{
	if (!m_doWaterRender)
		return;

	LightEnvironmentClass lenv;
	for (Int i = 0; i < reinterpret_cast<const WaterGlobalLightView *>(TheWritableGlobalData)->m_numGlobalLights; i++)
	{
		LightClass *light = new LightClass(LightClass::DIRECTIONAL);
		light->Set_Ambient(Vector3(0.0f, 0.0f, 0.0f));
		light->Set_Diffuse(Vector3(reinterpret_cast<const WaterGlobalLightView *>(TheWritableGlobalData)->m_diffuse[i].X,
			reinterpret_cast<const WaterGlobalLightView *>(TheWritableGlobalData)->m_diffuse[i].Y,
			reinterpret_cast<const WaterGlobalLightView *>(TheWritableGlobalData)->m_diffuse[i].Z));
		Matrix3D tm;
		matrixSet(tm, Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
			Vector3(reinterpret_cast<const WaterGlobalLightView *>(TheWritableGlobalData)->m_lightPos[i]),
			Vector3(0.0f, 0.0f, 0.0f));
		light->Set_Transform(tm);
		lenv.Add_Light(*light);
		light->Release_Ref();
	}
	rinfo.light_environment = &lenv;

	Bool drewItems = false;
	for (_STL::vector<RenderableStandingWaterArea *>::iterator it = m_standingWaterAreas.begin(); it != m_standingWaterAreas.end(); ++it)
	{
		RenderableStandingWaterArea *area = *it;
		if (area->getItems().empty())
			continue;
		if (!reinterpret_cast<Rva0007FD89Entry *>(area)->rva0007FB85(&rinfo.Camera))
			continue;
		Rva00308DF0 *standingWaterArea = area->getStandingWaterArea();
		FXShaderSetup *shader = depthOnly
			? reinterpret_cast<Rva00100981 *>(this)->rva00100981().Peek()
			: reinterpret_cast<FXShaderSetup *>(standingWaterArea->rva00308DF0());
		if (!shader)
			continue;
		drewItems = true;
		RefCountPtr<FXShader::RenderingMethod> method;
		reinterpret_cast<HAnimComboDataClass &>(method).Set_HAnim(reinterpret_cast<HAnimClass *>(shader));
		rinfo.Push_Rendering_Method(method);
		for (_STL::set<Rva001014A9Item *>::const_iterator item = area->getItems().begin(); item != area->getItems().end(); ++item)
		{
			Rva001014A9Item *object = *item;
			if (object && object->Get_Drawer())
				object->Get_Drawer()->Render(rinfo);
		}
		rinfo.Pop_Rendering_Method();
	}
	if (drewItems)
		rva001173f0(reinterpret_cast<unsigned int>(&rinfo));

	for (_STL::vector<RenderableStandingWaterArea *>::iterator ocean = m_standingWaterAreas.begin(); ocean != m_standingWaterAreas.end(); ++ocean)
	{
		RenderableStandingWaterArea *area = *ocean;
		if (reinterpret_cast<Rva0007FD89Entry *>(area)->rva0007FB85(&rinfo.Camera))
			drawOceanWater(rinfo, area, depthOnly);
	}

	rinfo.light_environment = 0;
	for (_STL::vector<RenderableRiverArea *>::iterator river = m_riverAreas.begin(); river != m_riverAreas.end(); ++river)
	{
		RenderableRiverArea *area = *river;
		if (!rinfo.Camera.Cull_Box(reinterpret_cast<Rva0007E6F6 *>(area)->rva0007E6F6()))
			drawRiverWater(rinfo, area);
	}
}
