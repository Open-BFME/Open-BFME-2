// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005B2DDF@Rva005B2DDF@@QAEPAXII@Z @0x005B2DDF 42B
// Unlock lane: bounds-checked 2D grid lookup over a vector of 16-byte rows at +0x14.
// count = (finish-start)/16 via vector<BfmeE16>::size(); if a>=count return 0;
// if b>=4 return 0; else return ((void**)row)[a*4+b]. Callers 0x005B2E09/0x005B2E35
// (prev/next search loops) and 0x005B314B/0x005B3245 (sscanf %d,%d Apt tooltips
// CAH Palantir/HeroPowers) deref the result as a pointer. BfmeE16 is a size
// stand-in per stlport_vector_e16_o1.cpp; the 16B stride and sar-4 match retail.
#include <vector>
struct BfmeE16 { float x, y, z, w; };
struct Rva005B2E09Cell { int m_00; int m_04; int m_08; };
struct Rva005B269DRow { void* slots[4]; void rva005B269D(Rva005B2E09Cell* c, int v, unsigned idx); };
class Rva005B2DDF {
  char m_00[0x14];
  _STL::vector<BfmeE16> m_14;
public:
  void* rva005B2DDF(unsigned a, unsigned b);
  void* rva005B2E09(Rva005B2E09Cell* c);
  void* rva005B2E35(Rva005B2E09Cell* c);
};
void* Rva005B2DDF::rva005B2DDF(unsigned a, unsigned b)
{
  if (a >= m_14.size())
    return 0;
  if (b >= 4)
    return 0;
  return ((void**)&m_14[0])[a * 4 + b];
}
void* Rva005B2DDF::rva005B2E09(Rva005B2E09Cell* c)
{
  for (int cur = c->m_08 - 1; cur >= 0; ) {
    void* r = rva005B2DDF(c->m_04, cur);
    --cur;
    if (r != 0)
      return r;
  }
  return 0;
}
void* Rva005B2DDF::rva005B2E35(Rva005B2E09Cell* c)
{
  for (int cur = c->m_08 + 1; cur < 4; ) {
    void* r = rva005B2DDF(c->m_04, cur);
    ++cur;
    if (r != 0)
      return r;
  }
  return 0;
}
void Rva005B269DRow::rva005B269D(Rva005B2E09Cell* c, int v, unsigned idx)
{
  if (c->m_04 >= 0 && c->m_08 >= 0)
    return;
  if (idx >= 4)
    return;
  void** slot = (void**)((char*)this + idx * 4);
  if (*slot != 0)
    return;
  c->m_04 = v;
  c->m_08 = idx;
  *slot = c;
}
