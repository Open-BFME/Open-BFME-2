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

class ResourceGatheringManagerBase
{
public:
	virtual ~ResourceGatheringManagerBase() {}
};

class ResourceGatheringManager : public ResourceGatheringManagerBase
{
public:
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
