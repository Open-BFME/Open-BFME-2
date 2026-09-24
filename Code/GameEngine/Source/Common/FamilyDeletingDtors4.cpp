// cl: /O1 /MD
// Each class is declared locally so its deleting destructor is emitted;
// the retail dtor callee (a rowed UAE dtor) selects the identity.
// Same-shape family as FamilyDeletingDtors.cpp (??_GVersion 0x21C7 shape):
// virtual-dtor members with a TU-local dtor definition.

// ??_GRenderObjectDrawModuleTemplate@FXParticleSystem@@UAEPAXI@Z @0x3a9cdc
namespace FXParticleSystem { class RenderObjectDrawModuleTemplate { public: __declspec(noinline) virtual ~RenderObjectDrawModuleTemplate(); private: int m_famgen; }; }
FXParticleSystem::RenderObjectDrawModuleTemplate::~RenderObjectDrawModuleTemplate() { m_famgen = 0; }
void famgenDelete(FXParticleSystem::RenderObjectDrawModuleTemplate *p) { delete p; }

// ??_GGpuDrawModuleTemplate@FXParticleSystem@@UAEPAXI@Z @0x3a9f23
namespace FXParticleSystem { class GpuDrawModuleTemplate { public: __declspec(noinline) virtual ~GpuDrawModuleTemplate(); private: int m_famgen; }; }
FXParticleSystem::GpuDrawModuleTemplate::~GpuDrawModuleTemplate() { m_famgen = 0; }
void famgenDelete(FXParticleSystem::GpuDrawModuleTemplate *p) { delete p; }
