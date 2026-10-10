// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
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

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }

	Real X;
	Real Y;
	Real Z;
	Real W;
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
		{
			Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
			Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
			Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		}
	}

	Vector4 Row[3];
};

class Matrix4
{
public:
	__forceinline explicit Matrix4(const Matrix3D &m) { Init(m); }
	__forceinline Matrix4(const Matrix4 &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		Row[3] = m.Row[3];
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		Row[3] = m.Row[3];
		return *this;
	}
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0;
		Row[1] = r1;
		Row[2] = r2;
		Row[3] = r3;
	}
	__forceinline void Init(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
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
extern Matrix4 BFME2World;

enum _D3DTRANSFORMSTATETYPE
{
	D3DTS_VIEW = 2,
	D3DTS_PROJECTION = 3,
	D3DTS_WORLD = 256
};

class DX8Wrapper
{
public:
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __forceinline void Set_Transform(_D3DTRANSFORMSTATETYPE transform, const Matrix3D &m)
	{
		Matrix4 m2(m);
		switch ((int)transform)
		{
		case D3DTS_WORLD:
			BFME2World = m2.Transpose();
			render_state_changed |= 0x1;
			render_state_changed &= ~0x40000;
			break;
		case D3DTS_VIEW:
			render_state_view = m2.Transpose();
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
	static Matrix4 render_state_view;
};

// The rowed 0x00308DF0: the standing water area's (lazily reloaded) FX
// shader setup.
class Rva00308DF0Ref;
class Rva00308DF0
{
public:
	Rva00308DF0Ref *rva00308DF0();
};

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

class RenderableStandingWaterArea
{
public:
	Rva00308DF0 *getStandingWaterArea() const { return m_standingWaterArea; }

private:
	unsigned char m_pad00[0x40];
	Rva00308DF0 *m_standingWaterArea;	// +0x40
};

class WaterRenderObjClass
{
protected:
	void drawOceanWater(RenderInfoClass &rinfo, RenderableStandingWaterArea *area, Bool depthOnly);

private:
	unsigned char m_pad000[0x260];
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
