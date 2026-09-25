// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Emission info copy constructors.
//
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/
// FXParticleSystem/fx_particle_system.cpp (Ortho/Cylindrical shapes). BFME2
// keeps the same bodies: base copy out of line, vtable store, then one movsd
// triple per 12-byte random variable. TerrainFireEmissionInfo is new in BFME2
// (no donor); its layout comes from retail 0x003A6E0E and the sibling model in
// Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp.

namespace FXParticleSystem
{

struct GameClientRandomVariable
{
    unsigned int m_type;
    float m_low;
    float m_high;
};

class EmissionVelocityInfo
{
public:
    EmissionVelocityInfo(const EmissionVelocityInfo &that);
    virtual ~EmissionVelocityInfo();
};

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that);
    virtual ~CylindricalEmissionVelocityInfo();

private:
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
};

// ??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_var0(that.m_var0)
    , m_var1(that.m_var1)
{
}

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &that);
    virtual ~OrthoEmissionVelocityInfo();

private:
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
};

// ??0OrthoEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_var0(that.m_var0)
    , m_var1(that.m_var1)
    , m_var2(that.m_var2)
{
}

class EmissionVolumeInfo
{
public:
    EmissionVolumeInfo(const EmissionVolumeInfo &that);
    virtual ~EmissionVolumeInfo();

    bool m_flag;
};

// New in BFME2: no BFME1 donor. Layout from retail 0x003A6E0E (three 12-byte
// blocks at +8/+0x14/+0x20, scalar at +0x2C) and the sibling model in
// Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp.
class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
    TerrainFireEmissionInfo(const TerrainFireEmissionInfo &that);
    virtual ~TerrainFireEmissionInfo();

private:
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
    float m_unknown2C;
};

// ??0TerrainFireEmissionInfo@FXParticleSystem@@QAE@ABV01@@Z
TerrainFireEmissionInfo::TerrainFireEmissionInfo(const TerrainFireEmissionInfo &that)
    : EmissionVolumeInfo(that)
    , m_var0(that.m_var0)
    , m_var1(that.m_var1)
    , m_var2(that.m_var2)
    , m_unknown2C(that.m_unknown2C)
{
}

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &that);
    virtual ~SphericalEmissionVelocityInfo();

private:
    GameClientRandomVariable m_var0;
};

// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_var0(that.m_var0)
{
}

}
