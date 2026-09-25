// ??0LightningEmissionInfo@FXParticleSystem@@QAE@ABV01@@Z
// partial score=0.95 date=2026-09-25
// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// LightningEmissionInfo copy ctor, retail 0x003A6AF5 (154B).
//
// Shape follows the landed LineEmissionVolumeInfo copy (0x003A653B): the base
// EmissionVolumeInfo copy is implicit (no declared copy ctor), so retail folds
// it in as base vtable + flag byte, then the derived vtable. Member split from
// retail: six loose floats at +8..+0x1C (dword moves), then nine 12-byte
// random variables at +0x20..+0x8B (movsd triples). The default ctor at
// 0x0055D9A5 corroborates: it zeroes +8..+0x1C with movss and the nine blocks
// as (dword, float, float).

namespace FXParticleSystem
{

struct GameClientRandomVariable
{
    unsigned int m_type;
    float m_low;
    float m_high;
};

struct Point3D
{
    float x;
    float y;
    float z;
};

class Snapshot
{
public:
    virtual ~Snapshot();
};

class EmissionVolumeInfo : public Snapshot
{
public:
    virtual ~EmissionVolumeInfo();

    bool m_flag;
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
public:
    LightningEmissionInfo(const LightningEmissionInfo &that);
    virtual ~LightningEmissionInfo();

private:
    // BFME1 kept these as the first two entries of m_points[11]; BFME2 splits
    // the eleven blocks into two leading points plus nine random variables.
    // The copy keeps the donor form: leading floats one at a time, the rest
    // as block copies.
    Point3D m_point0;
    Point3D m_point1;
    GameClientRandomVariable m_var0;
    GameClientRandomVariable m_var1;
    GameClientRandomVariable m_var2;
    GameClientRandomVariable m_var3;
    GameClientRandomVariable m_var4;
    GameClientRandomVariable m_var5;
    GameClientRandomVariable m_var6;
    GameClientRandomVariable m_var7;
    GameClientRandomVariable m_var8;
};

// ??0LightningEmissionInfo@FXParticleSystem@@QAE@ABV01@@Z
LightningEmissionInfo::LightningEmissionInfo(const LightningEmissionInfo &that)
    : EmissionVolumeInfo(that)
{
    m_point0.x = that.m_point0.x;
    m_point0.y = that.m_point0.y;
    m_point0.z = that.m_point0.z;
    m_point1.x = that.m_point1.x;
    m_point1.y = that.m_point1.y;
    m_point1.z = that.m_point1.z;
    m_var0 = that.m_var0;
    m_var1 = that.m_var1;
    m_var2 = that.m_var2;
    m_var3 = that.m_var3;
    m_var4 = that.m_var4;
    m_var5 = that.m_var5;
    m_var6 = that.m_var6;
    m_var7 = that.m_var7;
    m_var8 = that.m_var8;
}

}
