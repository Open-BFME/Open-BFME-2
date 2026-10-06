// cl: /MD
// ??_GUVBufferClass@@UAEPAXI@Z @0x000D20FC 28B
// Deleting dtor slot 1 of vtable 0x007CE338; calls rowed ??1UVBufferClass@@UAE@XZ at 0x000D2118 then rowed operator delete at 0x0002FD60.
class UVBufferClass { public: __declspec(noinline) virtual ~UVBufferClass(); private: int m_famgen; };
UVBufferClass::~UVBufferClass() { m_famgen = 0; }
void famgenDelete(UVBufferClass *p) { delete p; }
