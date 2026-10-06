// cl: /MD

// ??_GRva004104C9@@QAEPAXI@Z @0x004105A8
class Rva004104C9 { public: __declspec(noinline) ~Rva004104C9(); private: int m_famgen;
  friend void famgenDelete(Rva004104C9 *p); };
// Rva004104C9::~Rva004104C9: defined in Rva004104C9Dtor.cpp (its row's unit).
void famgenDelete(Rva004104C9 *p) { delete p; }

