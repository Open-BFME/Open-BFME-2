// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva003AE358@@UAEPAXI@Z @0x003AE33C, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x003AE358 plus rowed delete at 0x0002FD60. Evidence: vtable slot 0 entries 0x0081CA04/0x0081CAA4/0x0081D3A0, caller chain from 0x003AE358, sibling V3InlineTemplateDtor 0x003A583E shape.
// Secondary base at +0x10: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x10) at 0x003ACA8B in its vtable is target evidence for it.
// novtable bases: this unit only needs the derived vftable; base vftables and
// destructors belong to the rowed ??1Rva003AE358 and its bases' own units.
class __declspec(novtable) Rva003AE358Base0 { public: virtual ~Rva003AE358Base0(); private: char m_unmodelled_04[0x10 - 0x04]; };
class __declspec(novtable) Rva003AE358Base10 { public: virtual ~Rva003AE358Base10(); };
class Rva003AE358 : public Rva003AE358Base0, public Rva003AE358Base10 { public: explicit Rva003AE358(int) {} virtual ~Rva003AE358(); private: int m_famgen;
  friend void famgenDelete(Rva003AE358 *p); };
void famgenDelete(Rva003AE358 *p) { delete p; }
Rva003AE358 *famgenNew_Rva003AE358() { return new Rva003AE358(0); }
