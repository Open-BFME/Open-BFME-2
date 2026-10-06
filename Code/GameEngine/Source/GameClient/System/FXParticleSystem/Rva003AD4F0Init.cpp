// cl: /EHs-c-
// ?Rva003AD4F0Init@@YAXXZ @0x003AD4F0 33B guarded initializer calling rowed LIFE_EVENT ConcreteModuleClass getInstance at 0x003AADF8 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8069 (RVA 0x007B8069 ret). Evidence: caller staticInitModules at 0x003AE39F; prev 0x003AD4CF Rva003AD4CFInit; guard data VA 0x00E02C04.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class ParticleLifeEventModule;
class LifeEventModule;
class LifeEventModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const LIFE_EVENT_MODULE_KEY;
extern const char *const LIFE_EVENT_MODULE_NAME;
typedef ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule> LifeEventTag;
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
struct Holder003AD4F0
{
	Holder003AD4F0() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::LifeEventTag>::getInstance(); }
	~Holder003AD4F0();
};
void __cdecl Rva003AD4F0Init()
{
	static Holder003AD4F0 s_holder;
}
