// cl: /MD
// ??_GRva00508CF7@@UAEPAXI@Z @0x00508CDB 28B calls rowed ??1Rva00508CF7@@UAE@XZ at 0x00508CF7 then delete.
// Chain from 0x00508CF7 same 28B scalar-deleting shape.
class Rva00508CF7 { public: __declspec(noinline) virtual ~Rva00508CF7(); private: int m_famgen; };
Rva00508CF7::~Rva00508CF7() { m_famgen = 0; }
void famgenDelete(Rva00508CF7 *p) { delete p; }

// ??_GRva00508E87@@UAEPAXI@Z @0x00508E6B 28B calls rowed ??1Rva00508E87@@UAE@XZ at 0x00508E87 then delete.
// Chain from 0x00508E87 same 28B scalar-deleting shape.
class Rva00508E87 { public: __declspec(noinline) virtual ~Rva00508E87(); private: int m_famgen; };
Rva00508E87::~Rva00508E87() { m_famgen = 0; }
void famgenDelete(Rva00508E87 *p) { delete p; }
