// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii
//
// ?AddExternHandler@AptPlayer@@QAEXABVAsciiString@@HV?$AptRef@VAptExternHandler@@@@@Z
// retail 0x0022445D..0x002244CA (109 bytes ret 0xC; EH prolog FuncInfo 0x00B6F450).
// WorldBuilder twin AptPlayer::AddExternHandler (AptPlayer.cpp wb 0xB91990,
// assert "Extern added to different function:" at line 644): ignore a null
// handler; look the name up in the extern map at +0x20 (the find-or-insert
// subscript 0x0022402A, the same map SetExtern reads); keep a counted copy
// of the existing handler and leave an occupied entry alone; otherwise store
// the handler (+0) and its context word (+4).  Same shape as the matched
// AddCommandMap 0x002243E3 in AptPlayer.cpp.
//
// The handler assignment is the shared AptRef<T>::operator= body at
// 0x002174A4 (rowed as typed twins for AptCommandMap AptCustomRender
// AptTimer and AptOverButtonHandler).  Its definition must be visible here:
// only then does cl drop the null test before the parameter's final release
// as retail does.  This unit therefore also emits the AptExternHandler
// instantiation -- a byte-and-relocation twin of 0x002174A4.
#include "ascii_string.h"

struct TargetRef00217D4C { virtual void *destroy(unsigned); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

class AptRefCounted { public: void *m_vtbl; int m_refCount; };
class AptExternHandler : public AptRefCounted {};
template <class T> class AptRef {
public:
 T *m_ptr;
 AptRef(const AptRef &other) : m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->m_refCount; }
 ~AptRef()
 {
  if (m_ptr)
   ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
 }
 __declspec(noinline) AptRef &operator=(const AptRef &other);
};
template<class T> AptRef<T> &AptRef<T>::operator=(const AptRef &other) {
 if(this != &other) {
  if(other.m_ptr) ++other.m_ptr->m_refCount;
  if(m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
  m_ptr=other.m_ptr;
 }
 return *this;
}

// The map's twelve-byte record value: handle then context word.
struct AptExternEntry { AptRef<AptExternHandler> handler; int context; };
class Rva00468520;
class Rva0022402A { public: Rva00468520 &rva0022402A(const AsciiString &); };

class AptPlayer {
public:
 void AddExternHandler(const AsciiString &name, int context, AptRef<AptExternHandler> handler);
private:
 unsigned char m_pad000[0x20];
 Rva0022402A m_externMap; // +0x20
};

void AptPlayer::AddExternHandler(const AsciiString &name, int context, AptRef<AptExternHandler> handler)
{
 if(!handler.m_ptr) return;
 AptExternEntry &entry = reinterpret_cast<AptExternEntry &>(m_externMap.rva0022402A(name));
 AptRef<AptExternHandler> oldFunc = entry.handler;
 if(oldFunc.m_ptr) return;
 entry.handler = handler;
 entry.context = context;
}
