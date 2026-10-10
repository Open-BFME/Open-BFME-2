// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Constructor 0x000DFCD5..0x000DFDD9 (260B), destructor 0x000DFDD9 (88B).
// ZH W3dWaypointBuffer.cpp constructor/default-line-style is the semantic
// donor at BFME1 575ba2b04. Target/WB 0x87EE80 establish creation, handles,
// shader and line calls; target model is SCMoveHintSml and colour is .97/.64/.15.
// Target passes the address of the one-pointer texture handle to Set_Texture;
// retain the existing provider declaration without asserting its pointee type.

typedef int Int;

class RefCountClass
{
public:
	virtual void Delete_This(void) = 0;

	void Release_Ref(void)
	{
		if (--NumRefs == 0)
			Delete_This();
	}

	Int NumRefs;
};

class RenderObjClass : public RefCountClass {};
class Vector3 { public: Vector3(float a,float b,float c):X(a),Y(b),Z(c){} float X,Y,Z; };
class ShaderClass {public: ShaderClass(){} ShaderClass(const ShaderClass &s):m_bits(s.m_bits){} void Set_Depth_Compare(int x){m_bits=(m_bits&~7)|x;} static ShaderClass _PresetAdditiveShader; unsigned int m_bits;};
class SegLineRendererClass {public: enum TextureMapMode {UNIFORM_WIDTH_TEXTURE_MAP, UNIFORM_LENGTH_TEXTURE_MAP, TILED_TEXTURE_MAP};};
class TextureClass;
class SegmentedLineClass : public RefCountClass {public: virtual void Delete_This(void); SegmentedLineClass(); void Set_Texture(TextureClass*); void Set_Shader(ShaderClass); void Set_Width(float); void Set_Color(const Vector3&); void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode); char m_rest[0x12c-8];};

class TextureClass
{
public:
	void Release_Ref(void);
};

template<class T> class RefCountPtr {public: RefCountPtr():m_ptr(0){} ~RefCountPtr(){if(m_ptr)m_ptr->Release_Ref();} const RefCountPtr &operator=(const RefCountPtr &); operator T*() const {return m_ptr;} T *m_ptr;};
class BFME2ParticleTextureHandle:public RefCountPtr<TextureClass> {};
BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
RenderObjClass *Create_Render_Obj(const char*);

class W3DWaypointBuffer
{
public:
	W3DWaypointBuffer();
	~W3DWaypointBuffer();

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
	RefCountPtr<TextureClass> m_texture;
};

W3DWaypointBuffer::~W3DWaypointBuffer()
{
	if (m_waypointNodeRobj)
	{
		m_waypointNodeRobj->Release_Ref();
		m_waypointNodeRobj = 0;
	}
	if (m_line)
	{
		m_line->Release_Ref();
		m_line = 0;
	}
}

W3DWaypointBuffer::W3DWaypointBuffer()
{
 m_waypointNodeRobj=Create_Render_Obj("SCMoveHintSml");
 m_line=new SegmentedLineClass;
 m_texture=BFME2LoadParticleTexture("EXLaser.tga",0,0);
 // Native argument is the handle address, preserving the rowed provider ABI.
 m_line->Set_Texture(reinterpret_cast<TextureClass*>(&m_texture));
 ShaderClass shader=ShaderClass::_PresetAdditiveShader;
 shader.Set_Depth_Compare(7);
 m_line->Set_Shader(shader);
 m_line->Set_Width(1.5f);
 m_line->Set_Color(Vector3(0.97f,0.64f,0.15f));
 m_line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);
}
