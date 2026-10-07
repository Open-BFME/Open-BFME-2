// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport

// BFME1 donor: Rva00785FD0RendererConstructor.cpp at verified revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20; O1/SSE/G7 exact placement.
// Target facts: ctor11044C..110611 initializes three16-float identity blocks
// at +10/+50/+90; allocates a20-byte DX8VertexBuffer with FVF242 count4E20
// usage1; uses the proven four-byte texture-handle cleanup17098D. Existing
// setMode1100CA establishes the mode word+8 and dirty byte+0 independently.
// Named stencil/dtor call routes refer to this address-derived class. The
// original application type name and matrix role labels remain donor leads.
// Native storage extends through +DC; these members total E0 bytes. No new
// callee pins or allocator substitutions are used.

// TU-local matrix storage follows donor Matrix4::Make_Identity, avoiding
// the unrelated out-of-line Vector4::Set COMDAT emitted by the full header.
class NativeRendererRow {
public:
 float X,Y,Z,W;
 __forceinline NativeRendererRow() {}
 __forceinline void Set(float x,float y,float z,float w) { X=x;Y=y;Z=z;W=w; }
};
class NativeRendererMatrix {
public:
 __forceinline explicit NativeRendererMatrix(bool identity);
 __forceinline void Make_Identity();
protected:
 NativeRendererRow Row[4];
};
// ?NativeRendererMatrix::NativeRendererMatrix absent-from-retail
// Local implementation helper fully inlined into the verified constructor.
__forceinline NativeRendererMatrix::NativeRendererMatrix(bool identity) {
 if (identity) Make_Identity();
}
// ?NativeRendererMatrix::Make_Identity absent-from-retail
// Local implementation helper fully inlined into the verified constructor.
__forceinline void NativeRendererMatrix::Make_Identity() {
 Row[0].Set(1.0f,0.0f,0.0f,0.0f);
 Row[1].Set(0.0f,1.0f,0.0f,0.0f);
 Row[2].Set(0.0f,0.0f,1.0f,0.0f);
 Row[3].Set(0.0f,0.0f,0.0f,1.0f);
}

class DX8VertexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0, USAGE_DYNAMIC = 1 };

	DX8VertexBufferClass(unsigned fvf, unsigned short count, UsageType usage,
		unsigned vertex_size);
	virtual ~DX8VertexBufferClass();

private:
	unsigned char m_body[0x1c];
};

class TextureClass;
template<class T> class RefCountPtr
{
public:
	RefCountPtr() : m_resource(0) {}
	~RefCountPtr();

private:
	T *m_resource;
};

class Rva00785FD0Renderer
{
public:
	Rva00785FD0Renderer();
	void __fastcall setMode(int mode);

private:
	bool m_modeChanged;
	bool m_pendingTextureChange;
	unsigned char m_padding02[2];
	RefCountPtr<TextureClass> m_texture;
	unsigned m_mode;
	unsigned m_stencilGeneration;
	NativeRendererMatrix m_world;
	NativeRendererMatrix m_view;
	NativeRendererMatrix m_projection;
	DX8VertexBufferClass *m_vertexBuffer;
	unsigned m_vertexOffset;
	unsigned m_vertexCount;
	unsigned m_reserved;
};

Rva00785FD0Renderer::Rva00785FD0Renderer()
	:
		m_modeChanged(false),
		m_pendingTextureChange(false),
		m_mode(0),
		m_stencilGeneration(0),
		m_world(true),
		m_view(true),
		m_projection(true),
		m_vertexBuffer(0),
		m_vertexOffset(0),
		m_vertexCount(0),
		m_reserved(0)
{
	m_vertexBuffer = new DX8VertexBufferClass(
		0x242, 0x4e20, DX8VertexBufferClass::USAGE_DYNAMIC, 0);
}

void __fastcall Rva00785FD0Renderer::setMode(int mode)
{
 if (m_mode != (unsigned)mode) { m_mode = mode; m_modeChanged = true; }
}

typedef char NativeRendererSize[sizeof(Rva00785FD0Renderer)==0xe0 ? 1 : -1];
