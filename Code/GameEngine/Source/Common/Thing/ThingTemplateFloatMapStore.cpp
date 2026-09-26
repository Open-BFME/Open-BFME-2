// cl: /O1 /EHsc /arch:SSE /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ThingTemplate float-map store (shared float helper). The map access uses
// the rowed integer-float subscript directly.

#include <map>

class ThingTemplate
{
	char m_pad[0x3A0];
	_STL::map<int, float> m_floatMap;

public:
	void Rva0033D396StoreFloat(int key, float value);
};

void ThingTemplate::Rva0033D396StoreFloat(int key, float value)
{
	m_floatMap[key] = value;
}
