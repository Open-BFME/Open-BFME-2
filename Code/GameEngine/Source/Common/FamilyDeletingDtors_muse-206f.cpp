// cl: /MD
//
// ??_GAutoAbilityBehaviorModuleData@@UAEPAXI@Z, retail 0x0045A4FB, 28 bytes.
// Scalar deleting dtor (slot 0) for AutoAbilityBehaviorModuleData: calls the
// rowed ??1 at 0x0045A517 then operator delete at 0x0002FD60 when flag set.
// Shape follows FamilyDeletingDtors precedent (public virtual dtor with
// noinline plus famgenDelete emitting the ??_G; dtor call resolves via its
// row). Needs the ??1 row to exist.

// ??_GAutoAbilityBehaviorModuleData@@UAEPAXI@Z @0x45a4fb
class AutoAbilityBehaviorModuleData { public: __declspec(noinline) virtual ~AutoAbilityBehaviorModuleData(); private: int m_famgen; };
AutoAbilityBehaviorModuleData::~AutoAbilityBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(AutoAbilityBehaviorModuleData *p) { delete p; }
