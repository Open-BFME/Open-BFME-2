// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/RTS/ResourceGatheringManagerDestructor.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: ResourceGatheringManager::~ResourceGatheringManager 0x004F5BB0 (148B).
// Callee addresses are read off retail's call sites (reverse/symbols.csv).
// Only the placed bodies are carried; the donor's other definitions are
// omitted.
// Open-BFME5: ResourceGatheringManager's virtual destructor.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class ResourceGatheringManagerBase
{
public:
	virtual ~ResourceGatheringManagerBase() {}
};

class ResourceGatheringManager : public ResourceGatheringManagerBase
{
public:
	ResourceGatheringManager();
	virtual ~ResourceGatheringManager();
	virtual void slot1() = 0;
	virtual const char *name() const = 0;
	virtual void seed(void *) = 0;

private:
	_STL::list<int> m_supplyWarehouses;
	_STL::list<int> m_supplyCenters;
};

// ??1ResourceGatheringManager@@UAE@XZ
ResourceGatheringManager::~ResourceGatheringManager()
{
	m_supplyWarehouses.erase(m_supplyWarehouses.begin(), m_supplyWarehouses.end());
	m_supplyCenters.erase(m_supplyCenters.begin(), m_supplyCenters.end());
}

// ??0ResourceGatheringManager@@QAE@XZ, retail 0x004F5B63..0x004F5BAA (71
// bytes, EH): Zero Hour's empty constructor. The base is built first (EH
// state 0), the vtable 0x00C6327C stored, then both supply lists through the
// rowed list base constructor 0x004EC36C (state 1 between them). Its one
// caller, 0x002B0546, allocates the 12 bytes with the global operator new.
ResourceGatheringManager::ResourceGatheringManager()
{
}
