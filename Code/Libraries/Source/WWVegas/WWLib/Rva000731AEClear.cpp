// cl: /MD
//
// ?rva000731AE@Rva000731AE@@QAEXXZ @0x000731AE 70B via tail clear plus three array deletes
// Evidence: calls rowed delete[] 0x0002FD80 three times plus rowed clear 0x00072FE6; callers 0x00066700 0x000668AB 0x0006D668
// Retail frees +0x18 +0x38 +0x3C via delete[] then zeroes then sets +0x35 to 1 then tail-jmps to clear of embedded map at +0x4C
struct Rva00072FE6 {
  void rva00072FE6();
  unsigned char _pad[0x18];
};
void __cdecl operator delete[](void *p);
struct Rva000731AE {
  unsigned char _00[0x18];
  char *p18;
  unsigned char _1C[0x19];
  bool b35;
  unsigned char _36[2];
  char *p38;
  char *p3C;
  unsigned char _40[0x0C];
  Rva00072FE6 map4C;
  void rva000731AE();
};
void Rva000731AE::rva000731AE() {
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
  return map4C.rva00072FE6();
}
