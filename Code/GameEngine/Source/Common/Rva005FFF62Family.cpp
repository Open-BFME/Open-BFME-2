// cl: /O1 /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

// Keep the verified 125-byte Apt helper visible without inlining its call.
// Its bool argument is read before the dispatch; this lets the caller retain
// the incoming flag directly in BL, matching retail.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

AsciiString Rva00222834Get(int val);


static __forceinline const char *GetStr(const AsciiString &asciiString)
{
	char *stringData = *(char **)(void *)&asciiString;
	return stringData ? stringData + 8 : "";
}

// Primary owner: Rva00577AE9AptCall.cpp; this COMDAT copy is independently
// verified against the same complete 125-byte body and relocations.
// Retail 0x00577C23 125B, the next body: the same forward with an int and a
// bool, the bool as "0"/"1" through the rowed 0x004E678B (argc 2). Caller
// 0x005F31E0 ("SetUnitIconSlotVisibility", with the slot's Apt index).
char **__cdecl Rva004E678BGet(char **out, bool flag);

static inline const char *Rva00577C23Flag(const bool &b)
{
	char *text;
	return *Rva004E678BGet(&text, b);
}

inline __declspec(noinline) int __cdecl Rva00577C23AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, int *pInt, bool *pFlag)
{
	return target->rva00222B19(level, prefix, function, 2, GetStr(Rva00222834Get(*pInt)), (void *)Rva00577C23Flag(*pFlag), 0, 0, 0);
}

class Rva00222A8BTarget;
class Rva00222A8BTarget; extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget* target, void* level, const char* prefix, const char* name, const int& a, const char* const& b);
struct Rva005FFF62 {
  void* m_00;
  void* m_level;
  AsciiString m_prefix;
  // ... pad to 0x4C? array at +0x4C?
  unsigned char m_pad[0x4C - 0x08 - sizeof(AsciiString)];
  struct Elem { unsigned char _0; unsigned char _1; } m_swapButtonStates[1]; // idx*2 +0x4C, uses [esi+1]
  void Set(int idx, bool flag);
  void SetSwapButtonVisibility(int idx, bool visible);
};
void Rva005FFF62::Set(int idx, bool flag) {
  Elem* elem = &m_swapButtonStates[idx];
  if (flag == elem->_1) return;
  const char* b = flag ? "_up" : "_disabled";
  const char* prefix = m_prefix.str();
  const char* name = "SetSwapButtonState";
  Rva005252CDInvoke(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_level, prefix, name, idx, b);
  elem->_1 = flag;
}
// ?SetSwapButtonState@Rva0060005A@@QAEXH_N@Z @0x0060005A 8B member forwarder to rowed
// ?Set@Rva005FFF62@@QAEXH_N@Z (0x005FFF62; int bool args pass through shared
// stack slots). Caller 0x005FB121. Honest address name.
class Rva0060005A
{
public:
  void SetSwapButtonState(int idx, bool flag);
private:
  char m_pad[4];
  Rva005FFF62 *m_member;
};
void Rva0060005A::SetSwapButtonState(int idx, bool flag)
{
  return m_member->Set(idx, flag);
}

// Native 005FFFC1..00600052: swap two 12-byte panel records' trailing
// words after firing SlideHeroArmyPanel twice. The original stack indices
// are each passed by address; the other argument points at the opposite
// record's trailing word. A matching shape alone does not establish the
// containing class or the unobserved first eight record bytes.
int __cdecl Rva00525235Fire(void *, void *, const char *, const char *, int *, int *);
struct Rva005FFFC1 {
 void *word0;
 void *level;
 AsciiString prefix;
 void Swap(int firstIndex, int secondIndex);
};
void Rva005FFFC1::Swap(int firstIndex, int secondIndex) {
 if (firstIndex == secondIndex) return;
 int *first = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + (firstIndex + 3) * 12);
 int *second = reinterpret_cast<int *>(reinterpret_cast<char *>(this) + (secondIndex + 3) * 12);
 Rva00525235Fire(g_bfmeAptWindowManager, level, prefix.str(), "SlideHeroArmyPanel", &firstIndex, second + 2);
 Rva00525235Fire(g_bfmeAptWindowManager, level, prefix.str(), "SlideHeroArmyPanel", &secondIndex, first + 2);
 int saved = first[2];
 first[2] = second[2];
 second[2] = saved;
}

// Native600062..60006A loads receiver+4 then tail jumps to the owned
// 145B RET8 Swap5FFFC1. Two int arguments retain their original stack
// slots. Only this forwarding view is claimed; outer type/name unknown.
struct Rva00600062SwapForward {
    char opaque[4]; Rva005FFFC1 *impl;
    void forward(int first, int second);
};
void Rva00600062SwapForward::forward(int first, int second) {
    impl->Swap(first,second);
}

// Native005FFF17..005FFF62 RET8; WB163B8D0 names the visibility operation.
// Retail updates byte0 of the two-byte swap-button state after forwarding
// the original index and flag slots to the existing 125-byte Apt helper.
// The containing class remains an address view; only these accesses are proven.
void Rva005FFF62::SetSwapButtonVisibility(int idx, bool visible) {
  const bool saved=visible;
  Elem *state=&m_swapButtonStates[idx];
  if(saved==state->_0) return;
  Rva00577C23AptCall((Rva00222A8BTarget *)g_bfmeAptWindowManager,m_level,m_prefix.str(),"SetSwapButtonVisibility",&idx,&visible);
  state->_0=saved;
}

// Native00600052..0060005A: member+4 forwards both original stack arguments
// to the independently verified visibility setter at005FFF17. The enclosing
// object's identity is unproven; the adjacent state forwarder0060005A and
// panel swap forwarder00600062 already live in this family unit.
struct Rva00600052VisibilityForward {
    char opaque[4]; Rva005FFF62 *impl;
    void forward(int index, bool visible);
};
void Rva00600052VisibilityForward::forward(int index, bool visible) {
    impl->SetSwapButtonVisibility(index,visible);
}
