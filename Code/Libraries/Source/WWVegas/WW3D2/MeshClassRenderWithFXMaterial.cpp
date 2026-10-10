// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// MeshClass FX-material render. Retail 14A880/2482; RET8.
// WorldBuilder 9CAB00 mesh.cpp:899 and FXShaderRenderer caller A21E40
// establish purpose; target callers17454D/174612 establish owning-pointer/count ABI.
// Primary guide: BFME1 575ba2b04 matrix headers and the existing 14C000
// Render_Material_Pass transfer; ZH mesh.cpp has no FX-material implementation.
// Target access proves mesh Model C4 / BaseVertexOffset300 / Anchor310,
// model flags18 / counts24,28 / material94 / geometryBC, and transform18.
// Rva00087A93 is the existing four-byte owning-pointer owner (7B724 dtor),
// not a claim that the donor RefCountPtr template spelling is retail's type.
// The combined decrement/zero test emits native early-inline/late-outline cleanup.
// Native Matrix4 construction uses count4/stride16 and folded callback47A6A9.
// Reuse its existing neutral Row16 provider, adapting the reference vector math
// spelling locally. The callback bytes do not establish an original row type.
#define Vector4 Rva0047A6A9Row16
#include "matrix3d.h"
#undef Vector4
typedef Rva0047A6A9Row16 Vector4;

class Matrix4
{
public:
	Matrix4(void) {};
	Matrix4(const Matrix4 &m);
	__forceinline explicit Matrix4(const Matrix3D &m);
	__forceinline explicit Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3);
	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0, 0.0, 0.0, 0.0);
		Row[1].Set(0.0, 1.0, 0.0, 0.0);
		Row[2].Set(0.0, 0.0, 1.0, 0.0);
		Row[3].Set(0.0, 0.0, 0.0, 1.0);
	}
	__forceinline void Init(const Matrix3D &m) { Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0, 0.0, 0.0, 1.0); }
	__forceinline void Init(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3) { Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3; }
	__forceinline Vector4 &operator[](int i) { return Row[i]; }
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	__forceinline Matrix4 Transpose(void) const
	{
		return Matrix4(
			Vector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			Vector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			Vector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			Vector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3]; return *this; }
	void Get_Inverse(Matrix4 &set_inverse) const;
protected:
	Vector4 Row[4];
};

__forceinline Matrix4::Matrix4(const Matrix4 &m)
{
	Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
}

__forceinline Matrix4::Matrix4(const Matrix3D &m)
{
	Init(m);
}

__forceinline Matrix4::Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
{
	Init(r0, r1, r2, r3);
}

enum D3DTRANSFORMSTATETYPE
{
	D3DTS_VIEW = 2,
	D3DTS_PROJECTION = 3,
	D3DTS_WORLD = 256,
	D3DTS_FORCE_DWORD = 0x7fffffff
};

struct D3DMATRIX
{
	float m[4][4];
};

struct IDirect3DDevice8
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual long __stdcall SetTransform(D3DTRANSFORMSTATETYPE state, const D3DMATRIX *matrix);
	virtual long __stdcall GetTransform(D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix);
};

extern Matrix4 BFME2World;
extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	enum ChangedStates
	{
		WORLD_CHANGED = 1 << 0,
		VIEW_CHANGED = 1 << 1,
		WORLD_IDENTITY = 1 << 18,
		VIEW_IDENTITY = 1 << 19
	};

	static __forceinline void Set_MeshFX_Transform(D3DTRANSFORMSTATETYPE transform, const Matrix3D &m)
	{
		Matrix4 m2(m);
		switch ((int)transform) {
		case D3DTS_WORLD:
			BFME2World = m2.Transpose();
			render_state_changed |= (unsigned)WORLD_CHANGED;
			render_state_changed &= ~(unsigned)WORLD_IDENTITY;
			break;
		case D3DTS_VIEW:
			(&BFME2World)[1] = m2.Transpose();
			render_state_changed |= (unsigned)VIEW_CHANGED;
			render_state_changed &= ~(unsigned)VIEW_IDENTITY;
			break;
		default:
			matrix_changes++;
			m2 = m2.Transpose();
			_Get_D3D_Device8()->SetTransform(transform, (D3DMATRIX *)&m2);
			number_of_DX8_calls++;
			break;
		}
	}

	static __forceinline void Get_MeshFX_Transform(D3DTRANSFORMSTATETYPE transform, Matrix4 &m)
	{
		D3DMATRIX mat;
		switch ((int)transform) {
		case D3DTS_WORLD:
			if (render_state_changed & WORLD_IDENTITY) m.Make_Identity();
			else m = BFME2World.Transpose();
			break;
		case D3DTS_VIEW:
			if (render_state_changed & VIEW_IDENTITY) m.Make_Identity();
			else m = (&BFME2World)[1].Transpose();
			break;
		default:
			_Get_D3D_Device8()->GetTransform(transform, &mat);
			number_of_DX8_calls++;
			m = *(Matrix4 *)&mat;
			m = m.Transpose();
			break;
		}
	}

	static __forceinline void Set_MeshFX_World_Identity(void)
	{
		if (render_state_changed & (unsigned)WORLD_IDENTITY) return;
		BFME2World.Make_Identity();
		render_state_changed |= (unsigned)WORLD_CHANGED | (unsigned)WORLD_IDENTITY;
	}

	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static void Draw_Triangles(unsigned int start_index, unsigned int polygon_count, unsigned int min_vertex_index, unsigned int vertex_count);

protected:
	static unsigned matrix_changes;
	static unsigned render_state_changed;
	static IDirect3DDevice8 *D3DDevice;
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); } int Dec_Ref(void) { return --NumRefs; }

protected:
	int NumRefs;
};

namespace FXShader { class RenderingMethod; }
class Rva00087A93
{
public:
	Rva00087A93(RefCountClass *p) : Referent(p) {}
	Rva00087A93(const Rva00087A93 &p) : Referent(p.Referent) { if (Referent) Referent->Add_Ref(); }
	~Rva00087A93(void)
	{
		if (Referent && Referent->Dec_Ref()==0) Referent->Delete_This();
	}
	bool IsBound(void) const { return Referent != 0; }
	FXShader::RenderingMethod *operator->(void) const { return reinterpret_cast<FXShader::RenderingMethod*>(Referent); }

private:
	RefCountClass *Referent;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
public:
	virtual void slot1();
	virtual bool Begin(int *passCount, int flags);	// slot 2
	virtual void Begin_Pass(int pass);	// slot 3
	virtual void slot4(int mode);	// slot 4
	virtual void End_Pass(void);	// slot 5
	virtual void End(void);	// slot 6
};
}

// The shared empty member body 0x000B3FD0 (FXShaderGeometry's end-of-draw hook).
class PathfindLayer
{
public:
	void rva000B3FD0();
};

class FXShaderGeometry
{
public:
	void Begin_Rendering(unsigned short idx);
	void End_Rendering(void) { ((PathfindLayer *)this)->rva000B3FD0(); }
	bool Get_Flag0(void) const { return m_flag0; }
	int *Get_Bone_Data(void) { return m_bones; }
	int Get_Bone_Count(void) const { return m_boneCount; }

private:
	bool m_flag0;	// +0x00
	char m_pad01[0x13];
	int m_bones[3];	// +0x14
	int m_boneCount;	// +0x20
};

class MeshMatDescClass
{
public:
	bool Has_FX_Shader(int pass) const { return FXShader[pass] != 0 || FXShaderArray[pass] != 0; }

private:
	char _bfme_unk_00[0xB8];
	void *FXShader[4];	// +0xB8
	char _bfme_unk_c8[0x108 - 0xC8];
	void *FXShaderArray[4];	// +0x108
};

class MeshModelClass
{
public:
	enum FlagsType {
		ALIGNED = 0x00000200,
		SKIN = 0x00000400,
		ORIENTED = 0x00000800
	};

	int Get_Flag(FlagsType flag) { return Flags & flag; }
	int Get_Polygon_Count(void) const { return PolyCount; }
	int Get_Vertex_Count(void) const { return VertexCount; }
	bool Is_FX_Shader_Material(void) const { return CurMatDesc->Has_FX_Shader(0); }

	char _bfme_unk_00[0x18];
	int Flags;	// +0x18
	char _bfme_unk_1c[0x24 - 0x1C];
	int PolyCount;	// +0x24
	int VertexCount;	// +0x28
	char _bfme_unk_2c[0x94 - 0x2C];
	MeshMatDescClass *CurMatDesc;	// +0x94
	char _bfme_unk_98[0xBC - 0x98];
	FXShaderGeometry *FXShaderGeometryData;	// +0xBC
};

class HTreeClass;

class Rva0014D3E7
{
public:
	void rva0014D3E7(int a, int b, int c);
};

class Rva0014D405
{
public:
	void rva0014D405();
};

class FXShaderParameterSourceNamespaceSAS;
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;

#define VSLOTS_10(p) \
	virtual void _bfme_slot_##p##0(void); virtual void _bfme_slot_##p##1(void); \
	virtual void _bfme_slot_##p##2(void); virtual void _bfme_slot_##p##3(void); \
	virtual void _bfme_slot_##p##4(void); virtual void _bfme_slot_##p##5(void); \
	virtual void _bfme_slot_##p##6(void); virtual void _bfme_slot_##p##7(void); \
	virtual void _bfme_slot_##p##8(void); virtual void _bfme_slot_##p##9(void);

class RenderObjClass : public RefCountClass
{
public:
	virtual void _bfme_slot_01(void); virtual void _bfme_slot_02(void);
	virtual void _bfme_slot_03(void); virtual void _bfme_slot_04(void);
	virtual void _bfme_slot_05(void); virtual void _bfme_slot_06(void);
	virtual void _bfme_slot_07(void); virtual void _bfme_slot_08(void);
	virtual void _bfme_slot_09(void);
	VSLOTS_10(1)
	virtual void Validate_Transform(void) const;	// 20
	virtual void _bfme_slot_21(void); virtual void _bfme_slot_22(void);
	virtual void _bfme_slot_23(void); virtual void _bfme_slot_24(void);
	virtual void _bfme_slot_25(void); virtual void _bfme_slot_26(void);
	virtual void _bfme_slot_27(void); virtual void _bfme_slot_28(void);
	virtual void _bfme_slot_29(void);
	VSLOTS_10(3) VSLOTS_10(4)
	virtual void _bfme_slot_50(void); virtual void _bfme_slot_51(void);
	virtual void _bfme_slot_52(void); virtual void _bfme_slot_53(void);
	virtual void _bfme_slot_54(void); virtual void _bfme_slot_55(void);
	virtual void _bfme_slot_56(void); virtual void _bfme_slot_57(void);
	virtual HTreeClass *Get_HTree(void) const;	// 58

	const Matrix3D &Get_MeshFX_Transform(void) const { Validate_Transform(); return Transform; }
	RenderObjClass *Get_Container(void) const { return Container; }

protected:
	char _bfme_unk_08[0x18 - 0x08];
	Matrix3D Transform;	// +0x18
	char _bfme_unk_48[0x7C - 0x48];
	RenderObjClass *Container;	// +0x7C
	char _bfme_unk_80[0xC4 - 0x80];
};

class MeshClass : public RenderObjClass
{
public:
	void Render_With_FX_Material(Rva00087A93 method, int count);
	MeshClass **Get_Anchor(void) { return Anchor; }
	MeshModelClass *Peek_Model(void) { return Model; }
	int Get_Base_Vertex_Offset(void) const { return BaseVertexOffset; }

private:
	MeshModelClass *Model;	// +0xC4
	char _bfme_unk_c8[0x300 - 0xC8];
	int BaseVertexOffset;	// +0x300
	char _bfme_unk_304[0x310 - 0x304];
	MeshClass **Anchor;	// +0x310
};

void MeshClass::Render_With_FX_Material(Rva00087A93 method, int count)
{
	if (!Model || !Model->Is_FX_Shader_Material() || !Model->FXShaderGeometryData || !method.IsBound()) {
		return;
	}

	if (Model->Get_Flag(MeshModelClass::SKIN)) {
		if (Get_Anchor() && *Get_Anchor() && *Get_Anchor() != this) {
			Matrix3D inv;
			Matrix3D result;
			(*Get_Anchor())->Get_MeshFX_Transform().Get_Inverse(inv);
			Matrix3D::Multiply(Get_MeshFX_Transform(), inv, &result);
			DX8Wrapper::Set_MeshFX_Transform(D3DTS_WORLD, result);
		} else {
			DX8Wrapper::Set_MeshFX_World_Identity();
		}
		if (!Model->FXShaderGeometryData->Get_Flag0() && Container && Container->Get_HTree()) {
			reinterpret_cast<Rva0014D3E7 *>(g_00DF36B4)->rva0014D3E7(
				(int)Container->Get_HTree(),
				(int)Model->FXShaderGeometryData->Get_Bone_Data(),
				Model->FXShaderGeometryData->Get_Bone_Count());
		}
	} else if (count <= 1) {
		if (Peek_Model()->Get_Flag(MeshModelClass::ALIGNED) || Peek_Model()->Get_Flag(MeshModelClass::ORIENTED)) {
			Matrix4 view;
			DX8Wrapper::Get_MeshFX_Transform(D3DTS_VIEW, view);
			Matrix4 inv;
			view.Get_Inverse(inv);
			Vector3 mesh_position;
			Transform.Get_Translation(&mesh_position);
			Vector3 target;
			if (Peek_Model()->Get_Flag(MeshModelClass::ALIGNED)) {
				target = mesh_position + Vector3(inv[0][2], inv[1][2], inv[2][2]);
			} else {
				target.Set(inv[0][3], inv[1][3], inv[2][3]);
			}
			Matrix3D tm;
			tm.Obj_Look_At(mesh_position, target, 0.0f);
			DX8Wrapper::Set_MeshFX_Transform(D3DTS_WORLD, tm);
		} else {
			DX8Wrapper::Set_MeshFX_Transform(D3DTS_WORLD, Transform);
		}
	}

	method->slot4(1);
	Model->FXShaderGeometryData->Begin_Rendering(Get_Base_Vertex_Offset());
	DX8Wrapper::Draw_Triangles(0, Model->Get_Polygon_Count() * count, 0, Model->Get_Vertex_Count() * count);
	Model->FXShaderGeometryData->End_Rendering();
	if (Model->Get_Flag(MeshModelClass::SKIN) && !Model->FXShaderGeometryData->Get_Flag0()) {
		reinterpret_cast<Rva0014D405 *>(g_00DF36B4)->rva0014D405();
	}
}
