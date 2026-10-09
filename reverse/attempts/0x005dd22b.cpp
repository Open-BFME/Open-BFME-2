// ?rva005DD22B@Rva005DD22B@@QAEXXZ
// partial score=0.92 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 005DD22B..005DD2D3: register the two observed AptStats callbacks.
// The containing class name and member-function identities are not inferred
// from the strings. The native callback payloads are (this, code pointer),
// with targets 005DD14D (RET12) and 005DD1D0 (RET4). The second adder is
// reached through the owner at +18, then its embedded adder at +4.
#include "ascii_string.h"
class __single_inheritance Rva005DD22B;
struct DelegateDesc { void *m_object; void (Rva005DD22B::*m_method)(); };
class Rva00579E47 { public: Rva00579E47(const DelegateDesc &); private: void *m_ptr; };
class AptScreenInitGadgets;
class AptCommandMap;
template<class T> class AptRef : public Rva00579E47 {
public:
 __forceinline AptRef(const DelegateDesc &d) : Rva00579E47(d) {}
 AptRef(const AptRef &);
 ~AptRef();
};
void _bfme_setAptScreenRef(const AsciiString &, AptRef<AptScreenInitGadgets>);
class AptCommandMapAdder { public: void AddCommandMap(const AsciiString &, AptRef<AptCommandMap>); };
struct Rva005DD22BOwner { unsigned word0; AptCommandMapAdder adder; };
class Rva005DD22B {
public:
 void rva005DD22B();
 void callback005DD14D();
 void callback005DD1D0();
private:
 unsigned char prefix[0x18];
 Rva005DD22BOwner *owner;
};
void Rva005DD22B::rva005DD22B() {
 DelegateDesc payload;
 {
  AsciiString name("AptStats::InitGadgets");
  payload.m_method = &Rva005DD22B::callback005DD14D;
  payload.m_object = this;
  _bfme_setAptScreenRef(name, AptRef<AptScreenInitGadgets>(payload));
 }
 {
  AsciiString name("Stats::OnSelectFaction");
  payload.m_method = &Rva005DD22B::callback005DD1D0;
  payload.m_object = this;
  owner->adder.AddCommandMap(name, AptRef<AptCommandMap>(payload));
 }
}
