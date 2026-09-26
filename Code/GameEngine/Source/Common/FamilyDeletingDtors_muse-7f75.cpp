// cl: /O1 /MD
// ??_GRadiateFearUpdateModuleData@@UAEPAXI@Z @0x0049C1D2 28B
// Deleting dtor slot 0 of vtable 0x00850FF0; calls rowed ??1 at 0x0049C1EE then rowed operator delete at 0x0002FD60.
class RadiateFearUpdateModuleData { public: __declspec(noinline) virtual ~RadiateFearUpdateModuleData(); private: int m_famgen; };
RadiateFearUpdateModuleData::~RadiateFearUpdateModuleData() { m_famgen = 0; }
void famgenDelete(RadiateFearUpdateModuleData *p) { delete p; }

// ??_GGiveUpgradeUpdateModuleData@@UAEPAXI@Z @0x0049C624 28B
// Deleting dtor slot 0 of vtable 0x00851280; calls rowed ??1 at 0x0049C640 then rowed operator delete at 0x0002FD60.
class GiveUpgradeUpdateModuleData { public: __declspec(noinline) virtual ~GiveUpgradeUpdateModuleData(); private: int m_famgen; };
GiveUpgradeUpdateModuleData::~GiveUpgradeUpdateModuleData() { m_famgen = 0; }
void famgenDelete(GiveUpgradeUpdateModuleData *p) { delete p; }

// ??_GRva0031468C@@QAEPAXI@Z @0x00314926 28B
// Scalar deleting dtor; calls rowed ??1 at 0x0031468C then rowed operator delete at 0x0002FD60.
class Rva0031468C { public: __declspec(noinline) ~Rva0031468C(); private: int m_famgen; };
Rva0031468C::~Rva0031468C() { m_famgen = 0; }
void famgenDelete(Rva0031468C *p) { delete p; }
