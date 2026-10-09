// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
//
// ?doParticles@GpuDrawModule@FXParticleSystem@@UAEHAAVRenderInfoClass@@PAXPAH@Z
// retail 0x005639A4..0x00563CAF (779 bytes EH RET 0xC).
// WorldBuilder twin 0x0142B2A0 FXParticleSystem::GpuDrawModule::doParticles
// (fxpsgpudrawmodule.cpp assert line 142) with its debug matrix setup and
// D3D validation stripped. The body is shared by three module vtables
// (0x0081C4D8 0x0081CDA0 0x0081D598 hold it). Target evidence:
//  - nothing (returns 0) while WW3D::IsCurrentlyRenderingShadowMap or when
//    TheWritableGlobalData +0xC60 is not -1;
//  - the +0x04 particle system (or the rowed null system Make001FCBD7)
//    gives its +0xA4 storage whose slots 11..15 return the vertex
//    declaration the vertex buffer the vertex count the index buffer and
//    the shader (by value); all four must be present;
//  - the world transform becomes the identity (BFME2World with the world
//    changed bit set and the identity bit cleared) the buffers are bound
//    (rowed Set_Vertex_Buffer / Set_Index_Buffer) the declaration set
//    (D3D slot 87) and the rowed Apply_Render_State_Changes runs;
//  - the shader is pushed (rowed Push_Rendering_Method) the stack goes to
//    the pinned 0x001688FF and its first method draws count/2 triangles per
//    pass (rowed Draw_Triangles) when Begin succeeds; then the pinned
//    0x00168952 Pop_Rendering_Method and both shaders cleared;
//  - the third argument is advanced by the storage slot 7 count.
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

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
	bool IsBound(void) const { return Referent != 0; }

private:
	T *Referent;
};

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

class RenderInfoClass
{
public:
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);
	const RenderingMethodStackType &Get_Rendering_Method_Stack(void) const;
};

void Rva001688FF(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);
void Rva00168952(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);

#define PAD_STDCALL10(p) \
	virtual void __stdcall p##0() = 0; virtual void __stdcall p##1() = 0; virtual void __stdcall p##2() = 0; \
	virtual void __stdcall p##3() = 0; virtual void __stdcall p##4() = 0; virtual void __stdcall p##5() = 0; \
	virtual void __stdcall p##6() = 0; virtual void __stdcall p##7() = 0; virtual void __stdcall p##8() = 0; \
	virtual void __stdcall p##9() = 0;

struct IDirect3DVertexDeclaration9;

struct IDirect3DDevice8
{
	PAD_STDCALL10(d0) PAD_STDCALL10(d1) PAD_STDCALL10(d2) PAD_STDCALL10(d3) PAD_STDCALL10(d4)
	PAD_STDCALL10(d5) PAD_STDCALL10(d6) PAD_STDCALL10(d7)
	virtual void __stdcall d80() = 0; virtual void __stdcall d81() = 0; virtual void __stdcall d82() = 0;
	virtual void __stdcall d83() = 0; virtual void __stdcall d84() = 0; virtual void __stdcall d85() = 0;
	virtual void __stdcall d86() = 0;
	virtual long __stdcall SetVertexDeclaration(IDirect3DVertexDeclaration9 *decl) = 0;	// slot 87
	virtual void __stdcall d88() = 0; virtual void __stdcall d89() = 0;
	virtual void __stdcall d90() = 0; virtual void __stdcall d91() = 0;
	virtual long __stdcall SetVertexShader(void *shader) = 0;	// slot 92
	PAD_STDCALL10(e0)
	virtual void __stdcall f103() = 0; virtual void __stdcall f104() = 0;
	virtual void __stdcall f105() = 0; virtual void __stdcall f106() = 0;
	virtual long __stdcall SetPixelShader(void *shader) = 0;	// slot 107
};

extern unsigned number_of_DX8_calls;

class IndexBufferClass;
class VertexBufferClass;

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline Vector4(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Vector4 &operator=(const Vector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline void Set(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
	Real X, Y, Z, W;
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D(bool identity)
	{
		if (identity)
		{
			Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
			Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
			Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		}
	}
	__forceinline const Vector4 &operator[](int i) const { return Row[i]; }
	Vector4 Row[3];
};

class Matrix4
{
public:
	__forceinline explicit Matrix4(const Matrix3D &m)
	{
		Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4() {}
	__forceinline explicit Matrix4(bool identity)
	{
		if (identity)
			Make_Identity();
	}
	__forceinline Matrix4(const Vector4 &r0, const Vector4 &r1, const Vector4 &r2, const Vector4 &r3)
	{
		Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3;
	}
	__forceinline Matrix4(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
	}
	__forceinline Matrix4 &operator=(const Matrix4 &m)
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3];
		return *this;
	}
	__forceinline void Make_Identity(void)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
		Row[3].Set(0.0f, 0.0f, 0.0f, 1.0f);
	}
	__forceinline Matrix4 Transpose(void) const
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
void BFME2Set_Device_Transform(int transform, const Matrix4 &m);

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned int stream);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static void Apply_Render_State_Changes(void);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __forceinline void Set_Transform(int transform, const Matrix3D &m)
	{
		Matrix4 m2(m);
		switch (transform)
		{
		case 256:
			BFME2World = m2.Transpose();
			render_state_changed |= 0x1;
			render_state_changed &= ~0x40000;
			break;
		default:
			m2 = m2.Transpose();
			BFME2Set_Device_Transform(transform, m2);
			break;
		}
	}
	static __forceinline void Set_Vertex_Declaration(IDirect3DVertexDeclaration9 *decl)
	{
		_Get_D3D_Device8()->SetVertexDeclaration(decl);
		number_of_DX8_calls++;
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
};

namespace FXParticleSystem { class GpuDrawModule; }

class WW3D
{
	friend class FXParticleSystem::GpuDrawModule;
	static bool IsCurrentlyRenderingShadowMap;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GpuDrawGlobalDataView
{
	char m_pad000[0xC60];
	Int m_C60; // +0xC60
};

class GpuParticleStorage
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06();
	virtual Int getParticleCount();	// slot 7
	virtual void s08(); virtual void s09(); virtual void s10();
	virtual IDirect3DVertexDeclaration9 *getVertexDeclaration();	// slot 11
	virtual VertexBufferClass *getVertexBuffer();	// slot 12
	virtual UnsignedInt getVertexCount();	// slot 13
	virtual IndexBufferClass *getIndexBuffer();	// slot 14
	virtual RefCountPtr<FXShader::RenderingMethod> getShader();	// slot 15
};

class ParticleSystem
{
public:
	char m_pad000[0xA4];
	GpuParticleStorage *m_storage; // +0xA4
};
extern ParticleSystem *Make001FCBD7(void);

namespace FXParticleSystem {
class GpuDrawModule
{
public:
	virtual Int doParticles(RenderInfoClass &rinfo, void *unused, Int *particleCount);

private:
	ParticleSystem *getSystem() const
	{
		ParticleSystem *system = m_system;
		if (system == 0)
			system = Make001FCBD7();
		return system;
	}

	ParticleSystem *m_system; // +0x04
};

Int GpuDrawModule::doParticles(RenderInfoClass &rinfo, void *unused, Int *particleCount)
{
	if (WW3D::IsCurrentlyRenderingShadowMap)
		return 0;
	if (reinterpret_cast<GpuDrawGlobalDataView *>(TheWritableGlobalData)->m_C60 != -1)
		return 0;

	GpuParticleStorage *storage = getSystem()->m_storage;
	IDirect3DVertexDeclaration9 *vertexDeclaration = storage->getVertexDeclaration();
	VertexBufferClass *vertexBuffer = storage->getVertexBuffer();
	UnsignedInt vertexCount = storage->getVertexCount();
	IndexBufferClass *indexBuffer = storage->getIndexBuffer();
	RefCountPtr<FXShader::RenderingMethod> shader = storage->getShader();
	if (!vertexBuffer || !indexBuffer || !vertexDeclaration || !shader.IsBound())
		return 0;

	DX8Wrapper::Set_Transform(256, Matrix3D(true));
	DX8Wrapper::Set_Vertex_Buffer(vertexBuffer, 0);
	DX8Wrapper::Set_Index_Buffer(indexBuffer, 0);
	DX8Wrapper::Set_Vertex_Declaration(vertexDeclaration);
	DX8Wrapper::Apply_Render_State_Changes();

	rinfo.Push_Rendering_Method(shader);
	Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
	RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
	Int passes;
	if (current->Begin(&passes, 0xffff))
	{
		for (Int pass = 0; pass < passes; pass++)
		{
			current->Begin_Pass(pass);
			DX8Wrapper::Draw_Triangles(0, vertexCount / 2, 0, vertexCount);
			current->End_Pass();
		}
		current->End();
	}
	Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
	rinfo.Pop_Rendering_Method();
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
	*particleCount += storage->getParticleCount();
	return 0;
}
}
