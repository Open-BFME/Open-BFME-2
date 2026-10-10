// ?tossEmitters@W3DTankDraw@@QAEXXZ
// partial score=0.901398 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD
// Twin guide: verified W3DTankDraw::tossEmitters CB5C3; target
// has two handles at2E8/2F4 independently observed in ctor/createEmitters.
class Rva001F384AByteZeroSetter {
public:
    void disable();
};
class Rva001F3852ByteOneSetter {
public:
    void enable();
};
struct Rva001F3C43Arg {
    char m_pad[0x74];
    int m_value;
};
class Rva001F3C43Slot {
public:
    void set(const Rva001F3C43Arg *arg);
};
class ParticleSystem : public Rva001F3C43Slot {
public:
    void destroy();
};
ParticleSystem *Make001FCBD7();
struct BfmeParticleSystemHandle {
    ~BfmeParticleSystemHandle();
    ParticleSystem *volatile m_system;
    void *m_prev;
    void *m_next;
    __forceinline ParticleSystem *getRaw()const{return m_system;} ParticleSystem *get() const {
        ParticleSystem *p = m_system;
        if (!p)
            p = Make001FCBD7();
        return p;
    }
};
class W3DTankDraw {
protected:
    void tossEmitters();
    void createEmitters();
    void enableEmitters(bool enable);
    char m_pad0[0x2e8];
    BfmeParticleSystemHandle m_dust;
    BfmeParticleSystemHandle m_dirt;

};
void W3DTankDraw::tossEmitters()
{
    if (m_dust.getRaw()) {
        m_dust.get()->set(0);
        m_dust.get()->destroy();
        if (m_dust.getRaw()) {
            m_dust.~BfmeParticleSystemHandle();
            m_dust.m_system = 0;
        }
    }
    if (m_dirt.getRaw()) {
        m_dirt.get()->set(0);
        m_dirt.get()->destroy();
        if (m_dirt.getRaw()) {
            m_dirt.~BfmeParticleSystemHandle();
            m_dirt.m_system = 0;
        }
    }
}
