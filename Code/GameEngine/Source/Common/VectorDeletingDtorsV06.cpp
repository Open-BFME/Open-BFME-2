// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/fxparticle_link
// Retail tables C1C2F4 and C1C314 identify the named category-8 wrappers.
// Their canonical module base and existing constructors emit both delete thunks.
#include "ModuleTemplate.h"
#include <new>
#include "../../Include/GameClient/EventModuleInfo.h"
namespace FXParticleSystem {
class SecondaryModuleBase { public: virtual ~SecondaryModuleBase(); virtual void v1() = 0; };
class ModuleInfo {};
template <int Category> class CategoryModuleTemplate;
template <> class CategoryModuleTemplate<8> : public ModuleTemplate, public SecondaryModuleBase, public EventModuleInfo { public: virtual ~CategoryModuleTemplate(); };
class LifeEventModuleInfo {
public: virtual ~LifeEventModuleInfo(); virtual void v1() = 0;
private: void *m_name; unsigned int m_values[3]; unsigned int m_eventType;
};
class TerrainCollisionModuleInfo {
public: virtual ~TerrainCollisionModuleInfo(); virtual void v1() = 0;
private: void *m_eventName; unsigned int m_eventTime[3]; bool m_flag; unsigned int m_cached;
};
class LifeEventModuleTemplate : public CategoryModuleTemplate<8>, public LifeEventModuleInfo { public: LifeEventModuleTemplate(); virtual ~LifeEventModuleTemplate(); };
class TerrainCollisionModuleTemplate : public CategoryModuleTemplate<8>, public TerrainCollisionModuleInfo { public: TerrainCollisionModuleTemplate(); virtual ~TerrainCollisionModuleTemplate(); };
class LifeEventModule;
class TerrainCollisionModule;
class ParticleLifeEventModule;
class ParticleTerrainCollisionModule;
extern const char *const LIFE_EVENT_MODULE_KEY;
extern const char *const LIFE_EVENT_MODULE_NAME;
extern const char *const TERRAIN_COLLISION_MODULE_KEY;
extern const char *const TERRAIN_COLLISION_MODULE_NAME;
template <int Category, const char *const &Key, const char *const &Name, class Module, class Template, class Default>
class ModuleTag { public: typedef Template TemplateType; };
template <class Tag> class ConcreteModuleTemplate : public Tag::TemplateType {
public:
 ConcreteModuleTemplate() {}
 virtual ~ConcreteModuleTemplate();
 virtual void v1();
 virtual typename Tag::TemplateType *clone() const;
};
typedef ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT_MODULE_KEY, LIFE_EVENT_MODULE_NAME, LifeEventModule, LifeEventModuleTemplate, ParticleLifeEventModule> > LifeEventConcrete;
typedef ConcreteModuleTemplate<ModuleTag<8, TERRAIN_COLLISION_MODULE_KEY, TERRAIN_COLLISION_MODULE_NAME, TerrainCollisionModule, TerrainCollisionModuleTemplate, ParticleTerrainCollisionModule> > TerrainCollisionConcrete;
typedef char LifeSize[(sizeof(LifeEventConcrete) == 0x24) ? 1 : -1];
typedef char TerrainSize[(sizeof(TerrainCollisionConcrete) == 0x28) ? 1 : -1];
}
// ?<bfmeVectorDeleteAnchorV06> absent-from-retail
void bfmeVectorDeleteAnchorV06() {
 new FXParticleSystem::LifeEventConcrete[2];
 new FXParticleSystem::TerrainCollisionConcrete[2];
}
