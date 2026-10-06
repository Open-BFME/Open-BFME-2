// cl: /MD
// ?rva004213DB@Rva004210B0@@QAEXPBVModuleData@@@Z @0x004213DB 33B
// Add-if-absent over vector<ModuleData*> at +8: contains check via rowed
// 0x004210B0 then push_back via rowed 0x004DFCB0. Same this and same arg
// prove the Rva004210B0 owner. Evidence: unlock lane; callees rowed;
// caller at 0x00421568; unblocks 0x00421520.
class ModuleData;
namespace _STL
{
template <class T> class allocator
{
};
template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
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
