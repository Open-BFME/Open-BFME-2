// cl: /O1 /MD
//
// Scalar deleting destructors of the 28B flag-test shape, batch B01:
// push esi / mov esi,ecx / call <dtor> / test [esp+8],1 / je / push esi /
// call ??3 (0x2FD60) / pop ecx / mov eax,esi / pop esi / ret 4.
//
// Target facts: each ??_G body and the destructor address it calls are read
// from the retail bytes; the destructor is a Ghidra-inventoried function
// start with no other pin or ledger row, and is pinned opaquely.
// Not established: the owning class, its layout and its destructor body.
// Each class below is therefore declared with nothing but the virtual
// destructor the ??_G needs; __declspec(noinline) keeps that destructor out
// of line so the ??_G calls it through the pin, and its empty body here is a
// placeholder, not a claim (present-unmatched). Names are address-derived
// (Rva<dtor rva>) and disclaim identity.
// Audit 2026-09-26: all 30 wrapper/callee boundaries and both calls verified.
// Virtual declarations are emission scaffolds, not recovered class layouts.
// Nine wrappers have no pointer occurrence in retail .rdata/.data; virtual
// ownership is unproven for those, as documented in the audit table.
// See docs/reconstruction/deleting-destructor-identity-audit.md.

// ??_GRva000C2980@@UAEPAXI@Z @0x000C3808 28B; calls pinned ??1 at 0x000C2980
class Rva000C2980 { public: __declspec(noinline) virtual ~Rva000C2980(); };
// ??1Rva000C2980@@UAE@XZ present-unmatched
Rva000C2980::~Rva000C2980() {}
void Rva000C2980_Delete(Rva000C2980 *p) { delete p; }

// ??_GRva000D1E88@@UAEPAXI@Z @0x000D1E6C 28B; calls pinned ??1 at 0x000D1E88
void __cdecl operator delete[](void *p) throw();
extern int g_bfmeVftBVJS[];
class Rva000D1E88 { public: __declspec(noinline) virtual ~Rva000D1E88(); private: int _pad04; void *m_arr08; };
Rva000D1E88::~Rva000D1E88() { delete[] (char *)m_arr08; *(int **)this = g_bfmeVftBVJS; }
void Rva000D1E88_Delete(Rva000D1E88 *p) { delete p; }

// ??_GRva000D1BA6@@UAEPAXI@Z @0x000D208D 28B; calls pinned ??1 at 0x000D1BA6
class Rva000D1BA6 { public: __declspec(noinline) virtual ~Rva000D1BA6(); };
// ??1Rva000D1BA6@@UAE@XZ present-unmatched
Rva000D1BA6::~Rva000D1BA6() {}
void Rva000D1BA6_Delete(Rva000D1BA6 *p) { delete p; }

// ??_GRva00142FE0@@UAEPAXI@Z @0x000E00A4 28B; calls pinned ??1 at 0x00142FE0
class Rva00142FE0 { public: __declspec(noinline) virtual ~Rva00142FE0(); };
// ??1Rva00142FE0@@UAE@XZ present-unmatched
Rva00142FE0::~Rva00142FE0() {}
void Rva00142FE0_Delete(Rva00142FE0 *p) { delete p; }

// ??_GRva000E3B41@@UAEPAXI@Z @0x000E3CC5 28B; calls pinned ??1 at 0x000E3B41
class Rva000E3B41Base0 { public: virtual ~Rva000E3B41Base0(); private: char m_unmodelled[0x4]; };
// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) at 0x000E3BD9 in its vtable is target evidence for it.
class Rva000E3B41Base8 { public: virtual ~Rva000E3B41Base8(); private: char m_unmodelled[0xBC]; };
// Secondary base at +0xC8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC8) at 0x000E3BE1 in its vtable is target evidence for it.
class Rva000E3B41BaseC8 { public: virtual ~Rva000E3B41BaseC8(); };
class Rva000E3B41 : public Rva000E3B41Base0, public Rva000E3B41Base8, public Rva000E3B41BaseC8 { public: __declspec(noinline) virtual ~Rva000E3B41(); };
// ??1Rva000E3B41@@UAE@XZ present-unmatched
Rva000E3B41::~Rva000E3B41() {}
void Rva000E3B41_Delete(Rva000E3B41 *p) { delete p; }

// ??_GRva000E5033@@UAEPAXI@Z @0x000E583E 28B; calls pinned ??1 at 0x000E5033
class Rva000E5033 { public: __declspec(noinline) virtual ~Rva000E5033(); };
// ??1Rva000E5033@@UAE@XZ present-unmatched
Rva000E5033::~Rva000E5033() {}
void Rva000E5033_Delete(Rva000E5033 *p) { delete p; }

// ??_GRva000E59D3@@UAEPAXI@Z @0x000E5A2B 28B; calls pinned ??1 at 0x000E59D3
class Rva000E59D3 { public: __declspec(noinline) virtual ~Rva000E59D3(); };
// ??1Rva000E59D3@@UAE@XZ present-unmatched
Rva000E59D3::~Rva000E59D3() {}
void Rva000E59D3_Delete(Rva000E59D3 *p) { delete p; }

// ??_GRva000E6387@@UAEPAXI@Z @0x000E63C0 28B; calls pinned ??1 at 0x000E6387
class Rva000E6387 { public: __declspec(noinline) virtual ~Rva000E6387(); };
// ??1Rva000E6387@@UAE@XZ present-unmatched
Rva000E6387::~Rva000E6387() {}
void Rva000E6387_Delete(Rva000E6387 *p) { delete p; }

// ??_GRva000E6C6F@@UAEPAXI@Z @0x000E6D78 28B; calls pinned ??1 at 0x000E6C6F
class Rva000E6C6F { public: __declspec(noinline) virtual ~Rva000E6C6F(); };
// ??1Rva000E6C6F@@UAE@XZ present-unmatched
Rva000E6C6F::~Rva000E6C6F() {}
void Rva000E6C6F_Delete(Rva000E6C6F *p) { delete p; }

// ??_GRva000E9BAC@@UAEPAXI@Z @0x000E9CDF 28B; calls pinned ??1 at 0x000E9BAC
class Rva000E9BAC { public: __declspec(noinline) virtual ~Rva000E9BAC(); };
// ??1Rva000E9BAC@@UAE@XZ present-unmatched
Rva000E9BAC::~Rva000E9BAC() {}
void Rva000E9BAC_Delete(Rva000E9BAC *p) { delete p; }

// ??_GRva000EDA94@@UAEPAXI@Z @0x000EDF07 28B; calls pinned ??1 at 0x000EDA94
class Rva000EDA94 { public: __declspec(noinline) virtual ~Rva000EDA94(); };
// ??1Rva000EDA94@@UAE@XZ present-unmatched
Rva000EDA94::~Rva000EDA94() {}
void Rva000EDA94_Delete(Rva000EDA94 *p) { delete p; }

// ??_GRva000EEEF4@@UAEPAXI@Z @0x000EEFEC 28B; calls pinned ??1 at 0x000EEEF4
class Rva000EEEF4 { public: __declspec(noinline) virtual ~Rva000EEEF4(); };
// ??1Rva000EEEF4@@UAE@XZ present-unmatched
Rva000EEEF4::~Rva000EEEF4() {}
void Rva000EEEF4_Delete(Rva000EEEF4 *p) { delete p; }

// ??_GRva00613B90@@UAEPAXI@Z @0x000F0B65 28B; calls pinned ??1 at 0x00613B90
class Rva00613B90 { public: __declspec(noinline) virtual ~Rva00613B90(); };
// ??1Rva00613B90@@UAE@XZ present-unmatched
Rva00613B90::~Rva00613B90() {}
void Rva00613B90_Delete(Rva00613B90 *p) { delete p; }

// ??_GRva000EFC45@@UAEPAXI@Z @0x000F1698 28B; calls pinned ??1 at 0x000EFC45
class Rva000EFC45 { public: __declspec(noinline) virtual ~Rva000EFC45(); };
// ??1Rva000EFC45@@UAE@XZ present-unmatched
Rva000EFC45::~Rva000EFC45() {}
void Rva000EFC45_Delete(Rva000EFC45 *p) { delete p; }

// ??_GRva000F26DC@@UAEPAXI@Z @0x000F2B81 28B; calls pinned ??1 at 0x000F26DC
class Rva000F26DC { public: __declspec(noinline) virtual ~Rva000F26DC(); };
// ??1Rva000F26DC@@UAE@XZ present-unmatched
Rva000F26DC::~Rva000F26DC() {}
void Rva000F26DC_Delete(Rva000F26DC *p) { delete p; }

// ??_GRva000F2797@@UAEPAXI@Z @0x000F2B9D 28B; calls pinned ??1 at 0x000F2797
class Rva000F2797 { public: __declspec(noinline) virtual ~Rva000F2797(); };
// ??1Rva000F2797@@UAE@XZ present-unmatched
Rva000F2797::~Rva000F2797() {}
void Rva000F2797_Delete(Rva000F2797 *p) { delete p; }

// ??_GRva00102188@@UAEPAXI@Z @0x001021BE 28B; calls pinned ??1 at 0x00102188
class Rva00102188 { public: __declspec(noinline) virtual ~Rva00102188(); };
// ??1Rva00102188@@UAE@XZ present-unmatched
Rva00102188::~Rva00102188() {}
void Rva00102188_Delete(Rva00102188 *p) { delete p; }

// ??_GRva001041D8@@UAEPAXI@Z @0x00104723 28B; calls pinned ??1 at 0x001041D8
class Rva001041D8Base0 { public: virtual ~Rva001041D8Base0(); private: char m_unmodelled[0x8]; };
// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x001042C7 in its vtable is target evidence for it.
class Rva001041D8BaseC { public: virtual ~Rva001041D8BaseC(); };
class Rva001041D8 : public Rva001041D8Base0, public Rva001041D8BaseC { public: __declspec(noinline) virtual ~Rva001041D8(); };
// ??1Rva001041D8@@UAE@XZ present-unmatched
Rva001041D8::~Rva001041D8() {}
void Rva001041D8_Delete(Rva001041D8 *p) { delete p; }

// ??_GRva00104DB0@@UAEPAXI@Z @0x00104F16 28B; calls pinned ??1 at 0x00104DB0
class Rva00104DB0 { public: __declspec(noinline) virtual ~Rva00104DB0(); };
// ??1Rva00104DB0@@UAE@XZ present-unmatched
Rva00104DB0::~Rva00104DB0() {}
void Rva00104DB0_Delete(Rva00104DB0 *p) { delete p; }

// ??_GRva00109BEB@@UAEPAXI@Z @0x00109DB3 28B; calls pinned ??1 at 0x00109BEB
class Rva00109BEB { public: __declspec(noinline) virtual ~Rva00109BEB(); };
// ??1Rva00109BEB@@UAE@XZ present-unmatched
Rva00109BEB::~Rva00109BEB() {}
void Rva00109BEB_Delete(Rva00109BEB *p) { delete p; }

// ??_GRva001095B2@@UAEPAXI@Z @0x0010B9C9 28B; calls pinned ??1 at 0x001095B2
class Rva001095B2 { public: __declspec(noinline) virtual ~Rva001095B2(); };
// ??1Rva001095B2@@UAE@XZ present-unmatched
Rva001095B2::~Rva001095B2() {}
void Rva001095B2_Delete(Rva001095B2 *p) { delete p; }

// ??_GRva0010C785@@UAEPAXI@Z @0x0010C825 28B; calls pinned ??1 at 0x0010C785
class Rva0010C785 { public: __declspec(noinline) virtual ~Rva0010C785(); };
// ??1Rva0010C785@@UAE@XZ present-unmatched
Rva0010C785::~Rva0010C785() {}
void Rva0010C785_Delete(Rva0010C785 *p) { delete p; }

// ??_GRva0010F7EE@@UAEPAXI@Z @0x0010F7D2 28B; calls pinned ??1 at 0x0010F7EE
class Rva0010F7EE { public: __declspec(noinline) virtual ~Rva0010F7EE(); };
// ??1Rva0010F7EE@@UAE@XZ present-unmatched
Rva0010F7EE::~Rva0010F7EE() {}
void Rva0010F7EE_Delete(Rva0010F7EE *p) { delete p; }

// ??_GRva0010F83E@@UAEPAXI@Z @0x0010F822 28B; calls pinned ??1 at 0x0010F83E
class Rva0010F83E { public: __declspec(noinline) virtual ~Rva0010F83E(); };
// ??1Rva0010F83E@@UAE@XZ present-unmatched
Rva0010F83E::~Rva0010F83E() {}
void Rva0010F83E_Delete(Rva0010F83E *p) { delete p; }
