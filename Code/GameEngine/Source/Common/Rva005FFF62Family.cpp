// cl: /O1 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Rva00222A8BTarget;
extern Rva00222A8BTarget* _g_pRva00224BC9;
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
  Rva005252CDInvoke(_g_pRva00224BC9, m_04, prefix, name, idx, b);
  e->_1 = flag;
}
