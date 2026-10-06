// cl: /MD
// ?rva00098690@Rva00098690@@QAEXXZ, retail 0x00098690, 87 bytes.
// Two contiguous BfmeParticleSystemHandles at +0x4C/+0x58: if m_system then
// get()->destroy() (null-or-Make fallback via pinned Make001FCBD7 then rowed
// destroy 0x001F462C), then if still set dtor via rowed 0x0004CBC0 and clear.
// Spelt from W3DTankTruckDraw::tossEmitters precedent (volatile m_system
// preserves retail's redundant null-or-Make chases that /O1 folds).
// Callees rowed/pinned; callers 0x000986E7 (dtor) and 0x0009873C. Owner
// unproven so honest address-derived struct (no vtable).

class ParticleSystem
{
public:
	void destroy();
};

ParticleSystem *Make001FCBD7();

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	ParticleSystem *volatile m_system;
	void *m_previous;
	void *m_next;
	ParticleSystem *get() const
	{
		ParticleSystem *target = m_system;
		if (!target)
			target = Make001FCBD7();
		return target;
	}
};

class Rva00098690
{
public:
	void rva00098690();
private:
	unsigned char m_pad[0x4C];
	BfmeParticleSystemHandle m_first; // +0x4C
	BfmeParticleSystemHandle m_second; // +0x58
};

void Rva00098690::rva00098690()
{
	if (m_first.m_system)
	{
		m_first.get()->destroy();
		if (m_first.m_system)
		{
			m_first.~BfmeParticleSystemHandle();
			m_first.m_system = 0;
		}
	}
	if (m_second.m_system)
	{
		m_second.get()->destroy();
		if (m_second.m_system)
		{
			m_second.~BfmeParticleSystemHandle();
			m_second.m_system = 0;
		}
	}
}
