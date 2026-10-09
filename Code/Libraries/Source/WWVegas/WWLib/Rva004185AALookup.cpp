// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// LivingWorldAutoResolveBodyTemplate::getRegenRateForLevel (WorldBuilder name, LivingWorldAutoResolveBody.cpp line 88: lower_bound in the +0x0C map).
// stlport
// was ?rva004185AA@Rva004185AA@@QAEMH@Z @0x004185AA 58B floor lookup over map<int,float> at +0xc via rowed lower_bound 0x00382A92 and rowed decrement 0x000242C0 default BfmeZeroRange caller 0x0059AF30
#include <map>

// Native signed comparison is already inline in the recovered operation.
// Keep its external owner in stlport_list_int.cpp at RVA0x00626F90.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}

extern const float BfmeZeroRange; // ?BfmeZeroRange@@3MB

class LivingWorldAutoResolveBodyTemplate
{
public:
	float getRegenRateForLevel(int key);
private:
	char m_pad[12];
	_STL::map<int, float> m_map;
};

float LivingWorldAutoResolveBodyTemplate::getRegenRateForLevel(int key)
{
	_STL::map<int, float>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || it->first > key) {
		if (it == m_map.begin())
			return BfmeZeroRange;
		--it;
	}
	return it->second;
}
