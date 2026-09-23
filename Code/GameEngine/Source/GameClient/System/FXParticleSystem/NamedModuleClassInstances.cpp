// cl: /O1 /EHs-c-
// FXParticleSystem module-class singletons for the named ModuleTag
// instantiations: ConcreteModuleClass<TAG>::getInstance and the
// ConcreteModuleTemplate<TAG>::getClass accessor that forwards to it.
//
// Identity: every function here is exported under its decorated name
// (reverse/exports.csv); the tag arguments below are read back out of those
// names. getInstance is a guarded function-local static: construct once
// through the class's private constructor, register the destructor with
// atexit, return the object. getClass is a tail jump into it.
//
// FXParticleSystemModules.cpp models the same classes with a class-static
// instance for their constructors and createTemplate; the retail accessor is
// the function-local form, so it lives in its own unit.

namespace FXParticleSystem
{

template <int CATEGORY>
class DefaultParticleModule;
class ParticleLifeEventModule;
class ParticleTerrainCollisionModule;
class RenderObjectParticleUpdateModule;

template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE,
	class TEMPLATE, class DEFAULT>
class ModuleTag
{
};

template <class TAG>
class ConcreteModuleClass
{
public:
	__declspec(noinline) static const ConcreteModuleClass<TAG> &getInstance();
	~ConcreteModuleClass();

private:
	ConcreteModuleClass();

	void *m_words[4];
};

template <class TAG>
class ConcreteModuleTemplate
{
public:
	virtual const ConcreteModuleClass<TAG> &getClass() const;
};

template <class TAG>
const ConcreteModuleClass<TAG> &ConcreteModuleClass<TAG>::getInstance()
{
	static ConcreteModuleClass<TAG> s_instance;
	return s_instance;
}

template <class TAG>
const ConcreteModuleClass<TAG> &ConcreteModuleTemplate<TAG>::getClass() const
{
	return ConcreteModuleClass<TAG>::getInstance();
}

#define FX_NAMED_TAG(CATEGORY, KEY, MOD, DEFAULT)                                             	extern const char *const KEY##_MODULE_KEY;                                            	extern const char *const KEY##_MODULE_NAME;                                           	class MOD;                                                                            	class MOD##Template;                                                                  	typedef ModuleTag<CATEGORY, KEY##_MODULE_KEY, KEY##_MODULE_NAME, MOD, MOD##Template,   		DEFAULT > MOD##Tag;                                                            	template const ConcreteModuleClass<MOD##Tag> &ConcreteModuleClass<MOD##Tag>::getInstance(); 	template const ConcreteModuleClass<MOD##Tag> &ConcreteModuleTemplate<MOD##Tag>::getClass() const;

FX_NAMED_TAG(2, RENDEROBJECT_UPDATE, RenderObjectUpdateModule, RenderObjectParticleUpdateModule)
FX_NAMED_TAG(4, CYLINDRICAL_EMISSION_VELOCITY, CylindricalEmissionVelocityModule, DefaultParticleModule<4>)
FX_NAMED_TAG(4, HEMISPHERICAL_EMISSION_VELOCITY, HemisphericalEmissionVelocityModule, DefaultParticleModule<4>)
FX_NAMED_TAG(4, OUTWARD_EMISSION_VELOCITY, OutwardEmissionVelocityModule, DefaultParticleModule<4>)
FX_NAMED_TAG(4, SPHERICAL_EMISSION_VELOCITY, SphericalEmissionVelocityModule, DefaultParticleModule<4>)
FX_NAMED_TAG(5, BOX_EMISSION_VOLUME, BoxEmissionVolumeModule, DefaultParticleModule<5>)
FX_NAMED_TAG(5, CYLINDER_EMISSION_VOLUME, CylinderEmissionVolumeModule, DefaultParticleModule<5>)
FX_NAMED_TAG(5, LIGHTNING_EMISSION, LightningEmissionModule, DefaultParticleModule<5>)
FX_NAMED_TAG(5, LINE_EMISSION_VOLUME, LineEmissionVolumeModule, DefaultParticleModule<5>)
FX_NAMED_TAG(5, SPHERE_EMISSION_VOLUME, SphereEmissionVolumeModule, DefaultParticleModule<5>)
FX_NAMED_TAG(5, TERRAIN_FIRE_EMISSION, TerrainFireEmissionModule, DefaultParticleModule<5>)
FX_NAMED_TAG(6, BUTTERFLY_DRAW, ButterflyDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(6, GPU_DRAW, GpuDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(6, LIGHTNING_DRAW, LightningDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(6, QUAD_DRAW, QuadDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(6, RENDEROBJECT_DRAW, RenderObjectDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(6, STREAK_DRAW, StreakDrawModule, DefaultParticleModule<6>)
FX_NAMED_TAG(8, LIFE_EVENT, LifeEventModule, ParticleLifeEventModule)
FX_NAMED_TAG(8, TERRAIN_COLLISION, TerrainCollisionModule, ParticleTerrainCollisionModule)

#undef FX_NAMED_TAG

}
