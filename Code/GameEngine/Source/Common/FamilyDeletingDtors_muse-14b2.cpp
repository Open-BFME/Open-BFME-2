// cl: /O1 /MD
// ??_GDynamicShroudClearingRangeUpdateModuleData@@UAEPAXI@Z @0x0048B618 28B
// Deleting dtor slot 0 of vtable 0x0084BEF8; calls rowed ??1 at 0x0048B634 then rowed operator delete at 0x0002FD60.
class DynamicShroudClearingRangeUpdateModuleData { public: __declspec(noinline) virtual ~DynamicShroudClearingRangeUpdateModuleData(); private: int m_famgen; };
DynamicShroudClearingRangeUpdateModuleData::~DynamicShroudClearingRangeUpdateModuleData() { m_famgen = 0; }
void famgenDelete(DynamicShroudClearingRangeUpdateModuleData *p) { delete p; }
