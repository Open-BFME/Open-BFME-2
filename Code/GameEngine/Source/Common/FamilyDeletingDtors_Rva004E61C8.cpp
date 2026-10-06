// cl: /MD
// ??_GRva004E61C8@@UAEPAXI@Z @0x004E6231 28B: scalar deleting dtor calling ??1Rva004E61C8 at 0x004E61C8.
// Same-shape sibling of ??_GRva001E3624; needs ??1 row to exist.
class Rva004E61C8 { public: __declspec(noinline) virtual ~Rva004E61C8(); private: int m_famgen; };
Rva004E61C8::~Rva004E61C8() { m_famgen = 0; }
void famgenDelete(Rva004E61C8 *p) { delete p; }
