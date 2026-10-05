// cl: /O1 /EHs-c-
// ?Rva003AD63AInit@@YAXXZ @0x003AD63A 33B guarded initializer calling rowed BOX_EMISSION_VOLUME ConcreteModuleClass getInstance at 0x003AB4BA then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB805F (RVA 0x007B805F ret). Evidence: caller staticInitModules at 0x003AE3EF; prev 0x003AD619 Rva003AD619Init; guard data VA 0x00E02C2C.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class BoxEmissionVolumeModule;
class BoxEmissionVolumeModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const BOX_EMISSION_VOLUME_MODULE_KEY;
extern const char *const BOX_EMISSION_VOLUME_MODULE_NAME;
typedef ModuleTag<5, BOX_EMISSION_VOLUME_MODULE_KEY, BOX_EMISSION_VOLUME_MODULE_NAME, BoxEmissionVolumeModule, BoxEmissionVolumeModuleTemplate, DefaultParticleModule<5> > BoxEmissionVolumeTag;
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
struct Holder003AD63A
{
	Holder003AD63A() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::BoxEmissionVolumeTag>::getInstance(); }
	~Holder003AD63A();
};
void __cdecl Rva003AD63AInit()
{
	static Holder003AD63A s_holder;
}
