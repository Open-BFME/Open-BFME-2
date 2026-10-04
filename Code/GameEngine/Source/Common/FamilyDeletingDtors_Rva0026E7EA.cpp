// cl: /O1 /MD
// ??_GRva0026E7EA@@UAEPAXI@Z @0x0026E81A, 28B.
// Scalar deleting dtor; calls rowed ??1 at 0x0026E7EA plus rowed delete at
// 0x0002FD60.

class Rva0026E7EA { public: __declspec(noinline) virtual ~Rva0026E7EA(); private: int m_famgen;
  friend void famgenDelete(Rva0026E7EA *p); };
Rva0026E7EA::~Rva0026E7EA() { m_famgen = 0; }
void famgenDelete(Rva0026E7EA *p) { delete p; }
