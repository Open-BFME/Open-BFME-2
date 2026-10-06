// cl: /Oy- /MD
// ?rva004D6C7C@Rva004D6C7C@@QAEXPBVObject@@@Z @0x004D6C7C (32B):
// Conditional ScienceType push_back via by-value getter: null-check arg,
// inline load of Science at +0x74 into eax, spill to dead arg slot [ebp+8],
// push its address into +0x04 vector via rowed push_back @0x002E01C6.
// Callers 0x002ACAE7 (Object* from findObjectByID) and 0x002ACC24 (vector
// element dereferenced at +0x74). Honest-address name.

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
	void push_back(const T &value);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class Object
{
public:
	__forceinline ScienceType getScience() const
	{
		return *(const ScienceType *)((const char *)this + 0x74);
	}

private:
	char m_pad[0x78];
};

class Rva004D6C7C
{
public:
	void rva004D6C7C(const Object *obj);

private:
	char m_pad04[4];
	_STL::vector<ScienceType> m_vec04;
};

void Rva004D6C7C::rva004D6C7C(const Object *obj)
{
	if (!obj)
		return;
	m_vec04.push_back(obj->getScience());
}
