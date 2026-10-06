// cl: /MD
// ?rva0059E390@Rva0059E390@@QAEXPBVModuleData@@@Z @0x0059E390 23B: guarded ModuleData vector append at +4.
// Evidence: rowed vector push_back 0x004DFCB0; caller 0x0059E46F in Rva0059E436Parse; pin ?rva0059E390@Rva0059E390@@QAEXPBVModuleData@@@Z.
class ModuleData;

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector
{
public:
	void push_back(const T &);
private:
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};
}

class Rva0059E390
{
public:
	void rva0059E390(const ModuleData *p);
private:
	char m_pad00[4];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec04;
};

void Rva0059E390::rva0059E390(const ModuleData *p)
{
	if (p)
		m_vec04.push_back(p);
}
