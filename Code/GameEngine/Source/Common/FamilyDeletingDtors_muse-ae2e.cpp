// cl: /O1 /MD
// Each class redeclares its public virtual destructor and defines it locally,
// which emits the scalar deleting destructor in this TU; the dtor call inside
// resolves through that destructor's own row (same pattern as spec_gdtor).

// ??_GCreateObjectDieModuleData@@UAEPAXI@Z @0x485e50
class CreateObjectDieModuleData { public: __declspec(noinline) virtual ~CreateObjectDieModuleData(); private: int m_famgen;
  friend void famgenDelete(CreateObjectDieModuleData *p); };
CreateObjectDieModuleData::~CreateObjectDieModuleData() { m_famgen = 0; }
void famgenDelete(CreateObjectDieModuleData *p) { delete p; }

// ??_GCreateObjectDieIfEldestKindofModuleData@@UAEPAXI@Z @0x485e6c
class CreateObjectDieIfEldestKindofModuleData { public: __declspec(noinline) virtual ~CreateObjectDieIfEldestKindofModuleData(); private: int m_famgen;
  friend void famgenDeleteEldest(CreateObjectDieIfEldestKindofModuleData *p); };
CreateObjectDieIfEldestKindofModuleData::~CreateObjectDieIfEldestKindofModuleData() { m_famgen = 0; }
void famgenDeleteEldest(CreateObjectDieIfEldestKindofModuleData *p) { delete p; }
