// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00418573@Rva00418573@@QAEMH@Z @0x00418573 55B floor lookup over map<int,float> at +0 via rowed lower_bound 0x00382A92 and rowed decrement 0x000242C0 default 1.0f callers 0x004F99CC 0x0059AECC
#include <map>

extern float g_Va00BBB8D8;

class Rva00418573
{
public:
	float rva00418573(int key);
private:
	_STL::map<int, float> m_map;
};

float Rva00418573::rva00418573(int key)
{
	_STL::map<int, float>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || it->first > key) {
		if (it == m_map.begin())
			return g_Va00BBB8D8;
		--it;
	}
	return it->second;
}
