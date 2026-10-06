// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00413FC1@Rva00413FC1@@QAEPAHH@Z @0x00413FC1 54B: floor lookup in map<int,int> at +0xC via lower_bound.
// Evidence: unlock lane, rowed _M_lower_bound 0x00382A92 and rowed _M_decrement 0x000242C0, add eax+0x14 returns mapped value, callers at 0x002BCB4C and 0x004F68E5.
#include <map>
class Rva00413FC1
{
public:
  int *rva00413FC1(int key);
private:
  char m_pad00[12];
  _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > m_map0C;
};
int *Rva00413FC1::rva00413FC1(int key)
{
  _STL::map<int, int>::iterator it = m_map0C.lower_bound(key);
  if (it != m_map0C.end()) {
    if (it->first <= key)
      return &it->second;
  }
  if (it == m_map0C.begin())
    return 0;
  --it;
  return &it->second;
}
