// cl: /O1 /EHs-c-
// ?Rva003AD5D7Init@@YAXXZ @0x003AD5D7 33B guarded initializer calling rowed OUTWARD_EMISSION_VELOCITY ConcreteModuleClass getInstance at 0x003AB2FF then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8062 (RVA 0x007B8062 ret). Evidence: caller staticInitModules at 0x003AE3E0; prev 0x003AD5B6 Rva003AD5B6Init; guard data VA 0x00E02C20.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class OutwardEmissionVelocityModule;
class OutwardEmissionVelocityModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const OUTWARD_EMISSION_VELOCITY_MODULE_NAME;
typedef ModuleTag<4, OUTWARD_EMISSION_VELOCITY_MODULE_KEY, OUTWARD_EMISSION_VELOCITY_MODULE_NAME, OutwardEmissionVelocityModule, OutwardEmissionVelocityModuleTemplate, DefaultParticleModule<4> > OutwardEmissionVelocityTag;
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
struct Holder003AD5D7
{
	Holder003AD5D7() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::OutwardEmissionVelocityTag>::getInstance(); }
	~Holder003AD5D7();
};
void __cdecl Rva003AD5D7Init()
{
	static Holder003AD5D7 s_holder;
}
