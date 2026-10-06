// cl: /MD
// ??_GRva00517397@@UAEPAXI@Z @0x0051737B 28B
// Deleting dtor calls rowed ??1Rva00517397@@UAE@XZ at 0x00517397 then rowed operator delete at 0x0002FD60.
class Rva00517397 { public: __declspec(noinline) virtual ~Rva00517397(); private: int m_famgen;
  friend void famgenDelete(Rva00517397 *p); };
Rva00517397::~Rva00517397() { m_famgen = 0; }
void famgenDelete(Rva00517397 *p) { delete p; }

// ??_GRva002E0F1E@@UAEPAXI@Z @0x002E18A7 28B
// Deleting dtor calls rowed ??1Rva002E0F1E@@UAE@XZ at 0x002E0F1E then rowed operator delete at 0x0002FD60.
class Rva002E0F1E { public: __declspec(noinline) virtual ~Rva002E0F1E(); private: int m_famgen;
  friend void famgenDelete(Rva002E0F1E *p); };
Rva002E0F1E::~Rva002E0F1E() { m_famgen = 0; }
void famgenDelete(Rva002E0F1E *p) { delete p; }
