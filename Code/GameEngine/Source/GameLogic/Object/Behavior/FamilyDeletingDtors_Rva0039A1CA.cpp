// cl: /MD
//
// ??_GRva0039A1CA@@UAEPAXI@Z, retail 0x0039A1AE (28 bytes).
// Deleting dtor for Rva0039A1CA whose ??1 is rowed at 0x0039A1CA; the call
// resolves through that row. Placeholder ??1 is a duplicate kept only to emit
// the deleting copy, following FamilyDeletingDtors.cpp.
class Rva0039A1CA { public: __declspec(noinline) virtual ~Rva0039A1CA(); private: int m_famgen; };
Rva0039A1CA::~Rva0039A1CA() { m_famgen = 0; }
void famgenDelete(Rva0039A1CA *p) { delete p; }
