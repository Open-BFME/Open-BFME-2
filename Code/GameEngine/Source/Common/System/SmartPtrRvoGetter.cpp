// cl: /O1 /Oy- /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Target165B3FDAEB and30B3FDA90; WB10726E0 independently exposes two
// conditional stop calls through twelve-byte intrusive handles at1C/15C.
// BFME1 2f243 LivingWorldManagerParticleSystem.cpp supplies operator-> and
// nonthrowing conditional cleanup semantics; target proves every offset/call.
// Returned ParticleSystem is explicitly viewed as the existing opaque getter
// or byte setter: their established address-derived names remain uncertain.
// Existing in-image null-factory and cleanup providers are reused unchanged.
// Explicit null-first branch and actual nonthrowing destructor close native
// late EBX push and avoid an extra final EH-state reset. No new pins/aliases.
class ParticleSystem;
ParticleSystem *Make001FCBD7();
class Rva001F384AByteZeroSetter { public: void disable(); };
class Rva003FDA90SmartField;
class RvaSmartPtr12 { public:
 RvaSmartPtr12(const RvaSmartPtr12 &);
 void rva0004CBC0() throw();
 // ?RvaSmartPtr12::~RvaSmartPtr12 present-unmatched
 ~RvaSmartPtr12() throw() { if(m_ptr) rva0004CBC0(); }
 operator bool() const { return m_ptr!=0; }
 ParticleSystem *operator->() const { if(!m_ptr) return Make001FCBD7();return m_ptr; }
 ParticleSystem *m_ptr;void *prev,*next;
};
class Rva003FDA90SmartField { public: RvaSmartPtr12 get() const; private: char prefix[0x15c];RvaSmartPtr12 value; };
class Rva003FDD05Host { public: void rva003FDAEB(); char prefix[0x1c];RvaSmartPtr12 handle; };
void Rva003FDD05Host::rva003FDAEB() {
 if(handle) {
  reinterpret_cast<Rva001F384AByteZeroSetter *>(handle.operator->())->disable();
  if(reinterpret_cast<Rva003FDA90SmartField *>(handle.operator->())->get())
   reinterpret_cast<Rva001F384AByteZeroSetter *>(reinterpret_cast<Rva003FDA90SmartField *>(handle.operator->())->get().operator->())->disable();
 }
}

RvaSmartPtr12 Rva003FDA90SmartField::get() const { return value; }
