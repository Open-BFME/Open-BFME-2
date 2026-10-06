// cl: /MD
// ??_GObjectTypes@@UAEPAXI@Z @0x00376AC3 28B
// Deleting dtor slot 0 of vtable 0x00C18630; calls rowed ??1 at 0x00376ADF then rowed operator delete at 0x0002FD60.
class ObjectTypes { public: __declspec(noinline) virtual ~ObjectTypes(); private: int m_famgen; };
ObjectTypes::~ObjectTypes() { m_famgen = 0; }
void famgenDelete(ObjectTypes *p) { delete p; }
