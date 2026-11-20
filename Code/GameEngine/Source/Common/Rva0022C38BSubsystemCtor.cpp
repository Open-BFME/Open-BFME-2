// cl: /O1 /G7 /arch:SSE /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme_stlport_int_dealloc_link
// stlport
//
// ??0Rva0022C38BSubsystem@@QAE@XZ retail 0x0022DE2E 33B, the subsystem
// GameEngine::init creates through initSubsystem<Rva0022C38BSubsystem>
// (pinned): the canonical subsystem base constructor, the derived vtable
// 0x007E7660, then an empty vector at +0xC through the ICF-shared
// _Vector_base constructor 0x00211E58. Retail builds it without an EH
// frame. The element type is unknown; int stands in for it (all element
// types share the one folded base constructor).
#include <vector>
#include "int_dealloc.h"


#include "subsystem_interface.h"

class Rva0022C38BSubsystem : public SubsystemInterface
{
public:
	Rva0022C38BSubsystem();
	virtual ~Rva0022C38BSubsystem();
private:
	_STL::vector<int> m_entries; // +0xC
};

Rva0022C38BSubsystem::Rva0022C38BSubsystem()
{
}

// The class's destructor: this unit's constructor row stores the vftable whose slot 0 is the
// deleting destructor at 0x022DE4F, and its body calls 0x00413A24, where the destructor row lives.
#pragma comment(linker, "/alternatename:??1Rva0022C38BSubsystem@@UAE@XZ=??1Rva00413A24@@UAE@XZ")
