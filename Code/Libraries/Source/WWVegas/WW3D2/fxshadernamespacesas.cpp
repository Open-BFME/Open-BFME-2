// cl: /O1 /arch:SSE /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// fxshadernamespacesas.cpp -- the "Sas" FX parameter source: the DirectX
// Standard Annotations and Semantics namespace ("Sas.Camera.WorldToView",
// "Sas.NumPointLights", ...) that FX shaders bind their parameters through.
//
// Target facts: the source registers itself under "Sas" (ctor 0x001510C2,
// dtor 0x001505CD); its vtable 0x00BD3A34 slot 1 is the dispatcher 0x0014FAC2,
// which splits the parameter path through the rowed Rva001530E9Parse
// 0x001530E9 and either binds a callback through the rowed
// FXShaderParameterBinder::AddBinding 0x00153ACA or forwards a path to a
// member source's slot 1. Member offsets and vtables come from the ctor:
// +0x04 camera (vtable 0x00BD3898), +0x10 time (0x00BD3834), +0x14/+0x2C/+0x44
// the ambient, directional and point light arrays, +0x5C the shadow array
// (0x00BD3A54) and +0xB8 the skeleton (0x00BD38A0).
//
// Names: WorldBuilder.exe (debug build of the same tree) carries this file's
// path Code\Libraries\Source\WWVegas\WW3D2\fxshadernamespacesas.cpp in the
// asserts of FXShaderParameterSourceNamespaceSAS::ResolveBindings (same arm
// strings in the same order, each arm m_<member>.ResolveBindings) and of the
// nested SourceNamespace_Matrix::ResolveBindings, ::SetInverse and
// ::SetInverseTranspose. Bodies without an assert keep address names.

#include <vector>

typedef long HRESULT;
typedef const char *D3DXHANDLE;

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n();
struct ID3DXEffect
{
	FX_SLOT(00) FX_SLOT(01) FX_SLOT(02) FX_SLOT(03) FX_SLOT(04) FX_SLOT(05) FX_SLOT(06) FX_SLOT(07)
	FX_SLOT(08) FX_SLOT(09) FX_SLOT(10) FX_SLOT(11) FX_SLOT(12) FX_SLOT(13) FX_SLOT(14) FX_SLOT(15)
	FX_SLOT(16) FX_SLOT(17) FX_SLOT(18) FX_SLOT(19) FX_SLOT(20) FX_SLOT(21) FX_SLOT(22) FX_SLOT(23)
	FX_SLOT(24) FX_SLOT(25)
	virtual HRESULT __stdcall SetInt(D3DXHANDLE parameter, int value);	// +0x68
	FX_SLOT(27) FX_SLOT(28) FX_SLOT(29) FX_SLOT(30) FX_SLOT(31)
	FX_SLOT(32) FX_SLOT(33) FX_SLOT(34) FX_SLOT(35) FX_SLOT(36) FX_SLOT(37)
	virtual HRESULT __stdcall SetMatrix(D3DXHANDLE parameter, const void *matrix);	// +0x98
	FX_SLOT(39) FX_SLOT(40) FX_SLOT(41) FX_SLOT(42) FX_SLOT(43)
	virtual HRESULT __stdcall SetMatrixTranspose(D3DXHANDLE parameter, const void *matrix);	// +0xB0
};
#undef FX_SLOT

#include <string.h>
struct D3DXMATRIX
{
	D3DXMATRIX() {}
	float m[4][4];
};
extern "C" D3DXMATRIX *__stdcall D3DXMatrixInverse(D3DXMATRIX *out, float *determinant, const D3DXMATRIX *matrix);
extern "C" D3DXMATRIX *__stdcall D3DXMatrixTranspose(D3DXMATRIX *out, const D3DXMATRIX *matrix);

// Output of the rowed path parser 0x001530E9: the leading component, its
// "[*]" and "[n]" flags and index, then the remainder after the first '.'.
struct Rva001530E9Path
{
	char m_name[0x40];
	bool m_hasStar;
	bool m_hasBracket;
	int m_index;
	const char *m_rest;
};
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
class Rva0007671F
{
public:
	Rva0007671F();
private:
	float m_rows[4][4];
};

class LightEnvironmentClass;

// The rowed point/non-point light counters 0x0013F6F0/0x0013F750
// (Rva0013F6F0Cluster.cpp) run on DX8Wrapper's light environment.
class Rva0013F6F0LightEnv
{
public:
	int countNonPoint() const;
	int countPoint() const;
};

class DX8Wrapper
{
public:
	static LightEnvironmentClass *Get_Light_Environment() { return Light_Environment; }
protected:
	static LightEnvironmentClass *Light_Environment;
};

class FXShaderParameterBinder;

class FXShaderParameterSourceNamespace
{
public:
	virtual ~FXShaderParameterSourceNamespace();
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder) = 0;
};

// An array source ("AmbientLight[0].Color", "Shadow[*]..."): the elements
// and the source used for an index out of range. Its dispatchers
// (0x00150E54 for the light arrays, 0x00150FCC for shadows) are slot 1 of
// vtables 0x00BD3A3C/44/4C/54.
template <class T>
class FXShaderParameterSourceNamespace_Array : public FXShaderParameterSourceNamespace
{
public:
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

	int GetSize() const { return m_Elements.size(); }
	T &rva0014F454(int index);

private:
	std::vector<T> m_Elements;
	T m_Default;
};

class FXShaderParameterSourceNamespaceSAS : public FXShaderParameterSourceNamespace
{
public:
	// The matrix source (vtable 0x00BD3828: deleting dtor 0x001F45C3, the
	// dispatcher 0x0014FC48, a pure slot 2 yielding the matrix); the camera's
	// and skeleton's matrices (vtables 0x00BD383C/48/74/80/8C) override slot 2.
	struct SourceNamespace_Matrix : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		virtual void slot02(Rva0007671F &matrix) = 0;

		void rva0014D440(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetInverse(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetInverseTranspose(ID3DXEffect *effect, D3DXHANDLE parameter);
	};

	// vtable 0x00BD3898, dispatcher 0x0014FCC6; two matrix sources follow.
	struct SourceNamespace_Camera : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void *m_matrices[2];
	};

	// vtable 0x00BD3834, dispatcher 0x0014FD69.
	struct SourceNamespace_Time : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
	};

	// Array elements: vtables 0x00BD3854/5C/64 (dispatchers 0x0014FDCA,
	// 0x0014FE33, 0x0014FEB8), each carrying its index.
	struct SourceNamespace_AmbientLight : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		int m_index;
	};
	struct SourceNamespace_DirectionalLight : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		int m_index;
	};
	struct SourceNamespace_PointLight : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		int m_index;
	};

	// vtable 0x00BD386C, dispatcher 0x0014FF57; WorldBuilder tests the handle
	// at +0x48 through an inline accessor (name not in either binary).
	struct SourceNamespace_Shadow : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		bool hasShadowMap() const { return m_shadowMap != 0; }
		char m_pad04[0x48 - 0x04];
		void *m_shadowMap;
	};

	// vtable 0x00BD38A0, dispatcher 0x0014FFF6.
	struct SourceNamespace_Skeleton : public FXShaderParameterSourceNamespace
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
	};

	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

	void NumShadows(ID3DXEffect *effect, D3DXHANDLE parameter);

private:
	SourceNamespace_Camera m_SourceNamespace_Camera;					// +0x04
	SourceNamespace_Time m_SourceNamespace_Time;						// +0x10
	FXShaderParameterSourceNamespace_Array<SourceNamespace_AmbientLight> m_SourceNamespace_AmbientLight;		// +0x14
	FXShaderParameterSourceNamespace_Array<SourceNamespace_DirectionalLight> m_SourceNamespace_DirectionalLight;	// +0x2C
	FXShaderParameterSourceNamespace_Array<SourceNamespace_PointLight> m_SourceNamespace_PointLight;			// +0x44
	FXShaderParameterSourceNamespace_Array<SourceNamespace_Shadow> m_SourceNamespace_Shadow;				// +0x5C
	SourceNamespace_Skeleton m_SourceNamespace_Skeleton;					// +0xB8
};

// A bound method: the object and the member function the rowed delegate
// constructor 0x00579E47 copies into its ref-counted impl.
class DelegateTarget
{
};

struct DelegateDesc
{
	typedef void (DelegateTarget::*Method)(ID3DXEffect *, D3DXHANDLE);

	template <class T>
	DelegateDesc(T *object, void (T::*method)(ID3DXEffect *, D3DXHANDLE))
		: m_object(object), m_method(reinterpret_cast<Method>(method)) {}

	void *m_object;
	Method m_method;
};

typedef void (*FXShaderParameterCallback)(ID3DXEffect *effect, D3DXHANDLE parameter);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// The callback handle FXShaderParameterBinder::AddBinding takes by value and
// destroys, built in its argument slot from a static callback or a bound
// method. WorldBuilder shows both as template constructors of one handle
// base (0x00750610 for a callback, 0x009FD3E0 for a delegate); retail rows
// their out-of-line copies 0x00080221 and 0x00579E47 under the two
// placeholder classes chained here.
class Rva00080221
{
public:
	Rva00080221(const int *callback);
	TargetRef00217D4C *m_ptr;
};

class Rva00579E47 : public Rva00080221
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	Rva00579E47(const int *callback) : Rva00080221(callback) {}
};

struct TreeHintRef00217D4C : public Rva00579E47
{
	TreeHintRef00217D4C(FXShaderParameterCallback callback) : Rva00579E47((const int *)&callback) {}
	TreeHintRef00217D4C(DelegateDesc desc) : Rva00579E47(desc) {}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class FXShaderParameterBinder
{
public:
	void AddBinding(TreeHintRef00217D4C callback, D3DXHANDLE parameter);
};

// Retail 0x0014D595, 27 bytes: 1 while DX8Wrapper has a light environment.
void Rva0014D595NumAmbientLights(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	effect->SetInt(parameter, DX8Wrapper::Get_Light_Environment() != 0);
}

// Retail 0x0014D64C, 35 bytes.
void Rva0014D64CNumDirectionalLights(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0013F6F0LightEnv *env = (Rva0013F6F0LightEnv *)DX8Wrapper::Get_Light_Environment();
	effect->SetInt(parameter, env ? env->countNonPoint() : 0);
}

// Retail 0x0014D7B1, 35 bytes.
void Rva0014D7B1NumPointLights(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0013F6F0LightEnv *env = (Rva0013F6F0LightEnv *)DX8Wrapper::Get_Light_Environment();
	effect->SetInt(parameter, env ? env->countPoint() : 0);
}

// Retail 0x0014FAC2, 390 bytes.
void FXShaderParameterSourceNamespaceSAS::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	Rva001530E9Path t;
	Rva001530E9Parse(name, &t);
	if (_strcmpi(t.m_name, "Camera") == 0)
		m_SourceNamespace_Camera.ResolveBindings(t.m_rest, parameter, binder);
	else if (_strcmpi(t.m_name, "Time") == 0)
		m_SourceNamespace_Time.ResolveBindings(t.m_rest, parameter, binder);
	else if (_strcmpi(t.m_name, "NumAmbientLights") == 0)
		binder->AddBinding(TreeHintRef00217D4C(Rva0014D595NumAmbientLights), parameter);
	else if (_strcmpi(t.m_name, "AmbientLight") == 0)
		m_SourceNamespace_AmbientLight.ResolveBindings(name, parameter, binder);
	else if (_strcmpi(t.m_name, "NumDirectionalLights") == 0)
		binder->AddBinding(TreeHintRef00217D4C(Rva0014D64CNumDirectionalLights), parameter);
	else if (_strcmpi(t.m_name, "DirectionalLight") == 0)
		m_SourceNamespace_DirectionalLight.ResolveBindings(name, parameter, binder);
	else if (_strcmpi(t.m_name, "NumPointLights") == 0)
		binder->AddBinding(TreeHintRef00217D4C(Rva0014D7B1NumPointLights), parameter);
	else if (_strcmpi(t.m_name, "PointLight") == 0)
		m_SourceNamespace_PointLight.ResolveBindings(name, parameter, binder);
	else if (_strcmpi(t.m_name, "NumShadows") == 0)
		binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &FXShaderParameterSourceNamespaceSAS::NumShadows)), parameter);
	else if (_strcmpi(t.m_name, "Shadow") == 0)
		m_SourceNamespace_Shadow.ResolveBindings(name, parameter, binder);
	else if (_strcmpi(t.m_name, "Skeleton") == 0)
		m_SourceNamespace_Skeleton.ResolveBindings(t.m_rest, parameter, binder);
}

// Retail 0x0014F86C, 66 bytes: the leading run of shadows with a map.
void FXShaderParameterSourceNamespaceSAS::NumShadows(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	int i;
	for (i = 0; i < 1; i++)
	{
		if (!m_SourceNamespace_Shadow.rva0014F454(i).hasShadowMap())
			break;
	}
	effect->SetInt(parameter, i);
}

// Retail 0x0014F454, 44 bytes: an index out of range yields the default.
template <class T>
T &FXShaderParameterSourceNamespace_Array<T>::rva0014F454(int index)
{
	if (index >= 0 && index < m_Elements.size())
		return m_Elements[index];
	return m_Default;
}

// Retail 0x0014FC48, 126 bytes: the bare name binds the matrix, "Inverse" and
// "InverseTranspose" its inverse and inverse transpose.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Matrix::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	if (name == 0)
		binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Matrix::rva0014D440)), parameter);
	else
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "Inverse") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Matrix::SetInverse)), parameter);
		else if (_strcmpi(t.m_name, "InverseTranspose") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Matrix::SetInverseTranspose)), parameter);
	}
}

// Retail 0x0014D440, 52 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Matrix::rva0014D440(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0007671F m;
	slot02(m);
	effect->SetMatrixTranspose(parameter, &m);
}

// Retail 0x0014D474, 87 bytes: a singular matrix falls back to its transpose.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Matrix::SetInverse(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0007671F m;
	D3DXMATRIX inverse;
	slot02(m);
	if (D3DXMatrixInverse(&inverse, 0, (const D3DXMATRIX *)&m) == 0)
		D3DXMatrixTranspose(&inverse, (const D3DXMATRIX *)&m);
	effect->SetMatrixTranspose(parameter, &inverse);
}

// Retail 0x0014D4CB, 87 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Matrix::SetInverseTranspose(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0007671F m;
	D3DXMATRIX inverse;
	slot02(m);
	if (D3DXMatrixInverse(&inverse, 0, (const D3DXMATRIX *)&m) == 0)
		D3DXMatrixTranspose(&inverse, (const D3DXMATRIX *)&m);
	effect->SetMatrix(parameter, &inverse);
}
