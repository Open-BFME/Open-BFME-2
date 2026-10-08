// cl: /MD
// Scalar deleting destructors that retail keeps but never references: no
// vtable slot, call or jmp reaches them. Each is the 28B shape that calls
// the complete destructor, tests bit 0 of the flags, frees through
// operator delete 0x0002FD60 and returns this with ret 4. Each class is
// declared locally only so its deleting destructor is emitted; the
// destructor call resolves through an address-derived pin in
// reverse/symbols.csv read from the wrapper's own REL32. Owner identities
// and layouts are not recovered.

// ??_GRva004D960C@@QAEPAXI@Z @0x004D96E4 28B: calls ~Rva004D960C 0x004D960C
class Rva004D960C { public: ~Rva004D960C(); };
void famgenDelete(Rva004D960C *p) { delete p; }

// ??_GRva002C6E4E@@QAEPAXI@Z @0x004E938C 28B: calls ~Rva002C6E4E 0x002C6E4E
class Rva002C6E4E { public: ~Rva002C6E4E(); };
void famgenDelete(Rva002C6E4E *p) { delete p; }

// ??_GRva004F7DD4@@QAEPAXI@Z @0x004F7E91 28B: calls ~Rva004F7DD4 0x004F7DD4
class Rva004F7DD4 { public: ~Rva004F7DD4(); };
void famgenDelete(Rva004F7DD4 *p) { delete p; }

// ??_GRva005011B4@@QAEPAXI@Z @0x0050160D 28B: calls ~Rva005011B4 0x005011B4
class Rva005011B4 { public: ~Rva005011B4(); };
void famgenDelete(Rva005011B4 *p) { delete p; }

// ??_GRva0050174A@@QAEPAXI@Z @0x00501D7A 28B: calls ~Rva0050174A 0x0050174A
class Rva0050174A { public: ~Rva0050174A(); };
void famgenDelete(Rva0050174A *p) { delete p; }

// ??_GRva005BEA22@@QAEPAXI@Z @0x0051E2DF 28B: calls ~Rva005BEA22 0x005BEA22
class Rva005BEA22 { public: ~Rva005BEA22(); };
void famgenDelete(Rva005BEA22 *p) { delete p; }

// ??_GRva005C8565@@QAEPAXI@Z @0x005686D9 28B: calls ~Rva005C8565 0x005C8565
class Rva005C8565 { public: ~Rva005C8565(); };
void famgenDelete(Rva005C8565 *p) { delete p; }

// ??_GRva005C8FBD@@QAEPAXI@Z @0x005C80B5 28B: calls ~Rva005C8FBD 0x005C8FBD
class Rva005C8FBD { public: ~Rva005C8FBD(); };
void famgenDelete(Rva005C8FBD *p) { delete p; }

// ??_GRva005E3585@@QAEPAXI@Z @0x005E3599 28B: calls ~Rva005E3585 0x005E3585
class Rva005E3585 { public: ~Rva005E3585(); };
void famgenDelete(Rva005E3585 *p) { delete p; }

// ??_GRva005F1295@@QAEPAXI@Z @0x005F12FE 28B: calls ~Rva005F1295 0x005F1295
class Rva005F1295 { public: ~Rva005F1295(); };
void famgenDelete(Rva005F1295 *p) { delete p; }

// ??_GRva005F2B22@@QAEPAXI@Z @0x005F2F64 28B: calls ~Rva005F2B22 0x005F2B22
class Rva005F2B22 { public: ~Rva005F2B22(); };
void famgenDelete(Rva005F2B22 *p) { delete p; }

// ??_GRva005F75C9@@QAEPAXI@Z @0x005F7654 28B: calls ~Rva005F75C9 0x005F75C9
class Rva005F75C9 { public: ~Rva005F75C9(); };
void famgenDelete(Rva005F75C9 *p) { delete p; }

// ??_GRva005F9877@@QAEPAXI@Z @0x005F9B32 28B: calls ~Rva005F9877 0x005F9877
class Rva005F9877 { public: ~Rva005F9877(); };
void famgenDelete(Rva005F9877 *p) { delete p; }

// ??_GRva00603C57@@QAEPAXI@Z @0x00603F90 28B: calls ~Rva00603C57 0x00603C57
class Rva00603C57 { public: ~Rva00603C57(); };
void famgenDelete(Rva00603C57 *p) { delete p; }
