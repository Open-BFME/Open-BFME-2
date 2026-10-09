// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder retains AptInGameSpellBookInterface.cpp and helper identities.
// Twenty-four20B button caches start50. WB and retail agree on level4/string8.
#include "ascii_string.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C68508[];
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const int &,const char *const &);
namespace AptUtils { AsciiString DotPath2SlashPath(const char *); }
struct DelegateDesc;
struct SpellOverButtonDesc { void *receiver;int slotNum; };
class Rva0052A7C1 {public:Rva0052A7C1 &rva0052A7C1(const DelegateDesc *);private:void *ptr;};
class AptOverButtonHandler {public:void *vtable;int refCount;};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
template<class T> class AptRef {
public:
 AptRef(const SpellOverButtonDesc *desc) {((Rva0052A7C1 *)this)->rva0052A7C1((const DelegateDesc *)desc);}
 AptRef(const AptRef &other):ptr(other.ptr){if(ptr)++ptr->refCount;}
 ~AptRef(){if(ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)ptr);}
private:T *ptr;
};
class AptPlayer {public:void AddOverButtonHandler(const AsciiString &,AptRef<AptOverButtonHandler>);};
class AptInGameSpellBookInterface {
public: class Impl {
 public: void SetButtonState(int slotNum,int state);
 void OnClipLoaded(const char *params);
 static AsciiString GetButtonImageTargetName(int slotNum);
 private:
 struct ButtonSlot { int unknown0;int state;char unknown8[12]; };
 void *m_owner;void *m_level;AsciiString m_clipName;char unknownC[0x44];ButtonSlot m_slots[24];
};
};
// WB013C4DD0 and native92B52A414..52A470: cdecl hidden AsciiString return.
// Format a local then copy it into the returned object before local cleanup.
AsciiString AptInGameSpellBookInterface::Impl::GetButtonImageTargetName(int slotNum) {
 AsciiString result;
 result.format("InGameSpellBookSpell%dImage",slotNum+1);
 return result;
}
// WB013C5600 and native244B52AC3C..52AD30: clip name plus24 hover handlers.
// The descriptor stores receiver/index and constructs the by-value reference in place.
void AptInGameSpellBookInterface::Impl::OnClipLoaded(const char *params) {
 m_clipName=params;
 AsciiString prefix;
 prefix.format("Palantir/%s/Spell%%d/",AptUtils::DotPath2SlashPath(m_clipName.str()).str());
 for(int i=0;i<24;++i) {
  AsciiString path;
  path.format(prefix.str(),i+1);
  SpellOverButtonDesc descriptor={this,i};
  ((AptPlayer *)g_bfmeAptWindowManager)->AddOverButtonHandler(path,&descriptor);
 }
}
// WB013C5DC0 and native89B52A804..52A85D RET8. The one-based index is
// a const-reference temporary; retail reuses the dead slotNum argument for it.
void AptInGameSpellBookInterface::Impl::SetButtonState(int slotNum,int state) {
 ButtonSlot &slot=m_slots[slotNum];
 if(slot.state==state)return;
 Rva005252CDInvoke((Rva00222A8BTarget *)g_bfmeAptWindowManager,m_level,m_clipName.str(),"SetButtonState",slotNum+1,g_00C68508[state]);
 slot.state=state;
}