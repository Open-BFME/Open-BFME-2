// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004FF8DA@Rva004FF8DA@@QAE_NHH@Z @0x004FF8DA 54B: bounds-checked vector-array presence via rowed int-int _M_find 0x00388F63. Evidence: unlock lane ret 8 two ints lea-esp-8 key plus ecx+0x38 tree plus imul 0xC stride plus idx<8 plus (finish-start)/0x58 count.
#include <map>
#include <vector>

struct BfmePod88
{
	int a[22];
};

class Rva004FF8DA
{
public:
	bool rva004FF8DA(int idx, int key);
private:
	char m_pad[0x38];
	_STL::map<int, int> m_map;
};

bool Rva004FF8DA::rva004FF8DA(int idx, int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	_STL::vector<BfmePod88> *arr = *(_STL::vector<BfmePod88> **)((char *)it._M_node + 0x14);
	_STL::vector<BfmePod88> *v = &arr[idx];
	if (idx < 8 && v->size() > 0)
		return true;
	return false;
}
