// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// WorldBuilder retains AptInGameSpellBookInterface.cpp and helper identities.
// Twenty-four20B button caches start50. WB and retail agree on level4/string8.
#include "ascii_string.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_00C68508[];
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget *,void *,const char *,const char *,const int &,const char *const &);
class AptInGameSpellBookInterface {
public: class Impl {
 public: void SetButtonState(int slotNum,int state);
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