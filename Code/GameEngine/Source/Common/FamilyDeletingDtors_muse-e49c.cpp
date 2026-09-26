// cl: /O1 /MD
// Each class redeclares its protected virtual destructor and defines it locally,
// which emits the scalar deleting destructor in this TU; the dtor call inside
// resolves through that destructor's own row (same pattern as spec_gdtor).

// ??_GCritterEmitterUpdate@@MAEPAXI@Z @0x004C8DC6
class CritterEmitterUpdate { protected: __declspec(noinline) virtual ~CritterEmitterUpdate(); private: int m_famgen;
  friend void famgenDelete(CritterEmitterUpdate *p); };
CritterEmitterUpdate::~CritterEmitterUpdate() { m_famgen = 0; }
void famgenDelete(CritterEmitterUpdate *p) { delete p; }
