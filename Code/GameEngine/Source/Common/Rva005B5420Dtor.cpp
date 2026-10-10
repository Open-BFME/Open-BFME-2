// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc /arch:SSE /G7
// stlport
// ??1Rva005B5420@@UAE@XZ @0x005B5420 101B.
// Virtual dtor closing CahClass InitGadgets and destroying map at +0x1C.
// Evidence: leaf lane plus caller deleting dtor 0x005B576E; vtables
// 0x00873450/0x00872B74; literal CahClass::InitGadgets; close row plus
// StringBase ctor plus releaseBuffer plus rb-tree dtor rows.
#include "ascii_string.h"
#include <map>

typedef int Int;

struct Rva0040A603Record { char bytes[1]; };

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
	_STL::map<Int, Rva0040A603Record> m_map1C;
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
