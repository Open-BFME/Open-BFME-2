// cl: /MD
// ?rva004D6BCD@Rva004D6BCD@@QBE_NPBVObject@@@Z @0x004D6BCD (35B):
// Linear search of the +0x04 ScienceType vector for the Science at arg+0x74.
// Retail loads target to edx, begin to eax, end to ecx, loops dword cmp,
// returns AL 1/0. Callers 0x00260F5D and 0x002AA1A1; unblocks 0x002AA191.
// Honest-address name.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Object
{
public:
	char m_pad[0x74];
	ScienceType m_science;
};

class Rva004D6BCD
{
public:
	bool rva004D6BCD(const Object *obj) const;

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec04;
};

bool Rva004D6BCD::rva004D6BCD(const Object *obj) const
{
	ScienceType target = obj->m_science;
	for (ScienceType *p = m_vec04.m_start; p != m_vec04.m_finish; ++p) {
		if (target == *p)
			return true;
	}
	return false;
}
