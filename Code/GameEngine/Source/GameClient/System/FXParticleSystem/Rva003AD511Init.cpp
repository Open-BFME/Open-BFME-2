// cl: /O1 /EHs-c-
// ?Rva003AD511Init@@YAXXZ @0x003AD511 33B guarded initializer calling rowed RENDEROBJECT_UPDATE ConcreteModuleClass getInstance at 0x003AAF77 then rowed atexit at 0x006291F8 registering cleanup VA 0x00BB8068 (RVA 0x007B8068 ret). Evidence: caller staticInitModules at 0x003AE3C2; prev 0x003AD4F0 Rva003AD4F0Init; guard data VA 0x00E02C08.
namespace FXParticleSystem
{
template <int CATEGORY>
class DefaultParticleModule;
class RenderObjectParticleUpdateModule;
class RenderObjectUpdateModule;
class RenderObjectUpdateModuleTemplate;
template <int CATEGORY, const char *const &KEY, const char *const &NAME, class MODULE, class TEMPLATE, class DEFAULT>
class ModuleTag
{
};
extern const char *const RENDEROBJECT_UPDATE_MODULE_KEY;
extern const char *const RENDEROBJECT_UPDATE_MODULE_NAME;
typedef ModuleTag<2, RENDEROBJECT_UPDATE_MODULE_KEY, RENDEROBJECT_UPDATE_MODULE_NAME, RenderObjectUpdateModule, RenderObjectUpdateModuleTemplate, RenderObjectParticleUpdateModule> RenderObjectUpdateTag;
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
struct Holder003AD511
{
	Holder003AD511() { FXParticleSystem::ConcreteModuleClass<FXParticleSystem::RenderObjectUpdateTag>::getInstance(); }
	~Holder003AD511();
};
void __cdecl Rva003AD511Init()
{
	static Holder003AD511 s_holder;
}
