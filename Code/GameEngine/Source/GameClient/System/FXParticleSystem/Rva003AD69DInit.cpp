// cl: /O1 /EHs-c-
// ?Rva003AD69DInit@@YAXXZ @0x003AD69D 33B guarded initializer calling rowed LIGHTNING_EMISSION ConcreteModuleClass getInstance at 0x003AB652 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB805C (RVA 0x007B805C ret). Evidence: caller staticInitModules at 0x003AE3FE; prev 0x003AD67C Rva003AD67CInit; guard data VA 0x00E02C38.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class LightningEmissionModule;
class LightningEmissionModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const LIGHTNING_EMISSION_MODULE_KEY;
extern const char *const LIGHTNING_EMISSION_MODULE_NAME;
typedef ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME, LightningEmissionModule, LightningEmissionModuleTemplate, DefaultParticleModule<5> > LightningEmissionTag;
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
struct Holder003AD69D
{
	Holder003AD69D() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::LightningEmissionTag>::getInstance(); }
	~Holder003AD69D();
};
void __cdecl Rva003AD69DInit()
{
	static Holder003AD69D s_holder;
}
