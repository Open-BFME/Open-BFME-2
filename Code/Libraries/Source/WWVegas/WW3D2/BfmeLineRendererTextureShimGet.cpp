// cl: /Ob0 /EHsc /MD /DNDEBUG
//
// LineRendererShim::getTexture, retail 0x0015E120 (33B).
// Retail calls BFMELineRendererTexture::Get_Texture at 0x00191210 and uses
// this+0xDC for its texture subobject. BFME1 uses +0x104, so that layout is
// not carried over.

struct TextureClass
{
	unsigned Vtable;
	unsigned short Refs;
	void Release_Ref();
};

class ParticleBufferClass
{
public:
	class TextureHandleClass
	{
	public:
		TextureClass *Ptr;
		TextureHandleClass( TextureClass *p );
	};
	class LineRendererShim;
};

class BFMELineRendererTexture
{
	TextureClass *m_texture;
public:
	ParticleBufferClass::TextureHandleClass Get_Texture() const;
};

// BFMELineRendererTexture::Get_Texture: defined in BfmeLineRendererTextureGet.cpp (its row's unit).

class ParticleBufferClass::LineRendererShim
{
	char m_prefix[ 0xDC ];
	BFMELineRendererTexture m_texture;
public:
	TextureHandleClass getTexture() const;
};

ParticleBufferClass::TextureHandleClass
ParticleBufferClass::LineRendererShim::getTexture() const
{
	volatile int guard = 0;
	return m_texture.Get_Texture();
}
