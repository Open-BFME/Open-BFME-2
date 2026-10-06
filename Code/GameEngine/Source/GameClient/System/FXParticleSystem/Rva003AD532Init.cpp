// cl: /EHs-c-
// ?Rva003AD532Init@@YAXXZ @0x003AD532 33B guarded initializer calling rowed TERRAIN_COLLISION ConcreteModuleClass getInstance at 0x003AB028 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8067 (RVA 0x007B8067 ret). Evidence: caller staticInitModules at 0x003AE3C7; prev 0x003AD511 Rva003AD511Init; guard data VA 0x00E02C0C.
namespace FXParticleSystem
{
class ParticleTerrainCollisionModule;
class TerrainCollisionModule;
class TerrainCollisionModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const TERRAIN_COLLISION_MODULE_KEY;
extern const char *const TERRAIN_COLLISION_MODULE_NAME;
typedef ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule> TerrainCollisionTag;
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
struct Holder003AD532
{
	Holder003AD532() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::TerrainCollisionTag>::getInstance(); }
	~Holder003AD532();
};
void __cdecl Rva003AD532Init()
{
	static Holder003AD532 s_holder;
}
