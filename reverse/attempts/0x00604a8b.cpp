// ?rva00604A8B@Rva00604A8B@@QAEXPAX0000@Z
// partial score=0.7 date=2026-10-06
// cl: /O1 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct Rva00604A8B {
  virtual void _v0();
  virtual void _v1();
  virtual void _v2();
  virtual void _v3();
  virtual void _v4();
  virtual void _v5();
  virtual void Virt18(int a0, const char* s0, const char* s1, const char* s2, void* a4, void* a5);
  void M(void* a0, void* a1, void* a2, void* a3, void* a4);
};
void Rva00604A8B::M(void* a0, void* a1, void* a2, void* a3, void* a4) {
  const char* s0 = ((AsciiString*)a0)->str();
  const char* s1 = ((AsciiString*)a1)->str();
  const char* s2 = ((AsciiString*)a2)->str();
  Virt18(0, s0, s1, s2, a3, a4);
}
