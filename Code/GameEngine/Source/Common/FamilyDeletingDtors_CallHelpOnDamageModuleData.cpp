// cl: /O1 /MD
// ??_GCallHelpOnDamageModuleData@@UAEPAXI@Z @0x004BB4FB 28B
// Deleting dtor calls ICF-twin ??1 at 0x004BB517 (rowed as dup_004bb517 for TerrainResourceBehaviorModuleData) then rowed operator delete at 0x0002FD60.
// Evidence: dtor lane vtable 0x00859EB8 slot 0 class of ??0CallHelpOnDamageModuleData; retail push esi call ??1 test flag delete ret 4.
class CallHelpOnDamageModuleData { public: __declspec(noinline) virtual ~CallHelpOnDamageModuleData(); private: int m_famgen;
  friend void famgenDelete(CallHelpOnDamageModuleData *p); };
// ??1CallHelpOnDamageModuleData@@UAE@XZ present-unmatched
CallHelpOnDamageModuleData::~CallHelpOnDamageModuleData() { m_famgen = 0; }
void famgenDelete(CallHelpOnDamageModuleData *p) { delete p; }
