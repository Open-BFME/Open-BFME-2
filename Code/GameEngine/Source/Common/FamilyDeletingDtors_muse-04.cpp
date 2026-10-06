// cl: /MD
// ??_GRva0026AF86@@UAEPAXI@Z @0x0026AF6A 28B
// Deleting dtor; calls rowed ??1Rva0026AF86@@UAE@XZ at 0x0026AF86 then rowed operator delete at 0x0002FD60.
class Rva0026AF86 { public: __declspec(noinline) virtual ~Rva0026AF86(); private: int m_famgen;
  friend void famgenDelete(Rva0026AF86 *p); };
Rva0026AF86::~Rva0026AF86() { m_famgen = 0; }
void famgenDelete(Rva0026AF86 *p) { delete p; }
