// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// CrowdResponseTemplate::getCrowdResponseDataForThreshold (WorldBuilder name, CrowdResponseSystem.cpp line 102: lower_bound in the +0x08 threshold map).
// stlport
// was ?rva0041530B@Rva0041530B@@QAEPAHH@Z, retail 0x0041530B 64B. Floor lookup over map<int,int> at +8 via rowed lower_bound 0x00382A92 and rowed decrement 0x000242C0. Empty is node_count at +0xC. Caller 0x004DAD40.
#include <map>

class CrowdResponseTemplate
{
public:
	int *getCrowdResponseDataForThreshold(int key);
private:
	unsigned char m_pad[8];
	_STL::map<int, int> m_map;
};

int *CrowdResponseTemplate::getCrowdResponseDataForThreshold(int key)
{
	if (m_map.empty())
		return 0;
	_STL::map<int, int>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || it->first > key)
	{
		if (it == m_map.begin())
			return 0;
		--it;
	}
	return &it->second;
}
