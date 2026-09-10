// cl: /O1 /DNDEBUG /MD
//
// ParticleEmitterClass::Is_Stopped, retail 0x001A1BE0, 12 bytes.
// Active lives at +0x110 (same offset Stop at 0x001A1BD0 writes).
// Kept out of part_emt.cpp: that TU emits load/test instead of
// xor-eax / cmp [ecx+110h],al / sete.

class ParticleEmitterClass
{
	unsigned char _M_layout[0x110];
	bool Active;

public:
	bool Is_Stopped();
};

bool ParticleEmitterClass::Is_Stopped()
{
	return Active == false;
}
