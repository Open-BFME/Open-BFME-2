// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@XZ
// partial score=0.98 date=2026-09-25
// cl: /DNDEBUG /MD /EHsc /O1 /Ob2 /arch:SSE

// TerrainCollisionModuleInfo default constructor @0x56459E: vtable 0xC1C218,
// a zeroed int, one random variable ranged (0, 0) through rowed setRange
// 0x002341E7, a false flag and a trailing zero. Same TU model as the LifeEvent
// info thunk: the declared variable destructor carries the second EH state.

namespace FXParticleSystem
{

class GameClientRandomVariable
{
public:
    enum DistributionType
    {
        CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
    };

    GameClientRandomVariable() : m_type(CONSTANT), m_low(0.0f), m_high(0.0f) {}
    ~GameClientRandomVariable();
    void setRange(float low, float high, DistributionType type = UNIFORM);

private:
    DistributionType m_type;
    float m_low;
    float m_high;
};

class Xfer;

class Snapshot
{
public:
    Snapshot() {}
    Snapshot(const Snapshot &that);

    virtual ~Snapshot();
    virtual void crc(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
    virtual void xfer(Xfer *xfer) = 0;
};

class TerrainCollisionModuleInfo : public Snapshot
{
public:
    TerrainCollisionModuleInfo();
    virtual ~TerrainCollisionModuleInfo();

private:
    int m_unknown04;
    GameClientRandomVariable m_var08;
    bool m_flag14;
    int m_unknown18;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@XZ @0x56459E
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo()
    : Snapshot(), m_unknown04(0), m_var08(), m_unknown18(0)
{
    m_var08.setRange(0.0f, 0.0f);
    m_flag14 = false;
}

}
