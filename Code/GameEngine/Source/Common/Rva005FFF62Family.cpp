// cl: /O1 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Rva00222A8BTarget;
class Rva00222A8BTarget; extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005252CDInvoke(Rva00222A8BTarget* target, void* level, const char* prefix, const char* name, const int& a, const char* const& b);
struct Rva005FFF62 {
  void* m_00;
  void* m_04;
  AsciiString m_08;
  // ... pad to 0x4C? array at +0x4C?
  unsigned char m_pad[0x4C - 0x08 - sizeof(AsciiString)];
  struct Elem { unsigned char _0; unsigned char _1; } m_4C[1]; // idx*2 +0x4C, uses [esi+1]
  void Set(int idx, bool flag);
};
void Rva005FFF62::Set(int idx, bool flag) {
  Elem* e = &m_4C[idx];
  if (flag == e->_1) return;
  const char* b = flag ? "_up" : "_disabled";
  const char* prefix = m_08.str();
  const char* name = "SetSwapButtonState";
  Rva005252CDInvoke(((Rva00222A8BTarget *)g_bfmeAptWindowManager), m_04, prefix, name, idx, b);
  e->_1 = flag;
}
// 0x005FBAFE sibling.
void __cdecl rva00977C23(int* a0, int* a1, int a2, void* a3, int a4, int a5);
struct Rva005FBAFE {
  void* m_00;
  void* m_04;
  AsciiString m_08;
  unsigned char m_pad[0x3C - 0x08 - sizeof(AsciiString)];
  struct Elem { unsigned char _0[4]; unsigned char _4; unsigned char _5[3]; } m_3C[1];
  void Set2(int idx);
};
void Rva005FBAFE::Set2(int idx) {
  Elem* e = &m_3C[idx];
  if (e->_4 == 0) return;
  bool b0 = false;
  const char* prefix = m_08.str();
  const char* name = "SetBannerVisibility";
  rva00977C23((int*)((Rva00222A8BTarget *)g_bfmeAptWindowManager), (int*)m_04, (int)prefix, (void*)name, (int)&idx, (int)&b0);
  e->_4 = 0;
}

// ?rva005FBB9E@Rva005FBB9E@@QAEXH@Z @0x005FBB9E 8B member forwarder to rowed
// ?Set2@Rva005FBAFE@@QAEXH@Z (0x005FBAFE; int arg passes through the shared
// stack slot). No callers. Honest address name.
class Rva005FBB9E
{
public:
  void rva005FBB9E(int idx);
private:
  char m_pad[4];
  Rva005FBAFE *m_member;
};
void Rva005FBB9E::rva005FBB9E(int idx)
{
  return m_member->Set2(idx);
}

// ?rva0060005A@Rva0060005A@@QAEXH_N@Z @0x0060005A 8B member forwarder to rowed
// ?Set@Rva005FFF62@@QAEXH_N@Z (0x005FFF62; int bool args pass through shared
// stack slots). Caller 0x005FB121. Honest address name.
class Rva0060005A
{
public:
  void rva0060005A(int idx, bool flag);
private:
  char m_pad[4];
  Rva005FFF62 *m_member;
};
void Rva0060005A::rva0060005A(int idx, bool flag)
{
  return m_member->Set(idx, flag);
}
