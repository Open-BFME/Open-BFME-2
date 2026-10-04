// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0033C259@ModuleInfo@@QBEMH@Z @0x0033C259 47B: map<int int> find at +0x3A0 guarded by flag at +0x3A4 returns float bits of mapped int else BfmeZeroRange.
// Evidence: calls rowed map _M_find at 0x00388F63; node+0x14 fld (0x18 node via stlport_map_int_int_os); caller 0x00268B64; neighbours ModuleInfo rows.
#include <map>
extern const float BfmeZeroRange;
class ModuleInfo
{
public:
	float rva0033C259(int key) const;
private:
	char m_pad[0x3A0];
	_STL::map<int, int> m_map3A0;
};
float ModuleInfo::rva0033C259(int key) const
{
	if (m_map3A0.empty())
		return BfmeZeroRange;
	else
	{
		_STL::map<int, int>::const_iterator it = m_map3A0.find(key);
		if (it == m_map3A0.end())
			return BfmeZeroRange;
		return *(const float *)&it->second;
	}
}
