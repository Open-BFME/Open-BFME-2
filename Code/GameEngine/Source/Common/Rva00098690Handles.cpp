// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00098690@Rva00098690@@QAEXXZ, retail 0x00098690, 87 bytes.
// Two contiguous BfmeParticleSystemHandles at +0x4C/+0x58: if m_system then
// get()->destroy() (null-or-Make fallback via pinned Make001FCBD7 then rowed
// destroy 0x001F462C), then if still set dtor via rowed 0x0004CBC0 and clear.
// Spelt from W3DTankTruckDraw::tossEmitters precedent (volatile m_system
// preserves retail's redundant null-or-Make chases that /O1 folds).
// Callees rowed/pinned; callers 0x000986E7 (dtor) and 0x0009873C. Owner
// unproven so honest address-derived struct (no vtable).

#include "ascii_string.h"

class RvaSmartPtr12
{
public:
    RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw();
    void rva0004CBC0() throw();
};

class ParticleSystem
{
public:
	void destroy();
	void rva001F45F4(bool flag);
};

ParticleSystem *Make001FCBD7();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw() { if (m_system) reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0(); }
    BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &other)
    { reinterpret_cast<RvaSmartPtr12 *>(this)->operator=(*reinterpret_cast<const RvaSmartPtr12 *>(&other)); return *this; }
	ParticleSystem *volatile m_system;
	void *m_previous;
	void *m_next;
	ParticleSystem *get() const
	{
		ParticleSystem *target = m_system;
		if (!target)
            return Make001FCBD7();
        return target;
	}
};

class Rva00098690
{
public:
	void rva00098690();
    bool rva0009873C();
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
			reinterpret_cast<RvaSmartPtr12 *>(&m_first)->rva0004CBC0();
			m_first.m_system = 0;
		}
	}
	if (m_second.m_system)
	{
		m_second.get()->destroy();
		if (m_second.m_system)
		{
			reinterpret_cast<RvaSmartPtr12 *>(&m_second)->rva0004CBC0();
			m_second.m_system = 0;
		}
	}
}

class Rva00564E0D { public: AsciiString rva00564E0D(); };
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getTextureFilename() const; }; }
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
    ParticleSystemTemplate *findTemplate(const AsciiString &) const;
    BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *, bool);
};
extern ParticleSystemManager *TheParticleSystemManager;
class GameLODManager { public: char unmodelled[0x1778]; int level; };
extern GameLODManager *TheGameLODManager;
class Rva001F384AByteZeroSetter { public: void disable(); };

// Native 9873C..98894 RET0: same complete receiver as the 87-byte cleanup
// above. The original product name is unknown; two names at0C/10 and two
// handles at4C/58 are independently witnessed by the called provider bodies.
bool Rva00098690::rva0009873C()
{
    rva00098690();
    if (TheParticleSystemManager)
    {
        AsciiString name = reinterpret_cast<Rva00564E0D *>(this)->rva00564E0D();
        const ParticleSystemTemplate *first = TheParticleSystemManager->findTemplate(name);
        if (first && !m_first.m_system)
        {
            m_first = TheParticleSystemManager->createParticleSystem(first, true);
            m_first.get()->rva001F45F4(false);
            reinterpret_cast<Rva001F384AByteZeroSetter *>(m_first.get())->disable();
        }
        if (TheGameLODManager && TheGameLODManager->level > 1)
        {
            AsciiString other = reinterpret_cast<const FXParticleSystem::ParticleSystemTemplate *>(this)->getTextureFilename();
            const ParticleSystemTemplate *second = TheParticleSystemManager->findTemplate(other);
            if (second && !m_second.m_system)
            {
                m_second = TheParticleSystemManager->createParticleSystem(second, true);
                m_second.get()->rva001F45F4(false);
                reinterpret_cast<Rva001F384AByteZeroSetter *>(m_second.get())->disable();
            }
        }
    }
    return true;
}
