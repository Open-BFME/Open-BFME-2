// cl: /O1 /MD
// Scalar deleting destructors that retail keeps but never references: no
// vtable slot, call or jmp reaches them. Each is the 28B shape that calls
// the pinned complete destructor, tests bit 0 of the flags, frees through
// operator delete 0x0002FD60 and returns this with ret 4. Each class is
// declared locally only so its deleting destructor is emitted; the
// destructor call resolves through that destructor's own pin in
// reverse/symbols.csv.
// Owner identities and layouts are not recovered.

// ??_GRva004E668E@@QAEPAXI@Z @0x0029B219 28B: calls pinned ~Rva004E668E 0x004E668E
class Rva004E668E { public: ~Rva004E668E(); };
void famgenDelete(Rva004E668E *p) { delete p; }

// ??_GRva004E6A9B@@QAEPAXI@Z @0x0029B235 28B: calls pinned ~Rva004E6A9B 0x004E6A9B
class Rva004E6A9B { public: ~Rva004E6A9B(); };
void famgenDelete(Rva004E6A9B *p) { delete p; }

// ??_GRva004FA2E2@@QAEPAXI@Z @0x002B2F21 28B: calls pinned ~Rva004FA2E2 0x004FA2E2
class Rva004FA2E2 { public: ~Rva004FA2E2(); };
void famgenDelete(Rva004FA2E2 *p) { delete p; }

// ??_GRva002B74DE@@QAEPAXI@Z @0x002B813F 28B: calls pinned ~Rva002B74DE 0x002B74DE
class Rva002B74DE { public: ~Rva002B74DE(); };
void famgenDelete(Rva002B74DE *p) { delete p; }

// ??_GRva00527CCE@@QAEPAXI@Z @0x002D33BB 28B: calls pinned ~Rva00527CCE 0x00527CCE
class Rva00527CCE { public: ~Rva00527CCE(); };
void famgenDelete(Rva00527CCE *p) { delete p; }

// ??_GRva00527FA2@@QAEPAXI@Z @0x002D33D7 28B: calls pinned ~Rva00527FA2 0x00527FA2
class Rva00527FA2 { public: ~Rva00527FA2(); };
void famgenDelete(Rva00527FA2 *p) { delete p; }

// ??_GRva0057417E@@QAEPAXI@Z @0x0042C0BF 28B: calls pinned ~Rva0057417E 0x0057417E
class Rva0057417E { public: ~Rva0057417E(); };
void famgenDelete(Rva0057417E *p) { delete p; }

// ??_GRva00578C43@@QAEPAXI@Z @0x0042D4CF 28B: calls pinned ~Rva00578C43 0x00578C43
class Rva00578C43 { public: ~Rva00578C43(); };
void famgenDelete(Rva00578C43 *p) { delete p; }

// ??_GRva0057BD01@@QAEPAXI@Z @0x0042D53F 28B: calls pinned ~Rva0057BD01 0x0057BD01
class Rva0057BD01 { public: ~Rva0057BD01(); };
void famgenDelete(Rva0057BD01 *p) { delete p; }

// ??_GRva004E6935@@QAEPAXI@Z @0x004E6A01 28B: calls pinned ~Rva004E6935 0x004E6935
class Rva004E6935 { public: ~Rva004E6935(); };
void famgenDelete(Rva004E6935 *p) { delete p; }

// ??_GRva0052634F@@QAEPAXI@Z @0x005264BD 28B: calls pinned ~Rva0052634F 0x0052634F
class Rva0052634F { public: ~Rva0052634F(); };
void famgenDelete(Rva0052634F *p) { delete p; }

// ??_GRva005262BF@@QAEPAXI@Z @0x005264D9 28B: calls pinned ~Rva005262BF 0x005262BF
class Rva005262BF { public: ~Rva005262BF(); };
void famgenDelete(Rva005262BF *p) { delete p; }

// ??_GRva00527E53@@QAEPAXI@Z @0x00527F6C 28B: calls pinned ~Rva00527E53 0x00527E53
class Rva00527E53 { public: ~Rva00527E53(); };
void famgenDelete(Rva00527E53 *p) { delete p; }

// ??_GRva005282BA@@QAEPAXI@Z @0x00528566 28B: calls pinned ~Rva005282BA 0x005282BA
class Rva005282BA { public: ~Rva005282BA(); };
void famgenDelete(Rva005282BA *p) { delete p; }

// ??_GRva005D32D4@@QAEPAXI@Z @0x0057854E 28B: calls pinned ~Rva005D32D4 0x005D32D4
class Rva005D32D4 { public: ~Rva005D32D4(); };
void famgenDelete(Rva005D32D4 *p) { delete p; }

// ??_GRva005D3C2B@@QAEPAXI@Z @0x00578586 28B: calls pinned ~Rva005D3C2B 0x005D3C2B
class Rva005D3C2B { public: ~Rva005D3C2B(); };
void famgenDelete(Rva005D3C2B *p) { delete p; }

// ??_GRva005D4FFC@@QAEPAXI@Z @0x0057B960 28B: calls pinned ~Rva005D4FFC 0x005D4FFC
class Rva005D4FFC { public: ~Rva005D4FFC(); };
void famgenDelete(Rva005D4FFC *p) { delete p; }

// ??_GRva005E893E@@QAEPAXI@Z @0x005CE156 28B: calls pinned ~Rva005E893E 0x005E893E
class Rva005E893E { public: ~Rva005E893E(); };
void famgenDelete(Rva005E893E *p) { delete p; }
