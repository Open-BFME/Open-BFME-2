// cl: /O2 /Oy /DNDEBUG /MD
//
// ParticleEmitterClass::Get_Texture, retail 0x001A0D10, 33 bytes.
// Dedicated TU so part_emt.cpp and part_buf.cpp cannot see this body.
// Buffer lives at +0x12C; the handle type is trivial here so dest is
// forwarded into ParticleBufferClass::Get_Texture.

class BFME2ParticleTextureHandle
{
	void *Ptr;
};

class ParticleBufferClass
{
public:
	BFME2ParticleTextureHandle Get_Texture() const;
};

class ParticleEmitterClass
{
	char pad[0x12C];
	ParticleBufferClass *Buffer;

public:
	BFME2ParticleTextureHandle Get_Texture() const;
};

BFME2ParticleTextureHandle ParticleEmitterClass::Get_Texture() const
{
	volatile int pad = 0;
	return Buffer->Get_Texture();
}
