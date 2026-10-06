// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// ?Rva0040AA73Load@@YGXXZ @0x0040AA73 98B
// Free AwardSystem INI loader via temp INI plus rowed ctor 0x2CDB0 plus
// StringBase ctor 0x37BA0 plus pinned loadFile 0x2DC75 plus rowed dtor
// 0x2CE5B when g_00E02F78 set with literal Data\INI\AwardSystem.ini.
// Evidence: rowed INI ctor/dtor plus set plus vtable 0x008392E0 slot 1.
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
	INI();
	~INI();
	void loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);
private:
	char m_pad[0x87C];
};

extern int g_00E02F78;
// g_00E02F78: matched references place it at VA 0xe02f78 (zero-filled .bss).
int g_00E02F78;

void __stdcall Rva0040AA73Load()
{
	if (g_00E02F78 == 0) {
		return;
	}
	INI ini;
	ini.loadFile("Data\\INI\\AwardSystem.ini", INI_LOAD_OVERWRITE, 0);
}
