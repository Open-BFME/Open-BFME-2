// cl: /EHsc /MD /DNDEBUG
//
// BFMELineRendererTexture::Get_Texture, retail 0x00191210 (29B).
// Dedicated TU so part_buf.cpp keeps its matched callers.
// Same WORD-refcount owning-handle shape as bfme2_particle_texture_accessor
// (30B at 0x001790E0); here the texture slot is at +0, not +36.

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
		TextureHandleClass( TextureClass *p ) : Ptr( p ) { if ( Ptr ) ++Ptr->Refs; }
		TextureHandleClass( const TextureHandleClass &p ) : Ptr( p.Ptr ) { if ( Ptr ) ++Ptr->Refs; }
		~TextureHandleClass();
	};
};

class BFMELineRendererTexture
{
	TextureClass *Texture;
public:
	ParticleBufferClass::TextureHandleClass Get_Texture() const;
};

ParticleBufferClass::TextureHandleClass BFMELineRendererTexture::Get_Texture() const
{
	return ParticleBufferClass::TextureHandleClass( Texture );
}
