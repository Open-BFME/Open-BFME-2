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
	FX_SLOT(45) FX_SLOT(46) FX_SLOT(47)
	FX_SLOT(48) FX_SLOT(49) FX_SLOT(50) FX_SLOT(51) FX_SLOT(52) FX_SLOT(53) FX_SLOT(54) FX_SLOT(55)
	FX_SLOT(56) FX_SLOT(57) FX_SLOT(58) FX_SLOT(59) FX_SLOT(60) FX_SLOT(61) FX_SLOT(62) FX_SLOT(63)
	FX_SLOT(64) FX_SLOT(65) FX_SLOT(66) FX_SLOT(67) FX_SLOT(68) FX_SLOT(69) FX_SLOT(70) FX_SLOT(71)
	FX_SLOT(72) FX_SLOT(73) FX_SLOT(74) FX_SLOT(75) FX_SLOT(76) FX_SLOT(77)
	virtual HRESULT __stdcall SetRawValue(D3DXHANDLE parameter, const void *data, unsigned int byteOffset, unsigned int bytes);	// +0x138
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

// The rowed registry of named sources (WorldBuilder 0x009E9C10).
void __cdecl Rva00153565Register(const char *name, void *source);

// WWMath's Vector4 and Matrix4 (Vector4 Row[4]), only as far as the camera
// and skeleton matrix sources inline them.
class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix4
{
public:
	__forceinline Matrix4() {}
	__forceinline Matrix4(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}
	__forceinline explicit Matrix4(bool identity)
	{
		if (identity)
			Make_Identity();
	}
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Init(r0, r1, r2, r3);
	}
	__forceinline void Init(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4 Transpose() const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this;
	}
	static void Multiply(const Matrix4 &a, const Matrix4 &b, Matrix4 *res);

protected:
	Vector4 Row[4];
};

// The 0x40-byte matrix the setters build (rowed ctor 0x0007671F).
class Rva0007671F : public Matrix4
{
public:
	Rva0007671F();
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

enum D3DTRANSFORMSTATETYPE
{
	D3DTS_VIEW = 2,
	D3DTS_PROJECTION = 3,
	D3DTS_WORLD = 256
};

// DX8Wrapper's render state (render_state at 0x009EE5D8): the world and view
// transforms it keeps transposed at +0x1EC and +0x22C.
struct RenderStateStruct
{
	char m_unknown[0x1EC];
	Matrix4 world;
	Matrix4 view;
};

class DX8Wrapper
{
	enum ChangedStates
	{
		WORLD_IDENTITY = 1 << 18,
		VIEW_IDENTITY = 1 << 19
	};
public:
	static LightEnvironmentClass *Get_Light_Environment() { return Light_Environment; }
	static __forceinline void Get_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4 &m)
	{
		switch ((int)transform)
		{
		case D3DTS_WORLD:
			if (render_state_changed & WORLD_IDENTITY) m.Make_Identity();
			else m = render_state.world.Transpose();
			break;
		case D3DTS_VIEW:
			if (render_state_changed & VIEW_IDENTITY) m.Make_Identity();
			else m = render_state.view.Transpose();
			break;
		case D3DTS_PROJECTION:
			m = DeviceProjectionMatrix.Transpose();
			break;
		default:
			m.Make_Identity();
			break;
		}
	}
protected:
	static LightEnvironmentClass *Light_Environment;
	static RenderStateStruct render_state;
	static unsigned render_state_changed;
	static Matrix4 DeviceProjectionMatrix;
};

class FXShaderParameterBinder;

// The texture handle (texture.cpp): a 16-bit reference count at +4 that the
// rowed TextureBaseClass::Release_Ref (0x0061ED10) drops; RefCountPtr's
// assignment is rowed at 0x000424D0 and its copy constructor pinned at
// 0x000424BB.
class TextureBaseClass
{
public:
	__forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

class TextureClass : public TextureBaseClass
{
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : ptr(0) {}
	RefCountPtr(const RefCountPtr &that) : ptr(that.ptr)
	{
		if (ptr)
			ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
	const RefCountPtr &operator=(const RefCountPtr &that);

	T *ptr;
};

// The rowed second PushDynamicSetStack 0x0015354E takes its argument under
// this placeholder enum; the skeleton source passes 1.
enum ScienceType
{
	SCIENCE_INVALID = 0
};

// The 0x30-byte transform the skeleton's instancing vector holds.
class Vector3
{
public:
	__forceinline Vector3() {}
	__forceinline Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }

	float X;
	float Y;
	float Z;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline void Get_Translation(Vector3 *set) const
	{
		set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3];
	}
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2];
		return *this;
	}

	Vector4 Row[3];
};

class Quaternion
{
public:
	__forceinline Quaternion() {}
	__forceinline Quaternion &operator=(const Quaternion &q) { X = q.X; Y = q.Y; Z = q.Z; W = q.W; return *this; }

	float X;
	float Y;
	float Z;
	float W;
};

Quaternion Build_Quaternion(const Matrix3D &m);

// The bone palette the SetArray_MeshToJointToWorld_* setters upload
// (WorldBuilder's asserts name the bound; retail compares against 100).
#define MAX_SUPPORTED_BONE_MATRICES 100

// An HTree pivot's current transform (+0x30 of the 0x58-byte pivot): a
// rotation quaternion and a translation, expanded into a Matrix3D the way
// WorldBuilder's out-of-line copy (0x009FAF30) does.
struct HTreePivotTransform
{
	__forceinline void Get_Matrix3D(Matrix3D &m) const
	{
		float xx = Rotation.X * Rotation.X * 2.0f;
		float xy = Rotation.X * Rotation.Y * 2.0f;
		float xz = Rotation.X * Rotation.Z * 2.0f;
		float xw = Rotation.X * Rotation.W * 2.0f;
		float yy = Rotation.Y * Rotation.Y * 2.0f;
		float yz = Rotation.Y * Rotation.Z * 2.0f;
		float yw = Rotation.Y * Rotation.W * 2.0f;
		float zz = Rotation.Z * Rotation.Z * 2.0f;
		float zw = Rotation.Z * Rotation.W * 2.0f;
		m[0][0] = 1.0f - yy - zz;
		m[0][1] = xy - zw;
		m[0][2] = xz + yw;
		m[1][0] = xy + zw;
		m[1][1] = 1.0f - zz - xx;
		m[1][2] = yz - xw;
		m[2][0] = xz - yw;
		m[2][1] = yz + xw;
		m[2][2] = 1.0f - yy - xx;
		m[0][3] = Translation.X;
		m[1][3] = Translation.Y;
		m[2][3] = Translation.Z;
	}

	Quaternion Rotation;
	Vector3 Translation;
};

// The 0x20-byte palette entry SetArray_MeshToJointToWorld_BoneTransform
// uploads: a pivot transform and a zeroed last float.
struct BoneTransform : public HTreePivotTransform
{
	__forceinline BoneTransform() : m_unused(0.0f) {}
	__forceinline void Set(const Matrix3D &m)
	{
		Rotation = Build_Quaternion(m);
		m.Get_Translation(&Translation);
	}

	float m_unused;
};

struct HTreePivot
{
	char m_unknown00[0x30];
	HTreePivotTransform Transform;
	char m_unknown4C[0x58 - 0x4C];
};

// HTreeClass (Name[16], NumPivots, Pivot): the skinned mesh's hierarchy.
class HTreeClass
{
public:
	int Num_Pivots() const { return NumPivots; }
	const HTreePivotTransform &Get_Transform(int pivot) const { return Pivot[pivot].Transform; }
private:
	char Name[16];
	int NumPivots;
	HTreePivot *Pivot;
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
	FXShaderParameterSourceNamespace_Array(int numElements);
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

	int GetSize() const { return m_Elements.size(); }
	T &rva0014F454(int index);
	void GrowArray(int totalNumElements);

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
		SourceNamespace_Matrix() {}
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
			Matrix_WorldToView() {}
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_Projection : public SourceNamespace_Matrix
		{
			Matrix_Projection() {}
			virtual void slot02(Rva0007671F &matrix);
		};

		SourceNamespace_Camera() {}
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

		Matrix_WorldToView m_WorldToView;	// +0x04
		Matrix_Projection m_Projection;		// +0x08
	};

	// vtable 0x00BD3834, dispatcher 0x0014FD69.
	struct SourceNamespace_Time : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_Time() {}
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
	};

	// Array elements: vtables 0x00BD3854/5C/64 (dispatchers 0x0014FDCA,
	// 0x0014FE33, 0x0014FEB8), each carrying its light index.
	struct SourceNamespace_AmbientLight : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_AmbientLight() {}
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D5B0(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetIndex(int index) { m_index = index; }
		int m_index;
	};
	struct SourceNamespace_DirectionalLight : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_DirectionalLight() {}
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D66F(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetIndex(int index) { m_index = index; }
		int m_index;
	};
	struct SourceNamespace_PointLight : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_PointLight() {}
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D90E(ID3DXEffect *effect, D3DXHANDLE parameter);
		void SetIndex(int index) { m_index = index; }
		int m_index;
	};

	// vtable 0x00BD386C, dispatcher 0x0014FF57; WorldBuilder tests the handle
	// at +0x48 through an inline accessor (name not in either binary).
	struct SourceNamespace_Shadow : public FXShaderParameterSourceNamespace_Struct
	{
		SourceNamespace_Shadow();
		virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);
		void rva0014D96A(ID3DXEffect *effect, D3DXHANDLE parameter);
		void rva0014DA92(const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap);
		bool hasShadowMap() const { return m_shadowMap.ptr != 0; }
		void SetIndex(int index) { m_index = index; }
		int m_index;
		Matrix4 m_WorldToShadow;		// +0x08
		RefCountPtr<TextureClass> m_shadowMap;	// +0x48
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
			Matrix_MeshToJointToWorld() {}
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_MeshToJointToView : public SourceNamespace_Matrix
		{
			Matrix_MeshToJointToView() {}
			virtual void slot02(Rva0007671F &matrix);
		};
		struct Matrix_MeshToJointToProjection : public SourceNamespace_Matrix
		{
			Matrix_MeshToJointToProjection() {}
			virtual void slot02(Rva0007671F &matrix);
		};

		Matrix_MeshToJointToWorld m_MeshToJointToWorld;			// +0x04
		Matrix_MeshToJointToView m_MeshToJointToView;			// +0x08
		Matrix_MeshToJointToProjection m_MeshToJointToProjection;	// +0x0C
		const HTreeClass *m_SkinInfo;					// +0x10
		const std::vector<short> *m_BoneMappingTable;			// +0x14
		int m_NumJointsPerVertex;					// +0x18
		const std::vector<Matrix3D> *m_InstancingInfo;			// +0x1C
	};

	FXShaderParameterSourceNamespaceSAS();
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder);

	void NumShadows(ID3DXEffect *effect, D3DXHANDLE parameter);
	void SetShadowMapInfo(int shadowMapIndex, const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap);
	void rva0014F7F2(int shadowMapIndex);

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
// Retail 0x001510C2, 154 bytes (WorldBuilder 0x009F7D20): one ambient
// light, four directional and four point lights and one shadow, registered
// as "Sas".
FXShaderParameterSourceNamespaceSAS::FXShaderParameterSourceNamespaceSAS()
	: m_SourceNamespace_AmbientLight(1),
	  m_SourceNamespace_DirectionalLight(4),
	  m_SourceNamespace_PointLight(4),
	  m_SourceNamespace_Shadow(1)
{
	Rva00153565Register("Sas", this);
}

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

// Retail 0x0014F778, 122 bytes (WorldBuilder 0x009F87C0, which asserts the
// index is in range).
void FXShaderParameterSourceNamespaceSAS::SetShadowMapInfo(int shadowMapIndex, const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap)
{
	if (shadowMapIndex < 0 || shadowMapIndex >= m_SourceNamespace_Shadow.GetSize())
		return;
	m_SourceNamespace_Shadow.rva0014F454(shadowMapIndex).rva0014DA92(worldToShadow, shadowMap);
}

// Retail 0x0014F7F2, 122 bytes (WorldBuilder 0x009F8870): an identity
// transform and no map.
void FXShaderParameterSourceNamespaceSAS::rva0014F7F2(int shadowMapIndex)
{
	SetShadowMapInfo(shadowMapIndex, Matrix4(true), RefCountPtr<TextureClass>());
}

// Retail 0x00150D8A, 0x00150DFD, 0x00150F19 (87 bytes each) and 0x00150F70
// (92 bytes, shadows): the default element answers for index -1.
template <class T>
FXShaderParameterSourceNamespace_Array<T>::FXShaderParameterSourceNamespace_Array(int numElements)
{
	m_Default.SetIndex(-1);
	if (numElements > 0)
		GrowArray(numElements);
}

// Retail 0x00150C97, 0x00150CD0, 0x00150D09 (57 bytes each) and 0x00150D42
// (72 bytes, shadows); WorldBuilder asserts
// "!(totalNumElements < m_Elements.size())".
template <class T>
void FXShaderParameterSourceNamespace_Array<T>::GrowArray(int totalNumElements)
{
	if (totalNumElements < m_Elements.size())
		return;
	int i = m_Elements.size();
	m_Elements.resize(totalNumElements);
	for (; i < totalNumElements; i++)
		m_Elements[i].SetIndex(i);
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

// Retail 0x0014DCC8, 404 bytes (vtable 0x00BD383C slot 2).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Camera::Matrix_WorldToView::slot02(Rva0007671F &matrix)
{
	DX8Wrapper::Get_Transform(D3DTS_VIEW, matrix);
}

// Retail 0x0014DE5C, 300 bytes (vtable 0x00BD3848 slot 2).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Camera::Matrix_Projection::slot02(Rva0007671F &matrix)
{
	DX8Wrapper::Get_Transform(D3DTS_PROJECTION, matrix);
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

// Retail 0x0014DA92, 154 bytes (WorldBuilder 0x009F9EB0).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow::rva0014DA92(const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap)
{
	m_WorldToShadow = worldToShadow;
	RefCountPtr<TextureClass> &map = m_shadowMap;
	map = shadowMap;
}

// Retail 0x0014DB9F, 160 bytes.
FXShaderParameterSourceNamespaceSAS::SourceNamespace_Shadow::SourceNamespace_Shadow()
	: m_index(-1), m_WorldToShadow(true)
{
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

// Retail 0x0014DFE5, 828 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_BoneTransform(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	D3DXPARAMETER_DESC desc;
	if (effect->GetParameterDesc(parameter, &desc) < 0)
		return;
	if (desc.Elements <= 0)
		return;

	static BoneTransform bones[MAX_SUPPORTED_BONE_MATRICES];

	if (m_InstancingInfo)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_InstancingInfo->size() > desc.Elements)
			return;
		int i = 0;
		for (std::vector<Matrix3D>::const_iterator it = m_InstancingInfo->begin(); it != m_InstancingInfo->end(); ++it, ++i)
			bones[i].Set(*it);
		effect->SetRawValue(parameter, bones, 0, m_InstancingInfo->size() * sizeof(BoneTransform));
	}
	else if (m_SkinInfo && m_BoneMappingTable)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_BoneMappingTable->size() > desc.Elements || m_BoneMappingTable->back() >= m_SkinInfo->Num_Pivots())
			return;
		int i = 0;
		for (std::vector<short>::const_iterator it = m_BoneMappingTable->begin(); it != m_BoneMappingTable->end(); ++it, ++i)
			(HTreePivotTransform &)bones[i] = m_SkinInfo->Get_Transform(*it);
		effect->SetRawValue(parameter, bones, 0, m_BoneMappingTable->size() * sizeof(BoneTransform));
	}
	else
	{
		Rva0007671F world;
		DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
		BoneTransform bone;
		bone.Set((const Matrix3D &)world);
		effect->SetRawValue(parameter, &bone, 0, sizeof(BoneTransform));
	}
}

// Retail 0x0014E321, 1000 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_Matrix3D(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	D3DXPARAMETER_DESC desc;
	if (effect->GetParameterDesc(parameter, &desc) < 0)
		return;
	if (desc.Elements <= 0)
		return;

	static Matrix3D bones[MAX_SUPPORTED_BONE_MATRICES];

	if (m_InstancingInfo)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_InstancingInfo->size() > desc.Elements)
			return;
		effect->SetRawValue(parameter, &(*m_InstancingInfo)[0], 0, m_InstancingInfo->size() * sizeof(Matrix3D));
	}
	else if (m_SkinInfo && m_BoneMappingTable)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_BoneMappingTable->size() > desc.Elements || m_BoneMappingTable->back() >= m_SkinInfo->Num_Pivots())
			return;
		int i = 0;
		for (std::vector<short>::const_iterator it = m_BoneMappingTable->begin(); it != m_BoneMappingTable->end(); ++it, ++i)
			m_SkinInfo->Get_Transform(*it).Get_Matrix3D(bones[i]);
		effect->SetRawValue(parameter, bones, 0, m_BoneMappingTable->size() * sizeof(Matrix3D));
	}
	else
	{
		Rva0007671F world;
		DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
		effect->SetRawValue(parameter, &world, 0, sizeof(Matrix3D));
	}
}

// Retail 0x0014E709, 1227 bytes.
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::SetArray_MeshToJointToWorld_Matrix4x4(ID3DXEffect *effect, D3DXHANDLE parameter)
{
	D3DXPARAMETER_DESC desc;
	if (effect->GetParameterDesc(parameter, &desc) < 0)
		return;
	if (desc.Elements <= 0)
		return;

	static Rva0007671F bones[MAX_SUPPORTED_BONE_MATRICES];
	static bool first = true;
	if (first)
	{
		for (int i = 0; i < MAX_SUPPORTED_BONE_MATRICES; i++)
			bones[i].Make_Identity();
		first = false;
	}

	if (m_InstancingInfo)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_InstancingInfo->size() > desc.Elements)
			return;
		int i = 0;
		for (std::vector<Matrix3D>::const_iterator it = m_InstancingInfo->begin(); it != m_InstancingInfo->end(); ++it, ++i)
			(Matrix3D &)bones[i] = *it;
		effect->SetRawValue(parameter, bones, 0, m_InstancingInfo->size() * sizeof(Matrix4));
	}
	else if (m_SkinInfo && m_BoneMappingTable)
	{
		if (desc.Elements > MAX_SUPPORTED_BONE_MATRICES || m_BoneMappingTable->size() > desc.Elements || m_BoneMappingTable->back() >= m_SkinInfo->Num_Pivots())
			return;
		int i = 0;
		for (std::vector<short>::const_iterator it = m_BoneMappingTable->begin(); it != m_BoneMappingTable->end(); ++it, ++i)
			m_SkinInfo->Get_Transform(*it).Get_Matrix3D((Matrix3D &)bones[i]);
		effect->SetRawValue(parameter, bones, 0, m_BoneMappingTable->size() * sizeof(Matrix4));
	}
	else
	{
		Rva0007671F world;
		DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
		effect->SetRawValue(parameter, &world, 0, sizeof(Matrix4));
	}
}

// Retail 0x0014EBD4, 404 bytes (vtable 0x00BD3874 slot 2).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::Matrix_MeshToJointToWorld::slot02(Rva0007671F &matrix)
{
	DX8Wrapper::Get_Transform(D3DTS_WORLD, matrix);
}

// Retail 0x0014ED68, 674 bytes (vtable 0x00BD3880 slot 2).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::Matrix_MeshToJointToView::slot02(Rva0007671F &matrix)
{
	Rva0007671F world;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	Rva0007671F view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Matrix4::Multiply(view, world, &matrix);
}

// Retail 0x0014F00A, 929 bytes (vtable 0x00BD388C slot 2).
void FXShaderParameterSourceNamespaceSAS::SourceNamespace_Skeleton::Matrix_MeshToJointToProjection::slot02(Rva0007671F &matrix)
{
	Rva0007671F world;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	Rva0007671F view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Rva0007671F projection;
	DX8Wrapper::Get_Transform(D3DTS_PROJECTION, projection);
	Rva0007671F worldToView;
	Matrix4::Multiply(view, world, &worldToView);
	Matrix4::Multiply(projection, worldToView, &matrix);
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
