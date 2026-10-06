// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00413BC5@Rva00413BC5@@QAEHH@Z @0x00413BC5 61B: map<int,int> find with stride extension.
// Evidence: unlock lane, rowed _M_find 0x00388F63 and rowed _M_decrement 0x000242C0, found returns +0x14, miss with size!=0 uses (key-last_key)*stride+last_value, caller at 0x002BCA37.
#include <map>
class Rva00413BC5
{
public:
  int rva00413BC5(int key);
private:
  _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > m_map00;
  int m_stride0C;
};
int Rva00413BC5::rva00413BC5(int key)
{
  _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator it = m_map00.find(key);
  if (it == m_map00.end()) {
    if (m_map00.empty())
      return 0;
    _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > >::iterator last = m_map00.end();
    --last;
    return (key - last->first) * m_stride0C + last->second;
  }
  return it->second;
}
