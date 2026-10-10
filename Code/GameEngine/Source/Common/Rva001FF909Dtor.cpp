// cl: /O1 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??1Rva001FF909@@UAE@XZ, retail 0x001FF909..0x001FF9E4 (219 bytes, EH):
// a subsystem's destructor (opaque pin of its scalar deleting destructor;
// table 0x00BE25B4). It ::deletes every non-null object of its first
// owned-pointer vector (+0x0C) and empties it, ::deletes every object of
// its second (+0x18) by index and empties it (both through the rowed
// vector<void *> range erase 0x0031BD55), then both vectors' storage goes
// to GameFree and the rowed SubsystemInterface destructor runs. Retail's
// unwind map: SubsystemInterface (state 0), the +0x0C and +0x18 vectors
// (states 1, 2) through the shared free-first-pointer body 0x0007FAB3.
// Owner and element identities are not established.
#include <vector>

void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template<> inline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) Rva00030830GameFree(_M_start); }
template<> vector<void *>::iterator vector<void *>::erase(iterator first, iterator last);
}

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	int m_04;
	int m_08;
};

class Rva001FF909Owned
{
public:
	virtual ~Rva001FF909Owned();
};

class Rva001FF909 : public SubsystemInterface
{
public:
	virtual ~Rva001FF909();
private:
	_STL::vector<void *> m_first;		// +0x0C
	_STL::vector<void *> m_second;		// +0x18
};

Rva001FF909::~Rva001FF909()
{
	for (_STL::vector<void *>::iterator it = m_first.begin(); it != m_first.end(); )
	{
		Rva001FF909Owned *owned = static_cast<Rva001FF909Owned *>(*it++);
		if (owned)
			::delete owned;
	}
	m_first.clear();
	for (unsigned int i = 0; i < m_second.size(); ++i)
		::delete static_cast<Rva001FF909Owned *>(m_second[i]);
	m_second.clear();
}
