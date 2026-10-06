// cl: /MD
// ?rva003B0433@Rva003B0433@@QAEXAAPBVModuleData@@@Z @0x003B0433 33B
// Unlock lane: push ModuleData ref to vector then push_heap int range with greater.
// Evidence: callees push_back 0x004DFCB0 row ModuleFactory and push_heap 0x003B02B8 row stlport; callers 0x003B0454 and 0x003B07B8 slot 10 of 0x0081DA10 class Rva003B0401; prev ModuleNameGetters2 next OpaqueSingleInheritanceDtors same dir.
class ModuleData;

namespace _STL {
template <class T> class allocator;
template <class T, class Alloc> class vector
{
public:
	void push_back(const T &x);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T> struct greater
{
};
template <class It, class Comp> void push_heap(It first, It last, Comp comp);
}

class Rva003B0433
{
public:
	void rva003B0433(const ModuleData *&m);
private:
	_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > m_vec;
	_STL::greater<int> m_comp;
};

void Rva003B0433::rva003B0433(const ModuleData *&m)
{
	m_vec.push_back(m);
	_STL::push_heap((int *)m_vec._M_start, (int *)m_vec._M_finish, m_comp);
}
