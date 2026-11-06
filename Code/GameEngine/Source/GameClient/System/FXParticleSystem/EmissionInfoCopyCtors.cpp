// cl: /DNDEBUG /MD /GX- /Ob2

// Emission info copy constructors.
//
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/System/
// FXParticleSystem/fx_particle_system.cpp (Ortho/Cylindrical shapes). BFME2
// keeps the same bodies: base copy out of line, vtable store, then one movsd
// triple per 12-byte random variable. TerrainFireEmissionInfo is new in BFME2
// (no donor); its layout comes from retail 0x003A6E0E and the sibling model in
// Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp.

class Xfer;
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

#include "../../../../Include/GameClient/EmissionVolumeInfo.h"
#include "../../../../Include/GameClient/EmissionVelocityInfo.h"
#include "../../../../Include/GameClient/CylindricalEmissionVelocityInfo.h"
#include "../../../../Include/GameClient/TerrainFireEmissionInfo.h"
#include "../../../../Include/GameClient/SphericalEmissionVelocityInfo.h"
#include "../../../../Include/GameClient/OrthoEmissionVelocityInfo.h"
namespace FXParticleSystem
{


// BFME1 donor fx_particle_system.cpp:733 is an empty DoXfer override; target
// exports identify EmissionVelocityInfo at 0x0047A69C.
// ?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z
void EmissionVelocityInfo::DoXfer(Xfer &xfer)
{
}

// Retail exports fold this class's default/copy/lifetime with Cylindrical.
// Native copy3A7501 calls the four-byte base, then copies twelve-byte
// members at +4/+0x10. Member roles are not established by this layout.
class OutwardEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
    OutwardEmissionVelocityInfo(const OutwardEmissionVelocityInfo &that);
    virtual ~OutwardEmissionVelocityInfo();
private:
    ::GameClientRandomVariable m_04;
    ::GameClientRandomVariable m_10;
};

OutwardEmissionVelocityInfo::OutwardEmissionVelocityInfo(const OutwardEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that), m_04(that.m_04), m_10(that.m_10)
{
}

// ??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_04(that.m_04)
    , m_10(that.m_10)
{
}

// ??0OrthoEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
OrthoEmissionVelocityInfo::OrthoEmissionVelocityInfo(const OrthoEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_04(that.m_04)
    , m_10(that.m_10)
    , m_1C(that.m_1C)
{
}


// New in BFME2: no BFME1 donor. Layout from retail 0x003A6E0E (three 12-byte
// blocks at +8/+0x14/+0x20, scalar at +0x2C) and the sibling model in
// Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp.
// ??0TerrainFireEmissionInfo@FXParticleSystem@@QAE@ABV01@@Z
TerrainFireEmissionInfo::TerrainFireEmissionInfo(const TerrainFireEmissionInfo &that)
    : EmissionVolumeInfo(that)
    , m_08(that.m_08)
    , m_14(that.m_14)
    , m_20(that.m_20)
    , m_2C(that.m_2C)
{
}

// ??0SphericalEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z
SphericalEmissionVelocityInfo::SphericalEmissionVelocityInfo(const SphericalEmissionVelocityInfo &that)
    : EmissionVelocityInfo(that)
    , m_04(that.m_04)
{
}

}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?construct_from@OutwardEmissionVelocityModuleTemplateSubCopyShim@FXParticleSystem@@QAEXPBX@Z=??0CylindricalEmissionVelocityInfo@FXParticleSystem@@QAE@ABV01@@Z")

// Target exports identify the empty volume transfer as the same RET4 fold.
void FXParticleSystem::EmissionVolumeInfo::DoXfer(Xfer &) {}
