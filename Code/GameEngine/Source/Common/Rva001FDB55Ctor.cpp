// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// ??0Rva001FDB55@@QAE@XZ @0x001FDB55 76B.
// PlayerTemplateStore (pinned ??0PlayerTemplateStore at this address; WorldBuilder
// names its slot 5 PlayerTemplateStore::attemptRefresh). Default ctor: base BFME2NativeNetwork via its inline ctor (which calls the
// rowed baseConstruct 0x001B4E63), vptr 0x007E1BB0, vector<BfmeE16> at +0xC
// via the rowed _Vector_base ctor 0x00211E58, set<AsciiString> at +0x18 via
// the rowed set ctor 0x000D3A71, and -1 at +0x24. Base layout (vptr + flag
// + value = 12B) from BFME2NativeNetworkBaseConstruct.cpp; element and
// member patterns from stlport_vector_e16_o1.cpp and
// stlport_asciistring_set_base.cpp. The base carries an empty virtual dtor
// with a _ReadWriteBarrier body: it keeps the base-destruction EH states
// retail arms (early state 0 plus state 1) while emitting no normal-path
// instruction (shape-lever guide prescription). Sole caller at 0x0022EA94.
#include <vector>
#include <set>

#include "ascii_string.h"

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

bool operator<(const AsciiString &, const AsciiString &);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// 0x001B4E63 is the rowed SubsystemInterface ctor.
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork();
	virtual ~BFME2NativeNetwork() { _ReadWriteBarrier(); }
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

// ??0BFME2NativeNetwork@@QAE@XZ present-unmatched
__forceinline BFME2NativeNetwork::BFME2NativeNetwork()
{
	reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface();
}

class PlayerTemplateStore : public BFME2NativeNetwork
{
public:
	PlayerTemplateStore();
	// Declared only: the destructor is rowed in Rva001FDB55Dtor.cpp, so this
	// unit must not emit its own (divergent) implicit copy for the vtable.
	virtual ~PlayerTemplateStore();
private:
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set;
	int m_state24;
};

PlayerTemplateStore::PlayerTemplateStore()
{
	m_state24 = -1;
}
