// cl: /O1 /MD
// ??_GLevelGrantSpecialPowerModuleData@@UAEPAXI@Z @0x004C2C06 28B
// Deleting dtor slot 0 of vtable 0x0085C828; calls rowed ??1 at 0x004C2C22 then rowed operator delete at 0x0002FD60.
class LevelGrantSpecialPowerModuleData { public: __declspec(noinline) virtual ~LevelGrantSpecialPowerModuleData(); private: int m_famgen; };
LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(LevelGrantSpecialPowerModuleData *p) { delete p; }
// ??_GScriptActions@@UAEPAXI@Z @0x003BE5AD 28B
// Deleting dtor slot 0 of vtable 0x0081FE48; calls rowed ??1 at 0x003BD582 then rowed operator delete at 0x0002FD60.
class ScriptActions { public: __declspec(noinline) virtual ~ScriptActions(); private: int m_famgen; };
ScriptActions::~ScriptActions() { m_famgen = 0; }
void famgenDelete(ScriptActions *p) { delete p; }
