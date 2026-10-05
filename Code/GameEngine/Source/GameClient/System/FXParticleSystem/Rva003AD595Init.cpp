// cl: /O1 /EHs-c-
// ?Rva003AD595Init@@YAXXZ @0x003AD595 33B guarded initializer calling rowed HEMISPHERICAL_EMISSION_VELOCITY ConcreteModuleClass getInstance at 0x003AB1A9 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8064 (RVA 0x007B8064 ret). Evidence: caller staticInitModules at 0x003AE3D6; prev 0x003AD574 Rva003AD574Init; guard data VA 0x00E02C18.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class HemisphericalEmissionVelocityModule;
class HemisphericalEmissionVelocityModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME;
typedef ModuleTag<4, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY, HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME, HemisphericalEmissionVelocityModule, HemisphericalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > HemisphericalEmissionVelocityTag;
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
struct Holder003AD595
{
	Holder003AD595() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::HemisphericalEmissionVelocityTag>::getInstance(); }
	~Holder003AD595();
};
void __cdecl Rva003AD595Init()
{
	static Holder003AD595 s_holder;
}
