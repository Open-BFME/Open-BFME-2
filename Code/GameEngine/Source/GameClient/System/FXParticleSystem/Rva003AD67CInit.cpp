// cl: /O1 /EHs-c-
// ?Rva003AD67CInit@@YAXXZ @0x003AD67C 33B guarded initializer calling rowed CYLINDER_EMISSION_VOLUME ConcreteModuleClass getInstance at 0x003AB5CA then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB805D (RVA 0x007B805D ret). Evidence: caller staticInitModules at 0x003AE3F9; prev 0x003AD65B Rva003AD65BInit; guard data VA 0x00E02C34.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class CylinderEmissionVolumeModule;
class CylinderEmissionVolumeModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_KEY;
extern const char *const CYLINDER_EMISSION_VOLUME_MODULE_NAME;
typedef ModuleTag<5, CYLINDER_EMISSION_VOLUME_MODULE_KEY, CYLINDER_EMISSION_VOLUME_MODULE_NAME, CylinderEmissionVolumeModule, CylinderEmissionVolumeModuleTemplate, DefaultParticleModule<5> > CylinderEmissionVolumeTag;
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
struct Holder003AD67C
{
	Holder003AD67C() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::CylinderEmissionVolumeTag>::getInstance(); }
	~Holder003AD67C();
};
void __cdecl Rva003AD67CInit()
{
	static Holder003AD67C s_holder;
}
