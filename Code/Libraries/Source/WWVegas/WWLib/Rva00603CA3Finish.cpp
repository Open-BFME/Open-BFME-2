// ?rva00603CA3@Rva00603C0F@@QAE_NPBDPAUOut603CA3@@@Z
// partial score=0.95 date=2026-09-29
// ?rva00603CA3@Rva00603C0F@@QAE_NPBDPAUOut603CA3@@@Z
// partial score=0.95 date=2026-09-29
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#include <map>
extern "C" char *__cdecl strcpy(char *dest, const char *src);
char *__cdecl Rva00605365(char *);
struct Rva00603A00Mapped { unsigned int m_bits; };
struct Rva006038D4Less { bool operator()(const char *a, const char *b) const; };
typedef _STL::pair<const char* const, Rva00603A00Mapped> InnerPair;
typedef _STL::map<const char*, Rva00603A00Mapped, Rva006038D4Less> InnerMap;
typedef _STL::pair<const char* const, InnerMap> OuterPair;
typedef _STL::map<const char*, InnerMap, Rva006038D4Less> OuterMap;
struct Out603CA3 { unsigned int m_a; unsigned int m_b; unsigned int m_c; unsigned int m_d; };
struct Rva00603C0F {
  char m_pad[4];
  OuterMap m_map;
  const void *rva00603C0F(const char *a, const char *b);
  bool rva00603CA3(const char *a, Out603CA3 *out);
};
bool Rva00603C0F::rva00603CA3(const char *a, Out603CA3 *out) {
  char buf[260];
  strcpy(buf, a);
  const char *n = Rva00605365(buf);
  const void *found = rva00603C0F(buf, n);
  if (!found) return false;
  if (!out) return true;
  out->m_a = 0;
  out->m_b = *(unsigned int*)((char*)found + 8);
  out->m_c = 0;
  out->m_d = 0;
  return true;
}
