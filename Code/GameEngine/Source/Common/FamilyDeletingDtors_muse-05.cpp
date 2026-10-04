// cl: /O1 /MD
// ??_GRva00329D0E@@QAEPAXI@Z @0x00329D98
// Deleting dtor for Rva00329D0E whose ??1 is rowed at 0x00329D0E.
// Evidence: retail push esi mov esi ecx call ??1 test flag delete ret 4;
// chain lane after landing ??1Rva00329D0E.
class Rva00329D0E { public: ~Rva00329D0E(); };
void famgenDelete(Rva00329D0E *p) { delete p; }
// ??_GRenderObjectDrawModuleInfo@FXParticleSystem@@UAEPAXI@Z @0x003A9B7B 28B
// Deleting dtor calls rowed ??1RenderObjectDrawModuleInfo@FXParticleSystem@@UAE@XZ at 0x003A9A8B then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x003A9A8B; retail push esi call ??1 test flag delete ret 4.
namespace FXParticleSystem { class RenderObjectDrawModuleInfo { public: __declspec(noinline) virtual ~RenderObjectDrawModuleInfo(); private: int m_famgen; }; }
FXParticleSystem::RenderObjectDrawModuleInfo::~RenderObjectDrawModuleInfo() { m_famgen = 0; }
void famgenDelete(FXParticleSystem::RenderObjectDrawModuleInfo *p) { delete p; }
// ??_GLifeEventModuleInfo@FXParticleSystem@@UAEPAXI@Z @0x003AA011 28B
// Deleting dtor calls rowed ??1LifeEventModuleInfo@FXParticleSystem@@UAE@XZ at 0x003A9F8A then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x003A9F8A; retail push esi call ??1 test flag delete ret 4.
namespace FXParticleSystem { class LifeEventModuleInfo { public: __declspec(noinline) virtual ~LifeEventModuleInfo(); private: int m_famgen; }; }
FXParticleSystem::LifeEventModuleInfo::~LifeEventModuleInfo() { m_famgen = 0; }
void famgenDelete(FXParticleSystem::LifeEventModuleInfo *p) { delete p; }
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
// ??_GRva001DC0EC@@QAEPAXI@Z @0x001DC1E1 28B
// Deleting dtor calls rowed ??1Rva001DC0EC@@QAE@XZ at 0x001DC0EC then rowed operator delete at 0x0002FD60.
// Evidence: chain lane after landing 0x001DC0EC; retail push esi call ??1 test flag delete ret 4.
class Rva001DC0EC { public: ~Rva001DC0EC(); };
void famgenDelete(Rva001DC0EC *p) { delete p; }
