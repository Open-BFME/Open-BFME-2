// cl: /O1 /EHs-c-
// ?Rva003AD6BEInit@@YAXXZ @0x003AD6BE 33B guarded initializer calling rowed TERRAIN_FIRE_EMISSION ConcreteModuleClass getInstance at 0x003AB703 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB805B (RVA 0x007B805B ret). Evidence: caller staticInitModules at 0x003AE403; prev 0x003AD69D Rva003AD69DInit; guard data VA 0x00E02C3C.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class TerrainFireEmissionModule;
class TerrainFireEmissionModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_KEY;
extern const char *const TERRAIN_FIRE_EMISSION_MODULE_NAME;
typedef ModuleTag<5, TERRAIN_FIRE_EMISSION_MODULE_KEY, TERRAIN_FIRE_EMISSION_MODULE_NAME, TerrainFireEmissionModule, TerrainFireEmissionModuleTemplate, DefaultParticleModule<5> > TerrainFireEmissionTag;
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
struct Holder003AD6BE
{
	Holder003AD6BE() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::TerrainFireEmissionTag>::getInstance(); }
	~Holder003AD6BE();
};
void __cdecl Rva003AD6BEInit()
{
	static Holder003AD6BE s_holder;
}
