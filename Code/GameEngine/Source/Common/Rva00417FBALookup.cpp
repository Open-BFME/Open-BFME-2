// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00417FBA@Rva00417FBA@@QAEPAHH@Z @0x00417FBA 54B. Floor lookup over
// map<int,int> at +8 via rowed lower_bound 0x00382A92 and rowed decrement
// 0x000242C0. No empty check (cf Rva0041530B 64B which has one). Caller
// 0x004F9FC4. Landing unblocks 0x004F9F39.
#include <map>

class Rva00417FBA
{
public:
	int *rva00417FBA(int key);
private:
	unsigned char m_pad[8];
	_STL::map<int, int> m_map;
};

int *Rva00417FBA::rva00417FBA(int key)
{
	_STL::map<int, int>::iterator it = m_map.lower_bound(key);
	if (it == m_map.end() || it->first > key)
	{
		if (it == m_map.begin())
			return 0;
		--it;
	}
	return &it->second;
}
