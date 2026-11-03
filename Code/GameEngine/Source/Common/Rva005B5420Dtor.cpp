// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc /arch:SSE /G7
// stlport
// ??1Rva005B5420@@UAE@XZ @0x005B5420 101B.
// Virtual dtor closing CahClass InitGadgets and destroying the owned pointer list at +0x1C.
// Evidence: leaf lane plus caller deleting dtor 0x005B576E; vtables
// 0x00873450/0x00872B74; literal CahClass::InitGadgets; close row plus
// StringBase ctor plus releaseBuffer plus owning pointer-list dtor rows.
#include "ascii_string.h"
#include <stdlib.h>
// The native member cleanup calls 0x0040A603, whose complete body and EH
// graph establish the owning pointer-list type in 0CreateAHeroManager21FE49.
// The earlier tree spelling was only a donor guess: its clear pin targets
// the pointer-list clear body 0x0040A59B, not a tree operation.
class CreateAHeroData;
#include "../../Include/Common/Rva0040A3F9.h"
class Rva0040A530 : public Rva0040A3F9
{
public:
    Rva0040A530(bool flag);
    __declspec(noinline) ~Rva0040A530();
};

void _bfme_closeAptScreen(const AsciiString &s);

class Rva005B5420Base
{
public:
	virtual ~Rva005B5420Base() {}
};

class Rva005B5420 : public Rva005B5420Base
{
public:
	virtual ~Rva005B5420();
	void rva005B5418(const char *unused);
private:
	char m_pad04[0x1C - 4];
	Rva0040A530 m_ownedList1C;
};

Rva005B5420::~Rva005B5420()
{
	AsciiString s("CahClass::InitGadgets");
	_bfme_closeAptScreen(s);
}

void Rva00513866();
// Native5B5418..5B5420; registered by the Class page as Exit. The
// callback argument and receiver are unused; the shared close helper is
// called and the callback pops its one pointer argument.
void Rva005B5420::rva005B5418(const char *unused)
{
    Rva00513866();
}
