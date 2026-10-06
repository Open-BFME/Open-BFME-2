// cl: /MD
// ??_GStructureToppleUpdateModuleData@@UAEPAXI@Z @0x00257C6C, 28B.
// Scalar deleting dtor; calls rowed ??1 at 0x00257C88 plus rowed delete at
// 0x0002FD60.

class StructureToppleUpdateModuleData { public: __declspec(noinline) virtual ~StructureToppleUpdateModuleData(); private: int m_famgen;
  friend void famgenDelete(StructureToppleUpdateModuleData *p); };
StructureToppleUpdateModuleData::~StructureToppleUpdateModuleData() { m_famgen = 0; }
void famgenDelete(StructureToppleUpdateModuleData *p) { delete p; }
