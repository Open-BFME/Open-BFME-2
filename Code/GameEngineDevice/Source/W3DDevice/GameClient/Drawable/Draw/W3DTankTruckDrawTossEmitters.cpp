// cl: /MD
// ?tossEmitters@W3DTankTruckDraw@@IAEXXZ, retail 0x000CB5C3, 191 bytes.
// Ported from Open-BFME-1 Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankTruckDraw.cpp:201
// (ZH GeneralsMD second: W3DTankTruckDraw.cpp tossEmitter); BFME2 deltas are the 12-byte smart handles.
// Handles at +0x2ec/+0x2f8/+0x304 are BfmeParticleSystemHandle/RvaSmartPtr12 (cf. SmartPtrCopyCtor.cpp,
// ParticleSystemHandle_dtor.cpp); treads at +0x310 (caller 0xCE6A1) count at +0x354. Callees: pinned
// Make001FCBD7 empty fallback (BFME1 emptyParticleSystem role), rowed set 0x1F3C43 (attachToObject: arg+0x74
// Object ID or zero +0xb4), rowed destroy 0x1F462C, rowed handle dtor 0x4CBC0. Callers at 0xCDE9F/0xCDE52 and
// rowed setFullyObscuredByShroud 0xCDF1B; donor dtor/loadPostProcess call it. /O1 frameless xor-edi idiom;
// volatile m_system preserves retail's redundant null-or-Make chases that /O1 otherwise folds (158B wall).
// ?enableEmitters@W3DTankTruckDraw@@IAEX_N@Z, retail 0x000CB826, 165 bytes: donor enableEmitters(Bool)
// createEmitters + m_effectsInitialized=+0x2e8 + start/stop via rowed byte setters 0x1F384A(start=0)/0x1F3852(stop=1)
// at ParticleSystem+0x1a3; power only stops when !enable. Callers 0xCC798/0xCDE2D.
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
// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle {
    ~BfmeParticleSystemHandle();
    ParticleSystem *volatile m_system;
    void *m_prev;
    void *m_next;
    ParticleSystem *get() const {
        ParticleSystem *p = m_system;
        if (!p)
            p = Make001FCBD7();
        return p;
    }
};
class W3DTankTruckDraw {
protected:
    void tossEmitters();
    void createEmitters();
    void enableEmitters(bool enable);
    char m_pad0[0x2e8];
    unsigned char m_effectsInitialized;
    char m_pad1[0x2ec - 0x2e9];
    BfmeParticleSystemHandle m_dust;
    BfmeParticleSystemHandle m_dirt;
    BfmeParticleSystemHandle m_power;
};
void W3DTankTruckDraw::tossEmitters()
{
    if (m_dust.m_system) {
        m_dust.get()->set(0);
        m_dust.get()->destroy();
        if (m_dust.m_system) {
            reinterpret_cast<RvaSmartPtr12 *>(&m_dust)->rva0004CBC0();
            m_dust.m_system = 0;
        }
    }
    if (m_dirt.m_system) {
        m_dirt.get()->set(0);
        m_dirt.get()->destroy();
        if (m_dirt.m_system) {
            reinterpret_cast<RvaSmartPtr12 *>(&m_dirt)->rva0004CBC0();
            m_dirt.m_system = 0;
        }
    }
    if (m_power.m_system) {
        m_power.get()->set(0);
        m_power.get()->destroy();
        if (m_power.m_system) {
            reinterpret_cast<RvaSmartPtr12 *>(&m_power)->rva0004CBC0();
            m_power.m_system = 0;
        }
    }
}
void W3DTankTruckDraw::enableEmitters(bool enable)
{
    createEmitters();
    m_effectsInitialized = 1;
    if (m_dust.m_system) {
        if (enable)
            ((Rva001F384AByteZeroSetter *)m_dust.get())->disable();
        else
            ((Rva001F3852ByteOneSetter *)m_dust.get())->enable();
    }
    if (m_dirt.m_system) {
        if (enable)
            ((Rva001F384AByteZeroSetter *)m_dirt.get())->disable();
        else
            ((Rva001F3852ByteOneSetter *)m_dirt.get())->enable();
    }
    if (m_power.m_system) {
        if (!enable)
            ((Rva001F3852ByteOneSetter *)m_power.get())->enable();
    }
}
