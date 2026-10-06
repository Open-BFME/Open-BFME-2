// cl: /DNDEBUG /MD /EHsc
// ?destroy@ParticleSystem@@QAEXXZ, retail 0x001F462C, 50 bytes.
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/System/ParticleSys.cpp
// ParticleSystem::destroy (their matched 52B row): retail's body is a LOOP, not
// a call: m_slaveSystem->destroy() is a tail call to this same function, and the
// compiler turns that into a walk down the slave chain. The source below is the
// reference's recursion unchanged; the loop is the compiler's doing.
// BFME2 deltas (retail-measured): slave slot +0x15C, destroyed flag +0x1A4.
// The null-slave factory keeps BFME1's Make-style opaque pin.

class ParticleSystem;

ParticleSystem *Make001FCBD7(void);

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = m_target;
		if (!target)
			target = Make001FCBD7();
		return target;
	}

private:
	ParticleSystem *m_target;
};

struct BfmeParticleDestroyView
{
	unsigned char m_unreconstructed_000[0x15C];
	BfmeParticleSystemPtr m_slaveSystem;			///< retail this+0x15C
	unsigned char m_unreconstructed_160[0x1A4 - 0x160];
	unsigned char m_isDestroyed;				///< retail this+0x1A4
};

class ParticleSystem
{
public:
	void destroy(void);
};

void ParticleSystem::destroy(void)
{
	BfmeParticleDestroyView *self = (BfmeParticleDestroyView *)this;

	self->m_isDestroyed = true;
	if (self->m_slaveSystem)
	{
		self->m_slaveSystem->destroy();  // If we don't it will leak forever.  We are solely responsible for it.
	}
}
