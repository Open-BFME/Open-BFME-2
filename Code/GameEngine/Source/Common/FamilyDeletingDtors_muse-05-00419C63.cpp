// cl: /MD
// ??_GRva00419C7F@@UAEPAXI@Z, retail 0x00419C63, 28 bytes. Scalar deleting
// dtor calling rowed ??1Rva00419C7F@@UAE@XZ at 0x00419C7F then rowed operator
// delete at 0x0002FD60. Evidence: chain lane after landing 0x00419C7F;
// retail push esi mov esi ecx call ??1 test flag delete ret 4.
class Rva00419C7F { public: __declspec(noinline) virtual ~Rva00419C7F(); private: int m_famgen; };
Rva00419C7F::~Rva00419C7F() { m_famgen = 0; }
void famgenDelete(Rva00419C7F *p) { delete p; }
