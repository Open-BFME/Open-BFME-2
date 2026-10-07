// cl: /O1 /arch:SSE /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva005003C7@Rva005003C7@@QBE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBURva004FCD6DElement@@H@_STL@@U?$_Const_traits@U?$pair@$$CBURva004FCD6DElement@@H@_STL@@@2@@_STL@@U12@@_STL@@URva004FCD6DElement@@@Z @0x005003C7 (24B).
// Evidence: calls _Rb_tree equal_range 0x004FCD6D; callers 0x0059D2DA 0x0059DD3F; this+0x10.
#include <map>

struct Rva004FCD6DElement
{
	short words[1];
	bool operator<(const Rva004FCD6DElement &b) const { return words[0] < b.words[0]; }
	bool operator==(const Rva004FCD6DElement &b) const { return words[0] == b.words[0]; }
};

typedef _STL::map<Rva004FCD6DElement, int, _STL::less<Rva004FCD6DElement>, _STL::allocator<_STL::pair<Rva004FCD6DElement const, int> > > Rva005003C7Map;

class Rva005003C7
{
public:
	_STL::pair<Rva005003C7Map::const_iterator, Rva005003C7Map::const_iterator> rva005003C7(Rva004FCD6DElement key) const;
private:
	unsigned char m_pad[0x10];
	Rva005003C7Map m_map;
};

_STL::pair<Rva005003C7Map::const_iterator, Rva005003C7Map::const_iterator> Rva005003C7::rva005003C7(Rva004FCD6DElement key) const
{
	return m_map.equal_range(key);
}
