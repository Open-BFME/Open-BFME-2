// ?Swap@Rva005FFFC1@@QAEXHH@Z
// partial score=0.6 date=2026-10-06
// cl: /O1 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
class Rva00222A8BTarget;
extern Rva00222A8BTarget* _g_pRva00224BC9;
int __cdecl Rva00525235Fire(void* a1, void* a2, const char* a3, const char* a4, int* a5, int* a6);
struct Rva005FFFC1 {
  void* m_00;
  void* m_04;
  AsciiString m_08;
  unsigned char m_pad[0x24 - 0x08 - sizeof(AsciiString)];
  struct Elem { int _0[2]; int _8; } m_24[1]; // idx*12? base +36? use manual
  void Swap(int i0, int i1);
};
void Rva005FFFC1::Swap(int i0, int i1) {
  if (i0 == i1) return;
  // array at this+36? (i+3)*12
  char* base = (char*)this;
  int* e0 = (int*)(base + (i0 + 3) * 12);
  int* e1 = (int*)(base + (i1 + 3) * 12);
  const char* prefix = ((AsciiString*)((char*)this + 8))->str();
  const char* name = "SlideHeroArmyPanel";
  int t0 = 0; (void)t0;
  Rva00525235Fire(_g_pRva00224BC9, m_04, prefix, name, (int*)(e1 + 2), (int*)e1);
  const char* prefix2 = ((AsciiString*)((char*)this + 8))->str();
  Rva00525235Fire(_g_pRva00224BC9, m_04, prefix2, name, (int*)(e0 + 2), (int*)e0);
  int tmp = e0[2];
  e0[2] = e1[2];
  e1[2] = tmp;
}
