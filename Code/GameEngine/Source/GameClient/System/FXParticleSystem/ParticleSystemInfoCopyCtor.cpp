// cl: /O1 /EHsc

namespace FXParticleSystem
{
class ParticleSystemInfo;
}

class AsciiString;

// ParticleSystemInfo's declaration is reconstructed locally because the retail
// object is not available as a usable public header.  The member widths and
// offsets follow the BFME2 copy body and the corresponding GeneralsMD
// ParticleSys.h layout.
template <typename T>
class StringBase
{
    friend class FXParticleSystem::ParticleSystemInfo;
    friend class AsciiString;

private:
    StringBase(const StringBase<T> &that);

    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    void releaseBuffer();
    Header *m_data;

public:
    void set(const StringBase<T> &that);
};

inline void *operator new(unsigned int, void *storage)
{
    return storage;
}

class AsciiString
{
public:
    AsciiString(const AsciiString &that)
        : m_data(that.m_data)
    {
    }

    AsciiString &operator=(const AsciiString &that)
    {
        m_data.set(that.m_data);
        return *this;
    }

    ~AsciiString()
    {
        m_data.releaseBuffer();
    }

private:
    StringBase<char> m_data;
};

struct ThreeDwords
{
    unsigned int value0;
    unsigned int value1;
    unsigned int value2;
};

class Coord3D
{
public:
    Coord3D(const Coord3D &that)
        : x(that.x), y(that.y), z(that.z)
    {
    }

private:
    float x;
    float y;
    float z;
};

struct Region2D
{
    __declspec(nothrow) Region2D(const Region2D &that);

    float x_min;
    float y_min;
    float x_max;
    float y_max;
};

class Xfer;

class Snapshot
{
public:
    virtual ~Snapshot() {}
    virtual const char *GetSnapshotName() = 0;
    virtual void LoadPostProcess() = 0;
    virtual void DoXfer(Xfer &xfer) = 0;
};

namespace FXParticleSystem
{

class ParticleSystemInfo : public Snapshot
{
public:
    virtual ~ParticleSystemInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
    ParticleSystemInfo &operator=(const ParticleSystemInfo &that);

private:
    unsigned char m_isOneShot;
    unsigned int m_shaderType;
    unsigned int m_particleType;
    AsciiString m_particleTypeName;
    ThreeDwords m_angleZ;
    unsigned int m_systemLifetime;
    unsigned int m_volumeParticleDepth;
    ThreeDwords m_angularRateZ;
    ThreeDwords m_angularDamping;
    unsigned int m_windMotion;
    ThreeDwords m_velDamping;
    ThreeDwords m_lifetime;
    ThreeDwords m_startSize;
    AsciiString m_slaveSystemName;
    Coord3D m_slavePosOffset;
    AsciiString m_attachedSystemName;
    unsigned int m_emissionVelocityType;
    unsigned char m_isEmissionVolumeHollow;
    unsigned char m_isGroundAligned;
    unsigned char m_isEmitAboveGroundOnly;
    unsigned char m_isParticleUpTowardsEmitter;
    unsigned char m_windMotionMovingToEndAngle;
    unsigned char m_unknown85;
    Region2D m_uv;
    unsigned int m_unknown98;
};

ParticleSystemInfo &ParticleSystemInfo::operator=(
    const ParticleSystemInfo &that)
{
    m_isOneShot = that.m_isOneShot;
    m_shaderType = that.m_shaderType;
    m_particleType = that.m_particleType;
    m_particleTypeName = that.m_particleTypeName;
    m_angleZ = that.m_angleZ;
    m_systemLifetime = that.m_systemLifetime;
    m_volumeParticleDepth = that.m_volumeParticleDepth;
    m_angularRateZ = that.m_angularRateZ;
    m_angularDamping = that.m_angularDamping;
    m_windMotion = that.m_windMotion;
    m_velDamping = that.m_velDamping;
    m_lifetime = that.m_lifetime;
    m_startSize = that.m_startSize;
    m_slaveSystemName = that.m_slaveSystemName;
    m_slavePosOffset = that.m_slavePosOffset;
    m_attachedSystemName = that.m_attachedSystemName;
    m_emissionVelocityType = that.m_emissionVelocityType;
    m_isEmissionVolumeHollow = that.m_isEmissionVolumeHollow;
    m_isGroundAligned = that.m_isGroundAligned;
    m_isEmitAboveGroundOnly = that.m_isEmitAboveGroundOnly;
    m_isParticleUpTowardsEmitter = that.m_isParticleUpTowardsEmitter;
    m_windMotionMovingToEndAngle = that.m_windMotionMovingToEndAngle;
    m_unknown85 = that.m_unknown85;
    m_uv = that.m_uv;
    m_unknown98 = that.m_unknown98;
    return *this;
}

// Force MSVC to emit the otherwise implicit copy constructor as a standalone
// COMDAT.  This helper is never called by the game.
// ?forceParticleSystemInfoCopy@FXParticleSystem@@YAPAVParticleSystemInfo@1@PAXABV21@@Z absent-from-retail
__declspec(noinline) ParticleSystemInfo *forceParticleSystemInfoCopy(
    void *storage, const ParticleSystemInfo &source)
{
    return new (storage) ParticleSystemInfo(source);
}

}
