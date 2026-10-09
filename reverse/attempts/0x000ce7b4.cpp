// ?tossEmitters@W3DTankDraw@@IAEXXZ
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
class ParticleSystem
{
public:
	void destroy(void);
};
ParticleSystem *Make001FCBD7();

struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *object);
};

class ParticleSystemView
{
public:
	void attachToObject(const Rva001F3C43Arg *object) { ((Rva001F3C43Slot *)this)->set(object); }
	void destroy(void) { ((ParticleSystem *)this)->destroy(); }
};

struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	ParticleSystem *volatile m_system;
	void *m_prev;
	void *m_next;
	ParticleSystemView *operator->()
	{
		ParticleSystem *p = m_system;
		if (!p)
			p = Make001FCBD7();
		return (ParticleSystemView *)p;
	}
	__forceinline void clear()
	{
		if (m_system) {
			this->~BfmeParticleSystemHandle();
			m_system = 0;
		}
	}
};

class W3DTankDraw
{
protected:
	void tossEmitters(void);

	unsigned char m_pad000[0x2E8];
	BfmeParticleSystemHandle m_treadDebrisLeft;
	BfmeParticleSystemHandle m_treadDebrisRight;
};

static __forceinline void tossHandle(BfmeParticleSystemHandle &handle)
{
	if (handle.m_system) {
		handle->attachToObject(0);
		handle->destroy();
		handle.clear();
	}
}

// ?tossEmitters@W3DTankDraw@@IAEXXZ
void W3DTankDraw::tossEmitters(void)
{
	tossHandle(m_treadDebrisLeft);
	tossHandle(m_treadDebrisRight);
}
