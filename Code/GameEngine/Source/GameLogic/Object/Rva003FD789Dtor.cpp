// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /GX
// ??1Rva003FD789@@UAE@XZ @0x003FD789 69B
// ModuleData dtor: AsciiStrings at +0x0C and +0x1C via releaseBuffer then Snapshot base vtable 0x00BBB554.
// Same recipe as PillageModuleDataDtor, using the shared Snapshot base header
// and an empty derived body.
// Unblocks ??_G at 0x003FD82D.
#include "Common/Snapshot.h"

#include "ascii_string.h"

class Rva003FD789 : public Snapshot
{
public:
	virtual ~Rva003FD789();
private:
	char m_pad04[8];
	AsciiString m_0c;
	char m_pad10[12];
	AsciiString m_1c;
};

Rva003FD789::~Rva003FD789()
{
}
