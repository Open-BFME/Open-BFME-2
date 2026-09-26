// cl: /O1 /MD
// ??_GAudioLoopUpgradeModuleData@@UAEPAXI@Z @0x004B7EBD 28B
// Deleting dtor slot 0 of vtable 0x00858CF8; calls rowed ??1AudioLoopUpgradeModuleData@@UAE@XZ at 0x004B7C4C then rowed operator delete at 0x0002FD60.
class AudioLoopUpgradeModuleData { public: __declspec(noinline) virtual ~AudioLoopUpgradeModuleData(); private: int m_famgen; };
AudioLoopUpgradeModuleData::~AudioLoopUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(AudioLoopUpgradeModuleData *p) { delete p; }
