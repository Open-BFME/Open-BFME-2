// cl: /O1
// BFME1 FX particle module parser transferred to the BFME2 parser-table
// address.  The body is intentionally kept separate from the factory TU so
// each exported parser has an independently verifiable boundary.

struct FieldParse;

class INI
{
public:
    void initFromINI(void *what, const FieldParse *parseTable);
};

namespace FXParticleSystem
{
class PointEmissionVolumeModuleTemplate
{
public:
    void parse(INI *ini);
};

// ?parse@PointEmissionVolumeModuleTemplate@FXParticleSystem@@QAEXPAVINI@@@Z
void PointEmissionVolumeModuleTemplate::parse(INI *ini)
{
    ini->initFromINI(this, reinterpret_cast<const FieldParse *>(0x00C6BB6C));
}
}

namespace FXParticleSystem
{

#define FX_PARTICLE_PARSER(CLASS, TABLE)                                      \
class CLASS                                                                  \
{                                                                            \
public:                                                                      \
    void parse(INI *ini);                                                    \
};                                                                           \
void CLASS::parse(INI *ini)                                                  \
{                                                                            \
    ini->initFromINI(this, reinterpret_cast<const FieldParse *>(TABLE));     \
}

FX_PARTICLE_PARSER(LineEmissionVolumeModuleTemplate, 0x00C6BBD8)
FX_PARTICLE_PARSER(BoxEmissionVolumeModuleTemplate, 0x00C6BCD0)
FX_PARTICLE_PARSER(SphereEmissionVolumeModuleTemplate, 0x00C6BDB4)
FX_PARTICLE_PARSER(CylinderEmissionVolumeModuleTemplate, 0x00C6BEB0)
FX_PARTICLE_PARSER(LightningEmissionModuleTemplate, 0x00C6C008)
FX_PARTICLE_PARSER(OrthoEmissionVelocityModuleTemplate, 0x00C6C1B0)
FX_PARTICLE_PARSER(SphericalEmissionVelocityModuleTemplate, 0x00C6C230)
FX_PARTICLE_PARSER(CylindricalEmissionVelocityModuleTemplate, 0x00C6C294)
FX_PARTICLE_PARSER(OutwardEmissionVelocityModuleTemplate, 0x00C6C390)
FX_PARTICLE_PARSER(StreakDrawModuleTemplate, 0x00C6BB18)
FX_PARTICLE_PARSER(QuadDrawModuleTemplate, 0x00C6BB18)
FX_PARTICLE_PARSER(ButterflyDrawModuleTemplate, 0x00C6BB18)
FX_PARTICLE_PARSER(LightningDrawModuleTemplate, 0x00C6C608)
FX_PARTICLE_PARSER(RenderObjectUpdateModuleTemplate, 0x00C6C710)
FX_PARTICLE_PARSER(RenderObjectDrawModuleTemplate, 0x00C6C8E0)
FX_PARTICLE_PARSER(LifeEventModuleTemplate, 0x00C6CAC0)
FX_PARTICLE_PARSER(TerrainCollisionModuleTemplate, 0x00C6CB68)

#undef FX_PARTICLE_PARSER
}
