// cl: /O1 /MD
// ??_GRva003AE358@@UAEPAXI@Z @0x003AE33C, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x003AE358 plus rowed delete at 0x0002FD60. Evidence: vtable slot 0 entries 0x0081CA04/0x0081CAA4/0x0081D3A0, caller chain from 0x003AE358, sibling V3InlineTemplateDtor 0x003A583E shape.
// ??_GRva003AE358@@UAEPAXI@Z @0x003AE33C present-unmatched
// Secondary base at +0x10: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x10) at 0x003ACA8B in its vtable is target evidence for it.
class Rva003AE358Base0 { public: virtual ~Rva003AE358Base0(); private: char m_unmodelled_04[0x10 - 0x04]; };
class Rva003AE358Base10 { public: virtual ~Rva003AE358Base10(); };
class Rva003AE358 : public Rva003AE358Base0, public Rva003AE358Base10 { public: __declspec(noinline) virtual ~Rva003AE358(); private: int m_famgen;
  friend void famgenDelete(Rva003AE358 *p); };
Rva003AE358::~Rva003AE358() { m_famgen = 0; }
void famgenDelete(Rva003AE358 *p) { delete p; }
