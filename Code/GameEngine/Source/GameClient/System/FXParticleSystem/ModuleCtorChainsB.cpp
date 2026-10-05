// cl: -DNDEBUG -MD -GX- /Os
// ??0Rva003AA228@FXParticleSystem@@QAE@PAX0@Z @0x003AA228 42B
// ??0?$DefaultParticleModule@$03@FXParticleSystem@@QAE@PAX0@Z @0x003AC180 35B
// ??0?$DefaultParticleModule@$04@FXParticleSystem@@QAE@PAX0@Z @0x003ABF54 49B
// ??0BoxEmissionVolumeModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVBoxEmissionVolumeModuleTemplate@1@@Z @0x003AC034 75B
// ??0SphereEmissionVolumeModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVSphereEmissionVolumeModuleTemplate@1@@Z @0x003AC087 75B
// ??0TerrainFireEmissionModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVTerrainFireEmissionModuleTemplate@1@@Z @0x003AC12D 75B
// ??0OrthoEmissionVelocityModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVOrthoEmissionVelocityModuleTemplate@1@@Z @0x003AC1A3 68B
// ??0SphericalEmissionVelocityModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVSphericalEmissionVelocityModuleTemplate@1@@Z @0x003AC1F7 68B
// ??0CylindricalEmissionVelocityModule@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVCylindricalEmissionVelocityModuleTemplate@1@@Z @0x003AC24B 68B
// ??0Rva003AC297Module@FXParticleSystem@@QAE@AAV?$TrackingPtr@VParticleSystem@FXParticleSystem@@@1@PBVRva003AC297ModuleTemplate@1@@Z @0x003AC297 68B
// ??0Rva003ACCAD@@QAE@PAX0@Z @0x003ACCAD 49B
// ??0Rva003ACCDE@@QAE@PAX0@Z @0x003ACCDE 49B
// ??0Rva003ACD40@@QAE@PAX0@Z @0x003ACD40 49B
// ??0Rva003ACB79@@QAE@PAX0@Z @0x003ACB79 42B
// ??0Rva003ACBA3@@QAE@PAX0@Z @0x003ACBA3 42B
// ??0Rva003ACBCD@@QAE@PAX0@Z @0x003ACBCD 42B
// ??0Rva003ACBF7@@QAE@PAX0@Z @0x003ACBF7 42B
// ??0Rva003ACC21@@QAE@PAX0@Z @0x003ACC21 42B
// ??0Rva003AD16CModule@@QAE@PAXPAVRva003ADA72Template@@@Z @0x003AD16C 42B
// ??0Rva003AD19BModule@@QAE@PAXPAVRva003ADA95Template@@@Z @0x003AD19B 42B
// ??0Rva003AD1CAModule@@QAE@PAXPAVRva003ADAB8Template@@@Z @0x003AD1CA 42B
// ??0Rva003AD1F9Module@@QAE@PAXPAVRva003ADADBTemplate@@@Z @0x003AD1F9 42B
// ??0Rva003AD228Module@@QAE@PAXPAVRva003ADAFETemplate@@@Z @0x003AD228 42B
// ??0Rva003AD2E9Module@@QAE@PAXPAVRva003ADB67Template@@@Z @0x003AD2E9 49B
// ??0Rva003AD31FModule@@QAE@PAXPAVRva003ADB8ATemplate@@@Z @0x003AD31F 49B
// ??0Rva003AD3C1Module@@QAE@PAXPAVRva003ADC0FTemplate@@@Z @0x003AD3C1 49B
//
// The particle-module constructors under the emission volume and velocity
// modules, ported from the Open-BFME-1 donors
// game/GameEngine/Source/GameClient/System/FXParticleSystem/BoxEmissionVolumeModuleCtor.cpp
// and EmissionVelocityModuleCtors.cpp (the same shape as the rowed
// PointEmissionVolumeModule and LightningEmissionModule constructors).
//
// BFME 2 differs from the donors in one place: DefaultParticleModule<N> is not
// inlined, and it sits on one more out-of-line base, 0x003AA228, which owns the
// rowed DefaultModuleHeadBase at +0 and an interface slice at +0x14 whose
// implicit constructor stamps that slice before 0x003AA228 restamps both. The
// category-5 module adds a second slice at +0x18 the same way (retail stamps
// +0x18 twice); the category-4 module adds none. Category numbers are the
// donor's; the 0x003ABF54 spelling is the ledger's existing pin.
//
// Each module constructor forwards (system, template) to its DefaultParticleModule
// and copy-constructs its Info base from the template's Info base at +8 (the
// rowed copy constructors named below), then stamps its own vtables. Module names
// follow the donor and the Info each one copies; 0x003AC297 copies the
// Cylindrical Info and stamps the Cylindrical Info vtable but has its own +0
// vtable, so it keeps an address name. Vtable identities are not modelled
// beyond the subobject layout.

class RvaSmartPtr12;

class DefaultModuleHeadBase
{
public:
	DefaultModuleHeadBase( const RvaSmartPtr12 &smart, int i );
	virtual ~DefaultModuleHeadBase();

private:
	unsigned int m_storage[ 4 ];
};

namespace FXParticleSystem
{

class ParticleSystem;

template <class T>
class TrackingPtr
{
};

class Rva003AA228Slice
{
public:
	virtual void unusedVirtual();
};

class Rva003AA228 : public DefaultModuleHeadBase, public Rva003AA228Slice
{
public:
	Rva003AA228( void *system, void *module_template );
};

Rva003AA228::Rva003AA228( void *system, void *module_template )
	: DefaultModuleHeadBase( *reinterpret_cast<const RvaSmartPtr12 *>( system ),
		reinterpret_cast<int>( module_template ) )
{
}

class DefaultParticleModuleSnapshotSlice
{
public:
	virtual void unusedVirtual();
};

template <int Category>
class DefaultParticleModule;

template <>
class DefaultParticleModule<4> : public Rva003AA228
{
public:
	DefaultParticleModule( void *system, void *module_template );
};

DefaultParticleModule<4>::DefaultParticleModule( void *system, void *module_template )
	: Rva003AA228( system, module_template )
{
}

template <>
class DefaultParticleModule<5>
	: public Rva003AA228, public DefaultParticleModuleSnapshotSlice
{
public:
	DefaultParticleModule( void *system, void *module_template );
};

DefaultParticleModule<5>::DefaultParticleModule( void *system, void *module_template )
	: Rva003AA228( system, module_template )
{
}

class EmissionVolumeInfo
{
public:
	virtual void unusedVirtual();

private:
	bool m_flag;
};

class BoxEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
	BoxEmissionVolumeInfo( const BoxEmissionVolumeInfo &that );

private:
	float m_extents[ 3 ];
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
public:
	SphereEmissionVolumeInfo( const SphereEmissionVolumeInfo &that );
};

class TerrainFireEmissionInfo : public EmissionVolumeInfo
{
public:
	TerrainFireEmissionInfo( const TerrainFireEmissionInfo &that );
};

class EmissionVelocityInfo
{
public:
	virtual void unusedVirtual();
};

class OrthoEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	OrthoEmissionVelocityInfo( const OrthoEmissionVelocityInfo &that );
};

class SphericalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	SphericalEmissionVelocityInfo( const SphericalEmissionVelocityInfo &that );
};

class CylindricalEmissionVelocityInfo : public EmissionVelocityInfo
{
public:
	CylindricalEmissionVelocityInfo( const CylindricalEmissionVelocityInfo &that );
};

class ModuleTemplateSlice
{
public:
	virtual void unusedVirtual();
};

class CategoryModuleTemplateInfoSlice
{
public:
	virtual void unusedVirtual();
};

class CategoryModuleTemplateSlice
	: public ModuleTemplateSlice, public CategoryModuleTemplateInfoSlice
{
};

#define PARTICLE_INFO_MODULE( MODULE, INFO, CATEGORY )                       \
	class MODULE##Template                                                   \
		: public CategoryModuleTemplateSlice, public INFO                     \
	{                                                                        \
	};                                                                       \
	class MODULE : public DefaultParticleModule<CATEGORY>, public INFO        \
	{                                                                        \
	public:                                                                  \
		MODULE( TrackingPtr<ParticleSystem> &system,                          \
			const MODULE##Template *module_template );                         \
	};                                                                       \
	MODULE::MODULE( TrackingPtr<ParticleSystem> &system,                      \
		const MODULE##Template *module_template )                             \
		: DefaultParticleModule<CATEGORY>( &system,                            \
			const_cast<MODULE##Template *>( module_template ) ),                \
		  INFO( *module_template )                                            \
	{                                                                        \
	}

PARTICLE_INFO_MODULE( BoxEmissionVolumeModule, BoxEmissionVolumeInfo, 5 )
PARTICLE_INFO_MODULE( SphereEmissionVolumeModule, SphereEmissionVolumeInfo, 5 )
PARTICLE_INFO_MODULE( TerrainFireEmissionModule, TerrainFireEmissionInfo, 5 )
PARTICLE_INFO_MODULE( OrthoEmissionVelocityModule, OrthoEmissionVelocityInfo, 4 )
PARTICLE_INFO_MODULE( SphericalEmissionVelocityModule, SphericalEmissionVelocityInfo, 4 )
PARTICLE_INFO_MODULE( CylindricalEmissionVelocityModule, CylindricalEmissionVelocityInfo, 4 )
PARTICLE_INFO_MODULE( Rva003AC297Module, CylindricalEmissionVelocityInfo, 4 )

}

// ---- the two links above them ----------------------------------------------
//
// Each intermediate forwards (system, template) to one module constructor above
// (0x003ACBCD to the 0x003ACBA3 intermediate instead), and each pinned module
// constructor -- the ones the slot-2 template factories in
// ModuleTemplateFactorySlots.cpp call -- forwards to one intermediate; both then
// restamp every subobject vtable. ModuleCtorChainsA.cpp holds the same two links
// over other modules. Address-named: retail gives the call targets and the
// layout, nothing more.

typedef FXParticleSystem::TrackingPtr<FXParticleSystem::ParticleSystem> RvaParticleSystemPtr;

#define PARTICLE_MODULE_INTERMEDIATE( NAME, MODULE )                            \
	class NAME : public FXParticleSystem::MODULE                                \
	{                                                                         \
	public:                                                                   \
		NAME( void *system, void *module_template );                            \
	};                                                                        \
	NAME::NAME( void *system, void *module_template )                           \
		: FXParticleSystem::MODULE( *static_cast<RvaParticleSystemPtr *>( system ), \
			static_cast<const FXParticleSystem::MODULE##Template *>( module_template ) ) \
	{                                                                         \
	}

#define PARTICLE_MODULE_FINAL( NAME, TEMPLATE, BASE )                           \
	class TEMPLATE;                                                           \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		NAME( void *owner, TEMPLATE *module_template );                         \
	};                                                                        \
	NAME::NAME( void *owner, TEMPLATE *module_template )                        \
		: BASE( owner, module_template )                                       \
	{                                                                         \
	}

PARTICLE_MODULE_INTERMEDIATE( Rva003ACCAD, BoxEmissionVolumeModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACCDE, SphereEmissionVolumeModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACD40, TerrainFireEmissionModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACB79, OrthoEmissionVelocityModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACBA3, SphericalEmissionVelocityModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACBF7, CylindricalEmissionVelocityModule )
PARTICLE_MODULE_INTERMEDIATE( Rva003ACC21, Rva003AC297Module )

class Rva003ACBCD : public Rva003ACBA3
{
public:
	Rva003ACBCD( void *system, void *module_template );
};

Rva003ACBCD::Rva003ACBCD( void *system, void *module_template )
	: Rva003ACBA3( system, module_template )
{
}

PARTICLE_MODULE_FINAL( Rva003AD16CModule, Rva003ADA72Template, Rva003ACB79 )
PARTICLE_MODULE_FINAL( Rva003AD19BModule, Rva003ADA95Template, Rva003ACBA3 )
PARTICLE_MODULE_FINAL( Rva003AD1CAModule, Rva003ADAB8Template, Rva003ACBCD )
PARTICLE_MODULE_FINAL( Rva003AD1F9Module, Rva003ADADBTemplate, Rva003ACBF7 )
PARTICLE_MODULE_FINAL( Rva003AD228Module, Rva003ADAFETemplate, Rva003ACC21 )
PARTICLE_MODULE_FINAL( Rva003AD2E9Module, Rva003ADB67Template, Rva003ACCAD )
PARTICLE_MODULE_FINAL( Rva003AD31FModule, Rva003ADB8ATemplate, Rva003ACCDE )
PARTICLE_MODULE_FINAL( Rva003AD3C1Module, Rva003ADC0FTemplate, Rva003ACD40 )
