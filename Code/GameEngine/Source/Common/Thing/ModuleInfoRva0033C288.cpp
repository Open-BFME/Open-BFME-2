// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033C288@ModuleInfo@@QBEPBHH@Z @0x0033C288 43B: map<int int> find at +0x3AC guarded by flag at +0x3B0 returns mapped int* else 0.
// Evidence: calls rowed map _M_find at 0x00388F63; node+0x14 value (0x18 node via stlport_map_int_int_os); caller 0x00268A46; neighbours ModuleInfo rows.
#include <map>
class ModuleInfo
{
public:
	const int *rva0033C288(int key) const;
private:
	char m_pad[0x3AC];
	_STL::map<int, int> m_map3AC;
};
const int *ModuleInfo::rva0033C288(int key) const
{
	if (m_map3AC.empty())
		return 0;
	else
	{
		_STL::map<int, int>::const_iterator it = m_map3AC.find(key);
		if (it == m_map3AC.end())
			return 0;
		return &it->second;
	}
}
