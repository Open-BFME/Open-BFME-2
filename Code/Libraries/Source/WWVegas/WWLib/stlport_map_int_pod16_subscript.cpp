// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00257252@Rva00257252@@QAEAAUBfmePod16@@ABH@Z @0x00257252 92B
// Pod16 get-or-create via lower_bound plus hint insert with zero Pod16.
// Evidence: chain lane (calls our 0x00256F67 insert); caller 0x0025740B
// passes key at +0x14 and fills 16B at returned pointer; unblocks 0x002573EE.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
struct BfmePod16 { int a[4]; };
typedef _STL::pair<const int, BfmePod16> Pod16MapValue;
typedef _STL::map<int, BfmePod16, _STL::less<int>, _STL::allocator<Pod16MapValue> > Pod16Map;
class Rva00257252
{
public:
	BfmePod16 &rva00257252(const int &key);
private:
	Pod16Map m_map;
};
BfmePod16 &Rva00257252::rva00257252(const int &key)
{
	Pod16Map::iterator i = m_map.lower_bound(key);
	if (i == m_map.end() || m_map.key_comp()(key, (*i).first))
	{
		BfmePod16 zero = { 0, 0, 0, 0 };
		i = m_map.insert(i, Pod16MapValue(key, zero));
	}
	return (*i).second;
}
