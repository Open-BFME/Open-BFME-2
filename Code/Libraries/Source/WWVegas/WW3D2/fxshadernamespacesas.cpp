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

struct D3DXPARAMETER_DESC
{
	const char *Name;
	const char *Semantic;
	int Class;
	int Type;
	unsigned int Rows;
	unsigned int Columns;
	unsigned int Elements;
	unsigned int Annotations;
	unsigned int StructMembers;
	unsigned int Flags;
	unsigned int Bytes;
};

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n();
struct ID3DXEffect
{
	FX_SLOT(00) FX_SLOT(01) FX_SLOT(02) FX_SLOT(03)
	virtual HRESULT __stdcall GetParameterDesc(D3DXHANDLE parameter, D3DXPARAMETER_DESC *desc);	// +0x10
	FX_SLOT(05) FX_SLOT(06) FX_SLOT(07) FX_SLOT(08) FX_SLOT(09) FX_SLOT(10)
	virtual D3DXHANDLE __stdcall GetParameterElement(D3DXHANDLE parameter, unsigned int index);	// +0x2C
	FX_SLOT(12) FX_SLOT(13) FX_SLOT(14) FX_SLOT(15)
	FX_SLOT(16) FX_SLOT(17) FX_SLOT(18) FX_SLOT(19) FX_SLOT(20) FX_SLOT(21) FX_SLOT(22) FX_SLOT(23)
	FX_SLOT(24) FX_SLOT(25)
	virtual HRESULT __stdcall SetInt(D3DXHANDLE parameter, int value);	// +0x68
	FX_SLOT(27) FX_SLOT(28) FX_SLOT(29)
	virtual HRESULT __stdcall SetFloat(D3DXHANDLE parameter, float value);	// +0x78
	FX_SLOT(31) FX_SLOT(32) FX_SLOT(33)
	virtual HRESULT __stdcall SetVector(D3DXHANDLE parameter, const float *vector);	// +0x88
	FX_SLOT(35) FX_SLOT(36) FX_SLOT(37)
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
// "[*]" and "[n]" flags and index (WorldBuilder's asserts name these three
// t.m_IsArray, t.m_IsArrayElement and t.m_ArrayIndex), then the remainder
// after the first '.'.
struct Rva001530E9Path
{
	char m_name[0x40];
	bool m_IsArray;
	bool m_IsArrayElement;
	int m_ArrayIndex;
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

// DX8Wrapper's light environment (LightEnvironmentClass, BFME 2 layout of
// reference/shims/bfme2lightenv), under the placeholder name its rowed
// point/non-point light counters and finders 0x0013F6F0/20/50/80 carry
// (Rva0013F6F0Cluster.cpp).
class Rva0013F6F0LightEnv
{
public:
	int countNonPoint() const;
	int findNonPoint(int index) const;
	int countPoint() const;
	int findPoint(int index) const;

	struct Vector3
	{
		Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
		float X, Y, Z;
	};
	const Vector3 &Get_Equivalent_Ambient() const { return OutputAmbient; }
	const float *Get_Light_Direction(int i) const { return InputLights[i].Direction; }
	const float *Get_Light_Diffuse(int i) const { return InputLights[i].Diffuse; }
	float getPointOrad(int i) const { return InputLights[i].m_outerRadius; }
	const float *getPointDiffuse(int i) const { return InputLights[i].m_diffuse; }
	const float *getPointCenter(int i) const { return InputLights[i].m_center; }

private:
	struct InputLightStruct
	{
		float Direction[3];
		float Ambient[3];
		float Diffuse[3];
		bool DiffuseRejected;
		bool m_point;
		float m_center[3];
		float m_innerRadius;
		float m_outerRadius;
		float m_ambient[3];
		float m_diffuse[3];
	};

	void *m_vtable;
	int LightCount;
	float ObjectCenter[3];
	InputLightStruct InputLights[4];
	Vector3 OutputAmbient;
};

extern bool ShaderOverbrightEnabled;

class WW3D
{
public:
	static unsigned int Get_Sync_Time() { return SyncTime; }
private:
	static unsigned int SyncTime;
};

class DX8Wrapper
{
public:
	static LightEnvironmentClass *Get_Light_Environment() { return Light_Environment; }
protected:
	static LightEnvironmentClass *Light_Environment;
};

class FXShaderParameterBinder;

// The rowed second PushDynamicSetStack 0x0015354E takes its argument under
// this placeholder enum; the skeleton source passes 1.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

// The 0x30-byte transform the skeleton's instancing vector holds.
struct Matrix3D
{
	float Row[3][4];
};

class FXShaderParameterSourceNamespace
{
public:
	virtual ~FXShaderParameterSourceNamespace();
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder) = 0;
};

// The default source (WorldBuilder's fxshaderparameterbinder.cpp), whose
// rowed ResolveBindings 0x00153664 binds a struct parameter member by member;
// every leaf namespace runs it before its own names.
class FXShaderParameterSourceNamespace_Struct : public FXShaderParameterSourceNamespace
{
public:
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
};

// Effect setters rowed under placeholder names in their own units; the
// namespaces below bind them by address.
class Rva0014D722Outer;
class Rva0014D7D4Outer;
class Rva0014D887Outer;
class Rva0014D9F3Outer;
void __cdecl rva0014D522(void *effect, void *parameter);
class Rva0014D722This { public: void rva0014D722(Rva0014D722Outer *effect, void *parameter); };
class Rva0014D7D4This { public: void rva0014D7D4(Rva0014D7D4Outer *effect, void *parameter); };
class Rva0014D887This { public: void rva0014D887(Rva0014D887Outer *effect, void *parameter); };
class Rva0014D982This { public: void rva0014D982(ID3DXEffect *effect, D3DXHANDLE parameter); };
class Rva0014D9F3This { public: void rva0014D9F3(Rva0014D9F3Outer *effect, void *parameter); };

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

	// vtable 0x00BD3898, dispatcher 0x0014FCC6; the two matrix sources'
	// slot 2 (0x0014DCC8, 0x0014DE5C) build the camera matrices. Their type
	// names follow the arm strings.
	struct SourceNamespace_Camera : public FXShaderParameterSourceNamespace_Struct
	{
		struct Matrix_WorldToView : public SourceNamespace_Matrix
		{
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_Projection : public SourceNamespace_Matrix
		{
			virtual void slot02(Rva0007671F &matrix);
		};

		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

		Matrix_WorldToView m_WorldToView;	// +0x04
		Matrix_Projection m_Projection;		// +0x08
	};

	// vtable 0x00BD3834, dispatcher 0x0014FD69.
	struct SourceNamespace_Time : public FXShaderParameterSourceNamespace_Struct
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
	};

	// Array elements: vtables 0x00BD3854/5C/64 (dispatchers 0x0014FDCA,
	// 0x0014FE33, 0x0014FEB8), each carrying its light index.
	struct SourceNamespace_AmbientLight : public FXShaderParameterSourceNamespace_Struct
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D5B0(ID3DXEffect *effect, D3DXHANDLE parameter);
		int m_index;
	};
	struct SourceNamespace_DirectionalLight : public FXShaderParameterSourceNamespace_Struct
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D66F(ID3DXEffect *effect, D3DXHANDLE parameter);
		int m_index;
	};
	struct SourceNamespace_PointLight : public FXShaderParameterSourceNamespace_Struct
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D90E(ID3DXEffect *effect, D3DXHANDLE parameter);
		int m_index;
	};

	// vtable 0x00BD386C, dispatcher 0x0014FF57; WorldBuilder tests the handle
	// at +0x48 through an inline accessor (name not in either binary).
	struct SourceNamespace_Shadow : public FXShaderParameterSourceNamespace_Struct
	{
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D96A(ID3DXEffect *effect, D3DXHANDLE parameter);
		bool hasShadowMap() const { return m_shadowMap != 0; }
		int m_index;
		Rva0007671F m_WorldToShadow;	// +0x08
		void *m_shadowMap;		// +0x48
	};

	// vtable 0x00BD38A0, dispatcher 0x0014FFF6. Member names after the
	// WorldBuilder asserts of the SetArray_MeshToJointToWorld_* setters; the
	// matrix sources follow their arm strings.
	struct SourceNamespace_Skeleton : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_Skeleton();
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

		void rva0014DF88(ID3DXEffect *effect, D3DXHANDLE parameter);
		void rva0014DB2C(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetArray_MeshToJointToWorld_BoneTransform(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetArray_MeshToJointToWorld_Matrix3D(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetArray_MeshToJointToWorld_Matrix4x4(ID3DXEffect *effect, D3DXHANDLE parameter);

		struct Matrix_MeshToJointToWorld : public SourceNamespace_Matrix
		{
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_MeshToJointToView : public SourceNamespace_Matrix
		{
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_MeshToJointToProjection : public SourceNamespace_Matrix
		{
			virtual void slot02(Rva0007671F &matrix);
		};

		Matrix_MeshToJointToWorld m_MeshToJointToWorld;			// +0x04
		Matrix_MeshToJointToView m_MeshToJointToView;			// +0x08
		Matrix_MeshToJointToProjection m_MeshToJointToProjection;	// +0x0C
		const void *m_SkinInfo;						// +0x10
		const std::vector<unsigned short> *m_BoneMappingTable;		// +0x14
		int m_NumJointsPerVertex;					// +0x18
		const std::vector<Matrix3D> *m_InstancingInfo;			// +0x1C
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

	template <class T, class M>
	DelegateDesc(T *object, M method)
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
	ID3DXEffect *PeekEffect() const { return m_effect; }
	void PushDynamicSetStack(const char *name);
	void PushDynamicSetStack(ScienceType type);
	void PopDynamicSetStack();
	void AddBinding(TreeHintRef00217D4C callback, D3DXHANDLE parameter);
private:
	ID3DXEffect *m_effect;
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

// Retail 0x0014F86C, 47 bytes: the leading run of shadows with a map.
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

// Retail 0x0014FCC6, 163 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Camera::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "WorldToView") == 0)
			m_WorldToView.ResolveBindings(t.m_rest, parameter, binder);
		else if (_strcmpi(t.m_name, "Projection") == 0)
			m_Projection.ResolveBindings(t.m_rest, parameter, binder);
		else if (_strcmpi(t.m_name, "NearFarClipping") == 0)
			binder->AddBinding(TreeHintRef00217D4C((FXShaderParameterCallback)rva0014D522), parameter);
	}
}

// Retail 0x0014D564, 49 bytes: the sync time in seconds.
void Rva0014D564Now(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	effect->SetFloat(parameter, WW3D::Get_Sync_Time() * 0.001f);
}

// Retail 0x0014FD69, 97 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Time::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "Now") == 0)
			binder->AddBinding(TreeHintRef00217D4C(Rva0014D564Now), parameter);
	}
}

// Retail 0x0014FDCA, 105 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_AmbientLight::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "Color") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_AmbientLight::rva0014D5B0)), parameter);
	}
}

// Retail 0x0014D66F, 179 bytes: the indexed directional light's diffuse.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_DirectionalLight::rva0014D66F(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	float color[4];
	Rva0013F6F0LightEnv *env = (Rva0013F6F0LightEnv *)DX8Wrapper::Get_Light_Environment();
	if (env != 0 && m_index >= 0 && m_index < env->countNonPoint())
	{
		const float *diffuse = env->Get_Light_Diffuse(env->findNonPoint(m_index));
		color[0] = diffuse[0];
		color[1] = diffuse[1];
		color[2] = diffuse[2];
		if (ShaderOverbrightEnabled)
		{
			color[0] *= 2.0f;
			color[1] *= 2.0f;
			color[2] *= 2.0f;
		}
		color[3] = 0.0f;
		effect->SetVector(parameter, color);
		return;
	}
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	color[3] = 0.0f;
	effect->SetVector(parameter, color);
}

// Retail 0x0014FE33, 133 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_DirectionalLight::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "Color") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_DirectionalLight::rva0014D66F)), parameter);
		else if (_strcmpi(t.m_name, "Direction") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &Rva0014D722This::rva0014D722)), parameter);
	}
}

// Retail 0x0014D90E, 92 bytes: the indexed point light's outer radius.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_PointLight::rva0014D90E(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	Rva0013F6F0LightEnv *env = (Rva0013F6F0LightEnv *)DX8Wrapper::Get_Light_Environment();
	if (env != 0 && m_index >= 0 && m_index < env->countPoint())
		effect->SetFloat(parameter, env->getPointOrad(env->findPoint(m_index)));
	else
		effect->SetFloat(parameter, 0.0f);
}

// Retail 0x0014FEB8, 159 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_PointLight::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "Position") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &Rva0014D887This::rva0014D887)), parameter);
		else if (_strcmpi(t.m_name, "Color") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &Rva0014D7D4This::rva0014D7D4)), parameter);
		else if (_strcmpi(t.m_name, "Range") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_PointLight::rva0014D90E)), parameter);
	}
}

// Retail 0x0014D96A, 24 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow::rva0014D96A(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	effect->SetMatrixTranspose(parameter, &m_WorldToShadow);
}

// Retail 0x0014FF57, 159 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name != 0)
	{
		Rva001530E9Path t;
		Rva001530E9Parse(name, &t);
		if (_strcmpi(t.m_name, "WorldToShadow") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Shadow::rva0014D96A)), parameter);
		else if (_strcmpi(t.m_name, "ShadowMap") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &Rva0014D982This::rva0014D982)), parameter);
		else if (_strcmpi(t.m_name, "Zero_Zero_OneOverMapSize_OneOverMapSize") == 0)
			binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &Rva0014D9F3This::rva0014D9F3)), parameter);
	}
}

// Retail 0x00150E54 (197 bytes; the three light arrays' copies are folded
// there) and 0x00150FCC (218 bytes, shadows): "[*]" binds every element of
// the parameter array, "[n]" the one element; past the configured elements
// the default source answers. WorldBuilder's fxshaderparameterbinder.h
// asserts "Array shader parameter used without array notation" otherwise.
template <class T>
void FXShaderParameterSourceNamespace_Array<T>::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	Rva001530E9Path t;
	Rva001530E9Parse(name, &t);
	binder->PushDynamicSetStack(parameter);
	ID3DXEffect *effect = binder->PeekEffect();
	if (t.m_IsArray)
	{
		D3DXPARAMETER_DESC desc;
		effect->GetParameterDesc(parameter, &desc);
		for (unsigned int i = 0; i < desc.Elements; i++)
		{
			D3DXHANDLE element = effect->GetParameterElement(parameter, i);
			if (i < m_Elements.size())
				m_Elements[i].ResolveBindings(t.m_rest, element, binder);
			else
				m_Default.ResolveBindings(t.m_rest, element, binder);
		}
	}
	else if (t.m_IsArrayElement)
	{
		if (t.m_ArrayIndex >= 0 && t.m_ArrayIndex < m_Elements.size())
			m_Elements[t.m_ArrayIndex].ResolveBindings(t.m_rest, parameter, binder);
		else
			m_Default.ResolveBindings(t.m_rest, parameter, binder);
	}
	binder->PopDynamicSetStack();
}

template void FXShaderParameterSourceNamespace_Array<FXShaderParameterSourceNamespaceSAS::SourceNamespace_AmbientLight>::ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
template void FXShaderParameterSourceNamespace_Array<FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow>::ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);

// Retail 0x0014F40C, 44 bytes: the SAS ctor builds its +0xB8 member here.
FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::SourceNamespace_Skeleton()
	: m_SkinInfo(0), m_BoneMappingTable(0), m_NumJointsPerVertex(0), m_InstancingInfo(0)
{
}

// Retail 0x0014DF88, 93 bytes: the instancing transforms, else the skinned
// mesh's bone mapping, else one joint.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::rva0014DF88(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	if (m_InstancingInfo)
		effect->SetInt(parameter, m_InstancingInfo->size());
	else if (m_SkinInfo && m_BoneMappingTable)
		effect->SetInt(parameter, m_BoneMappingTable->size());
	else
		effect->SetInt(parameter, 1);
}

// Retail 0x0014DB2C, 20 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::rva0014DB2C(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	effect->SetInt(parameter, m_NumJointsPerVertex);
}

// Retail 0x0014FFF6, 468 bytes. WorldBuilder asserts the array checks; the
// release build returns there, and after a failed GetParameterDesc pops the
// set stack first.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, parameter, binder);
	if (name == 0)
		return;
	Rva001530E9Path t;
	Rva001530E9Parse(name, &t);
	if (_strcmpi(t.m_name, "NumJoints") == 0)
	{
		binder->PushDynamicSetStack((ScienceType)1);
		binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Skeleton::rva0014DF88)), parameter);
		binder->PopDynamicSetStack();
	}
	else if (_strcmpi(t.m_name, "NumJointsPerVertex") == 0)
	{
		binder->PushDynamicSetStack((ScienceType)1);
		binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Skeleton::rva0014DB2C)), parameter);
		binder->PopDynamicSetStack();
	}
	else if (_strcmpi(t.m_name, "MeshToJointToWorld") == 0)
	{
		if (!t.m_IsArray && !t.m_IsArrayElement || (t.m_IsArrayElement && t.m_ArrayIndex != 0))
			return;
		binder->PushDynamicSetStack((ScienceType)1);
		if (t.m_IsArray)
		{
			D3DXPARAMETER_DESC desc;
			if (binder->PeekEffect()->GetParameterDesc(parameter, &desc) < 0)
			{
				binder->PopDynamicSetStack();
				return;
			}
			if (desc.Class == 2 && desc.Type == 3 && desc.Rows == 4 && desc.Columns == 4 && desc.Elements > 0)
				binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_Matrix4x4)), parameter);
			else if (desc.Class == 5 && desc.Bytes == desc.Elements * 0x30)
				binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_Matrix3D)), parameter);
			else if (desc.Class == 5 && desc.Bytes == desc.Elements * 0x20)
				binder->AddBinding(TreeHintRef00217D4C(DelegateDesc(this, &SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_BoneTransform)), parameter);
		}
		else
			m_MeshToJointToWorld.ResolveBindings(t.m_rest, parameter, binder);
		binder->PopDynamicSetStack();
	}
	else if (_strcmpi(t.m_name, "MeshToJointToView") == 0)
	{
		if (!t.m_IsArrayElement || t.m_ArrayIndex != 0)
			return;
		binder->PushDynamicSetStack((ScienceType)1);
		m_MeshToJointToView.ResolveBindings(t.m_rest, parameter, binder);
		binder->PopDynamicSetStack();
	}
	else if (_strcmpi(t.m_name, "MeshToJointToProjection") == 0)
	{
		if (!t.m_IsArrayElement || t.m_ArrayIndex != 0)
			return;
		binder->PushDynamicSetStack((ScienceType)1);
		m_MeshToJointToProjection.ResolveBindings(t.m_rest, parameter, binder);
		binder->PopDynamicSetStack();
	}
}
