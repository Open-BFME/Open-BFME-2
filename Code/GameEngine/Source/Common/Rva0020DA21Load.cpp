// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// ?Rva0020DA21Load@@YGXPAVINI@@@Z @0x0020DA21 40B: free __stdcall INI loader for
// LargeGroupAudio. Evidence: rowed StringBase ctor 0x00037BA0 with literal
// Data\INI\LargeGroupAudio.ini pinned INI::loadFile 0x0002DC75; caller 0x0020DA49 plus 0x0020DB09.
template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);	// 0x0002DC75 returns 1
	char m_pad00[8];
	INILoadType m_08;
};

void __stdcall Rva0020DA21Load(INI *ini)
{
	ini->loadFile("Data\\INI\\LargeGroupAudio.ini", ini->m_08, 0);
}
