// cl: /O1 /EHs-c-
// ?Rva003AD619Init@@YAXXZ @0x003AD619 33B guarded initializer calling rowed LINE_EMISSION_VOLUME ConcreteModuleClass getInstance at 0x003AB432 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8060 (RVA 0x007B8060 ret). Evidence: caller staticInitModules at 0x003AE3EA; prev 0x003AD5F8 Rva003AD5F8Init; guard data VA 0x00E02C28.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class LineEmissionVolumeModule;
class LineEmissionVolumeModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const LINE_EMISSION_VOLUME_MODULE_KEY;
extern const char *const LINE_EMISSION_VOLUME_MODULE_NAME;
typedef ModuleTag<5, LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME, LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate, DefaultParticleModule<5> > LineEmissionVolumeTag;
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
struct Holder003AD619
{
	Holder003AD619() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::LineEmissionVolumeTag>::getInstance(); }
	~Holder003AD619();
};
void __cdecl Rva003AD619Init()
{
	static Holder003AD619 s_holder;
}
