// cl: /EHs-c-
// ?Rva003AD574Init@@YAXXZ @0x003AD574 33B guarded initializer calling rowed SPHERICAL_EMISSION_VELOCITY ConcreteModuleClass getInstance at 0x003AB0FE then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8065 (RVA 0x007B8065 ret). Evidence: caller staticInitModules at 0x003AE3D1; prev 0x003AD553 Rva003AD553Init; guard data VA 0x00E02C14.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const SPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
typedef ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME, SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > SphericalEmissionVelocityTag;
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
}
struct Holder003AD574
{
	Holder003AD574() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::SphericalEmissionVelocityTag>::getInstance(); }
	~Holder003AD574();
};
void __cdecl Rva003AD574Init()
{
	static Holder003AD574 s_holder;
}
