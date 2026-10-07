// cl: /MD
// ??_GRva003ABC58@@UAEPAXI@Z @0x003AF929 28B
// Deleting dtor calls rowed ??1Rva003ABC58@@UAE@XZ at 0x003ABC58 then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x003ABC58; retail push esi call ??1 test flag delete ret 4.
// Secondary base at +0x1C: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x1C) at 0x003ABFD9 in its vtable is target evidence for it.
class Rva003ABC58Base0 { public: virtual ~Rva003ABC58Base0(); private: char m_unmodelled_04[0x1C - 0x04]; };
class Rva003ABC58Base1C { public: virtual ~Rva003ABC58Base1C(); };
class Rva003ABC58 : public Rva003ABC58Base0, public Rva003ABC58Base1C { public: __declspec(noinline) virtual ~Rva003ABC58(); private: int m_famgen;
  friend void famgenDelete(Rva003ABC58 *p); };
Rva003ABC58::~Rva003ABC58() { m_famgen = 0; }
void famgenDelete(Rva003ABC58 *p) { delete p; }
// ??_GRva003ABA36@@UAEPAXI@Z @0x003AE8D5 28B
// Deleting dtor calls rowed ??1Rva003ABA36@@UAE@XZ at 0x003ABA36 then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x003ABA36; retail push esi call ??1 test flag delete ret 4;
// vtable slot 0 of 0x0081C860 family.
// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) at 0x003AC1EF in its vtable is target evidence for it.
class Rva003ABA36Base0 { public: virtual ~Rva003ABA36Base0(); private: char m_unmodelled_04[0x18 - 0x04]; };
class Rva003ABA36Base18 { public: virtual ~Rva003ABA36Base18(); };
class Rva003ABA36 : public Rva003ABA36Base0, public Rva003ABA36Base18 { public: __declspec(noinline) virtual ~Rva003ABA36(); private: int m_famgen;
  friend void famgenDelete(Rva003ABA36 *p); };
Rva003ABA36::~Rva003ABA36() { m_famgen = 0; }
void famgenDelete(Rva003ABA36 *p) { delete p; }