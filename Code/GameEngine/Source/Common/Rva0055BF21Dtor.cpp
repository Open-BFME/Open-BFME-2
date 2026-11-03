// cl: /DNDEBUG /MD
//
// ??1Rva0055BF21@@UAE@XZ @0x003A972D (5B): the destructor of the class whose
// ctor 0x0055BF21 is rowed in DefaultModuleDerivedSmartCtors.cpp. Its vftable
// 0x00C1D638 slot 0 is the deleting dtor 0x003AEF18, the one the vftables of
// its siblings Rva0055B5BF (0x00C1D5E8) and Rva0055F98A (0x00C1D6C8) hold too,
// and that calls 0x003A972D: one unadjusted JMP to ~Rva003AEEB3 0x003A5817
// (the TailJumpWrappers5B.cpp shape: novtable over the base it jumps to).
// The three empty destructors are one folded body; owner identity unknown.
#include "../../Include/GameClient/Rva003AEEB3.h"

class __declspec(novtable) Rva0055BF21 : public Rva003AEEB3
{
public:
	virtual ~Rva0055BF21();
};

Rva0055BF21::~Rva0055BF21()
{
}
