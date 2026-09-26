// cl: /O1 /MD
// ??_GRva0048BC03Base@@UAEPAXI@Z @0x0048C098 28B
// Deleting dtor slot 0 of vtable 0x0084C110; calls rowed ??1 at 0x0048BC46 then rowed operator delete at 0x0002FD60.
class Rva0048BC03Base { public: __declspec(noinline) virtual ~Rva0048BC03Base(); private: int m_famgen; };
Rva0048BC03Base::~Rva0048BC03Base() { m_famgen = 0; }
void famgenDelete(Rva0048BC03Base *p) { delete p; }
