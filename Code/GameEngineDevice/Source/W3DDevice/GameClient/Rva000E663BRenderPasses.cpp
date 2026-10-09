// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc
// stlport
//
// ?rva000E663B@Rva000EC9C6@@QAEXH@Z retail 0x000E663B..0x000E67E3
// (424 bytes EH RET 4). The render step the rowed 0x000EC9C6 forwards to
// when its +0x28 count list leads with a non-zero count; the argument is
// the RenderInfoClass. It follows the matched road pass in
// W3DRoadBufferDrawRoads.cpp (same callee shapes): the light environment
// of the render info is set (rowed DX8Wrapper::Set_Light_Environment) the
// +0x34 rendering method is pushed (rowed Push_Rendering_Method) and the
// stack handed to the pinned 0x001688FF; the stack's first method (held
// by reference count) runs Begin(&passes 0xFFFF) with g_009EBC90 pointing
// at this object; per pass each buffer set up to the first zero +0x28
// index count binds its +0x1C index buffer and +0x04 vertex buffer (rowed
// Set_Index_Buffer / Set_Vertex_Buffer) and draws count/3 triangles over
// the +0x10 vertex count (rowed Draw_Triangles); then End the pinned
// 0x00168952 Pop_Rendering_Method and the vertex and pixel shaders are
// cleared. Class identity is address-derived from the caller.
#include <vector>

typedef int Int;

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

void Rva001688FF(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);
void Rva00168952(const RefCountPtr<FXShader::RenderingMethod> *methods, Int count);

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

class IndexBufferClass;
class VertexBufferClass;

class DX8Wrapper
{
public:
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned int stream);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

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
};

class Rva000E6AC0;
extern Rva000E6AC0 *g_009EBC90;

class Rva000EC9C6
{
public:
	void rva000E663B(int arg);

private:
	int m_00;
	_STL::vector<VertexBufferClass *> m_vertexBuffers;   // +0x04
	_STL::vector<Int> m_vertexCounts;                    // +0x10
	_STL::vector<IndexBufferClass *> m_indexBuffers;     // +0x1C
	_STL::vector<Int> m_indexCounts;                     // +0x28
	RefCountPtr<FXShader::RenderingMethod> m_method;     // +0x34
};

void Rva000EC9C6::rva000E663B(int arg)
{
	RenderInfoClass &rinfo = *reinterpret_cast<RenderInfoClass *>(arg);

	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
	rinfo.Push_Rendering_Method(m_method);
	Rva001688FF(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());

	RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
	Int passes = 0;
	g_009EBC90 = reinterpret_cast<Rva000E6AC0 *>(this);
	current->Begin(&passes, 0xffff);
	for (Int pass = 0; pass < passes; pass++)
	{
		current->Begin_Pass(pass);
		for (unsigned int i = 0; i < m_vertexBuffers.size(); i++)
		{
			if (m_indexCounts[i] == 0)
				break;
			DX8Wrapper::Set_Index_Buffer(m_indexBuffers[i], 0);
			DX8Wrapper::Set_Vertex_Buffer(m_vertexBuffers[i], 0);
			DX8Wrapper::Draw_Triangles(0, m_indexCounts[i] / 3, 0, m_vertexCounts[i]);
		}
		current->End_Pass();
	}
	current->End();
	g_009EBC90 = 0;

	Rva00168952(rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
	rinfo.Pop_Rendering_Method();
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
}
