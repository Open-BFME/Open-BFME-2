// cl: /O1 /MD
// ??_GRousingSpeechUpdateModuleData@@UAEPAXI@Z @0x004AD333 28B
// Deleting dtor slot 0 of vtable 0x00855048; calls rowed ??1 at 0x004AD34F then rowed operator delete at 0x0002FD60.
class RousingSpeechUpdateModuleData { public: __declspec(noinline) virtual ~RousingSpeechUpdateModuleData(); private: int m_famgen; };
RousingSpeechUpdateModuleData::~RousingSpeechUpdateModuleData() { m_famgen = 0; }
void famgenDelete(RousingSpeechUpdateModuleData *p) { delete p; }
