// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?Rva0041355DParse@@YAXPAVINI@@@Z @0x0041355D 88B: parse Pod16 via rowed 0x0041330C then insert into global store map.
// Evidence: chain lane calls just-landed 0x0041330C, rowed _M_insert 0x00256583 via insert_unique, float literal g_Va00BBB8D8, global g_00E03040 with map at +0xC.
#include <map>
struct FieldParse;
class INI
{
public:
  void initFromINI(void *what, const FieldParse *table);
};
struct BfmePod16
{
  int m_id;
  float m_f0;
  float m_f1;
  float m_f2;
};
class Rva0041330C
{
public:
  void rva0041330C(INI *ini);
};
struct HandicapStore
{
  char m_pad[12];
  _STL::map<int, BfmePod16, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod16> > > m_map0C;
};
extern float g_Va00BBB8D8;
extern HandicapStore *g_00E03040;
void Rva0041355DParse(INI *ini)
{
  BfmePod16 local;
  local.m_id = 0;
  local.m_f0 = g_Va00BBB8D8;
  local.m_f1 = g_Va00BBB8D8;
  local.m_f2 = g_Va00BBB8D8;
  ((Rva0041330C *)&local)->rva0041330C(ini);
  int key = local.m_id;
  BfmePod16 copy = local;
  g_00E03040->m_map0C.insert(_STL::pair<const int, BfmePod16>(key, copy));
}
