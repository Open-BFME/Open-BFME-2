// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// ?init@AwardSystemManager@@UAEXXZ @0x0040AA73 98B: AwardSystemManager::init
// (WorldBuilder name; the same Data\INI\AwardSystem.ini load), slot 1
// (SubsystemInterface::init) of the manager's vftable 0x00C392E0.
// Free AwardSystem INI loader via temp INI plus rowed ctor 0x2CDB0 plus
// StringBase ctor 0x37BA0 plus pinned loadFile 0x2DC75 plus rowed dtor
// 0x2CE5B when BfmeAwardSystemManagerInstance (0x00E02F78) set with literal Data\INI\AwardSystem.ini.
// Evidence: rowed INI ctor/dtor plus set plus vtable 0x008392E0 slot 1.
#include "ascii_string.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

struct FieldParse;
class INI
{
public:
	void initFromINI(void *,const FieldParse *);
	static void parseUnsignedInt(INI *,void *,void *,const void *);
	static void parseAsciiString(INI *,void *,void *,const void *);
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer); // 0x0002DC75 returns 1
	static void parseBool(INI *, void *, void *, const void *);
	char m_pad00[0x87C];
};

class AwardSystemManager
{
public:
	virtual void init();
};

// VA 0x00E02F78 is the instance pointer AwardSystemManager.cpp defines (its
// ctor stores `this` there); data row owner.
extern AwardSystemManager *BfmeAwardSystemManagerInstance;
void AwardSystemManager::init()
{
	if (BfmeAwardSystemManagerInstance == 0) {
		return;
	}
	INI ini;
	ini.loadFile("Data\\INI\\AwardSystem.ini", INI_LOAD_OVERWRITE, 0);
}
