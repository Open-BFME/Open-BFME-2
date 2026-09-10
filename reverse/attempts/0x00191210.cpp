// ?Get_Texture@BFMELineRendererTexture@@QBE?AVTextureHandleClass@ParticleBufferClass@@XZ
// partial score=0.8 date=2026-09-09
// cl: /G7 /DNDEBUG /MD
//
// BFMELineRendererTexture::Get_Texture, retail 0x00191210, 29 bytes.
// Kept out of part_buf.cpp so ParticleBufferClass::Get_Texture cannot
// see this body. Copies this+0 into the return object and Add_Refs
// a uint16 at the pointee +4. volatile pad forces the extra stack
// slot retail uses (push ecx / mov [esp],0 / pop).

class TextureClass
{
public:
	int _M_vptr_or_pad;
	unsigned short refs;
};

class ParticleBufferClass
{
public:
	class TextureHandleClass
	{
	public:
		TextureClass *Ptr;
		TextureHandleClass() : Ptr(0) {}
		TextureHandleClass(const TextureHandleClass &other) : Ptr(other.Ptr) {}
	};
};

class BFMELineRendererTexture
{
	TextureClass *Ptr;

public:
	ParticleBufferClass::TextureHandleClass Get_Texture() const;
};

ParticleBufferClass::TextureHandleClass BFMELineRendererTexture::Get_Texture() const
{
	volatile int pad = 0;
	TextureClass *p = Ptr;
	ParticleBufferClass::TextureHandleClass out;
	out.Ptr = p;
	if (p)
		p->refs++;
	(void)pad;
	return out;
}
