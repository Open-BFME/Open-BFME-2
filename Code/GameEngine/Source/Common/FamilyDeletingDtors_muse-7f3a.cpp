// cl: /O1 /MD
// ??_GRubbleRiseUpdateModuleData@@UAEPAXI@Z @0x00256C3E 28B
// Deleting dtor slot 0 of vtable RVA 0x7F3B40 (VA 0xBF3B40); calls rowed ??1 at 0x00256C5A then rowed operator delete at 0x0002FD60.
class RubbleRiseUpdateModuleData { public: __declspec(noinline) virtual ~RubbleRiseUpdateModuleData(); private: int m_famgen; };
RubbleRiseUpdateModuleData::~RubbleRiseUpdateModuleData() { m_famgen = 0; }
void famgenDelete(RubbleRiseUpdateModuleData *p) { delete p; }
