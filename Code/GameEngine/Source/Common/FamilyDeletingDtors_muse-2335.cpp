// cl: /O1 /MD
// ??_GRandomSoundSelectorClientBehaviorModuleData@@UAEPAXI@Z @0x002578C2 28B
// Deleting dtor slot 0 of vtable 0x007F42A8; calls rowed ??1 at 0x002578DE then rowed operator delete at 0x0002FD60.
class RandomSoundSelectorClientBehaviorModuleData { public: __declspec(noinline) virtual ~RandomSoundSelectorClientBehaviorModuleData(); private: int m_famgen; };
// ??1RandomSoundSelectorClientBehaviorModuleData@@UAE@XZ present-unmatched
RandomSoundSelectorClientBehaviorModuleData::~RandomSoundSelectorClientBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(RandomSoundSelectorClientBehaviorModuleData *p) { delete p; }
