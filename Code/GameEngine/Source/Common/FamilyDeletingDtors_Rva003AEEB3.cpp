// cl: /MD
// ??_GRva003AEEB3@@UAEPAXI@Z @0x003AEEFC, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x003A5817 plus rowed delete at 0x0002FD60. Evidence: vtable slot 0 at 0x0081D5FC class of copy ctor 0x003AEEB3.
// ??_GRva003AEEB3@@UAEPAXI@Z @0x003AEEFC present-unmatched
class Rva003AEEB3 { public: __declspec(noinline) virtual ~Rva003AEEB3(); private: int m_famgen;
  friend void famgenDelete(Rva003AEEB3 *p); };
Rva003AEEB3::~Rva003AEEB3() { m_famgen = 0; }
void famgenDelete(Rva003AEEB3 *p) { delete p; }
