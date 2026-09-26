// cl: /O1 /MD
// ??_GReplaceSelfUpgradeModuleData@@UAEPAXI@Z @0x004B795E 28B
// Deleting dtor slot 0 of vtable 0x00858B40; calls rowed ??1ReplaceSelfUpgradeModuleData@@UAE@XZ at 0x004B797A then rowed operator delete at 0x0002FD60.
class ReplaceSelfUpgradeModuleData { public: __declspec(noinline) virtual ~ReplaceSelfUpgradeModuleData(); private: int m_famgen; };
ReplaceSelfUpgradeModuleData::~ReplaceSelfUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(ReplaceSelfUpgradeModuleData *p) { delete p; }

// ??_GReplaceSelfUpgrade@@MAEPAXI@Z @0x004B70CF 28B
// Deleting dtor slot 0 of vtable 0x00858B10; calls rowed ??1ReplaceSelfUpgrade@@MAE@XZ at 0x004B70EB then rowed operator delete at 0x0002FD60.
class ReplaceSelfUpgrade { protected: __declspec(noinline) virtual ~ReplaceSelfUpgrade(); private: int m_famgen;
  friend void famgenDelete(ReplaceSelfUpgrade *p); };
ReplaceSelfUpgrade::~ReplaceSelfUpgrade() { m_famgen = 0; }
void famgenDelete(ReplaceSelfUpgrade *p) { delete p; }

// ??_GAudioLoopUpgrade@@MAEPAXI@Z @0x004B7D37 28B
// Deleting dtor slot 0 of vtable 0x00858CC4; calls rowed ??1AudioLoopUpgrade@@MAE@XZ at 0x004B7B20 then rowed operator delete at 0x0002FD60.
class AudioLoopUpgrade { protected: __declspec(noinline) virtual ~AudioLoopUpgrade(); private: int m_famgen;
  friend void famgenDelete(AudioLoopUpgrade *p); };
AudioLoopUpgrade::~AudioLoopUpgrade() { m_famgen = 0; }
void famgenDelete(AudioLoopUpgrade *p) { delete p; }
