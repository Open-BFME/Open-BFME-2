// cl: /O1 /MD
// ??_GRebuildHoleExposeDieModuleData@@UAEPAXI@Z @0x004869B0
// Deleting dtor slot 0 of vtable 0xC4AD40; calls the rowed ??1 at 0x4869CC.
class RebuildHoleExposeDieModuleData { public: __declspec(noinline) virtual ~RebuildHoleExposeDieModuleData(); private: int m_famgen; };
RebuildHoleExposeDieModuleData::~RebuildHoleExposeDieModuleData() { m_famgen = 0; }
void famgenDelete(RebuildHoleExposeDieModuleData *p) { delete p; }
