// cl: /MD
//
// ?rva00073C7A@Rva00073C7A@@QAEXXZ @0x00073C7A 70B via tail clear plus three array deletes
// Evidence: calls rowed delete[] 0x0002FD80 three times plus rowed clear 0x00072FE6; callers 0x000668C3 0x0006D68C 0x00074414
// Retail frees +0x18 +0x38 +0x3C via delete[] then zeroes then sets +0x35 to 1 then tail-jmps to clear of embedded map at +0x44
struct Rva00072FE6 {
  void rva00072FE6();
  unsigned char _pad[0x18];
};
void __cdecl operator delete[](void *p);
struct Rva00073C7A {
  unsigned char _00[0x18];
  char *p18;
  unsigned char _1C[0x19];
  bool b35;
  unsigned char _36[2];
  char *p38;
  char *p3C;
  unsigned char _40[0x04];
  Rva00072FE6 map44;
  void rva00073C7A();
};
void Rva00073C7A::rva00073C7A() {
  if (p18)
    operator delete[](p18);
  p18 = 0;
  if (p38)
    operator delete[](p38);
  p38 = 0;
  if (p3C)
    operator delete[](p3C);
  p3C = 0;
  b35 = true;
  return map44.rva00072FE6();
}
