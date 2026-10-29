// cl: /O1
// stlport46
// The two-argument ctor at 0x0040CB11 is rowed in Rva0040ECCF.cpp,
// whose caller already emits the byte-exact inline definition.
// Entry ctor for sorted vector: int key at +0, Holder value at +4 via copy ctor.
// Evidence: 1 caller at 0x0040ED06; callee copy ctor 0x004F6093 now rowed; shared 8-byte entry layout with twin getters and binary search.
#include <new.h>

// The holder copy at 0x004F6093 only copies its pointer and increments the
// pointee's reference count. Neither copy throws; stating that contract also
// keeps the header's placement delete from adding EH to _Construct (0x004F6A64).
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) throw();
};

class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(int key, const Rva004F6093Holder &val);
	Rva0040CB11Entry(const Rva0040CB11Entry &other) throw();
private:
	int m_first;
	Rva004F6093Holder m_second;
};

inline Rva0040CB11Entry::Rva0040CB11Entry(const Rva0040CB11Entry &other) throw() : m_first(other.m_first), m_second(other.m_second)
{
}

namespace _STL
{

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value)
{
	if (p)
		new (p) T1(value);
}

}

template void _STL::_Construct(Rva0040CB11Entry *, const Rva0040CB11Entry &);
