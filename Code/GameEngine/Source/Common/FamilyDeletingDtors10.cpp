// cl: /MD
// Scalar deleting destructors that retail keeps but never references: no
// vtable slot, call or jmp reaches them. Each is the 28B shape that calls
// the pinned complete destructor, tests bit 0 of the flags, frees through
// operator delete 0x0002FD60 and returns this with ret 4. Each class is
// declared locally only so its deleting destructor is emitted; the
// destructor call resolves through that destructor's own pin in
// reverse/symbols.csv.
// Owner identities and layouts are not recovered.

// ??_GRva005CEFD3@@QAEPAXI@Z @0x005CF046 28B: calls pinned ~Rva005CEFD3 0x005CEFD3
class Rva005CEFD3 { public: ~Rva005CEFD3(); };
void famgenDelete(Rva005CEFD3 *p) { delete p; }

// ??_GRva005D07E1@@QAEPAXI@Z @0x005D0863 28B: calls pinned ~Rva005D07E1 0x005D07E1
class Rva005D07E1 { public: ~Rva005D07E1(); };
void famgenDelete(Rva005D07E1 *p) { delete p; }

// ??_GRva005D1210@@QAEPAXI@Z @0x005D1260 28B: calls pinned ~Rva005D1210 0x005D1210
class Rva005D1210 { public: ~Rva005D1210(); };
void famgenDelete(Rva005D1210 *p) { delete p; }

// ??_GRva005E1D07@@QAEPAXI@Z @0x005E1D41 28B: calls pinned ~Rva005E1D07 0x005E1D07
class Rva005E1D07 { public: ~Rva005E1D07(); };
void famgenDelete(Rva005E1D07 *p) { delete p; }

// ??_GRva005E4925@@QAEPAXI@Z @0x005E49C4 28B: calls pinned ~Rva005E4925 0x005E4925
class Rva005E4925 { public: ~Rva005E4925(); };
void famgenDelete(Rva005E4925 *p) { delete p; }

// ??_GRva005E5FFB@@QAEPAXI@Z @0x005E60B5 28B: calls pinned ~Rva005E5FFB 0x005E5FFB
class Rva005E5FFB { public: ~Rva005E5FFB(); };
void famgenDelete(Rva005E5FFB *p) { delete p; }

// ??_GRva005E6D0D@@QAEPAXI@Z @0x005E6D74 28B: calls pinned ~Rva005E6D0D 0x005E6D0D
class Rva005E6D0D { public: ~Rva005E6D0D(); };
void famgenDelete(Rva005E6D0D *p) { delete p; }

// ??_GRva005E98A0@@QAEPAXI@Z @0x005E98E1 28B: calls pinned ~Rva005E98A0 0x005E98A0
class Rva005E98A0 { public: ~Rva005E98A0(); };
void famgenDelete(Rva005E98A0 *p) { delete p; }

// ??_GRva005EB8D6@@QAEPAXI@Z @0x005EB9D6 28B: calls pinned ~Rva005EB8D6 0x005EB8D6
class Rva005EB8D6 { public: ~Rva005EB8D6(); };
void famgenDelete(Rva005EB8D6 *p) { delete p; }

// ??_GRva005EC09B@@QAEPAXI@Z @0x005EC162 28B: calls pinned ~Rva005EC09B 0x005EC09B
class Rva005EC09B { public: ~Rva005EC09B(); };
void famgenDelete(Rva005EC09B *p) { delete p; }

// ??_GRva005EDE64@@QAEPAXI@Z @0x005EDED7 28B: calls pinned ~Rva005EDE64 0x005EDE64
class Rva005EDE64 { public: ~Rva005EDE64(); };
void famgenDelete(Rva005EDE64 *p) { delete p; }

// ??_GRva005F3FFC@@QAEPAXI@Z @0x005F407A 28B: calls pinned ~Rva005F3FFC 0x005F3FFC
class Rva005F3FFC { public: ~Rva005F3FFC(); };
void famgenDelete(Rva005F3FFC *p) { delete p; }

// ??_GRva005F54DA@@QAEPAXI@Z @0x005F55DE 28B: calls pinned ~Rva005F54DA 0x005F54DA
class Rva005F54DA { public: ~Rva005F54DA(); };
void famgenDelete(Rva005F54DA *p) { delete p; }

// ??_GRva005F6051@@QAEPAXI@Z @0x005F630E 28B: calls pinned ~Rva005F6051 0x005F6051
class Rva005F6051 { public: ~Rva005F6051(); };
void famgenDelete(Rva005F6051 *p) { delete p; }

// ??_GRva005FAD8D@@QAEPAXI@Z @0x005FAF41 28B: calls pinned ~Rva005FAD8D 0x005FAD8D
class Rva005FAD8D { public: ~Rva005FAD8D(); };
void famgenDelete(Rva005FAD8D *p) { delete p; }

// ??_GRva005FCA8B@@QAEPAXI@Z @0x005FCB11 28B: calls pinned ~Rva005FCA8B 0x005FCA8B
class Rva005FCA8B { public: ~Rva005FCA8B(); };
void famgenDelete(Rva005FCA8B *p) { delete p; }

// ??_GImpl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEPAXI@Z @0x005FD8C9 28B: calls recovered ~Impl 0x005FD628
// Destructor-only view of the owner whose native member cleanup is recovered.
namespace StrategicHUD { class ArmyUnitSwapperMovieClip { public: class Impl; }; class ArmyUnitSwapperMovieClip::Impl { public: ~Impl(); }; }
void famgenDelete(StrategicHUD::ArmyUnitSwapperMovieClip::Impl *p) { delete p; }

// ??_GRva005FF5F6@@QAEPAXI@Z @0x005FF659 28B: calls pinned ~Rva005FF5F6 0x005FF5F6
class Rva005FF5F6 { public: ~Rva005FF5F6(); };
void famgenDelete(Rva005FF5F6 *p) { delete p; }
