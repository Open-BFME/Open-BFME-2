// cl: /O1 /MD
// ??_GShipSlowDeathBehaviorModuleData@@UAEPAXI@Z @0x0045E98E
// Deleting dtor slot 0 of vtable 0x842E98; calls ??1 at 0x461FED (twin-pinned
// as ??1ShipSlowDeathBehaviorModuleData; body rowed as
// ??1GiantBirdSlowDeathBehaviorModuleData).
class ShipSlowDeathBehaviorModuleData { public: __declspec(noinline) virtual ~ShipSlowDeathBehaviorModuleData(); private: int m_famgen; };
// ??1ShipSlowDeathBehaviorModuleData@@UAE@XZ present-unmatched
ShipSlowDeathBehaviorModuleData::~ShipSlowDeathBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(ShipSlowDeathBehaviorModuleData *p) { delete p; }
