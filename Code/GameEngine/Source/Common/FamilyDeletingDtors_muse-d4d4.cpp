// cl: /O1 /MD
// ??_GSpecialPowerModuleData@@UAEPAXI@Z @0x00548A09 slot 0 of vtable 0x86A520.
// Follows the FamilyDeletingDtors precedent (e.g. muse-a8e6 for
// W3DStreakDrawModuleData): trivial local dtor emits the deleting wrapper;
// its call resolves through the rowed ??1 at 0x548948 plus delete at 0x2FD60.
class SpecialPowerModuleData { public: __declspec(noinline) virtual ~SpecialPowerModuleData(); private: int m_famgen; };
SpecialPowerModuleData::~SpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(SpecialPowerModuleData *p) { delete p; }
