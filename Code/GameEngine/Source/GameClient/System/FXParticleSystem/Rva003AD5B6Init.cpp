// cl: /O1 /EHs-c-
// ?Rva003AD5B6Init@@YAXXZ @0x003AD5B6 33B guarded initializer calling rowed CYLINDRICAL_EMISSION_VELOCITY ConcreteModuleClass getInstance at 0x003AB254 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8063 (RVA 0x007B8063 ret). Evidence: caller staticInitModules at 0x003AE3DB; prev 0x003AD595 Rva003AD595Init; guard data VA 0x00E02C1C.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class CylindricalEmissionVelocityModule;
class CylindricalEmissionVelocityModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY;
extern const char *const CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME;
typedef ModuleTag<4, CYLINDRICAL_EMISSION_VELOCITY_MODULE_KEY, CYLINDRICAL_EMISSION_VELOCITY_MODULE_NAME, CylindricalEmissionVelocityModule, CylindricalEmissionVelocityModuleTemplate, DefaultParticleModule<4> > CylindricalEmissionVelocityTag;
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
struct Holder003AD5B6
{
	Holder003AD5B6() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::CylindricalEmissionVelocityTag>::getInstance(); }
	~Holder003AD5B6();
};
void __cdecl Rva003AD5B6Init()
{
	static Holder003AD5B6 s_holder;
}
