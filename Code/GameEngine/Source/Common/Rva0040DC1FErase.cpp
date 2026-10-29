// cl: /O1
// stlport46
// ?erase@?$vector@URva004F69C3@@V?$allocator@URva004F69C3@@@_STL@@@_STL@@QAEPAURva004F69C3@@PAU3@@Z, retail 0x0040DC1F, 55 bytes.
// Vector<Rva004F69C3> single erase via copy_ptrs twin at 0x0040D8FB and rowed
// dtor 0x004F69C3. Same 55B shape as ModuleInfo Nugget erase 0x0033C3BC.
// Callers at 0x0040DD86 0x0040DE08 0x0040DE93 0x0040DFEA.
struct Rva004F69C3
{
	int m_00;
	void *m_04;
	~Rva004F69C3();
};

namespace _STL
{

struct __false_type
{
};

template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	typedef T *iterator;
	iterator erase(iterator position);
	iterator end() { return m_finish; }
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class I, class O>
O __copy_ptrs(I first, I last, O result, const __false_type &tag);

}

inline _STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> >::iterator
_STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> >::erase(iterator position)
{
	_STL::__false_type tag;
	if (position + 1 != end())
		__copy_ptrs(position + 1, m_finish, position, tag);
	--m_finish;
	m_finish->~Rva004F69C3();
	return position;
}

template _STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> >::iterator _STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> >::erase(_STL::vector<Rva004F69C3, _STL::allocator<Rva004F69C3> >::iterator);

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??$__copy_ptrs@PAURva004F69C3@@PAU1@@_STL@@YAPAURva004F69C3@@PAU1@00ABU__false_type@0@@Z=??$__copy_ptrs@PAVRva0040D0A4Entry@@PAV1@@_STL@@YAPAVRva0040D0A4Entry@@PAV1@00U__false_type@0@@Z")
