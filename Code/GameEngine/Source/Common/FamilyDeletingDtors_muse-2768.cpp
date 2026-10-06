// cl: /MD
// ??_GStructureBodyModuleData@@UAEPAXI@Z @0x0025706B, 28B.
// Scalar deleting dtor slot 0 of vtable 0x007F4028; calls rowed ??1 at
// 0x00257087 plus rowed delete at 0x0002FD60.

// ??_GStructureBodyModuleData@@UAEPAXI@Z @0x0025706B
class StructureBodyModuleData { public: __declspec(noinline) virtual ~StructureBodyModuleData(); private: int m_famgen;
  friend void famgenDelete(StructureBodyModuleData *p); };
StructureBodyModuleData::~StructureBodyModuleData() { m_famgen = 0; }
void famgenDelete(StructureBodyModuleData *p) { delete p; }
