// cl: /MD
// ?rva0059E3A7@Rva0059E3A7@@QAEXPBVModuleData@@@Z @0x0059E3A7 23B: guarded ModuleData vector append at +0x10.
// Evidence: rowed vector push_back 0x004DFCB0; caller 0x0059E54A in Rva0059E511Parse; pin ?rva0059E3A7@Rva0059E3A7@@QAEXPBVModuleData@@@Z.
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

class Rva0059E3A7
{
public:
	void rva0059E3A7(const ModuleData *p);
private:
	char m_pad00[16];
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec10;
};

void Rva0059E3A7::rva0059E3A7(const ModuleData *p)
{
	if (p)
		m_vec10.push_back(p);
}
