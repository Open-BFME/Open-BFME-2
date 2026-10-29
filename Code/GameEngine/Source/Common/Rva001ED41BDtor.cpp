// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// ??1Rva001ED41B@@UAE@XZ @0x001ED41B 91B: MI dtor with vector plus clear plus SubsystemInterface plus final g_00BBB554. Evidence: pin plus caller 0x001ED530 deleting dtor plus prev 0x001ED413 plus next 0x001ED476 plus callees 0x001ED363 0x000AD6F4 0x001B4E74.
#include <vector>
// Suppress this TU's non-retail copy of ??$_Destroy@PAVRva001ED0DE@@@_STL@@YAXPAVRva001ED0DE@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva001ED0DE;
namespace _STL { template <> void _Destroy<Rva001ED0DE *>(Rva001ED0DE *,Rva001ED0DE *); }

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
};
// Declared only: the rowed copy (StlportVectorDtorFamily.cpp, 0x001ED363) serves the call.
namespace _STL { template <> vector<Rva001ED0DE, allocator<Rva001ED0DE> >::~vector(); }
// This unit's own row: the single-element _Destroy the vector dtor used to pull in.
template void _STL::_Destroy<Rva001ED0DE>(Rva001ED0DE *);

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
	void clear();
};

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva001ED41B : public Snapshot, public SubsystemInterface
{
public:
	virtual ~Rva001ED41B();
private:
	Rva000AD6F4 m_10;
	_STL::vector<Rva001ED0DE> m_14;
};

Rva001ED41B::~Rva001ED41B()
{
}
