// cl: /MD
// ??_GRva004FAC21@@UAEPAXI@Z, retail 0x004FAD9C (28 bytes).
// Scalar deleting destructor (slot 0 of vtable 0x008633B0) over the rowed
// ??1Rva004FAC21 at 0x004FADB8. The dtor TU cannot emit it (novtable
// class), so this family file emits it through delete; the ??1 and
// operator delete calls resolve through their rows. Evidence: chain from
// the just-landed ??1 plus the standard ??_G shape in the packet.

// ??_GRva004FAC21@@UAEPAXI@Z @0x4fad9c
class Rva004FAC21 { public: __declspec(noinline) virtual ~Rva004FAC21(); private: int m_famgen; };
Rva004FAC21::~Rva004FAC21() { m_famgen = 0; }
void famgenDelete(Rva004FAC21 *p) { delete p; }
