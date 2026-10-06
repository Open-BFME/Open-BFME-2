// cl: /EHs-c-
// ?Rva003AD65BInit@@YAXXZ @0x003AD65B 33B guarded initializer calling rowed SPHERE_EMISSION_VOLUME ConcreteModuleClass getInstance at 0x003AB542 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB805E (RVA 0x007B805E ret). Evidence: caller staticInitModules at 0x003AE3F4; prev 0x003AD63A Rva003AD63AInit; guard data VA 0x00E02C30.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class SphereEmissionVolumeModule;
class SphereEmissionVolumeModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const SPHERE_EMISSION_VOLUME_MODULE_KEY;
extern const char *const SPHERE_EMISSION_VOLUME_MODULE_NAME;
typedef ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME, SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate, DefaultParticleModule<5> > SphereEmissionVolumeTag;
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
struct Holder003AD65B
{
	Holder003AD65B() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::SphereEmissionVolumeTag>::getInstance(); }
	~Holder003AD65B();
};
void __cdecl Rva003AD65BInit()
{
	static Holder003AD65B s_holder;
}
