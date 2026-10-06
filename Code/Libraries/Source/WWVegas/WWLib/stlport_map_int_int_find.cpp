// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva004260DE@Rva004260DE@@QAEPAHH@Z @0x004260DE 31B evidence: map<int int> at +0x0C via rowed _M_find 0x388F63 plus header compare plus second at +0x14 plus callers 0x45EE06 0x45F134
#include <map>
class Rva004260DE
{
public:
	int *rva004260DE(int key);
private:
	char _00[0xc];
	_STL::map<int, int> m_map;
};
int *Rva004260DE::rva004260DE(int key)
{
	_STL::map<int, int>::iterator it = m_map.find(key);
	if (it == m_map.end())
		return 0;
	return &it->second;
}
