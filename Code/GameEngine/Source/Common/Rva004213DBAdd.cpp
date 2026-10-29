// cl: /MD
// stlport
// ?rva004213DB@Rva004210B0@@QAEXPBVModuleData@@@Z @0x004213DB 33B
// Add-if-absent over vector<ModuleData*> at +8: contains check via rowed
// 0x004210B0 then push_back via rowed 0x004DFCB0. Same this and same arg
// prove the Rva004210B0 owner. Evidence: unlock lane; callees rowed;
// caller at 0x00421568; unblocks 0x00421520.
class ModuleData;
#include <vector>

namespace _STL
{
// Bind the append to the rowed pointer-vector worker.
template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &value);
}
class Rva004210B0
{
public:
	bool rva004210B0(const ModuleData *data);
	void rva004213DB(const ModuleData *data);
private:
	char m_pad[8];
	_STL::vector<const ModuleData *> m_vec;
};
void Rva004210B0::rva004213DB(const ModuleData *data)
{
	if (!rva004210B0(data)) {
		m_vec.push_back(data);
	}
}
