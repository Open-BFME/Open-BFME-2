// cl: /O1 /MD
// Each class redeclares its public virtual destructor and defines it locally,
// which emits the scalar deleting destructor in this TU; the dtor call inside
// resolves through that destructor's own row (same pattern as spec_gdtor).

// ??_GPassiveAreaEffectBehaviorModuleData@@UAEPAXI@Z @0x484e8d
class PassiveAreaEffectBehaviorModuleData { public: __declspec(noinline) virtual ~PassiveAreaEffectBehaviorModuleData(); private: int m_famgen;
  friend void famgenDelete(PassiveAreaEffectBehaviorModuleData *p); };
PassiveAreaEffectBehaviorModuleData::~PassiveAreaEffectBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(PassiveAreaEffectBehaviorModuleData *p) { delete p; }

// ??_GPassiveAreaEffectBehavior@@UAEPAXI@Z @0x484c3c
class PassiveAreaEffectBehavior { public: __declspec(noinline) virtual ~PassiveAreaEffectBehavior(); private: int m_famgen;
  friend void famgenDelete(PassiveAreaEffectBehavior *p); };
PassiveAreaEffectBehavior::~PassiveAreaEffectBehavior() { m_famgen = 0; }
void famgenDelete(PassiveAreaEffectBehavior *p) { delete p; }
